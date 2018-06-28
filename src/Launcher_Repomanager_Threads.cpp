#include <headers/UnrealatedLauncherWindow.h>	// Repo Manager.
#include <headers/LauncherUtility.h>

#include <headers/external/git2.h>
#include <headers/external/git2/sys/transport.h>
#include <headers/external/git2/sys/openssl.h>
#include <headers/external/git2/cred_helpers.h>

using namespace UnrealatedLauncher;

// CALLBACKS:
int repoManager_fetchProgress(const git_transfer_progress *stats, void *payload){
	int fetch_percent = (100 * stats->received_objects) / stats->total_objects;
	double fetch_percentAsDouble = double(stats->received_objects) / stats->total_objects;
	
	int fetch_index = (100 * stats->indexed_objects) / stats->total_objects;
	double fetch_indexAsDouble = double(stats->indexed_objects) / stats->total_objects;
		
	Glib::ustring temp_progressBarText = "";
	
//	cout << "DEBUG:	Fetchprog Called.	Fetch: " << fetch_percent << "  double: " << fetch_percentAsDouble << "|	Index: " << fetch_index << " double: " << fetch_indexAsDouble << endl;

	((UnrealatedLauncherRepoManager*)payload)->threadComm_mutex_currentStage.lock();

	if(fetch_percent == 100){
		// Indexing in progress...
		temp_progressBarText = "Indexing... " + to_string(fetch_index) + "% completed.";
		
		// Increment task counter if not already:
		if( ! ((UnrealatedLauncherRepoManager*)payload)->threadComm_fetchProg_indexTaskAdded ){
			((UnrealatedLauncherRepoManager*)payload)->threadComm_currentStage++;
			((UnrealatedLauncherRepoManager*)payload)->threadComm_fetchProg_indexTaskAdded = true;
		} // END - Stage Checker.

		((UnrealatedLauncherRepoManager*)payload)->launcherRepoManager_setStatusFields(fetch_indexAsDouble, "Indexing", temp_progressBarText);

	} else{		// Fetch Progress is not 100% (Downloading)

		// Increment task counter if not already:
		if( ! ((UnrealatedLauncherRepoManager*)payload)->threadComm_fetchProg_fetchTaskAdded ){
			((UnrealatedLauncherRepoManager*)payload)->threadComm_currentStage++;
			((UnrealatedLauncherRepoManager*)payload)->threadComm_fetchProg_fetchTaskAdded = true;
		} // END - Stage Checker.
		
//		((UnrealatedLauncherRepoManager*)payload)->threadComm_currentStage++;
		// Cloning in progress...
		temp_progressBarText = "Downloading... " + to_string(fetch_percent) + "% completed.";

		((UnrealatedLauncherRepoManager*)payload)->launcherRepoManager_setStatusFields(fetch_percentAsDouble, "Fetching (Cloning)", temp_progressBarText);
	}
	((UnrealatedLauncherRepoManager*)payload)->threadComm_mutex_currentStage.unlock();
	
	return 0;
} // END - Fetch progress for UpdateLocalRepo.

