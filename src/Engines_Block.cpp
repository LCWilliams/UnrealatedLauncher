#include <headers/Launcher_Engines.h>

using namespace UnrealatedLauncher;

EngineBlock::EngineBlock(string p_installDir, string p_customImageDir, string p_CustomLabel, string p_gitCommit, string p_codeEditor){ 
	// Engine Block Constructor: New block with settings input from user, written to file.
	v_EngineInstallDir = p_installDir;
	v_gitCommit = p_gitCommit;
	v_InstallStatus = 0;
	v_codeEditor = p_codeEditor;

// Custom Image Dir:
	if(!p_customImageDir.empty() && checkImageExists(p_customImageDir)){ // Check if a custom image was set...
		v_CustomEngineImageDir = p_customImageDir;
		img_EngineImage.set(p_customImageDir);
		img_EngineImage.set(img_EngineImage.get_pixbuf()->scale_simple(300, 175, Gdk::INTERP_BILINEAR));
	} else { // If not, use default
		img_EngineImage.set("../img/guiElement/engine_image_default.svg");
		img_EngineImage.set(img_EngineImage.get_pixbuf()->scale_simple(300, 175, Gdk::INTERP_BILINEAR));
	} // END - custom image dir.

	v_EngineLabel = p_CustomLabel;
	v_DisplayedEngineLabel.set_label(v_EngineLabel);

	// CREATE INI FILE:
	
	CSimpleIniCaseA ini;
	string temp_test;
	string iniFileDir = "./config/engines/" + p_CustomLabel + ".ini";

	SI_Error temp_errorCheck = ini.SetValue("EngineGeneral", "EngineDir", p_installDir.c_str() );
	if(temp_errorCheck < 0){
		cerr << "ERROR: Failed to set Engine Label value." << endl;
	}
	
	temp_errorCheck = ini.SetValue("EngineGeneral", "Label", p_CustomLabel.c_str() );
	if(temp_errorCheck < 0){
		cerr << "ERROR: Failed to set Engine Directory value." << endl;
	}

	temp_errorCheck = ini.SetValue("EngineGeneral", "ImageDir", p_customImageDir.c_str() );
	if(temp_errorCheck < 0){
		cerr << "ERROR: Failed to set Custom Image value." << endl;
	}

	temp_errorCheck = ini.SetValue("EngineGeneral", "GitCommit", p_gitCommit.c_str() );
	if(temp_errorCheck < 0){
		cerr << "ERROR: Failed to set Git Commit value." << endl;
	}

	temp_errorCheck = ini.SetDoubleValue("EngineGeneral", "InstallStatus", 0 );
	if(temp_errorCheck < 0){
		cerr << "ERROR: Failed to set Install Status value." << endl;
	}
	
	temp_errorCheck = ini.SetValue("EngineGeneral", "codeEditor", p_codeEditor.c_str() );
	if(temp_errorCheck < 0){
		cerr << "ERROR: Failed to set Code Editor value." << endl;
	}

	temp_errorCheck = ini.Save(temp_test);
	if(temp_errorCheck < 0) { cerr << "ERROR:	Failed to save data." << endl;}
	
	temp_errorCheck = ini.SaveFile(iniFileDir.c_str());
	if(temp_errorCheck < 0) { cerr << "ERROR:	Failed to save file!" << endl; }
	
	// Run setup:
	if(temp_errorCheck == 0){
		EngineBlockSetup();
	} // END - Run setup if errorcheck is 0.
} // END - Engine Block Constructor

EngineBlock::EngineBlock(string p_SettingsFileDir){
	// Engine Block Constructor: Sets up an engine block from a saved file
	CSimpleIniCaseA ini;
	SI_Error temp_errorCheck = ini.LoadFile(p_SettingsFileDir.c_str());
	if(temp_errorCheck < 0){
		cerr << "ERROR:	Failed to load file: " << p_SettingsFileDir.c_str() << endl;
		return;
	}
	
	v_EngineInstallDir = ini.GetValue("EngineGeneral", "EngineDir", "ERROR: NO INSTALL DIRECTORY");
	v_DisplayedEngineLabel.set_label(ini.GetValue("EngineGeneral", "Label", "LABELNOTSET"));
	v_EngineLabel = v_DisplayedEngineLabel.get_text();
	v_gitCommit = ini.GetValue("EngineGeneral", "GitCommit", NULL); //Probably change to git thing?
	v_InstallStatus = ini.GetDoubleValue("EngineGeneral", "InstallStatus", 0);
	
	// Check image dir value for custom image.
	string imageDir = ini.GetValue("EngineGeneral", "ImageDir", "");


	if(imageDir == "" || !checkImageExists(imageDir)){
		if(checkImageExists("../img/guiElement/engine_image_default.svg")){ // Default image exists.
			img_EngineImage.set("../img/guiElement/engine_image_default.svg");
			img_EngineImage.set(img_EngineImage.get_pixbuf()->scale_simple(300, 175, Gdk::INTERP_BILINEAR));
		}else{
			cerr << "WARN:	Default Engine image not found!" << endl;
		} // END - Default image exists.
	}else{
		v_CustomEngineImageDir = imageDir;
		img_EngineImage.set(v_CustomEngineImageDir);
		img_EngineImage.set(img_EngineImage.get_pixbuf()->scale_simple(300, 175, Gdk::INTERP_BILINEAR));
	} // END - If else null.
	
	// Run setup:
	EngineBlockSetup();
} // END - Engine Block Constructor. From File

