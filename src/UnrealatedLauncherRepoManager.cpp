#include <headers/UnrealatedLauncherWindow.h>

using namespace UnrealatedLauncher;
using namespace LauncherUtility;

UnrealatedLauncherRepoManager::UnrealatedLauncherRepoManager():
	repoManager_login_frame("Login"), 
	repoManager_manageButtons_frame("Manage"), 
	repoManager_status_frame("Status"),
	repoManager_options_frame("Options"),
	btn_closeWindow("Hide Manger"),
	
// Login:
	txt_login_username("Username:"),
	txt_login_password("Password:"),
	txt_login_status_label("Status:"),
	txt_login_status("..."),
	btn_login_login("Login"),
	btn_login_logout("Logout"),
	btn_login_rememberDetails("Remember Login Details"),
	
// Manage:
	btn_manage_getNew("Get New Repository"),
	btn_manage_update("Update Launcher Repository"),
	btn_manage_generateLists("(Re)Generate Lists"),
	btn_manage_updateAll("Update All"),
	btn_manage_clearRepo("Clear Repo"),
	btn_manage_clearRepoConfirm("Confirm Clear"),
	btn_manage_clearRepoCancel("Cancel"),
	btn_manage_clearRepo_box(Gtk::ORIENTATION_HORIZONTAL),

// Status:
	txt_status_currentTask_label("Current Task:"),
	txt_status_currentTask("..."),
	txt_status_repoStatus_label("Repo Status:"),
	txt_status_repoStatus("..."),
	btn_status_cancel("Cancel"),
	
// OPTIONS:
	btn_options_lists_replace("Replace/Overwrite existing")