int repoManager_gitCredentialCallback(git_cred **output, const char *url, const char *username_from_url, unsigned int allowed_types, void *payload){
	cout << "DEBUG:	Credentials Called" << endl
		<<	"		> URL:			" << &url << endl
		<<	"		> Username:		" << &username_from_url << endl
		<< 	"		> AllowedTypes: " << allowed_types << endl;

/* SSH KEY TEST STUFF:
	string temp_publicKey = UnrealatedLauncherGlobal::launcherHomeDir + "/id_rsa.pub";
	string temp_privateKey = UnrealatedLauncherGlobal::launcherHomeDir + "/id_rsa";
	
	cout << "DEBUG:	Public Key: " << temp_publicKey << endl << "DEBUG:	Private key: " << temp_privateKey << endl;

//	error = git_cred_ssh_key_from_agent(out, username_from_url);
	return git_cred_ssh_key_new( output, username_from_url, temp_publicKey.c_str(), temp_privateKey.c_str(), "" );
*/

		cout << "DEBUG:	Repo Manager remember login: " << UnrealatedLauncherGlobal::repoManagerRememberLogin << endl;
		if(UnrealatedLauncherGlobal::repoManagerRememberLogin && !((UnrealatedLauncherRepoManager*)payload)->threadComm_attemptedLoginWithSavedInfo){
			// Try saved login first.
			cout << "DEBUG:	Attempting existing login first." << endl;
			((UnrealatedLauncherRepoManager*)payload)->threadComm_attemptedLoginWithSavedInfo = true;
			// Create local copies for convenience.
			string temp_username = ((UnrealatedLauncherRepoManager*)payload)->threadComm_username;
			string temp_password = ((UnrealatedLauncherRepoManager*)payload)->threadComm_password;
			return git_cred_userpass_plaintext_new( output, temp_username.c_str(), temp_password.c_str());
		}else{
			std::unique_lock<std::mutex>threadLock( ((UnrealatedLauncherRepoManager*)payload)->threadComm_mutex_currentStage );
			((UnrealatedLauncherRepoManager*)payload)->threadComm_loginPrompt = true;
			((UnrealatedLauncherRepoManager*)payload)->threadComm_loginPrompt_conditionVar.wait(threadLock);
			
			// Create local copies for convenience.
			string temp_username = ((UnrealatedLauncherRepoManager*)payload)->threadComm_username;
			string temp_password = ((UnrealatedLauncherRepoManager*)payload)->threadComm_password;

			return git_cred_userpass_plaintext_new( output, temp_username.c_str(), temp_password.c_str());
		} // END - ELSE.
} // END - Credential Callback

int repoManager_gitRemoteCallback(git_remote **remoterepo, git_repository *repo, const char *repoName, const char *repoURL, void *payload){
	cout << "DEBUG:	RemoteCallback called." << endl
		<< "		> Remote:	" << remoterepo << endl
		<< "		> Repo:		" << repo << endl 
		<< "		> RepoName:	" << repoName << endl 
		<< "		> URL:		" << repoURL << endl << endl;
	return 	git_remote_create(remoterepo, repo, repoName, repoURL );
}

int repoManager_gitTransport(git_transport **output, git_remote *remoteRepo, void *payload){
	cout << "DEBUG:	Transport Callback called." << endl
		<< "		> Output: 		" << output << endl 
		<< "		> Remote: 		" << remoteRepo << endl
		<< "		> Parameters:	" << payload << endl << endl;
	
	return git_transport_smart(output, remoteRepo, payload);
}// END - GitTransport

int RepoManager_ForEachTag_populateList(const char *name, git_oid *oid, void *payload){
	((UnrealatedLauncherRepoManager*)payload)->repoManager_objectIDsOfTags.push_back( git_oid_tostr_s(oid) );
	((UnrealatedLauncherRepoManager*)payload)->repoManager_objectSummaryOfTags.push_back( name );
	
	return 0;
} // ForEachTag - Populate 

int repoManager_forEachFetchHead(git_repository *repo, git_repository_fetchhead_foreach_cb callback, void *payload){
	
}

void repoManager_checkoutProgress(const char *path, size_t completed_steps, size_t total_steps, void *payload){
	cout << "Checkout Progress Called!" << endl << "		> Completed Steps: " << completed_steps << " of " << total_steps << endl;

	if(total_steps > 0){
		int v_checkoutPercent = (100 * completed_steps) / total_steps;
		double v_checkoutPercentAsDouble = double(completed_steps) / total_steps;
		Glib::ustring temp_progressBarText = "Downloading... " + to_string(v_checkoutPercent) + "% completed.";
		((UnrealatedLauncherRepoManager*)payload)->launcherRepoManager_setStatusFields(v_checkoutPercentAsDouble, "Merging (Checkout)", temp_progressBarText);
	} // END - If steps is higher than 0.
	else{
		((UnrealatedLauncherRepoManager*)payload)->launcherRepoManager_setStatusFields(0, "Merge Complete", "");
	}
} // END - Checkout Progress.


// NORMAL SHIT:

