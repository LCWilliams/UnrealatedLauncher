#include <headers/Launcher_Engines.h>

using namespace UnrealatedLauncher;

EngineBlock::EngineBlock(string p_installDir, string p_SourceDir, string p_customImageDir, string p_CustomLabel, string p_gitCommit){ 
	// Engine Block Constructor: New block with settings input from user, written to file.
	v_EngineInstallDir = p_installDir;
	v_gitCommit = p_gitCommit;
	v_InstallStatus = 0;

// Custom Image Dir:
	if(p_customImageDir != "" && checkImageExists(p_customImageDir)){ // Check if a custom image was set...
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
	string iniFileDir = "./config/engines/" +v_EngineLabel + ".ini";

	SI_Error temp_errorCheck = ini.SetValue("EngineGeneral", "EngineDir", p_installDir.c_str());
	ini.SetValue("EngineGeneral", "SourceDir", p_SourceDir.c_str());
	ini.SetValue("EngineGeneral", "Label", p_CustomLabel.c_str());
	ini.SetValue("EngineGeneral", "ImageDir", p_customImageDir.c_str());
	ini.SetValue("EngineGeneral", "GitCommit", p_gitCommit.c_str());
	ini.SetDoubleValue("EngineGeneral", "InstallStatus", 0);
	ini.SetBoolValue("EngineGeneral", "SourceBuild", v_BuiltFromSource);
	if(temp_errorCheck < 0) return;
	
	temp_errorCheck = ini.Save(temp_test);
	if(temp_errorCheck < 0) return;
	
	temp_errorCheck = ini.SaveFile(iniFileDir.c_str());
	if(temp_errorCheck < 0) return;

	// Run setup:
	EngineBlockSetup();
} // END - Engine Block Constructor

EngineBlock::EngineBlock(string p_SettingsFileDir){
	// Engine Block Constructor: Sets up an engine block from a saved file
	CSimpleIniCaseA ini;
	SI_Error temp_errorCheck = ini.LoadFile(p_SettingsFileDir.c_str());
	if(temp_errorCheck < 0) return;
	
	v_EngineInstallDir = ini.GetValue("EngineGeneral", "EngineDir", NULL);
	v_EngineSourceDir = ini.GetValue("EngineGeneral", "SourceDir", NULL);
	v_DisplayedEngineLabel.set_label(ini.GetValue("EngineGeneral", "Label", "LABELNOTSET"));
	v_EngineLabel = v_DisplayedEngineLabel.get_text();
	v_gitCommit = ini.GetValue("EngineGeneral", "GitCommit", NULL); //Probably change to git thing?
	v_InstallStatus = ini.GetDoubleValue("EngineGeneral", "InstallStatus", 0);
	v_BuiltFromSource = ini.GetBoolValue("Enginegeneral", "SourceBuild", NULL);
	
	// Check image dir value for custom image.
	string imageDir = ini.GetValue("EngineGeneral", "ImageDir", NULL);
	if(imageDir == "" || !checkImageExists(imageDir)){
		img_EngineImage.set("../img/guiElement/engine_image_default.svg");
		img_EngineImage.set(img_EngineImage.get_pixbuf()->scale_simple(300, 175, Gdk::INTERP_BILINEAR));
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
	v_DisplayedEngineLabel.set_valign(Gtk::ALIGN_END);
	v_DisplayedEngineLabel.set_halign(Gtk::ALIGN_END);
	v_DisplayedEngineLabel.set_margin_bottom(13);
	btn_EngineLaunch.set_label("LAUNCH");

	txt_infoBarText.set_hexpand(false);
	txt_infoBarText.set_line_wrap(true);
	txt_infoBarText.set_lines(3);
	txt_infoBarText.set_max_width_chars(1);
	
//	btn_Options.set_label("OPTIONS");

// PROGRESS BARS:
	v_LevelBar.set_mode(Gtk::LEVEL_BAR_MODE_DISCRETE);
	v_LevelBar.set_min_value(0);
	v_LevelBar.set_max_value(3);
	// 0: Not downloaded.
	// 1: Downloaded.
	// 2: Make Ran.
	// 3: Build ran.
	v_LevelBar.set_value(3);

	// Options Menu
	btn_Options.set_menu(v_optionsMenu);
	
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
	
		// Infobar Buttons:
	v_InfoBar.signal_response().connect(sigc::mem_fun(*this, &EngineBlock::InfoBarResponse));
	

// CSS STYLING:
	if(v_EngineSourceDir != ""){ // Check if source directory is set, then change name of the block to correspond. 
		set_name("SourceEngineBlock");
		v_BuiltFromSource = true;
	} else {
		set_name("BinaryEngineBlock");
		v_BuiltFromSource = false;
	} // END: if else.
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
		// CONTINUE...
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
	
} // END - EngineLaunch Btn Clicked.

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
			v_LevelBar.set_value(v_InstallStatus);
		break;
	} // END - Switch.
} // END - Status Check.