{ // LAUNCHER REPO MANAGER CONSTRUCTOR:
	// Grid settings:
	set_hexpand(true);
	set_vexpand(false);
	set_margin_bottom(5);
	set_name("LAUNCHER_REPO_MANAGER");

	// Attachment:
	attach(v_repoManager_flowBox, 0, 0, 1, 1); // Attach flow box.
	attach(btn_closeWindow, 0, 1, 1, 1); // Attach close window button.
	LauncherUtility_setFlowboxSettings(&v_repoManager_flowBox);

	// Login:
	repoManager_login_frame.add(repoManager_login);		// Add login grid to login frame.
	v_repoManager_flowBox.add(repoManager_login_frame);	// Add login frame to flowbox.
	LauncherUtility_setGridSettings(&repoManager_login);// Perform settings on the grid.
	
	v_login_revealer.add(v_login_subgrid_loginEntries);	// Add subgrid to revealer.
//	LauncherUtility_setGridSettings(&v_login_subgrid_loginEntries);	// perform settings on subgrid
		v_login_subgrid_loginEntries.set_hexpand(true);
		v_login_subgrid_loginEntries.set_row_spacing(3);
		v_login_subgrid_loginEntries.set_column_spacing(5);
		v_login_revealer.set_transition_type(Gtk::REVEALER_TRANSITION_TYPE_SLIDE_DOWN);
		v_login_revealer.set_transition_duration(500);
	
	repoManager_login.attach(v_login_revealer, 0, 0, 3, 1);
	
	// Debug show child:
	v_login_revealer.set_reveal_child(true);
	
	// LOGIN SUBGRID:
	v_login_subgrid_loginEntries.attach(txt_login_username, 0, 0, 1, 1);
		txt_login_username.set_halign(Gtk::ALIGN_END);
	v_login_subgrid_loginEntries.attach(btn_login_username, 1, 0, 1, 1);
		btn_login_username.set_tooltip_text("Your GitHub USERNAME; not the email you use with GitHub.");
		btn_login_username.set_hexpand();
	
	v_login_subgrid_loginEntries.attach(txt_login_password, 0, 1, 1, 1);
		txt_login_password.set_halign(Gtk::ALIGN_END);
	v_login_subgrid_loginEntries.attach(btn_login_password, 1, 1, 1, 1);
		btn_login_password.set_hexpand();
		btn_login_password.set_input_purpose(Gtk::INPUT_PURPOSE_PASSWORD);
		btn_login_password.set_visibility(false);
		btn_login_password.set_tooltip_text("The password you use to login to GitHub.");
	v_login_subgrid_loginEntries.attach(btn_login_login, 0, 2, 2, 1);

	v_login_subgrid_loginEntries.attach(btn_login_rememberDetails, 0, 3, 2, 1);
		btn_login_rememberDetails.set_tooltip_text("Will remember your login between sessions.\nWARNING: Will save your login information into a plain file inside your home directory.\nUse at your own discretion!");

	// LOGIN MAIN GRID:
	repoManager_login.attach(txt_login_status_label, 0, 2, 1, 1);
		txt_login_status_label.set_halign(Gtk::ALIGN_END);
	repoManager_login.attach(txt_login_status, 1, 2, 1, 1);
		txt_login_status.set_hexpand();
		LauncherUtility_setLabelWrapSettings(&txt_login_status, 1, 200, Pango::ELLIPSIZE_NONE);
		repoManager_login.set_valign(Gtk::ALIGN_CENTER);
	repoManager_login.attach(btn_login_logout, 0, 3, 2, 1);
		btn_login_logout.set_tooltip_text("Clears your login information, and deletes the file from disk\nif 'remember login' is checked.");


	// Signal Handlers:
	btn_login_login.signal_clicked().connect(sigc::mem_fun(*this, &UnrealatedLauncherRepoManager::btn_login_login_clicked));
	btn_login_logout.signal_clicked().connect(sigc::mem_fun(*this, &UnrealatedLauncherRepoManager::btn_login_logOut_clicked));



	// Buttons (manage):
	repoManager_manageButtons_frame.add(repoManager_manageButtons);
	v_repoManager_flowBox.add(repoManager_manageButtons_frame);
	LauncherUtility_setGridSettings(&repoManager_manageButtons);
	repoManager_manageButtons.set_valign(Gtk::ALIGN_CENTER);
	
	repoManager_manageButtons.attach(btn_manage_getNew, 0, 0, 1, 1);
		btn_manage_getNew.set_tooltip_text("Clones the repository from Github.");
		btn_manage_getNew.set_hexpand();
	repoManager_manageButtons.attach(btn_manage_update, 0, 1, 1, 1);
		btn_manage_update.set_tooltip_text("Updates the launcher repository.");
		btn_manage_update.set_hexpand();
	repoManager_manageButtons.attach(btn_manage_generateLists, 0, 2, 1, 1);
		btn_manage_generateLists.set_tooltip_text("Generates the lists used by the launcher for showing the commits.");
		btn_manage_generateLists.set_hexpand();
		
	repoManager_manageButtons.attach(btn_manage_updateAll, 1, 0, 1, 3);
		btn_manage_updateAll.set_tooltip_text("Will get new or Update the launcher repository, then regenerate lists.");
		
	repoManager_manageButtons.attach(btn_manage_clearRepo, 0, 3, 2, 1);
		btn_manage_clearRepo.set_tooltip_text("Will delete the launcher repository from disk. \nUse if you're encountering issues.");
	
	// ButtonBox:
	repoManager_manageButtons.attach(btn_manage_clearRepo_box, 0, 4, 2, 1);
		btn_manage_clearRepo_box.set_layout(Gtk::BUTTONBOX_EXPAND);
		btn_manage_clearRepo_box.add(btn_manage_clearRepoConfirm);
			btn_manage_clearRepoConfirm.set_name("btn_Red");
		btn_manage_clearRepo_box.add(btn_manage_clearRepoCancel);
	
	
	// BUTTON SIGNAL HANDLERS:
	btn_manage_getNew.signal_clicked().connect(sigc::mem_fun(*this, &UnrealatedLauncherRepoManager::btn_manage_getNew_clicked));
	btn_manage_update.signal_clicked().connect(sigc::mem_fun(*this, &UnrealatedLauncherRepoManager::btn_manage_update_clicked));
	btn_manage_generateLists.signal_clicked().connect(sigc::mem_fun(*this, &UnrealatedLauncherRepoManager::btn_manage_generateLists_clicked));
	btn_manage_updateAll.signal_clicked().connect(sigc::mem_fun(*this, &UnrealatedLauncherRepoManager::btn_manage_updateAll_clicked));
	btn_manage_clearRepo.signal_clicked().connect(sigc::mem_fun(*this, &UnrealatedLauncherRepoManager::btn_manage_clearRepo_clicked));
	btn_manage_clearRepoConfirm.signal_clicked().connect(sigc::mem_fun(*this, &UnrealatedLauncherRepoManager::btn_manage_clearRepoConfirm_clicked));
	btn_manage_clearRepoCancel.signal_clicked().connect(sigc::mem_fun(*this, &UnrealatedLauncherRepoManager::btn_manage_clearRepoCancel_clicked));


	// Status:
	repoManager_status_frame.add(repoManager_status);
	v_repoManager_flowBox.add(repoManager_status_frame);
	LauncherUtility_setGridSettings(&repoManager_status);
	repoManager_status.set_valign(Gtk::ALIGN_CENTER);
	
	
	repoManager_status.attach(txt_status_repoStatus_label, 0, 0, 1, 1);
	repoManager_status.attach(txt_status_repoStatus, 1, 0, 1, 1);
		LauncherUtility_setLabelWrapSettings(&txt_status_repoStatus, 2, 200, Pango::ELLIPSIZE_NONE);
	
	
	repoManager_status.attach(txt_status_currentTask_label, 0,1, 1, 1);
	repoManager_status.attach(txt_status_currentTask, 1, 1, 1, 1);
		txt_status_currentTask.set_hexpand();
		LauncherUtility_setLabelWrapSettings(&txt_status_currentTask, 2, 200, Pango::ELLIPSIZE_NONE);
	
	repoManager_status.attach(v_status_progressBar, 0, 2, 2, 1);
		v_status_progressBar.set_hexpand(true);
//		v_status_progressBar.set_size_request(320, -1);
		v_status_progressBar.set_pulse_step(0.05);
		v_status_progressBar.set_show_text(true);
		v_status_progressBar.set_ellipsize(Pango::ELLIPSIZE_START);
//		v_status_progressBar.set_halign(Gtk::ALIGN_CENTER);
		
		
	repoManager_status.attach(v_status_levelBar, 0, 3, 3, 1);
		v_status_levelBar.set_hexpand(false);
//		v_status_levelBar.set_size_request(300, -1);
		v_status_levelBar.set_mode(Gtk::LEVEL_BAR_MODE_DISCRETE);

//	repoManager_status.attach(btn_status_cancel, 0, 4, 2, 1);
//		btn_status_cancel.signal_clicked().connect(sigc::mem_fun(*this, &UnrealatedLauncherRepoManager::btn_status_cancel_clicked));
//		btn_status_cancel.set_tooltip_text("Calls git cancel: may take some time before it's called!");
//		
//	repoManager_status.attach(btn_status_cancel_force, 0, 5, 2, 1);
//		btn_status_cancel_force.signal_clicked().connect(sigc::mem_fun(*this, &UnrealatedLauncherRepoManager::btn_status_cancel_force_clicked));
//		btn_status_cancel_force.set_tooltip_text("Force kills the thread task.");
	
	
	// Options:
	repoManager_options_frame.add(repoManager_options);
	v_repoManager_flowBox.add(repoManager_options_frame);
	LauncherUtility_setGridSettings(&repoManager_options);
	
	Gtk::Label *txt_listOptions_label = Gtk::manage(new Gtk::Label("List Options:"));
	repoManager_options.attach(*txt_listOptions_label, 0, 0, 2, 1);
	repoManager_options.attach(btn_options_lists_replace, 0, 1, 2, 1);
	
//	LauncherUtility_setGridSettings(this);

	btn_closeWindow.signal_clicked().connect(sigc::mem_fun(*this, &UnrealatedLauncherRepoManager::btn_closeWindow_clicked));
	btn_closeWindow.set_border_width(10);

	show_all();

	CSimpleIniCaseA temp_ini;
	SI_Error temp_iniError = temp_ini.LoadFile(UnrealatedLauncherGlobal::launcherConfig.c_str());
	if(temp_iniError == 0){
		int temp_interval =  temp_ini.GetDoubleValue("Engines", "BackgroundRepoSyncInterval") * 60000;
		Glib::signal_timeout().connect(sigc::mem_fun(*this, &UnrealatedLauncherRepoManager::idle_backgroundSync), temp_interval );
	}

} // END - Launcher Repo Manager.