void UnrealatedLauncherRepoManager::RepoManager_timeout_updateGUI(){// updates all GUI items within Status.
	// Set Level bar (current stage).
	v_status_levelBar.set_value(threadComm_currentStage);
	
	// Set Progress Bar.
	v_status_progressBar.set_text(threadComm_currentTaskProgressText);
	if(threadComm_currentTaskProgress == 0){
		v_status_progressBar.pulse();
	}else{
		v_status_progressBar.set_fraction(threadComm_currentTaskProgress);
	}
	
	// Set Text/Labels:
	txt_status_currentTask.set_text(threadComm_currentTaskText);
	
	
// Set main window progress bar (shown when manager is hidden)
	if(ref_window->repoManager_getRevealed()){ // Manager is visible:
		ref_window->repoManager_setWindowProgressBarVisible(false);
	} else{ // Manager is hidden:
		ref_window->repoManager_setWindowProgressBarVisible(true);
		if(threadComm_currentTaskProgress == 0){
			ref_window->repoManager_updateWindowProgressBar(-1);
		}else{
			ref_window->repoManager_updateWindowProgressBar(threadComm_currentTaskProgress);
		} // END - If task progress/else.
	} // END - Else: manager is hidden
	
} // END - UpdateGUI

bool UnrealatedLauncherRepoManager::RepoManager_timeout(){	// Main Timeout function.
	threadComm_mutex_currentStage.lock();
 //DEBUG
/*
	cout << "DEBUG:	Timeout." << endl
		<< "		> CurrentStage: " << threadComm_currentStage << endl 
		<< "		> Current Task: " << threadComm_currentTaskText << endl
		<< "		> Current Prog: " << threadComm_currentTaskProgress * 100 << "%" << endl 
		<< "		> Task Details: " << threadComm_currentTaskProgressText << endl;
*/
	int temp_currentStage = threadComm_currentStage; // Local copy of variable to prevent mutex mess:
	RepoManager_timeout_updateGUI();

	threadComm_mutex_currentStage.unlock();
	
	if(threadComm_loginPrompt){
		threadComm_attemptedLoginWithSavedInfo = false;
		txt_login_status.set_text("Incorrect username/password! Try again.");
		v_login_revealer.set_reveal_child(true);
		btn_login_logout.hide();
		ref_window->repoManager_open();
		txt_status_currentTask.set_text("Waiting for login...");
	}
	
	if(temp_currentStage == 0){ 
		// Online task is finished.
		cout << "DEBUG:	" << "RepoManager_timeout current stage is 0." << endl;
		
		threadComm_onlineTaskBusy = false;
		repoManager_manageButtons_frame.set_sensitive(true);
		v_status_progressBar.set_fraction(0);
		v_status_progressBar.set_text("");
		ref_window->repoManager_setWindowProgressBarVisible(false);
//		ref_window->repoManager_closed();
		
	} // END - If current stage is 0.
	return temp_currentStage;
	
} // END - Repo Manager Timeout.

void UnrealatedLauncherRepoManager::launcherRepoManager_setStatusFields(double p_progressPercent, string p_task, string p_taskProgress){	// Updates the status elements.
	threadComm_currentTaskText = p_task;
	threadComm_currentTaskProgressText = p_taskProgress;
	threadComm_currentTaskProgress = p_progressPercent;
}

// THREAD FUNCTIONS:

