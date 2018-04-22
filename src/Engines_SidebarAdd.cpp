#include <headers/Launcher_Engines.h>

using namespace UnrealatedLauncher;

EngineAdd::EngineAdd(){
	// Grid Settings:
	set_vexpand(true);
	set_row_homogeneous(false);
	set_column_homogeneous(false);
	
//	set_valign(Gtk::ALIGN_CENTER);
	set_margin_start(10);
	set_margin_end(10);
	set_margin_bottom(10);
	set_margin_top(10);
	set_row_spacing(5);
	set_column_spacing(5);
	set_name("EngineTabSidePanel");
	
	// Buttons & ButtonBox:
	v_confirmCancelButtonBox.pack_end(btn_confirm, Gtk::PACK_EXPAND_WIDGET, 0);
	v_confirmCancelButtonBox.pack_start(btn_cancel, Gtk::PACK_EXPAND_WIDGET, 0);
	v_confirmCancelButtonBox.set_layout(Gtk::BUTTONBOX_EXPAND);
	v_confirmCancelButtonBox.set_valign(Gtk::ALIGN_END);
//	v_confirmCancelButtonBox.set_margin_top(40);
	v_confirmCancelButtonBox.set_size_request(-1, 35);
	btn_cancel.set_label("CANCEL");
	btn_confirm.set_label("CONFIRM");
	btn_addExisting.set_label("ADD EXISTING");
	btn_addExisting.set_active(false);
	btn_addExisting.set_size_request(-1, 35);
	btn_confirm.set_sensitive(false);
//	btn_addExisting.set_size_request(-1, 35);
//	btn_addExisting.set_halign(Gtk::ALIGN_CENTER);


	txt_label_sourceExample.set_hexpand();
	txt_label_sourceExample.set_line_wrap();
	txt_label_sourceExample.set_lines(2);
	txt_label_sourceExample.set_max_width_chars(1);
	txt_label_sourceExample.set_size_request(280, -1);
	txt_label_sourceExample.set_ellipsize(Pango::ELLIPSIZE_START);
	
	txt_label_installExample.set_hexpand();
	txt_label_installExample.set_line_wrap();
	txt_label_installExample.set_lines(2);
	txt_label_installExample.set_max_width_chars(1);
	txt_label_installExample.set_size_request(280, -1);
	txt_label_installExample.set_ellipsize(Pango::ELLIPSIZE_START);
	
	
	txt_label_loginStatus.set_hexpand(true);
	txt_label_loginStatus.set_line_wrap(true);
	txt_label_loginStatus.set_lines(2);
	txt_label_loginStatus.set_max_width_chars(1);
	txt_label_loginStatus.set_size_request(280, -1);
	txt_label_loginStatus.set_ellipsize(Pango::ELLIPSIZE_START);
	

	btn_updateLocalRepo.set_label("Update Local Repo");
	btn_gitLogin.set_label("Connect");

	txt_label_selectCommit.set_text("Commit:");
	txt_label_selectCommit.set_halign(Gtk::ALIGN_END);
	
	btn_sourceFolder.set_action(Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
	btn_installFolder.set_action(Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
	txt_label_selectSource.set_text("Source Folder:");
	txt_label_selectSource.set_halign(Gtk::ALIGN_END);
	
	txt_label_selectInstall.set_text("Install Folder:");
	txt_label_selectInstall.set_halign(Gtk::ALIGN_END);
	
	txt_label_engineLabel.set_text("Engine Label:");
	v_engineLabel.set_placeholder_text("engine label...");
	txt_label_engineLabel.set_halign(Gtk::ALIGN_END);

	txt_label_imageLabel.set_label("Custom Image:");
	txt_label_imageLabel.set_halign(Gtk::ALIGN_END);
	
	txt_label_loginUsername.set_text("Git Username:");
	txt_label_loginPassword.set_text("Git Password:");
	
	btn_showBranches.set_halign(Gtk::ALIGN_CENTER);
	btn_showBranches.set_label("Show Branches");
	btn_showCommits.set_halign(Gtk::ALIGN_CENTER);
	btn_showCommits.set_label("Show Commits");
	

	// Signal Handlers
	btn_cancel.signal_clicked().connect(sigc::mem_fun(*this, &EngineAdd::btn_Cancel_clicked));
	btn_addExisting.signal_toggled().connect(sigc::mem_fun(*this, &EngineAdd::btn_addExisting_clicked));
	btn_sourceFolder.signal_selection_changed().connect(sigc::mem_fun(*this, &EngineAdd::btn_sourceFolder_changed));
	btn_installFolder.signal_selection_changed().connect(sigc::mem_fun(*this, &EngineAdd::btn_installFolder_changed));
	v_commitSelector.signal_changed().connect(sigc::mem_fun(*this, &EngineAdd::v_engineSelector_changed));
	v_engineLabel.signal_changed().connect(sigc::mem_fun(*this, &EngineAdd::v_engineLabel_changed));

		// ONLINE:
	btn_updateLocalRepo.signal_clicked().connect(sigc::mem_fun(*this, &EngineAdd::btn_updateLocalRepo_clicked));
	btn_gitLogin.signal_clicked().connect(sigc::mem_fun(*this, &EngineAdd::btn_gitLogin_clicked));
		// LOGIN:
	
	// END - Buttons & ButtonBox
	

	// Login Grid:
	v_loginGrid.set_row_spacing(3);
	v_loginGrid.set_column_spacing(5);
	v_loginGrid.set_row_homogeneous(false);
	v_loginGrid.set_column_homogeneous(false);
		// Attachment:
//	attach(v_loginRevealer, 0, 2, 2, 1);
	v_loginRevealer.add(v_loginGrid);
	v_loginGrid.attach(txt_label_loginUsername, 0, 0, 1, 1);
		txt_label_loginUsername.set_halign(Gtk::ALIGN_END);
	v_loginGrid.attach(btn_login_username, 1, 0, 1, 1);
		btn_login_password.set_input_purpose(Gtk::INPUT_PURPOSE_EMAIL);
		btn_login_username.set_max_length(63);
		btn_login_username.set_tooltip_text("Your GitHub username");

	v_loginGrid.attach(txt_label_loginPassword, 0, 1, 1, 1);
		txt_label_loginPassword.set_halign(Gtk::ALIGN_END);
	v_loginGrid.attach(btn_login_password, 1, 1, 1, 1);
		btn_login_password.set_input_purpose(Gtk::INPUT_PURPOSE_PASSWORD);
		btn_login_password.set_visibility(false);
		btn_login_password.set_max_length(63);
	
	v_loginGrid.attach(btn_gitLogin, 0, 3, 2, 1);
	v_loginGrid.attach(txt_label_loginStatus, 0, 5, 2, 1);
//	v_loginGrid.attach(v_statusProgBar, 0, 6, 2, 1);
	
	
	//Online Grid:
	v_onlineGrid.set_row_spacing(3);
	v_onlineGrid.set_column_spacing(5);
	v_onlineGrid.set_row_homogeneous(false);
	v_onlineGrid.set_column_homogeneous(false);
	v_onlineGrid.set_hexpand(false);
		// Attachment:
	v_onlineRevealer.add(v_onlineGrid);
	// DEFAULT - Show online revealer by default.
	v_onlineRevealer.set_reveal_child(true);
	
	v_onlineGrid.attach(btn_updateLocalRepo, 0, 0, 2, 1);
	v_onlineGrid.attach(v_loginRevealer, 0, 1, 2, 1);
	v_onlineGrid.attach(v_statusProgBar, 0, 2, 2, 1);
	v_statusProgBar.set_hexpand(true);
	v_statusProgBar.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
	v_statusProgBar.set_halign(Gtk::ALIGN_CENTER);
	v_statusProgBar.set_fraction(1);
	v_statusProgBar.set_size_request(325, -1);
	v_statusProgBar.set_fraction(0);
	v_statusProgBar.set_show_text(true);
	v_statusProgBar.set_ellipsize(Pango::ELLIPSIZE_END);
	
	
	v_commitTypeRadioButtonBox.pack_start(btn_showBranches, Gtk::BUTTONBOX_CENTER, true, 0);
	v_commitTypeRadioButtonBox.pack_end(btn_showCommits, Gtk::BUTTONBOX_CENTER, true, 0);
	btn_showCommits.join_group(btn_showBranches);
	v_onlineGrid.attach(v_commitTypeRadioButtonBox, 0, 3, 2, 1);

// COMMIT SELECTOR:
	v_onlineGrid.attach(txt_label_version, 0, 4, 1, 1);
		txt_label_version.set_text("Select Commit:");
		txt_label_version.set_halign(Gtk::ALIGN_END);
	v_onlineGrid.attach(v_commitSelector, 1, 4, 1, 1);
		


		v_commitSelector.set_hexpand(true);
//		v_commitSelector.set_size_request(200, -1);
//		v_commitSelector.set_wrap_width(1); // Moved to Ini section below.
		v_commitSelector.set_button_sensitivity(Gtk::SENSITIVITY_AUTO);


	
	// Image chooser filter:
	btn_customImageChooser.set_action(Gtk::FILE_CHOOSER_ACTION_OPEN);
	auto v_imageFilter = Gtk::FileFilter::create();
	v_imageFilter->add_pixbuf_formats();
	btn_customImageChooser.set_filter(v_imageFilter);


// ATTACHMENT:
	attach(btn_addExisting, 0, 0, 2, 1);
	btn_addExisting.set_margin_bottom(15);
	
	
//	attach(btn_updateLocalRepo, 0, 1, 2, 1);
	attach(v_onlineRevealer, 0, 1, 2, 1);
	
//	attach(widget, lef, top, Wid, Hei);
	Gtk::Separator *v_addSeparator0 = Gtk::manage(new Gtk::Separator(Gtk::ORIENTATION_HORIZONTAL));
	v_addSeparator0->set_margin_top(5);
	v_addSeparator0->set_margin_bottom(20);
	attach(*v_addSeparator0, 0, 3, 3, 1);
	

	attach(txt_label_selectInstall, 0, 4, 1, 1);
	attach(btn_installFolder, 1, 4, 1, 1);
	attach(txt_label_installExample, 0, 5, 2, 1);
	txt_label_installExample.set_margin_bottom(20);
	txt_label_installExample.set_name("DULLEDTEXT");
	
	attach(txt_label_selectSource, 0, 6, 1, 1);
	attach(btn_sourceFolder, 1, 6, 1, 1);
	attach(txt_label_sourceExample, 0, 7, 2, 1);
	txt_label_sourceExample.set_margin_bottom(20);
	txt_label_sourceExample.set_name("DULLEDTEXT");

	attach(v_engineLabel, 1, 8, 1, 1);
	attach(txt_label_engineLabel, 0, 8, 1, 1);
	attach(txt_label_engineLabelStatus, 0, 9, 2, 1);
	txt_label_engineLabelStatus.set_margin_bottom(20);
	
	attach(txt_label_imageLabel, 0, 10, 1, 1);
	attach(btn_customImageChooser, 1, 10, 1, 1);



	Gtk::Separator *v_addSeparator1 = Gtk::manage(new Gtk::Separator(Gtk::ORIENTATION_HORIZONTAL));
	v_addSeparator1->set_margin_top(40);
	attach(*v_addSeparator1, 0, 11, 2, 1);
	attach(v_confirmCancelButtonBox, 0, 15, 2, 1);
	
	show_all();
	
	
	// Set file choosers to show default folders.
	CSimpleIniCaseA ini;
	string iniFileDir = "./config/UnrealatedLauncher.ini";
	SI_Error temp_errorCheck = ini.LoadFile(iniFileDir.c_str());
	if(temp_errorCheck != 0)return;
	btn_installFolder.set_filename(ini.GetValue("Engines", "defaultInstallDir"));
	btn_sourceFolder.set_filename(ini.GetValue("Engines", "defaultSourceDir"));
	v_maxCommits = ini.GetDoubleValue("Engines", "maxCommits");
	v_commitSelector.set_wrap_width(ini.GetDoubleValue("Engines", "commitWrap"));

} // END - Constructor.

EngineAdd::~EngineAdd(){
}


void EngineAdd::CheckCanConfirm(){
	// Set sensitive to false.
	btn_confirm.set_sensitive(false);
		
	// Perform checks, if any are true; return from the function.
	if((!btn_addExisting.get_active()) && v_commitSelector.get_active_text().empty()) return;
	
	if(btn_installFolder.get_uri() == btn_sourceFolder.get_uri() || btn_sourceFolder.get_uri() == btn_installFolder.get_uri()) return;
	
	if(btn_installFolder.get_uri().empty()) return;
	if((!btn_addExisting.get_active()) && btn_sourceFolder.get_uri().empty()) return;
	if(utility_checkDirectories(utility_RemoveFileFromString(btn_installFolder.get_uri())) != 0) return;
	if(utility_checkDirectories(utility_RemoveFileFromString(btn_sourceFolder.get_uri())) != 0) return;
	if(v_engineLabel.get_text().empty()) return;
	
	// If all checks return false, allow "Confirm" to be clicked.
	btn_confirm.set_sensitive(true);
}

void EngineAdd::v_engineSelector_changed(){
		auto v_cellRenderer = (Gtk::CellRendererText*)v_commitSelector.get_first_cell();
		v_cellRenderer->property_width_chars() = 1;
		v_cellRenderer->property_ellipsize() = Pango::ELLIPSIZE_END;
		v_cellRenderer->set_fixed_size(200, -1);
		
//		vector<Gtk::CellRendererText*>v_cellRendererArray = ((Gtk::CellRendererText*)v_commitSelector.get_cells();
//		cout << (Gtk::CellRendererText*)v_commitSelector.get_cells().size() << endl;
//		auto v_cellRenderer1 = (Gtk::CellRendererText*)v_commitSelector.get_cells()[1];
//		v_cellRenderer1->set_fixed_size(-1, -1);
	CheckCanConfirm();
} // END - Engine Selector Changed.

void EngineAdd::btn_Cancel_clicked(){
	cout << "OPERATION CANCELED!" << endl;
	// Reset all values...
	CSimpleIniCaseA ini;
	string iniFileDir = "./config/UnrealatedLauncher.ini";
	SI_Error temp_errorCheck = ini.LoadFile(iniFileDir.c_str());
	if(temp_errorCheck != 0)return;
	btn_installFolder.set_filename(ini.GetValue("Engines", "defaultInstallDir"));
	btn_sourceFolder.set_filename(ini.GetValue("Engines", "defaultSourceDir"));
	v_commitSelector.set_wrap_width(ini.GetDoubleValue("Engines", "commitWrap"));
	
// Add existing:
	btn_addExisting.set_active(false);

// Engine List:
	v_commitSelector.set_active(-1);
//	v_commitSelector.remove_all();
//	btn_connect.show();
	v_statusProgBar.set_fraction(0);
	
// labels:
	v_engineLabel.set_text("");
	txt_label_sourceExample.set_text("");
	txt_label_installExample.set_text("");

	// Close bar:
	v_tabReference->CloseAddWizard();
	
	if(gitInitialised){
		cout << "Shutting down Libgit 2.  Status:" <<  git_libgit2_shutdown() << endl;
		gitInitialised = false;
	}
}

void EngineAdd::btn_Confirm_clicked(){
	cout << "ADD ENGINE!" << endl;
	v_tabReference->CloseAddWizard();
}

void EngineAdd::btn_gitLogin_clicked(){
	login_username = btn_login_username.get_text();
	login_password = btn_login_password.get_text();
	v_loginRevealer.set_reveal_child(false);
	v_waitingOnLogin_conditionVar.notify_one();

	CSimpleIniCaseA ini;
	string iniFileDir = "./config/UnrealatedLauncher.ini";
	SI_Error temp_errorCheck = ini.LoadFile(iniFileDir.c_str());
	if(temp_errorCheck == 0){ v_maxCommits = ini.GetDoubleValue("Engines", "maxCommits"); }
	
	// Set button sensitive to false while function is working; add page task.
	btn_updateLocalRepo.set_sensitive(false);

	// Prevent user from clicking on modifying buttons:
	btn_addExisting.set_sensitive(false);
	btn_cancel.set_sensitive(false);
	btn_confirm.set_sensitive(false);

	cout << "Clearing old lists, UI may hang momentarily." << endl;
	v_mutex_commits.lock();
	// Clear current selections:
	v_commitSelector.remove_all();
	v_mutex_commits.unlock();
	
	thread updateRepoThread(&EngineAdd::threadFunction_updateLocalRepo, this);
	updateRepoThread.detach();
	
	// Monitors the Busy bool and changes the button sensitivity.
	v_OnlineThreadBusy = true;
	v_tabReference->SetPageTaskPercent(0);
	// Add task counter to page.
	v_tabReference->AddPageTask();
	Glib::signal_timeout().connect(sigc::mem_fun(*this, &EngineAdd::MonitorActivity), 50);
}

void EngineAdd::btn_addExisting_clicked(){
	
	v_onlineRevealer.set_reveal_child(!btn_addExisting.get_active());

	// If engine selector has been used:
	if(v_commitSelector.get_active_row_number() == -1){
		v_statusProgBar.set_fraction(0);
//		btn_gitLogin.set_visible(!btn_addExisting.get_active());
	}else{
		v_statusProgBar.set_fraction(0);
//		btn_gitLogin.set_visible(false);
	}
	
	CheckCanConfirm();
}

void EngineAdd::btn_sourceFolder_changed(){
	char resolvedSourceFolder[PATH_MAX];
	string temp_selectedSourceFolder = "...";
	if(!btn_sourceFolder.get_uri().empty()){
		temp_selectedSourceFolder = realpath( utility_RemoveFileFromString(btn_sourceFolder.get_uri()).c_str(), resolvedSourceFolder);
		switch(utility_checkDirectories(resolvedSourceFolder)){
		case 0:
			txt_label_sourceExample.set_text(resolvedSourceFolder);
			break;
			
		case 1:
			txt_label_sourceExample.set_markup("<span fgcolor='red'><b>You have chosen another engines Install Directory!</b></span>");
			break;
			
		case 2:
			txt_label_sourceExample.set_markup("<span fgcolor='red'><b>You have chosen another engines Source Directory!</b></span>");
			break;
		} // END - Switch
	} // END - IF button is not empty.
	
		if(btn_sourceFolder.get_uri() == btn_installFolder.get_uri() ){
			txt_label_sourceExample.set_markup("<span fgcolor='yellow'><b>Source Directory can not be the same as Install Directory!</b></span>");
		}
	CheckCanConfirm();
} // END - Source Folder Changed.

void EngineAdd::btn_installFolder_changed(){
	char resolvedInstallFolder[PATH_MAX];
	string temp_selectedInstallFolder = "...";
	if(!btn_installFolder.get_uri().empty()){
		temp_selectedInstallFolder = realpath( utility_RemoveFileFromString(btn_installFolder.get_uri()).c_str(), resolvedInstallFolder);
		switch(utility_checkDirectories(resolvedInstallFolder)){
			case 0:
				txt_label_installExample.set_text(resolvedInstallFolder);
				break;
 
			case 1:
				txt_label_installExample.set_markup("<span fgcolor='red'><b>You have chosen another engines Install Directory!</b></span>");
				break;
 
			case 2:
				txt_label_installExample.set_markup("<span fgcolor='red'><b>You have chosen another engines Source Directory!</b></span>");
				break;
		} // END - Switch
	} // END - If Button is not empty

	if(btn_installFolder.get_uri() == btn_sourceFolder.get_uri()){
		txt_label_installExample.set_markup("<span fgcolor='yellow'><b>Install Directory can not be the same as Source Directory!</b></span>");
	}
	CheckCanConfirm();
}

void EngineAdd::v_engineLabel_changed(){
	txt_label_engineLabelStatus.set_text("");
	
	// Append label to end of install path:
	char resolvedInstallFolder[PATH_MAX];
	string temp_selectedFolder = "";
	string temp_exampleText = txt_label_sourceExample.get_text() + v_engineLabel.get_text();
	
	temp_selectedFolder = realpath( utility_RemoveFileFromString(btn_installFolder.get_uri()).c_str(), resolvedInstallFolder);
	
	temp_exampleText = temp_selectedFolder +"/" + v_engineLabel.get_text().c_str();
	txt_label_installExample.set_text(temp_exampleText);
	
	temp_selectedFolder = realpath( utility_RemoveFileFromString(btn_sourceFolder.get_uri()).c_str(), resolvedInstallFolder);
	
	temp_exampleText = temp_selectedFolder +"/" + v_engineLabel.get_text().c_str();
	txt_label_sourceExample.set_text(temp_exampleText);
	
	CheckCanConfirm();

	for(int index = 0; index < static_cast<int>(v_tabReference->v_EngineBlockArray.size()); index++){
		if(v_tabReference->v_EngineBlockArray[index]->v_EngineLabel == v_engineLabel.get_text().c_str()){
				txt_label_engineLabelStatus.set_markup("<span fgcolor='red'><b>Label already used</b></span>");
		}
	}
}



void EngineAdd::btn_updateLocalRepo_clicked(){
	v_loginRevealer.set_reveal_child(true);
} // END - Update local repo clicked.


bool EngineAdd::MonitorActivity(){
	if(!v_OnlineThreadBusy){
		// Online thread is no longer busy.
		Glib::signal_idle().connect(sigc::mem_fun(*this, &EngineAdd::updateLocalRepo_finalStep));
		return false; // Return false to end timeout.

	} else { 
		// Online Thread Busy!
		
		if(v_mutex_waitingOnLogin.try_lock()){
			v_loginRevealer.set_reveal_child(v_waitingOnLogin);
		}
	
	if(v_mutex_progress.try_lock()){
			v_statusProgBar.set_text(v_statusProgBar_text);
		if(v_statusProgBar_progress == 0){
			v_statusProgBar.pulse();
		}else{
			v_statusProgBar.set_fraction(v_statusProgBar_progress);
		}
	} // END - If mutex lock.
	v_mutex_progress.unlock();
		return true;
	} // END - else
} // END - Monitor Activity.


bool EngineAdd::updateLocalRepo_finalStep(){
		
		if(!vec_commitComment[v_currentCommitIndex].empty() && v_currentCommitIndex < v_maxCommits){
//			v_tabReference->AddPageTask();
			
			Glib::ustring temp_text = "[" + to_string(v_currentCommitIndex +1) + "] " + vec_commitComment[v_currentCommitIndex];
			
			v_commitSelector.append(temp_text);

			// Temp values; for updating GUI
			temp_text = "Processing Commits | " + vec_commitComment[v_currentCommitIndex];
			double temp_progBarProgress = double(v_currentCommitIndex) / v_maxCommits;
//			cout << "Commit: " << temp_progBarText << " | " << temp_progBarProgress << "%" << endl;
			
			v_statusProgBar.set_fraction(temp_progBarProgress);
			v_statusProgBar.set_text(temp_text);
			updateLocalRepo_updatePageBar(temp_progBarProgress);
			
			v_currentCommitIndex++;
			
			return true;
		}else{
			v_tabReference->RemovePageTask();

			// Get progress bar text for final time:
			v_statusProgBar.set_text(v_statusProgBar_text);
			
			// Return button sensitivities:
			btn_updateLocalRepo.set_sensitive(true);
			v_statusProgBar.set_fraction(0);
			
			btn_addExisting.set_sensitive(true);
			btn_cancel.set_sensitive(true);
			
			v_OnlineThreadBusy = false;
			cout << "Page Tasks: " << v_tabReference->GetPageTasks() << endl;
			CheckCanConfirm();
			
			// Reset Index:
			v_currentCommitIndex = 0;
			
			return false;
		}
//	} // END - For Loop.
	return false;

} // END - UpdateCommitSelector :: Timeout

//												 UPDATE LOCAL REPO NONMEMBER FUNCTIONS
int updateLocalRepo_fetchProgress(const git_transfer_progress *stats, void *payload){
	int fetch_percent = (100 * stats->received_objects) / stats->total_objects;
	double fetch_percentAsDouble = double(stats->received_objects) / stats->total_objects;
	
	int fetch_index = (100 * stats->indexed_objects) / stats->total_objects;
	double fetch_indexAsDouble = double(stats->indexed_objects) / stats->total_objects;
	
	Glib::ustring temp_progressBarText = "";
	
//	cout << "fetch: " << fetch_percent << "  double: " << fetch_percentAsDouble << endl;

	if(fetch_percent == 100){
		// Indexing in progress...
		temp_progressBarText = "Indexing... " + to_string(fetch_index) + "% completed.";

		((EngineAdd*)payload)->updateLocalRepo_updateProgbar(temp_progressBarText, fetch_indexAsDouble);
		((EngineAdd*)payload)->updateLocalRepo_updatePageBar(fetch_indexAsDouble);
	} else{
		// Cloning in progress...
		temp_progressBarText = "Downloading... " + to_string(fetch_percent) + "% completed.";

		((EngineAdd*)payload)->updateLocalRepo_updateProgbar(temp_progressBarText, fetch_percentAsDouble);
		((EngineAdd*)payload)->updateLocalRepo_updatePageBar(fetch_percentAsDouble);
	}

	return 0;
} // END - Fetch progress for UpdateLocalRepo.

void updateLocalRepo_checkoutProgress(const char *path, size_t completed_steps, size_t total_steps, void *payload){
	if(total_steps > 0){
		int v_checkoutPercent = (100 * completed_steps) / total_steps;
		double v_checkoutPercentAsDouble = double(completed_steps) / total_steps;
		Glib::ustring temp_progressBarText = "Downloading... " + to_string(v_checkoutPercent) + "% completed.";
		((EngineAdd*)payload)->updateLocalRepo_updateProgbar(temp_progressBarText, v_checkoutPercentAsDouble);
		((EngineAdd*)payload)->updateLocalRepo_updatePageBar(v_checkoutPercentAsDouble);
	} // END - If steps is higher than 0.
	else{
		((EngineAdd*)payload)->updateLocalRepo_updateProgbar("Checkout Completed", 1);
	}
} // END - Checkout Progress.

int updateLocalRepo_getCredentials(git_cred **out, const char *url, const char *username_from_url, unsigned int allowed_types, void *payload){
	char *userName = NULL, *userPassword = NULL;
	cout << "cred callback called" << endl;
	// Check if file with credentials exists
	
	// files don't exist
//	updateLocalRepo_setWaitingOnLogin(true);
//	while(updateLocalRepo_getWaitingOnLogin)
{
		std::unique_lock<std::mutex>getCred_Lock( ((EngineAdd*)payload)->v_mutex_waitingOnLogin);
		((EngineAdd*)payload)->v_waitingOnLogin = true;
		((EngineAdd*)payload)->v_waitingOnLogin_conditionVar.wait(getCred_Lock);
}		
		*userName = ((EngineAdd*)payload)->updateLocalRepo_getLoginUsername();
		*userPassword = ((EngineAdd*)payload)->updateLocalRepo_getLoginUserpass();
		
	int error = git_cred_userpass_plaintext_new(out, userName, userPassword);
//	int error = git_cred_ssh_key_new(out, )
	return error;
}


void EngineAdd::threadFunction_updateLocalRepo(){
	// Reserve space in vectors:
	vec_commitComment.reserve(1000);
	vec_commitIDs.reserve(1000);
	
	
	// Testing:
//	v_loginRevealer.set_reveal_child(true);
	
	// Get variables from Ini:
	CSimpleIniCaseA ini;
	SI_Error temp_errorCheck = ini.LoadFile("./config/UnrealatedLauncher.ini");
		if(temp_errorCheck != 0)return;
	char v_launcherRepoPathAbsolute[PATH_MAX];
	v_launcherRepoPath = realpath(ini.GetValue("Engines", "launcherRepo"), v_launcherRepoPathAbsolute);

		cout << "-----------------------------------------" << endl << "UPDATING LOCAL REPO..." << endl << endl;

	// INITIALISE GIT:
	cerr << "Initialising libgit2 Library..." << endl;
	updateLocalRepo_updateProgbar("Initialising Libgit2 Library.", 0);
	
	if(git_libgit2_init() < 0){
		status_onlineTaskFailed("	Failed to initialise Libgit2.", "Libgit 2 Init failed.  Check Library Status!");
		return;
	} // END - Libgit2 Init check.
	
	gitInitialised = true;
		cout << "	Libgit 2 initialised." << endl;
	
// VARIABLES:
	git_repository *v_repo = NULL;
	git_remote *v_remoteRepo = NULL;
	git_annotated_commit *v_mergeHead[1];
	git_clone_options v_cloneOpts = GIT_CLONE_OPTIONS_INIT;
	git_fetch_options v_fetchOpts = GIT_FETCH_OPTIONS_INIT;
	git_merge_options v_mergeOpts = GIT_MERGE_OPTIONS_INIT;
	git_checkout_options v_checkoutOpts = GIT_CHECKOUT_OPTIONS_INIT;
	git_cred *v_loginCredentials;
//	int error = git_cred_userpass_plaintext_new(&v_loginCredentials, login_username, login_password);
	

// OPTIONS:
	v_cloneOpts.fetch_opts.callbacks.transfer_progress = updateLocalRepo_fetchProgress;
	v_cloneOpts.fetch_opts.callbacks.payload = this;
//	v_cloneOpts.fetch_opts.callbacks.credentials = updateLocalRepo_getCredentials;
	
	v_fetchOpts.callbacks.transfer_progress = updateLocalRepo_fetchProgress;
	v_fetchOpts.callbacks.payload = this;
	v_fetchOpts.download_tags = GIT_REMOTE_DOWNLOAD_TAGS_ALL;
	
	v_mergeOpts.file_favor = GIT_MERGE_FILE_FAVOR_THEIRS;
	
	v_checkoutOpts.progress_cb = updateLocalRepo_checkoutProgress;
	v_checkoutOpts.progress_payload = this;
	v_checkoutOpts.checkout_strategy = GIT_CHECKOUT_FORCE;
	

	cout << "Opening launcher repository..." << endl;
	updateLocalRepo_updateProgbar("Opening Launcher Repository.", 0);
	
	// Check if repo exists:
	if(git_repository_open(&v_repo, v_launcherRepoPath.c_str()) < 0){
			cerr << "	Launcher Repository not found; attempting clone..." << endl;
		updateLocalRepo_updateProgbar("Launcher Repository not found.  Attempting clone...", 0);
		// REPO DOESN'T EXIST
		
		// Create Credentials:
		
		
		// Attempt Clone:
		if(git_clone(&v_repo, REPO_PATH, v_launcherRepoPath.c_str(), &v_cloneOpts) < 0){
			status_onlineTaskFailed("	Failed to clone repo!", "Cloning Failed: Ensure your Git and Epic accounts are connected!");
			updateLocalRepo_updateProgbar("Unable to connect. See terminal for more information.", 0);
			return;
		} // END - Git Clone
		
	updateLocalRepo_updateProgbar("Clone completed", 0);
//		goto LABEL_UpdateLists; // Skips the Fetch process.  Remove? (User closes window before download completes; .git folder is present.
	} // END Repo Open
	
		cout << "	Launcher Repo opened." << endl;
		
		cout << "Attempting remote lookup..." << endl;
			updateLocalRepo_updateProgbar("Looking up remote.", 0);
		if(git_remote_lookup(&v_remoteRepo, v_repo, "origin") < 0){
			status_onlineTaskFailed("	Online Repository not found!", "Failed to find remote repository. \nCheck: Git and Epic accounts are connected! Check: You have an internet connection");
			return;
		} // END remote lookup Check.



		cout << "	Remote Found." << endl << "Attempting Fetch..." << endl;
		updateLocalRepo_updateProgbar("Fetching updates...", 0);
		if(git_remote_fetch(v_remoteRepo, NULL, &v_fetchOpts, "NULL") < 0){
			status_onlineTaskFailed("	Failed to Fetch updates!", "Failed to Fetch updates. See GitError.");
			return;
		} // END - Remote Fetch



// Repo, git_annotated_commit; heads to merge into.  size_t number of heads to merge, merge opts, checkout opts.

		const git_remote_head **head = NULL;
		size_t headCount = 0;
		
		cout << "	Looking up remotes..." << endl;
		updateLocalRepo_updateProgbar("Looking up remotes heads.", 0);
		if(git_remote_ls(&head, &headCount, v_remoteRepo) < 0){
			status_onlineTaskFailed("Failed to lookup remote.", "Failed to lookup remote heads. See GitError");
			return;
		} // END - remote LS, heads.
		
		git_oid objectID = head[0]->oid;
		
		cout << "	Getting commits..." << endl;
		updateLocalRepo_updateProgbar("Obtaining object IDs for merge...", 0);
		if(git_annotated_commit_lookup(&v_mergeHead[0], v_repo, &objectID) < 0){
			status_onlineTaskFailed("Merge from Fetchhead failed", "Failed to obtain object ID for merge.");
			return;
		} // END merge head from fetchhead.

		cout << "	Fetch completed." << endl << "Attempting Merge..." << endl;
		updateLocalRepo_updateProgbar("Attempting merge...", 0);
		if(git_merge(v_repo, (const git_annotated_commit **)(&v_mergeHead), 1, &v_mergeOpts, &v_checkoutOpts) < 0){
			status_onlineTaskFailed("Merge Failed.", "Failed to merge; see git error for more info:");
			return;
		} // END - Fetch.
		cout << "	Merge Successful!" << endl;
		
//	LABEL_UpdateLists:
		// UPDATE LISTS.
		git_revwalk *v_repoWalker = nullptr;
		git_revwalk_new(&v_repoWalker, v_repo);
		
		git_revwalk_push_head(v_repoWalker);
		
//		objectID = nullptr_t;
		Glib::ustring temp_commitProgressString = "";
		
		
		// START OF MUTEX LOCK
		v_mutex_commits.lock();
		
		cout << "Clearing old lists..." << endl;
		vec_commitIDs.clear();
		vec_commitComment.clear();
		
		cout << "Processing Commits: " << endl;
			updateLocalRepo_updateProgbar("Processing Commits...", 0);
// Populate Commits:
		while(!git_revwalk_next(&objectID, v_repoWalker)){
			git_commit *temp_commit = nullptr;
			
			git_commit_lookup(&temp_commit, v_repo, &objectID);
			
//			string temp_commitSummary = git_commit_summary(temp_commit);
//			temp_commitProgressString = "Processing Commits | " + temp_commitSummary;

			vec_commitIDs.push_back(git_oid_tostr_s(&objectID));
			vec_commitComment.push_back(git_commit_summary(temp_commit));

			git_commit_free(temp_commit);
			
		} // END - While loop.
//		updateLocalRepo_UpdateCommitSelector(ini.GetDoubleValue("Engines", "maxCommits"));
		
		
		v_mutex_commits.unlock();

		// Cleanup:
		git_repository_free(v_repo);
		git_remote_free(v_remoteRepo);

		cout << endl << "LOCAL REPOSITORY UPDATED." << endl;
		updateLocalRepo_updateProgbar("Local Repository Updated!", 0);
		v_OnlineThreadBusy = false;
		
		if(git_libgit2_shutdown() < 0){
			status_onlineTaskFailed("Failed to shutdown git.", "Failed to shutdown Libgit.");
			return;
		}
		gitInitialised = false;
		cout << "	Libgit 2 Shut down." << endl;

} // END - Thread Function.