EngineBlock::~EngineBlock(){
}// END - Engine block Destructor



// SETUP FUNCTION:
void EngineBlock::EngineBlockSetup(){
// Grid settings:
	set_border_width(5);
	set_hexpand(false);
	set_vexpand(false);
	set_valign(Gtk::ALIGN_CENTER);
	
// Attachment:
	attach(v_InfoBar, 0, -1, 1, 1);
	attach(v_DisplayedEngineLabel, 0, 0, 1, 1);
	attach(img_EngineImage, 0, 0, 1, 1);
	attach(v_ProgressBar, 0, 1, 1, 1);
	attach(v_LevelBar, 0, 2, 1, 1);
	attach(v_buttonBox, 0, 3, 1, 1);

		// InfoBar:
	auto infoBarContainer = dynamic_cast<Gtk::Container*>(v_InfoBar.get_content_area());
	infoBarContainer->add(txt_infoBarText);
	infoBarContainer->set_border_width(0);
	v_InfoBar.set_homogeneous(false);
	btn_infoBar_ConfirmDelete.set_name("btn_Red");
	
//	v_InfoBar.pack_start(txt_infoBarText, Gtk::PACK_EXPAND_WIDGET, 0);
	v_InfoBar.add_action_widget(btn_infoBar_Okay, 0);
	v_InfoBar.add_action_widget(btn_infoBar_ContinueInstall, 1);
//		btn_infoBar_ContinueInstall.signal_clicked().connect(sigc::mem_fun(*this, &EngineBlock::InstallEngine));
	v_InfoBar.add_action_widget(btn_infoBar_ConfirmDelete, 2);
	v_InfoBar.add_action_widget(btn_infoBar_CancelDelete, 0);
	v_InfoBar.set_hexpand(false);
	
	auto infobarActionArea = dynamic_cast<Gtk::Widget*>(v_InfoBar.get_action_area());
	infobarActionArea->set_hexpand(false);
	infobarActionArea->set_margin_end(0);
	infobarActionArea->set_margin_start(0);
	infobarActionArea->set_halign(Gtk::ALIGN_END);
	infobarActionArea->set_size_request(50, -1);
	
	btn_infoBar_CancelDelete.set_hexpand(false);
	btn_infoBar_ConfirmDelete.set_hexpand(false);

// Buttons
//	v_buttonBox.set_hexpand();
	v_buttonBox.set_size_request(-1, 50);
	v_buttonBox.set_layout(Gtk::BUTTONBOX_EXPAND);
	v_buttonBox.set_homogeneous(false);
	v_buttonBox.pack_start(btn_EngineLaunch, Gtk::PACK_EXPAND_WIDGET, 0);
	v_buttonBox.pack_end(btn_Options, Gtk::PACK_SHRINK, 0);
	
	btn_infoBar_Okay.set_label("Okay");
	btn_infoBar_ContinueInstall.set_label("Continue...");
	btn_infoBar_CancelDelete.set_label("Cancel");
	btn_infoBar_ConfirmDelete.set_label("Delete");


// LABELS:
	v_DisplayedEngineLabel.set_hexpand();
	v_DisplayedEngineLabel.set_line_wrap();
	v_DisplayedEngineLabel.set_lines(2);
	v_DisplayedEngineLabel.set_size_request(280, -1);
	v_DisplayedEngineLabel.set_max_width_chars(1);
	v_DisplayedEngineLabel.set_ellipsize(Pango::ELLIPSIZE_END);
	v_DisplayedEngineLabel.set_valign(Gtk::ALIGN_CENTER);
	v_DisplayedEngineLabel.set_halign(Gtk::ALIGN_CENTER);
	v_DisplayedEngineLabel.set_margin_bottom(13);
	btn_EngineLaunch.set_label("LAUNCH");

	txt_infoBarText.set_hexpand(false);
	txt_infoBarText.set_line_wrap(true);
	txt_infoBarText.set_lines(3);
	txt_infoBarText.set_max_width_chars(1);
	
//	btn_Options.set_label("OPTIONS");

// PROGRESS BARS:
	v_ProgressBar.set_show_text(false);
	v_ProgressBar.set_hexpand(false);
	v_ProgressBar.set_size_request(300, -1);
	v_ProgressBar.set_ellipsize(Pango::ELLIPSIZE_START);
	v_LevelBar.set_mode(Gtk::LEVEL_BAR_MODE_DISCRETE);
	v_LevelBar.set_min_value(0);
	v_LevelBar.set_max_value(3);
	
	// 0: Not downloaded/Copied.
	// 1: Downloaded/Copied.
	// 2: Make Ran.
	// 3: Build ran.
	v_LevelBar.set_value(3);

	// Options Menu
	btn_Options.set_menu(v_optionsMenu);
	
	// Build:
	v_optionsMenu.append(menuItem_build);
	menuItem_build.set_label("Build");
	menuItem_build.set_submenu(menu_build);
	
	menu_build.append(menu_build_generateFiles);
	menu_build_generateFiles.set_label("Generate Files");
	menu_build.append(menu_build_build);
	menu_build_build.set_label("Build");
	menu_build.append(menu_build_rebuild);
	menu_build_rebuild.set_label("Rebuild");
	
	// Manage:
	menuItem_manageMenu.set_label("Manage");
	v_optionsMenu.append(menuItem_manageMenu);
	menuItem_manageMenu.set_submenu(v_manageMenu);

	menuItem_archiveEngine.set_label("Archive Engine");
	v_manageMenu.append(menuItem_archiveEngine);
	menuItem_duplicateEngine.set_label("Duplicate Engine");
	v_manageMenu.append(menuItem_duplicateEngine);
	menuItem_deleteEngine.set_label("Delete Engine");
	v_manageMenu.append(menuItem_deleteEngine);

	v_optionsMenu.append(menuItem_openSettings);
	menuItem_openSettings.set_label("Preferences");
	
	
	
	// Show all menu items:
	v_optionsMenu.show_all();

	// Button Signal Handlers.
	menuItem_openSettings.signal_activate().connect(sigc::mem_fun(*this, &EngineBlock::menuItem_openPreferences_clicked));
	btn_EngineLaunch.signal_clicked().connect(sigc::mem_fun(*this, &EngineBlock::btn_EngineLaunch_Clicked));
	menuItem_deleteEngine.signal_activate().connect(sigc::mem_fun(*this, &EngineBlock::menuItem_deleteEngine_clicked));
	
	menu_build_build.signal_activate().connect(sigc::mem_fun(*this, &EngineBlock::menu_build_build_clicked));
	menu_build_generateFiles.signal_activate().connect(sigc::mem_fun(*this, &EngineBlock::menu_build_generateFiles_clicked));
	menu_build_rebuild.signal_activate().connect(sigc::mem_fun(*this, &EngineBlock::menu_build_rebuild_clicked));
		// Infobar Buttons:
	v_InfoBar.signal_response().connect(sigc::mem_fun(*this, &EngineBlock::InfoBarResponse));


// CSS STYLING:
	set_name("EngineBlock");
//	if(v_BuiltFromSource){ // Check if source directory is set, then change name of the block to correspond. 
//		v_BuiltFromSource = true;
//	} else {
//		set_name("BinaryEngineBlock");
//		v_BuiltFromSource = false;
//	} // END: if else.
	btn_EngineLaunch.set_name("EngineLaunchButton");
	btn_Options.set_name("BlockOptionsButton");


	// Run Show all, to show all items.
	show_all();
	
	// Hide all items that do not need to be shown:
	InfoBarResponse(0); // Run "okay/cancel/close" Infobar response.
	v_LevelBar.hide();
	v_ProgressBar.hide();
	set_no_show_all(true);
	
// Install Status Check:
	CheckInstallStatus();
} // END - Engine Block Setup.