UnrealatedLauncherRepoManager::~UnrealatedLauncherRepoManager(){
} // END - Destructor

// BUTTON FUNCTIONS:
void UnrealatedLauncherRepoManager::btn_closeWindow_clicked(){
	ref_window->repoManager_closed();
	
	// MIDDLEMEN:
	ref_window->ref_engineTab->middleMan_openRepoManager_bool = false;
	
} // Btn Close Window Clicked.


void UnrealatedLauncherRepoManager::launcherRepoManager_setup(){

	
	// Check 
	if(LauncherUtility_checkFileExists(UnrealatedLauncherGlobal::repoManagerLoginFile)){
		cout << "DEBUG:	Login Information Found" << endl;
		
		btn_login_rememberDetails.set_active(true);
		
	// Read File:
		string temp_array[2];
		ifstream temp_inFileStream(UnrealatedLauncherGlobal::repoManagerLoginFile.c_str());
		string temp_line;
		int loop_iterations = 0;
		while(getline(temp_inFileStream, temp_line) && loop_iterations != 2){
			temp_array[loop_iterations] = temp_line;
			loop_iterations++;
		} // END - While loop.
	// Set Strings:
		threadComm_username = temp_array[0];
		threadComm_password = temp_array[1];
		
//		cout << "DEBUG:	Login Info: " << temp_array[0] << " | " << temp_array[1] << endl;
		btn_login_username.set_text(threadComm_username);
		txt_login_status.set_text("Logged in with saved credentials.");
		v_login_revealer.set_reveal_child(false);
		btn_login_logout.show();
		RepoManager_setOnlineRelated(true);
		
	} else{
		txt_login_status.set_text("Login using your GitHub Credentials.");
		v_login_revealer.set_reveal_child(true);
		btn_login_logout.hide();
		RepoManager_setOnlineRelated(false);
	}
	
	btn_manage_clearRepo_box.hide();
	btn_status_cancel.hide();
	

// Test repo Open: changes GenerateList sensitivity.
	git_libgit2_init();
	
//	int temp_error = git_repository_open( (&repoManager_repo, repoManager_repoDirectory.c_str()) < 0);
	
	btn_manage_generateLists.set_sensitive(RepoManagerGit_OpenRepo());
	
	git_libgit2_shutdown();
	

} // END - Setup.