void UnrealatedLauncherRepoManager::RepoManager_thread_GetNew(){
	cout << endl << endl << "...................................GET NEW" << endl;
	cout << "GET NEW:	Initialising Libgit2..." << endl;
		
	threadComm_mutex_currentStage.lock();
	threadComm_attemptedLoginWithSavedInfo = false;
	++threadComm_currentStage; // First step.
	threadComm_currentTaskText = "Initialising Libgit2.";
	threadComm_mutex_currentStage.unlock();

	if(git_libgit2_init() < 0){
		RepoManager_thread_taskFailed("Failed to initialise Libgit2.", "Libgit2 Failed to initialise.");
		return;
	}// END - Libgit2 Init.
		cout << "		> Libgit2 Initialised." << endl; 
	
	
// SET GIT OPTIONS:
	git_clone_options repoManager_cloneOptions = GIT_CLONE_OPTIONS_INIT;
	repoManager_cloneOptions.fetch_opts.callbacks.credentials = repoManager_gitCredentialCallback;
	repoManager_cloneOptions.fetch_opts.callbacks.transfer_progress = repoManager_fetchProgress;
	repoManager_cloneOptions.fetch_opts.callbacks.payload = this;
	repoManager_cloneOptions.fetch_opts.download_tags = GIT_REMOTE_DOWNLOAD_TAGS_ALL;

	// Used to increment the task counter once in a function that's called repeatedly.
	threadComm_fetchProg_indexTaskAdded = false;
	threadComm_fetchProg_fetchTaskAdded = false;
//	string temp_repoPathResolved = LauncherUtility::LauncherUtility_realPath(UnrealatedLauncherGlobal::launcherRepositoryDir);
//	cout << "DEBUG:	Repo Resolved Path: " << temp_repoPathResolved << endl;

	if(git_remote_create_anonymous(&repoManager_remoteRepo, repoManager_repo, repoManager_RepoURL) < 0 ){
		RepoManager_thread_taskFailed("Failed to create remote.", "Failed to create a remote.");
	}

	threadComm_mutex_currentStage.lock();
	launcherRepoManager_setStatusFields(0, "Attempting Clone.", "");
	threadComm_mutex_currentStage.unlock();

	cout << "DEBUG:	Attempting clone." << endl;
	if(git_clone(&repoManager_repo, repoManager_RepoURL, UnrealatedLauncherGlobal::launcherRepositoryDir.c_str(), &repoManager_cloneOptions) < 0){
		RepoManager_thread_taskFailed("Failed to Clone the repository.", "Clone failed.");
		return;
	} // END - Git Clone
	
	
	threadComm_mutex_currentStage.lock();
	threadComm_currentTaskText = "Operation completed successfully!";
	threadComm_repoStatusText = "Repository Closed.";
	if(threadComm_multiStageTask){
		++threadComm_currentStage;
	} else{
		threadComm_currentStage = 0;
	}
	threadComm_mutex_currentStage.unlock();
	
	
	git_repository_free(repoManager_repo);
	if(git_libgit2_shutdown() < 0){
		cout << "WARN:	Libgit2 failed to shutdown after operation." << endl << "GITERR:	" << giterr_last()->message << endl;
	}
	

} // END - Thread - Get New.