void EngineBlock::PromptInfoBar(int p_typeCode, string p_message){
// Hide all buttons:
	btn_infoBar_Okay.hide();
	btn_infoBar_CancelDelete.hide();
	btn_infoBar_ConfirmDelete.hide();
	btn_infoBar_ContinueInstall.hide();

	switch(p_typeCode){
		case 0:
			v_InfoBar.set_message_type(Gtk::MESSAGE_INFO);
			txt_infoBarText.set_text(p_message);
			//v_InfoBar.set_show_close_button(true);
			btn_infoBar_Okay.show();
		break;
		
		case 1:
			txt_infoBarText.set_size_request(150, -1);
			v_InfoBar.set_message_type(Gtk::MESSAGE_QUESTION);
			txt_infoBarText.set_text("Installation is incomplete.");
			btn_infoBar_ContinueInstall.show();
		break;
		
		case 2:
			txt_infoBarText.set_size_request(100, -1);
			v_InfoBar.set_message_type(Gtk::MESSAGE_ERROR);
			txt_infoBarText.set_text("Confirm Deletion:");
			
			btn_infoBar_ConfirmDelete.show();
			btn_infoBar_CancelDelete.show();

		break;
	} // END - Switch.
	v_InfoBar.show();
}

void EngineBlock::InfoBarResponse(int p_response){
	switch(p_response){
		case 0: // Close/Cancel
			// If install status is not 0, show continue:
			if(v_InstallStatus != -1){
				PromptInfoBar(1, "");
			}else{
				v_InfoBar.hide();
				btn_infoBar_Okay.hide();
				btn_infoBar_CancelDelete.hide();
				btn_infoBar_ConfirmDelete.hide();
				btn_infoBar_ContinueInstall.hide();
			}
		break;
		case 1: // Continue Install
			EngineBlock_install();
			v_InfoBar.hide();
		break;
		case 2: // Delete
			set_sensitive(false);
			v_InfoBar.hide();
			// RUN DELETE FUNCTION
			DeleteEngine();
		break;
	} // END - Switch
}// END - Info bar response.