void UnrealatedLauncherRepoManager::launcherRepoManager_setRepoDirectory(string* p_path){	repoManager_repoDirectory = UnrealatedLauncherGlobal::launcherRepositoryDir;	}

void UnrealatedLauncherRepoManager::launcherRepoManager_setSettingsReference(UnrealatedSettings* p_settingsReference){	ref_settings = &*p_settingsReference;	}

void UnrealatedLauncherRepoManager::RepoManager_setOnlineRelated(bool p_state){	// Changes the sensitivity of online related buttons.
	if(threadComm_onlineTaskBusy && p_state){
		// Thread busy & set to true, likely called from Login button, don't change.
		cout << "DEBUG:	OnlineTaskThread is busy, and button state called to sensitive:	Ignored." << endl;
	} else{
		cout << "DEBUG:	OnlineTaskThread is not busy:	Button Status changed." << endl;
		btn_manage_getNew.set_sensitive(p_state);
		btn_manage_update.set_sensitive(p_state);
		btn_manage_updateAll.set_sensitive(p_state);
	}	// END - else.
} // END - SetOnline Related


bool UnrealatedLauncherRepoManager::idle_backgroundSync(){

	CSimpleIniCaseA temp_ini;
	SI_Error temp_iniError = temp_ini.LoadFile(UnrealatedLauncherGlobal::launcherConfig.c_str());
	
	if(temp_iniError == 0) {
		if( !threadComm_onlineTaskBusy ) {
			if( temp_ini.GetBoolValue("Engines", "BackgroundRepoSync_RegenList") ){	// Regen Lists on Sync:
					btn_manage_updateAll_clicked();
				} else{													// Update only.
					btn_manage_update_clicked();
				}
		}// END - Ini load.
	}

	return temp_ini.GetBoolValue("Engines", "BackgroundRepoSync");
}