// OTHER:
void EngineBlock::DeleteEngine(){
	//bool v_Busy = true;
	
	v_LevelBar.show();
	v_ProgressBar.set_show_text(true);
	v_LevelBar.set_max_value(2);
	v_LevelBar.set_value(0);
	v_ProgressBar.set_ellipsize(Pango::ELLIPSIZE_START);
//	v_ProgressBar.set_pulse_step(0.1);
	
	// Launch then join thread.
	
	thread thread1(&EngineBlock::threadFunction_DeleteEngine, this);
//	thread1.join();
	thread1.detach();
	
} // END - Deletion

void EngineBlock::threadFunction_DeleteEngine(){
//	v_deleteThreadBusy = true;
	struct stat v_statBuff;

// INSTALL DIRECTORY:
	if(!v_EngineInstallDir.empty()){ // If EngineInstallDir string is not empty, check if folder exists (outside deletion)
		// Check if directory exists.
		if(stat(v_EngineInstallDir.c_str(), &v_statBuff) == 0 && S_ISDIR(v_statBuff.st_mode)){
			DeleteEngineDirectory(v_EngineInstallDir);
			v_EngineInstallDir = ""; // MODIFY: Change to write to file.
			v_LevelBar.set_value(1);
		} // END If folder exists on disk.
	}else{ // If string is empty, and folder doesn't exist:
		v_LevelBar.set_value(1);
	}
	
// SOURCE DIRECTORY:
	if(!v_EngineSourceDir.empty()){
		if(stat(v_EngineSourceDir.c_str(), &v_statBuff) == 0 && S_ISDIR(v_statBuff.st_mode)){
			DeleteEngineDirectory(v_EngineSourceDir);
			v_EngineSourceDir = "";
			v_LevelBar.set_value(2);
		} // END - If folder exists on disk.
	}else{
		v_LevelBar.set_value(2);
	}
	v_ProgressBar.set_text("File removal completed.  Removing enigne block");
	v_ProgressBar.set_fraction(1);
	
	
	

	Launcher_EngineTab* v_engineTab = (Launcher_EngineTab*)get_ancestor(GTK_TYPE_GRID);
//	selfReturn = this;
	return v_engineTab->DeleteEngineBlock((EngineBlock*)this);
	
} // END - DeleteEngine ThreadFunction

void EngineBlock::DeleteEngineDirectory(string p_directory){

	DIR *installFolder = opendir(p_directory.c_str());
	struct dirent *next_file;
	char v_filePath[PATH_MAX];
	v_ProgressBar.set_fraction(0);
		
	// Delete all files/dirs.
	while ( (next_file = readdir(installFolder)) != NULL){

		if(strcmp(next_file->d_name, ".") && strcmp(next_file->d_name, "..")){
			sprintf(v_filePath, "%s/%s", p_directory.c_str(), next_file->d_name);
//			snprintf(v_filePath, (size_t)PATH_MAX, "%s/%s", p_directory.c_str(), next_file->d_name);
			// If next file is a directory, call the same function with the new directory.

			if(next_file->d_type == DT_DIR){
				DeleteEngineDirectory(v_filePath);
				cout << v_filePath << "\n";
			} // END - If.

		} // END - If Filename

		// Set next file, update the progress bar text, and remove the file:
		sprintf(v_filePath, "%s/%s", p_directory.c_str(), next_file->d_name);
		v_ProgressBar.set_text(v_filePath);
		std::remove(v_filePath);
		v_ProgressBar.pulse();
	} // END - While loop.
			
	closedir(installFolder);
	std::remove(p_directory.c_str());
	return;
} // END - DeleteEngineDirectory.
