#include <headers/UnrealatedLauncherWindow.h>	// Repo Manager.
#include <headers/Launcher_RepoManagerGit.h>	// Global GIT functions.

using namespace UnrealatedLauncher;

bool UnrealatedLauncherRepoManager::RepoManagerGit_OpenRepo(){			// Opens the launcher repository.  Returns FALSE on error/doesn't exist.
	git_libgit2_init();
	int temp_error = git_repository_open(&repoManager_repo, UnrealatedLauncherGlobal::launcherRepositoryDir.c_str());
	git_libgit2_shutdown();
	if(temp_error < 0){
		std::cerr << "WARN:	Launcher Repository not found. | GitError: " << giterr_last()->message << std::endl;
		txt_status_repoStatus.set_text("Failed to Open repository.");
		return false;
	} else{
		std::cout << "	Launcher Repository opened!" << std::endl;
		txt_status_repoStatus.set_text("Launcher Repository Open.");
		return true;
	} // End Error Check.

} // Open Launcher Repository.

bool UnrealatedLauncherRepoManager::RepoManagerGit_OpenRemote(){
	int temp_error = git_remote_create_anonymous(&repoManager_remoteRepo, repoManager_repo, repoManager_RepoURL);
	
	if(temp_error < 0 ){
		std::cerr << "WARN:	Remote Repository not found. | GitError: " << giterr_last()->message << std::endl;
		return false;
	} else{
		std::cout << "	Remote Repository Created!" << std::endl;
		return true;
	} // End Error Check.
	
}

void UnrealatedLauncherRepoManager::RepoManagerGit_SetCloneOptions(git_clone_options* p_cloneOptions){	// Sets Clone Options.
}	// END - Set Clone Options.


void UnrealatedLauncherRepoManager::RepoManagerGit_SetFetchOptions(git_fetch_options* p_fetchOptions){	// Sets fetch options.

}	// END - Set Fetch Options.


bool UnrealatedLauncherRepoManager::RepoManagerGit_TagMatches(string p_message){
	for(unsigned int index = 0 ; index < repoManager_objectIDsOfTags.size(); index++){

		string v_tagString = repoManager_objectIDsOfTags[index];
		if( v_tagString.compare(p_message) == 0 ){
			return true;
		} // END - Tag matches.
	} // END - For Loop.

	return false;
} // END - Tag Matches.