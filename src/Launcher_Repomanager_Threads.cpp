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
	
	cout << "DEBUG:	Fetchprog Called.	Fetch: " << fetch_percent << "  double: " << fetch_percentAsDouble << "|	Index: " << fetch_index << " double: " << fetch_indexAsDouble << endl;

	((UnrealatedLauncherRepoManager*)payload)->threadComm_mutex_currentStage.lock();

	if(fetch_percent == 100){
		// Indexing in progress...
		temp_progressBarText = "Indexing... " + to_string(fetch_index) + "% completed.";
		
		((UnrealatedLauncherRepoManager*)payload)->threadComm_currentStage = 3;

		((UnrealatedLauncherRepoManager*)payload)->launcherRepoManager_setStatusFields(fetch_indexAsDouble, "Indexing", temp_progressBarText);
	} else{
		
		((UnrealatedLauncherRepoManager*)payload)->threadComm_currentStage = 2;
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
		ref_window->repoManager_closed();
		
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
	threadComm_currentStage = 1; // First step.
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

//	string temp_repoPathResolved = LauncherUtility::LauncherUtility_realPath(UnrealatedLauncherGlobal::launcherRepositoryDir);
//	cout << "DEBUG:	Repo Resolved Path: " << temp_repoPathResolved << endl;
//
	if(git_remote_create_anonymous(&repoManager_remoteRepo, repoManager_repo, repoManager_RepoURL) < 0 ){
		RepoManager_thread_taskFailed("Failed to create remote.", "Failed to create a remote.");
	}
	

	cout << "DEBUG:	Attempting clone." << endl;
	if(git_clone(&repoManager_repo, repoManager_RepoURL, UnrealatedLauncherGlobal::launcherRepositoryDir.c_str(), &repoManager_cloneOptions) < 0){
		RepoManager_thread_taskFailed("Failed to Clone the repository.", "Clone failed.");
		return;
	} // END - Git Clone
	
	
	threadComm_mutex_currentStage.lock();
	threadComm_currentTaskText = "Operation completed successfully!";
	threadComm_repoStatusText = "Repository Closed.";
	threadComm_currentStage = 0; // Finished.
	threadComm_mutex_currentStage.unlock();
	
	
	git_repository_free(repoManager_repo);
	if(git_libgit2_shutdown() < 0){
		cout << "WARN:	Libgit2 failed to shutdown after operation." << endl << "GITERR:	" << giterr_last()->message << endl;
	}
	

} // END - Thread - Get New.

void UnrealatedLauncherRepoManager::RepoManager_thread_GenerateLists(){
	
}

void UnrealatedLauncherRepoManager::RepoManager_thread_update(){
	
}

void UnrealatedLauncherRepoManager::RepoManager_thread_updateAll(){
	
}

void UnrealatedLauncherRepoManager::RepoManager_thread_clearRepo(){
	struct stat v_statBuff;

	threadComm_mutex_currentStage.lock();
	threadComm_currentTaskText = "Removing Repository Files.";
	threadComm_currentStage = 1;
	threadComm_currentTaskProgress = 0;
	threadComm_mutex_currentStage.unlock();
	
	// Check if directory exists.
	if(stat(UnrealatedLauncherGlobal::launcherRepositoryDir.c_str(), &v_statBuff) == 0 && S_ISDIR(v_statBuff.st_mode)){
		clearRepo_calledCount = 0;
		RepoManager_thread_clearRepoPath(UnrealatedLauncherGlobal::launcherRepositoryDir);
//		cout << "DEBUG:	Setting current task to 0." << endl;
		
	}else{ // END If folder exists on disk.
		cout << "DEBUG:	Folder doesn't exist. Setting current task to 0." << endl;
	threadComm_mutex_currentStage.lock();
		threadComm_currentStage = 0;
	threadComm_mutex_currentStage.unlock();
	}
}

void UnrealatedLauncherRepoManager::RepoManager_thread_clearRepoPath(string p_path){
	clearRepo_calledCount++;
	
		threadComm_mutex_currentStage.lock();
		threadComm_currentStage = 1;
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
		
		threadComm_mutex_currentStage.lock();
		launcherRepoManager_setStatusFields(0, "Removing Repository Files.", v_filePath);
		threadComm_mutex_currentStage.unlock();
		
		std::remove(v_filePath);
	} // END - While loop.
			
	closedir(directory);
	std::remove(p_path.c_str());
	
	clearRepo_calledCount--;
	
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
		threadComm_currentStage = 0;
		threadComm_currentTaskProgress = 0;
		threadComm_currentTaskProgressText = "";
		threadComm_currentTaskText = p_status;
	threadComm_mutex_currentStage.unlock();
	
	// Shutdown Libgit 2.
	git_libgit2_shutdown();

} // END - Task Failed.