#include <headers/UnrealatedLauncherWindow.h>	// Repo Manager.
#include <headers/Launcher_Global.h>

using namespace UnrealatedLauncher;

void UnrealatedLauncherRepoManager::btn_login_login_clicked(){
// Set Username/Password variables:
	threadComm_username = btn_login_username.get_text();
	threadComm_password = btn_login_password.get_text();
	
	threadComm_attemptedLoginWithSavedInfo = false; // Set to false for future operations.

	if(!threadComm_username.empty() && !threadComm_password.empty()){
	// Save Details:
		CSimpleIniCaseA temp_ini;
		string dataString;
		SI_Error temp_errorCheck;
		temp_ini.LoadFile(UnrealatedLauncherGlobal::launcherConfig.c_str());
		temp_ini.SetBoolValue("General", "RememberGitLogin", btn_login_rememberDetails.get_active());
		
		temp_errorCheck = temp_ini.Save(dataString);
		if(temp_errorCheck < 0) return;
	
		temp_errorCheck = temp_ini.SaveFile(UnrealatedLauncherGlobal::launcherConfig.c_str());
		if(temp_errorCheck < 0) return;


		if(btn_login_rememberDetails.get_active()){
			ofstream temp_outputStream(UnrealatedLauncherGlobal::repoManagerLoginFile.c_str());
			temp_outputStream << threadComm_username << endl << threadComm_password;
			temp_outputStream.close();
		} // END - Save Details.
		
		v_login_revealer.set_reveal_child(false);
		btn_login_logout.show();
		RepoManager_setOnlineRelated(true);

		if(threadComm_onlineTaskBusy){
			// Callback induced login.
			threadComm_loginPrompt = false;
			threadComm_loginPrompt_conditionVar.notify_all();
		}
		
		string temp_status = "Logged in as: " + threadComm_username;
		txt_login_status.set_text(temp_status);
		
	} else{// END - If entries are NOT empty.
		txt_login_status.set_text("Login information cannot be empty!");
	}
}// END - Login Clicked.

void UnrealatedLauncherRepoManager::btn_login_logOut_clicked(){
	btn_login_logout.hide();
	v_login_revealer.set_reveal_child(true);
	RepoManager_setOnlineRelated(false);
	
	threadComm_password = "";
	btn_login_password.set_text("");
	std::remove(UnrealatedLauncherGlobal::repoManagerLoginFile.c_str());
	txt_login_status.set_text("Logged out!");
}



void UnrealatedLauncherRepoManager::btn_manage_clearRepo_clicked(){
	btn_manage_clearRepo.set_sensitive(false);
	btn_manage_clearRepo_box.show();
}

void UnrealatedLauncherRepoManager::btn_manage_clearRepoCancel_clicked(){
	btn_manage_clearRepo_box.hide();
	btn_manage_clearRepo.set_sensitive(true);
}

void UnrealatedLauncherRepoManager::btn_manage_clearRepoConfirm_clicked(){
	threadComm_onlineTaskBusy = true;
	
	repoManager_manageButtons_frame.set_sensitive(false);
	btn_manage_clearRepo_box.hide();
	btn_manage_clearRepo.set_sensitive(true);
	
	v_status_levelBar.set_max_value(2);
	// Find
	// Remove.
	
	thread  thread_clearRepo(&UnrealatedLauncherRepoManager::RepoManager_thread_clearRepo, this);
	thread_clearRepo.detach();
	
	Glib::signal_timeout().connect(sigc::mem_fun(*this, &UnrealatedLauncherRepoManager::RepoManager_timeout), 50);
	
}



void UnrealatedLauncherRepoManager::btn_manage_getNew_clicked(){
	RepoManager_updateRepoDir();
	
	btn_status_cancel.show();	// Show the cancel button.
	
	repoManager_manageButtons_frame.set_sensitive(false);

	threadComm_currentStage = 0;
	v_status_levelBar.set_max_value(3);
	// Connect
	// Download
	// Index

	threadComm_onlineTaskBusy = true;

	thread  thread_Getnew(&UnrealatedLauncherRepoManager::RepoManager_thread_GetNew, this);
	thread_Getnew.detach();
//	Glib::signal_idle().connect(sigc::mem_fun(*this, &UnrealatedLauncherRepoManager::RepoManager_timeout));	// Runs way too fast!
	Glib::signal_timeout().connect(sigc::mem_fun(*this, &UnrealatedLauncherRepoManager::RepoManager_timeout), 50);
	
//	cout << "DEBUG:	" << "Repo Dir: " << UnrealatedLauncherGlobal::launcherRepositoryDir.c_str() 
//	<< endl << "DEBUG:	" << "Repo URL: " << repoManager_RepoURL << endl;
	
} // END - Getnew Clicked.

void UnrealatedLauncherRepoManager::btn_manage_generateLists_clicked(){
	threadComm_onlineTaskBusy = true;
	
	repoManager_manageButtons_frame.set_sensitive(false);
	
	RepoManager_updateRepoDir();
	
	btn_status_cancel.show();	// Show the cancel button.
	
	repoManager_manageButtons_frame.set_sensitive(false);

	threadComm_currentStage = 0;
	v_status_levelBar.set_max_value(1);

	// Update Lists.
	thread  thread_Getnew(&UnrealatedLauncherRepoManager::RepoManager_thread_GenerateLists, this);
	thread_Getnew.detach();
	Glib::signal_timeout().connect(sigc::mem_fun(*this, &UnrealatedLauncherRepoManager::RepoManager_timeout), 50);
	
}

void UnrealatedLauncherRepoManager::btn_manage_update_clicked(){
	threadComm_onlineTaskBusy = true;

	repoManager_manageButtons_frame.set_sensitive(false);
	
	threadComm_currentStage = 0;
	v_status_levelBar.set_max_value(3);
	
	thread  thread_update(&UnrealatedLauncherRepoManager::RepoManager_thread_update, this);
	thread_update.detach();
	Glib::signal_timeout().connect(sigc::mem_fun(*this, &UnrealatedLauncherRepoManager::RepoManager_timeout), 50);
}

void UnrealatedLauncherRepoManager::btn_manage_updateAll_clicked(){
	threadComm_onlineTaskBusy = true;
	threadComm_multiStageTask = true;

	repoManager_manageButtons_frame.set_sensitive(false);
	
	threadComm_currentStage = 0;
	v_status_levelBar.set_max_value(5);
	/* STEPS:
	 * [1] Check,
	 * [3] Get New / Update
	 * [1] Generate Lists
	 */
	
	thread  thread_updateAll(&UnrealatedLauncherRepoManager::RepoManager_thread_updateAll, this);
	thread_updateAll.detach();
	Glib::signal_timeout().connect(sigc::mem_fun(*this, &UnrealatedLauncherRepoManager::RepoManager_timeout), 50);
}

void UnrealatedLauncherRepoManager::btn_status_cancel_clicked(){
	git_remote_stop(repoManager_remoteRepo);
	threadComm_currentStage = 0;
	cout << "DEBUG:	Cancel Clicked.  Waiting..." << endl;
	btn_status_cancel.hide();
	btn_status_cancel_force.show();
}

void UnrealatedLauncherRepoManager::btn_status_cancel_force_clicked(){
}