// BUTTON FUNCTIONS:
void EngineBlock::btn_EngineLaunch_Clicked(){
	engineBlock_run = true;
	Glib::signal_timeout().connect(sigc::mem_fun(*this, &EngineBlock::engineBlock_run_timeout), 1000);	// Check status every second.
	thread thread_launchEngine(&EngineBlock::threadFunction_launchEngine, this);
	thread_launchEngine.detach();
} // END - EngineLaunch Btn Clicked.

void EngineBlock::threadFunction_launchEngine(){
	string temp_command = v_EngineInstallDir + "/Engine/Binaries/Linux/UE4Editor";
	cout << ">>>>	Running command: " << temp_command << endl;
	system( temp_command.c_str() );
	cout << "DEBUG:	Engine Closed. " << endl;
	engineBlock_run_mutex.lock();
		engineBlock_run = false;	// Local bool to survive mutex lock.
	engineBlock_run_mutex.unlock();
} // END - thread.

bool EngineBlock::engineBlock_run_timeout(){
	engineBlock_run_mutex.lock();
		bool temp_statusBool = engineBlock_run;	// Local bool to survive mutex lock.
	engineBlock_run_mutex.unlock();
	
	if(temp_statusBool){	// Engine is currently running.
		btn_EngineLaunch.set_name("EngineLaunchButton_running");
		btn_EngineLaunch.set_label("RUNNING...");
	} else{					// Engine is no longer running.
		btn_EngineLaunch.set_name("EngineLaunchButton");
		btn_EngineLaunch.set_label("LAUNCH");
	}
	
	btn_EngineLaunch.set_sensitive(!temp_statusBool);
	btn_Options.set_sensitive(!temp_statusBool);
	return temp_statusBool;
} // END - Running timeout.

void EngineBlock::menuItem_openPreferences_clicked(){
//	EngineBlock* v_parentBlock = (EngineBlock*)get_ancestor(GTK_TYPE_GRID);	
//	EngineBlockOptions *window_blockOptions = new EngineBlockOptions(v_parentBlock);
//
//	Gtk::Window *parentWindow = dynamic_cast<Gtk::Window *>(this->get_ancestor(GTK_TYPE_WINDOW));
//	window_blockOptions->set_transient_for(*parentWindow);
//	
//	window_blockOptions->show_all();
} // END - Open preferences

void EngineBlock::menuItem_archiveEngine_clicked(){
	
} // END - Archive Engine.

void EngineBlock::menuItem_duplicateEngine_clicked(){
	
} // END - Duplicate Engine.

void EngineBlock::menuItem_deleteEngine_clicked(){
	PromptInfoBar(2, "");
} // END - Delete Engine

void EngineBlock::menu_build_generateFiles_clicked(){
	installEngine_threadBusy = true;
	thread thread_generateFiles(&EngineBlock::installEngine_thread_generateFiles, this);
	thread_generateFiles.detach();
	Glib::signal_timeout().connect(sigc::mem_fun(*this, &EngineBlock::installEngine_menuItem_timeout), 50);
	v_TabReference->AddPageTask();
} // END - Build Clicked.