void UnrealatedLauncherRepoManager::RepoManager_thread_GenerateLists(){
	cout << endl << endl << "...................................GENERATE LISTS" << endl;
	cout << "Initialising Libgit2..." << endl;
	
	threadComm_mutex_currentStage.lock();
	++threadComm_currentStage; // First step.
	threadComm_currentTaskText = "Initialising Libgit2.";
	threadComm_attemptedLoginWithSavedInfo = false;
	threadComm_mutex_currentStage.unlock();

	if(git_libgit2_init() < 0){
		RepoManager_thread_taskFailed("Failed to initialise Libgit2.", "Libgit2 Failed to initialise.");
		return;
	}// END - Libgit2 Init.
		cout << "		> Libgit2 Initialised." << endl; 
	
	threadComm_mutex_currentStage.lock();
	launcherRepoManager_setStatusFields(0, "Generating Lists.", "");
	threadComm_mutex_currentStage.unlock();
	
	if(!RepoManagerGit_OpenRepo()){
		RepoManager_thread_taskFailed("Failed to open repository!", "Failed to open repository.");
		return;
	}

	int			totalFiles = 0;	// The total number of files to be generated.
	git_revwalk *repo_revWalker = nullptr;


	if(git_revwalk_new(&repo_revWalker, repoManager_repo) < 0){
		RepoManager_thread_taskFailed("Failed to generate lists.", "Failed to create revision Walker.");
	}

	git_oid objectID;
	
	cout << "DEBUG:	Tags:" << endl;

	if( git_tag_foreach(repoManager_repo, RepoManager_ForEachTag_populateList, this) < 0 ){
		RepoManager_thread_taskFailed("Failed to get list of tags.", "Failed to get list of tags");
	}

	cout << "DEBUG:	Starting revision walk..." << endl;

// Populate TAGGED list:
	string temp_taggedListFileDir = UnrealatedLauncherGlobal::launcherHomeDir + "/lists/";
	string temp_taggedListFile = temp_taggedListFileDir + "tags.txt";
//	system("mkdir -p" + temp_taggedListFileDir.c_str() + "" );
	mkdir(temp_taggedListFileDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	
	ofstream temp_taggedListOutputStream( temp_taggedListFile.c_str() ); // Open file.

	for ( unsigned int index = 0; index < repoManager_objectSummaryOfTags.size() ; index++){
//		cout << "		> " << repoManager_objectSummaryOfTags[index] << endl;
		temp_taggedListOutputStream << repoManager_objectIDsOfTags[index] << endl << repoManager_objectSummaryOfTags[index] << endl;
	} // END - For Loop.

	temp_taggedListOutputStream.close(); 		// Close File.

	// Get total number of files to create:
	totalFiles = repoManager_objectIDsOfTags.size() + 1; // Add one for final "all" list file.
	float processedFiles = 0; // Count of processed files.  Used to update Level bar.

	// Revwalk from tag point.
	for(string& nameArray: repoManager_objectSummaryOfTags){
		++processedFiles; // Increment counter.

		string temp_filename = nameArray.erase(0, 10);
		string temp_tagListFile = temp_taggedListFileDir + temp_filename + ".txt";
		string temp_searchQuery = "*/" + temp_filename;
		ofstream temp_outputStream_singleTag( temp_tagListFile.c_str() );
		git_revwalk *tag_revwalker = nullptr;

		threadComm_mutex_currentStage.lock();
		threadComm_currentTaskProgress = processedFiles / totalFiles;
		threadComm_currentTaskProgressText = temp_filename;
		threadComm_mutex_currentStage.unlock();

		if(git_revwalk_new(&tag_revwalker, repoManager_repo) < 0){
			RepoManager_thread_taskFailed("Failed to generate lists.", "Failed to create revision Walker.");
		} // END - New Revwalker.

		if(git_revwalk_push_glob(tag_revwalker, temp_searchQuery.c_str() ) < 0 ){
			cout << "Failed to push glob for tag: " << temp_searchQuery << endl;
			return;
		} // END - Failed to push glob.

		git_revwalk_sorting(tag_revwalker, GIT_SORT_TOPOLOGICAL);

		while( !git_revwalk_next(&objectID, tag_revwalker) ){
			git_commit *temp_commit = nullptr;
			git_commit_lookup(&temp_commit, repoManager_repo, &objectID);
			temp_outputStream_singleTag << git_oid_tostr_s(&objectID) << endl << git_commit_summary(temp_commit) << endl;
			git_commit_free(temp_commit);
		} // END - While loop.
		temp_outputStream_singleTag.close();	// Close the file.
		
		
	} // END - For Loop.


// Populate "ALL" list:
	if(git_revwalk_push_head(repo_revWalker) < 0){
		RepoManager_thread_taskFailed("Failed to push head.", "Failed to push HEAD to revision walker.");
		return;
	}

	++processedFiles;
	threadComm_mutex_currentStage.lock();
	threadComm_currentTaskProgress = processedFiles / totalFiles;
//	threadComm_currentTaskProgressText = temp_filename;
	threadComm_attemptedLoginWithSavedInfo = false;
	threadComm_mutex_currentStage.unlock();

		string temp_tagListFile = temp_taggedListFileDir + "all.txt";
		ofstream temp_outputStream_listAll( temp_tagListFile.c_str() );

	while( !git_revwalk_next(&objectID, repo_revWalker) ){
		git_commit *temp_commit = nullptr;
		git_commit_lookup(&temp_commit, repoManager_repo, &objectID);

		temp_outputStream_listAll << git_oid_tostr_s(&objectID) << endl << git_commit_summary(temp_commit) << endl;
		
		threadComm_mutex_currentStage.lock();
		threadComm_currentTaskProgress = 0;
		threadComm_currentTaskProgressText = git_commit_summary(temp_commit);
		threadComm_mutex_currentStage.unlock();

		git_commit_free(temp_commit);
	} // END - While loop.
	
	temp_outputStream_listAll.close();
	
	cout << "		> Revision Walk Finished." << endl;
	
	threadComm_mutex_currentStage.lock();
	threadComm_currentTaskText = "Lists Generated Successfully.";
	
	if(threadComm_multiStageTask){
		++threadComm_currentStage;
	} else{
		threadComm_currentStage = 0;
	}
	
	threadComm_mutex_currentStage.unlock();
} // END - Generate Lists.

void UnrealatedLauncherRepoManager::RepoManager_thread_update(){
	cout << endl << endl << "...................................UPDATE" << endl;
	cout << "GET NEW:	Initialising Libgit2..." << endl;
	
	threadComm_mutex_currentStage.lock();
	++threadComm_currentStage; // First step.
	threadComm_currentTaskText = "Initialising Libgit2.";
	threadComm_attemptedLoginWithSavedInfo = false;
	threadComm_mutex_currentStage.unlock();

	if(git_libgit2_init() < 0){
		RepoManager_thread_taskFailed("Failed to initialise Libgit2.", "Libgit2 Failed to initialise.");
		return;
	}// END - Libgit2 Init.
		cout << "		> Libgit2 Initialised." << endl; 
	
	
	threadComm_mutex_currentStage.lock();
	threadComm_currentTaskText = "Attempting Fetch...";
	threadComm_mutex_currentStage.unlock();
	
	if(git_repository_open(&repoManager_repo, UnrealatedLauncherGlobal::launcherRepositoryDir.c_str()) < 0 ){
		RepoManager_thread_taskFailed("Failed to open local repo.  Make sure it exists!", "Failed to open Local Repository. See Git Error:");
		return;
	}
	
	if(git_remote_create_anonymous(&repoManager_remoteRepo, repoManager_repo, repoManager_RepoURL) < 0 ){
		RepoManager_thread_taskFailed("Failed to create remote.", "Failed to create a remote.");
	}
	
	cout << "		>Remote Lookup Successful." << endl;
	
//	git_remote_set_url(repoManager_repo, "origin", repoManager_RepoURL);
	
	git_fetch_options temp_fetchOptions = GIT_FETCH_OPTIONS_INIT;
		temp_fetchOptions.callbacks.credentials = repoManager_gitCredentialCallback;
		temp_fetchOptions.callbacks.transfer_progress = repoManager_fetchProgress;
		temp_fetchOptions.callbacks.payload = this;
		temp_fetchOptions.download_tags = GIT_REMOTE_DOWNLOAD_TAGS_ALL;
	
	// Used to increment the task counter once in a function that's called repeatedly.
	threadComm_fetchProg_indexTaskAdded = false;
	threadComm_fetchProg_fetchTaskAdded = false;
	
	if(git_remote_fetch(repoManager_remoteRepo, NULL, &temp_fetchOptions, NULL) < 0 ){
		RepoManager_thread_taskFailed("Failed to fetch updates.", "Failed to fetch any changes!");
		return;
	}
	
	
	const git_remote_head **head = NULL;
	size_t headCount = 0;
	
	if(git_remote_ls(&head, &headCount, repoManager_remoteRepo) < 0){
		RepoManager_thread_taskFailed("Failed to lookup heads.", "Failed to look up remote heads. See Git Error.");
		return;
	}
	
	git_oid objectID = head[0]->oid;
	git_annotated_commit *mergeHead[1];
	
	if(git_annotated_commit_lookup(&mergeHead[0], repoManager_repo, &objectID) < 0){
		RepoManager_thread_taskFailed("Failed to lookup heads.", "Failed to look up remote heads. See Git Error.");
		return;
	}
	
	git_merge_options temp_mergeOptions = GIT_MERGE_OPTIONS_INIT;
	temp_mergeOptions.file_favor = GIT_MERGE_FILE_FAVOR_THEIRS;
	
	git_checkout_options temp_checkoutOptions = GIT_CHECKOUT_OPTIONS_INIT;
	temp_checkoutOptions.progress_cb = repoManager_checkoutProgress;
	temp_checkoutOptions.progress_payload = this;
	temp_checkoutOptions.checkout_strategy = GIT_CHECKOUT_USE_THEIRS;
	
/*
*/

	git_object *temp_object; // Object outside in order to survive for commit lookup (for summary).

	if(git_merge(repoManager_repo, (const git_annotated_commit **)(&mergeHead), 1, &temp_mergeOptions, &temp_checkoutOptions) < 0){
//		RepoManager_thread_taskFailed("Failed to Merge.", "Failed to merge changes.");
		cout << "DEBUG:	Failed to merge: " << giterr_last()->message << endl << "		> Attempting a reset instead." << endl;
		
		git_object_lookup(&temp_object, repoManager_repo, &objectID, GIT_OBJ_ANY);

		cout << "		> PERFORMING RESET." << endl;
		
		if( git_reset(repoManager_repo, temp_object, GIT_RESET_HARD, &temp_checkoutOptions) < 0 ){
			RepoManager_thread_taskFailed("Failed to Reset.", "Failed to reset to origin.");
			cout << "-----	SORRY, THIS FEATURE HASN'T BEEN IMPLEMENTED PROPERLY." << endl;
			return;
		}
	} // END - Merge / Reset.


	// Obtaining Commit Summary:
	git_commit *temp_commit = nullptr;
	git_commit_lookup(&temp_commit, repoManager_repo, &objectID);
	ref_window->launcher_updateSidebar_currentCommit(git_commit_summary(temp_commit));

	git_commit_free(temp_commit);
	git_object_free(temp_object);

	git_repository_free(repoManager_repo);

	if(git_libgit2_shutdown() < 0){
		cout << "WARN:	Libgit2 failed to shutdown after operation." << endl << "GITERR:	" << giterr_last()->message << endl;
	}
	
	threadComm_mutex_currentStage.lock();
	threadComm_currentStage = 0;
	threadComm_multiStageTask = false;
	threadComm_mutex_currentStage.unlock();
} // END - Update

void UnrealatedLauncherRepoManager::RepoManager_thread_updateAll(){
	cout << endl << endl << "...................................UPDATE ALL" << endl;

git_libgit2_init();
	if(git_repository_open(&repoManager_repo, UnrealatedLauncherGlobal::launcherRepositoryDir.c_str()) < 0 ){
		cout << "DEBUG:	Repo not found. Get New." << endl;
		RepoManager_thread_GetNew();
	} else{
		cout << "DEBUG:	Repo Opened. Update." << endl;
		RepoManager_thread_update();
	}
	
	RepoManager_thread_GenerateLists();
	
	threadComm_mutex_currentStage.lock();
	threadComm_currentStage = 0;
	threadComm_multiStageTask = false;
	threadComm_mutex_currentStage.unlock();
}

void UnrealatedLauncherRepoManager::RepoManager_thread_clearRepo(){
	struct stat v_statBuff;

	threadComm_mutex_currentStage.lock();
	threadComm_currentTaskText = "Removing Repository Files.";
	++threadComm_currentStage;
	threadComm_currentTaskProgress = 0;
	threadComm_mutex_currentStage.unlock();
	
	// Check if directory exists.
	if(stat(UnrealatedLauncherGlobal::launcherRepositoryDir.c_str(), &v_statBuff) == 0 && S_ISDIR(v_statBuff.st_mode)){
		clearRepo_filesTotal = 0;
		clearRepo_filesDeleted = 0;
		clearRepo_calledCount = 0;
		
		RepoManager_thread_clearRepo_count(UnrealatedLauncherGlobal::launcherRepositoryDir);
		
		threadComm_mutex_currentStage.lock();
		++threadComm_currentStage;
		threadComm_mutex_currentStage.unlock();

		RepoManager_thread_clearRepoPath(UnrealatedLauncherGlobal::launcherRepositoryDir);
//		cout << "DEBUG:	Setting current task to 0." << endl;
		
	}else{ // END If folder exists on disk.
		cout << "DEBUG:	Folder doesn't exist. Setting current task to 0." << endl;
	}
	
	string temp_directory = UnrealatedLauncherGlobal::launcherHomeDir + "/lists";
	if(stat(temp_directory.c_str(), &v_statBuff) == 0 && S_ISDIR(v_statBuff.st_mode)){
		RepoManager_thread_clearRepo_count(temp_directory);
		RepoManager_thread_clearRepoPath(temp_directory);
	}
	
	threadComm_mutex_currentStage.lock();
		threadComm_currentStage = 0;
	threadComm_mutex_currentStage.unlock();
}

void UnrealatedLauncherRepoManager::RepoManager_thread_clearRepo_count(string p_path){
	DIR *directory = opendir(p_path.c_str());
	struct dirent *next_file;
	char v_filePath[PATH_MAX];
	
	// COUNT Files:
	while ( (next_file = readdir(directory)) != NULL){

		if(strcmp(next_file->d_name, ".") && strcmp(next_file->d_name, "..")){
			sprintf(v_filePath, "%s/%s", p_path.c_str(), next_file->d_name);
			// If next file is a directory, call the same function with the new directory.

			if(next_file->d_type == DT_DIR){
				RepoManager_thread_clearRepo_count(v_filePath);
				cout << v_filePath << "\n";
			} // END - If.

		} // END - If Filename

		// Set next file, update the progress bar text, and increment the file count:
		sprintf(v_filePath, "%s/%s", p_path.c_str(), next_file->d_name);
		++clearRepo_filesTotal;

		threadComm_mutex_currentStage.lock();
		launcherRepoManager_setStatusFields(0, "Finding files for removal", next_file->d_name);
		threadComm_mutex_currentStage.unlock();
		
	} // END - While loop.
			
	closedir(directory);
}

void UnrealatedLauncherRepoManager::RepoManager_thread_clearRepoPath(string p_path){
	++clearRepo_calledCount;
	
		threadComm_mutex_currentStage.lock();
		threadComm_currentStage = 2;
		threadComm_mutex_currentStage.unlock();
	
	
	DIR *directory = opendir(p_path.c_str());
	struct dirent *next_file;
	char v_filePath[PATH_MAX];
		
	// Delete all files/dirs.
	while ( (next_file = readdir(directory)) != NULL){

		if(strcmp(next_file->d_name, ".") && strcmp(next_file->d_name, "..")){
			sprintf(v_filePath, "%s/%s", p_path.c_str(), next_file->d_name);
			// If next file is a directory, call the same function with the new directory.

			if(next_file->d_type == DT_DIR){
				RepoManager_thread_clearRepoPath(v_filePath);
				cout << v_filePath << "\n";
			} // END - If.

		} // END - If Filename

		// Set next file, update the progress bar text, and remove the file:
		sprintf(v_filePath, "%s/%s", p_path.c_str(), next_file->d_name);
		clearRepo_filesDeleted++;
		
		threadComm_mutex_currentStage.lock();
		double temp_progress = clearRepo_filesDeleted / clearRepo_filesTotal;
		launcherRepoManager_setStatusFields(temp_progress, "Removing Repository Files.", v_filePath);
		threadComm_mutex_currentStage.unlock();
		
		std::remove(v_filePath);
	} // END - While loop.
			
	closedir(directory);
	std::remove(p_path.c_str());
	
	--clearRepo_calledCount;
	
	if(clearRepo_calledCount == 0){
		cout << "DEBUG:	ClearRepo Call count is 0." << endl;
		threadComm_mutex_currentStage.lock();
		threadComm_currentTaskText = "Removal complete.";
		threadComm_currentStage = 0;
		threadComm_mutex_currentStage.unlock();
	}
	return;
}

// Thread utility functions:
void UnrealatedLauncherRepoManager::RepoManager_thread_taskFailed(string p_status, string p_consoleError){ 
	cerr << "TASK FAILED!	" << p_consoleError << endl << "GIT ERROR:	" << giterr_last()->message << endl;
	
	threadComm_mutex_currentStage.lock();
		threadComm_attemptedLoginWithSavedInfo = false;
		threadComm_currentStage = 0;
		threadComm_currentTaskProgress = 0;
		threadComm_currentTaskProgressText = "";
		threadComm_currentTaskText = p_status;
	threadComm_mutex_currentStage.unlock();
	
	// Shutdown Libgit 2.
	git_libgit2_shutdown();

} // END - Task Failed.