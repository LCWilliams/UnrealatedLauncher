#include <headers/UnrealatedLauncherWindow.h>	// Repo Manager.
#include <headers/Launcher_RepoManagerGit.h>	// Global GIT functions.

using namespace UnrealatedLauncher;

bool UnrealatedLauncherRepoManager::RepoManagerGit_OpenRepo(){			// Opens the launcher repository.  Returns FALSE on error/doesn't exist.
	int temp_error = git_repository_open(&repoManager_repo, UnrealatedLauncherGlobal::launcherRepositoryDir.c_str());

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

void UnrealatedLauncherRepoManager::RepoManagerGit_SetCloneOptions(git_clone_options* p_cloneOptions){	// Sets Clone Options.
}	// END - Set Clone Options.


void UnrealatedLauncherRepoManager::RepoManagerGit_SetFetchOptions(git_fetch_options* p_fetchOptions){	// Sets fetch options.

}	// END - Set Fetch Options.