void EngineBlock::menu_build_build_clicked(){
	installEngine_threadBusy = true;
	thread thread_makeEngine(&EngineBlock::installEngine_thread_make, this);
	thread_makeEngine.detach();
	Glib::signal_timeout().connect(sigc::mem_fun(*this, &EngineBlock::installEngine_menuItem_timeout), 50);
	v_TabReference->AddPageTask();
} // END - Build

void EngineBlock::menu_build_rebuild_clicked(){
	v_InstallStatus = 0;
	EngineBlock_install();
} // END - Build


void EngineBlock::Infobar_Cancel(){ // Function for all cancel events on the infobar.
	v_InfoBar.set_show_close_button(false);
	v_InfoBar.hide();
} // END : Infobar Cancel.


// END - Button Functions

// CHECKERS:
bool EngineBlock::checkImageExists(const string& p_imageDir){
	ifstream file(p_imageDir.c_str());
	return (bool)file;
} // END - CheckImageExists.

void EngineBlock::CheckInstallStatus(){
	switch(v_InstallStatus){
		case -2: // Deletion interrupted:
			set_sensitive(false);
			DeleteEngine();
		break;
		
		case -1: // Installed fully.
			btn_EngineLaunch.set_sensitive(true);
			menuItem_archiveEngine.set_sensitive(true);
			menuItem_duplicateEngine.set_sensitive(true);
		break;

			case 0: case 1: case 2:
			btn_EngineLaunch.set_sensitive(false);
			menuItem_archiveEngine.set_sensitive(false);
			menuItem_duplicateEngine.set_sensitive(false);
			
			PromptInfoBar(1, "");
			v_LevelBar.show();
			v_ProgressBar.show();
			v_ProgressBar.set_show_text(false);
			v_LevelBar.set_value(v_InstallStatus);
		break;
	} // END - Switch.
} // END - Status Check.

// OTHER:
void EngineBlock::DeleteEngine(){
	v_InstallStatus = -2;
	v_LevelBar.show();
	v_ProgressBar.set_show_text(true);
	v_LevelBar.set_max_value(1);
	v_LevelBar.set_value(1);
	v_deleteThreadBusy = true;

	deleteEngine_filesTotal = 0;
	deleteEngine_calledCount = 0;
	deleteEngine_filesDeleted = 0;
	
	Glib::signal_timeout().connect(sigc::mem_fun(*this, &EngineBlock::threadFunction_DeleteEngine_idle), 75);

	// Launch then detatch thread.
	thread thread1(&EngineBlock::threadFunction_DeleteEngine, this);
	thread1.detach();
	
} // END - Deletion

bool EngineBlock::threadFunction_DeleteEngine_idle(){
	
	threadComm_delete_mutex.lock();
	v_ProgressBar.set_text(threadComm_delete_taskText);
	v_ProgressBar.set_fraction(threadComm_delete_taskPercent);
	v_TabReference->SetPageTaskPercent(threadComm_delete_taskPercent);
	threadComm_delete_mutex.unlock();
	
	return v_deleteThreadBusy; 
} // END - Idle Delete Engine.

void EngineBlock::threadFunction_DeleteEngine(){
	struct stat v_statBuff;

// INSTALL DIRECTORY:
	if(!v_EngineInstallDir.empty()){ // If EngineInstallDir string is not empty, check if folder exists (outside deletion)
		// Check if directory exists.
		if(stat(v_EngineInstallDir.c_str(), &v_statBuff) == 0 && S_ISDIR(v_statBuff.st_mode)){
			// Count files:
			EngineBlock_thread_Delete_count(v_EngineInstallDir);
			// Delete files:
			EngineBlock_thread_Delete(v_EngineInstallDir);
		} // END If folder exists on disk.
	}

	threadComm_delete_taskText = "File removal completed.  Removing enigne block";
	threadComm_delete_taskPercent = 1;


	Launcher_EngineTab* v_engineTab = (Launcher_EngineTab*)get_ancestor(GTK_TYPE_GRID);
//	selfReturn = this;
	v_deleteThreadBusy = false;
	return v_engineTab->DeleteEngineBlock((EngineBlock*)this);
	
} // END - DeleteEngine ThreadFunction

void EngineBlock::EngineBlock_thread_Delete_count(string p_path){

	DIR *directory = opendir(p_path.c_str());
	struct dirent *next_file;
	char v_filePath[PATH_MAX];
	
	// COUNT Files:
	while ( (next_file = readdir(directory)) != NULL){

		if(strcmp(next_file->d_name, ".") && strcmp(next_file->d_name, "..")){
			sprintf(v_filePath, "%s/%s", p_path.c_str(), next_file->d_name);
			// If next file is a directory, call the same function with the new directory.

			if(next_file->d_type == DT_DIR){
				EngineBlock_thread_Delete(v_filePath);
				cout << v_filePath << "\n";
			} // END - If.

		} // END - If Filename

		// Set next file, update the progress bar text, and increment the file count:
		sprintf(v_filePath, "%s/%s", p_path.c_str(), next_file->d_name);

		threadComm_delete_mutex.lock();
		++deleteEngine_filesTotal;
		threadComm_delete_taskPercent = 0;
		threadComm_delete_taskText = "Finding files for removal";
		threadComm_delete_mutex.unlock();
		
	} // END - While loop.
			
	closedir(directory);
}

void EngineBlock::EngineBlock_thread_Delete(string p_path){
	++deleteEngine_calledCount;
	
	DIR *directory = opendir(p_path.c_str());
	struct dirent *next_file;
	char v_filePath[PATH_MAX];
		
	// Delete all files/dirs.
	while ( (next_file = readdir(directory)) != NULL){

		if(strcmp(next_file->d_name, ".") && strcmp(next_file->d_name, "..")){
			sprintf(v_filePath, "%s/%s", p_path.c_str(), next_file->d_name);
			// If next file is a directory, call the same function with the new directory.

			if(next_file->d_type == DT_DIR){
				EngineBlock_thread_Delete(v_filePath);
			} // END - If.

		} // END - If Filename

		// Set next file, update the progress bar text, and remove the file:
		sprintf(v_filePath, "%s/%s", p_path.c_str(), next_file->d_name);
		
		threadComm_delete_mutex.lock();
		deleteEngine_filesDeleted++;
		threadComm_delete_taskPercent = (double)deleteEngine_filesDeleted / deleteEngine_filesTotal;
		threadComm_delete_taskText = next_file->d_name;
		threadComm_delete_mutex.unlock();
		
		std::remove(v_filePath);
	} // END - While loop.
			
	closedir(directory);
	std::remove(p_path.c_str());
	
	--deleteEngine_calledCount;
	
	if(deleteEngine_calledCount == 0){
		cout << "DEBUG:	Delete Engine Call count is 0." << endl;
		threadComm_delete_mutex.lock();
		threadComm_delete_taskText = "Removal complete.";
		v_deleteThreadBusy = false;
		threadComm_delete_mutex.unlock();
	}
	return;
}


void EngineBlock::InstallEngine(){
	v_ProgressBar.set_show_text(true);
	cout << "DEBUG:	Installing engine: " << v_EngineLabel << " | Status: [" << v_InstallStatus << "]" << endl;
	// 0: Not downloaded/Copied.
	// 1: Downloaded/Copied.
	// 2: Make Ran.
	// 3: Build ran.
	
	// Write current status to file:
	CSimpleIniCaseA ini;
	string temp_data;
	string iniFileDir = "./config/engines/" +v_EngineLabel + ".ini";
	SI_Error temp_errorCheck = ini.LoadFile(iniFileDir.c_str() );
	temp_errorCheck = ini.SetDoubleValue("EngineGeneral", "InstallStatus", v_InstallStatus);
		temp_errorCheck = ini.Save(temp_data);
		temp_errorCheck = ini.SaveFile(iniFileDir.c_str());
		if(temp_errorCheck < 0) cerr << "WARN:	Failed to write to settings file: " << iniFileDir << endl;
	
	
	switch (v_InstallStatus){
		
		case 0:{// Copy Repository.
			v_LevelBar.set_value(1);
			installEngine_threadBusy = true;

			thread thread_copySource(&EngineBlock::installEngine_thread_copySource, this);
			thread_copySource.detach();
			
			Glib::signal_timeout().connect(sigc::mem_fun(*this, &EngineBlock::installEngine_timeout), 50);
			break;
		}
		
		case 1:{ // Run Make
			v_LevelBar.set_value(2);
			installEngine_threadBusy = true;
			thread thread_generateFiles(&EngineBlock::installEngine_thread_generateFiles, this);
			thread_generateFiles.detach();
			Glib::signal_timeout().connect(sigc::mem_fun(*this, &EngineBlock::installEngine_timeout), 50);
			break;
		}
		
		case 2:{ // Build
			v_LevelBar.set_value(3);
			installEngine_threadBusy = true;
			thread thread_makeEngine(&EngineBlock::installEngine_thread_make, this);
			thread_makeEngine.detach();
			Glib::signal_timeout().connect(sigc::mem_fun(*this, &EngineBlock::installEngine_timeout), 50);
			break;
		}
	} // END - Switch.

} // END - Install engine.

bool EngineBlock::installEngine_timeout(){
//	cout << ">>>>	InstallEngine Timeout." << endl;
	installEngine_mutex.lock();
	
	int temp_threadBusy = installEngine_threadBusy;	// Local copy to survive mutex unlock.
	
	if(installEngine_errorOccured){
		installEngine_threadBusy = false;
		installEngine_errorOccured = false; // Reset bool.
		v_TabReference->RemovePageTask();
		PromptInfoBar(0, "An error occured.");
		cerr << "WARN: 	Error Occured." << endl;
	} else{

		if(installEngine_threadBusy){	// Thread is busy: Update progress bar/text.
			v_ProgressBar.set_text(installEngine_progressText);
			v_TabReference->SetPageTaskPercent(installEngine_progress);
			if(installEngine_progress == 0){ // IF Progress is 0, pulse bar:
				v_ProgressBar.pulse();
			} else{ // Set Progress Bar:
				v_ProgressBar.set_fraction(installEngine_progress);
			} // END - Puslse/Set progress bar.
		} else {						// Thread is no longer busy.
			cout << "DEBUG:	InstallEngineTimeout: Thread is no longer busy." << endl;
			if(v_InstallStatus < 3){	// Installation is not completed.
				cout << "DEBUG:	InstallEngineTimeout: Install status is not complete. Recalling install for next step." << endl;
				installEngine_mutex.unlock();
				InstallEngine();
			} else{
				cout << "DEBUG:	InstallEngine completed." << endl;
				v_TabReference->RemovePageTask();
				v_ProgressBar.hide();
				v_ProgressBar.set_show_text(false);
				v_LevelBar.hide();
				v_InstallStatus = -1;	// Ready to use.
				
				CSimpleIniCaseA ini;
				string temp_data;
					string iniFileDir = "./config/engines/" +v_EngineLabel + ".ini";
					SI_Error temp_errorCheck = ini.LoadFile(iniFileDir.c_str() );
					temp_errorCheck = ini.SetDoubleValue("EngineGeneral", "InstallStatus", v_InstallStatus);
					temp_errorCheck = ini.Save(temp_data);
					temp_errorCheck = ini.SaveFile(iniFileDir.c_str());
					if(temp_errorCheck < 0) cerr << "WARN:	Failed to write to settings file: " << iniFileDir << endl;
				CheckInstallStatus(); 	// Change state of button!
			} // END - If install Status is less than 3
		} // END - If thread is busy.

	} // END - If no error occured.
	
	installEngine_mutex.unlock();
	
	return temp_threadBusy;
} // END - Timeout.


bool EngineBlock::installEngine_menuItem_timeout(){
	installEngine_mutex.lock();
	
	int temp_threadBusy = installEngine_threadBusy;	// Local copy to survive mutex unlock.
	
	if(installEngine_threadBusy){	// Thread is busy: Update progress bar/text.
		v_ProgressBar.show();
		v_LevelBar.show();
		
		v_ProgressBar.set_text(installEngine_progressText);
		v_TabReference->SetPageTaskPercent(installEngine_progress);
		if(installEngine_progress == 0){ // IF Progress is 0, pulse bar:
			v_ProgressBar.pulse();
		} else{ // Set Progress Bar:
			v_ProgressBar.set_fraction(installEngine_progress);
		} // END - Puslse/Set progress bar.
	} else {						// Thread is no longer busy.
		cout << "DEBUG:	InstallEngineTimeout: Thread is no longer busy." << endl;
		cout << "DEBUG:	InstallEngine completed." << endl;
		v_TabReference->RemovePageTask();
		v_ProgressBar.hide();
		v_LevelBar.hide();
		v_InstallStatus = -1;	// Ready to use.
	} // END - If thread is busy.
	installEngine_mutex.unlock();
	
	return temp_threadBusy;
}

void EngineBlock::installEngine_thread_copySource(){
	cout << "DEBUG:	Copy Source..." << endl;
	
	string temp_command = "cp -avr " + UnrealatedLauncherGlobal::launcherRepositoryDir + "/. " + v_EngineInstallDir;
	cout << "		> Running Command: " << temp_command << endl;
	
	installEngine_mutex.lock();
		installEngine_progressText = "Copying Source...";
		installEngine_progress = 0;
	installEngine_mutex.unlock();
	
// Run Copy command:
	system(temp_command.c_str());

	cout << "		> Reverting to chosen commit..." << endl;
	installEngine_mutex.lock();
		installEngine_progressText = "Reverting source to chosen commit";
		installEngine_progress = 0;
	installEngine_mutex.unlock();

// Start of GIT elements:
	git_libgit2_init();

	git_repository *temp_repo;
	if( git_repository_open(&temp_repo, UnrealatedLauncherGlobal::launcherRepositoryDir.c_str()) < 0 ){
		cerr << "ERROR:	FAILED TO OPEN LAUNCHER REPOSITORY!" << endl << "GIT ERROR: " << giterr_last()->message;
		installEngine_errorOccured = true;
		goto FINISHED;
	}
	
	git_object *temp_repoObject;
	git_oid temp_repoObjectID;
	cout << "		> Commit: " << v_gitCommit << endl;
	char temp_objectID[40];
	strcpy( (char *) temp_objectID, v_gitCommit.c_str() );

	
	cout << "		> Getting Git Object ID from String" << endl;
	if( git_oid_fromstr( &temp_repoObjectID, temp_objectID ) ){
		cerr << "ERROR:	FAILED TO CREATE OBJECT ID" << endl << "GIT ERROR: " << giterr_last()->message;
		installEngine_errorOccured = true;
		goto FINISHED;
	}
	
	cout << "		> Lookup Object using ID" << endl;
	if( git_object_lookup(&temp_repoObject, temp_repo, &temp_repoObjectID, GIT_OBJ_ANY ) < 0 ){
		cerr << "ERROR:	FAILED TO FIND COMMIT" << endl << "GIT ERROR: " << giterr_last()->message;
		installEngine_errorOccured = true;
		goto FINISHED;
	} // END - Object Lookup
	
	cout << "		> (Soft) Resetting to commit object" << endl;
	if ( git_reset( temp_repo, temp_repoObject, GIT_RESET_HARD, NULL ) < 0 ) {
		cerr << "ERROR:	FAILED TO REVERT TO COMMIT" << endl << "GIT ERROR: " << giterr_last()->message;
		installEngine_errorOccured = true;
		goto FINISHED;
	} // END - Reset.
	
	git_repository_free(temp_repo);
	git_object_free(temp_repoObject);
	
	git_libgit2_shutdown();

	FINISHED:
// FINISHED:
	++v_InstallStatus;
	installEngine_threadBusy = false;
	cout << "		> Copy & GitReset Completed." << endl;
} // END - Copy Source Thread.

void EngineBlock::installEngine_thread_generateFiles(){
	cout << "DEBUG:	Generate Engine Files..." << endl;
	
	
//	string temp_command = "gnome-terminal -x '" + v_EngineInstallDir + "/Setup.sh'";	// Opens new terminal.
	string temp_command = "'" + v_EngineInstallDir + "/Setup.sh'";
	cout << "		> Running Command: " << temp_command << endl;
	
	installEngine_mutex.lock();
		installEngine_progressText = "Running Setup script...\nCheck the terminal for any sudo prompts.";
		installEngine_progress = 0;
	installEngine_mutex.unlock();

// Run Command:
//	FILE *temp_commandPipe;
//	temp_commandPipe = popen(temp_command.c_str(), "we");
	system(temp_command.c_str());
	
	temp_command = v_EngineInstallDir + "/GenerateProjectFiles.sh";
	cout << "		> Running Command: " << temp_command << endl;
	
	installEngine_mutex.lock();
		installEngine_progressText = "Running Generate Project Files script...";
		installEngine_progress = 0;
	installEngine_mutex.unlock();

// Run Command:
	system(temp_command.c_str());
	
//	cin >> temp_password.c_str();


// FINISHED:
	++v_InstallStatus;
	installEngine_threadBusy = false;
	cout << "		> Generate Engine files completed." << endl;
} // END - Make Engine.

void EngineBlock::installEngine_thread_make(){
cout << "DEBUG: Make Engine..." << endl;
	
	string temp_command = "chmod 777 -R " + v_EngineInstallDir + "/Makefile";
	system(temp_command.c_str());
	cout << "		>> Running Command: " << temp_command << endl;

	temp_command = "cd " + v_EngineInstallDir + " && make";
	cout << "		> Running Command: " << temp_command << endl;
	
	installEngine_mutex.lock();
		installEngine_progressText = "Making the Engine...";
		installEngine_progress = 0;
	installEngine_mutex.unlock();

// Run Command:
	system(temp_command.c_str());

// FINISHED:
	++v_InstallStatus;
	installEngine_threadBusy = false;
	cout << "Make Engine completed." << endl;
} // END - Make.