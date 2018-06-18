#include <headers/Launcher_Engines.h>

using namespace UnrealatedLauncher;
using namespace LauncherUtility;

EngineAdd::EngineAdd():

// Sections:
	section_initial_frame("Initial options:"),
	section_commits_frame("Select the commit (version):"),
	section_directories_frame("Install directories & label:"),
	section_labelAndImage_frame("Engine Label & Custom Image:"),
	section_confirm_frame("Confirm:"),

// Toggle/Radio Buttons:
	btn_toggle_showTags("Show Tagged Commits"),
	btn_toggle_showCommits("Show Commits"),
	
// Check buttons:
	btn_addExisting("Add Existing Engine"),
	btn_showCommitsAfterTaggedCommit("Show commits after tagged commit*"),
	btn_appendLabelToInstallDir("Append label to install directory"),
	btn_makeCopyOfImage("Make copy of image"),
	btn_startInstallAfterFinished("Start Install after finishing."),
	btn_chooser_codeEditor("text/plain"),
	
// Buttons:
	btn_cancel("Cancel"),
	btn_confirm("Confirm"),
	btn_manageLauncherRepo("Manage Launcher Repository"),
	btn_initial_updateLists("Refresh Lists"),
	
// Labels:
	txt_chooser_taggedCommits("Tagged Commit:"),
	txt_chooser_commits("Commit:"),
	txt_chooser_installFolder("Install Folder:"),
	txt_chooser_customImage("Custom Image:"),
	txt_chooser_codeEditor("Code Editor:"),

// Confirm:
	txt_confirm_commit_label("Commit:"),
	txt_confirm_installFolder_label("Install Dir:"),
	txt_confirm_codeEditor_label("Code Editor:")

{		 // EngineAdd:Constructor

	// Grid Settings:
	set_vexpand(false);
	set_row_homogeneous(false);
	set_column_homogeneous(false);
	set_margin_start(5);
	set_margin_end(5);
	set_margin_bottom(10);
	set_margin_top(10);
	set_row_spacing(20);
	set_column_spacing(2);
	set_name("EngineTabSidePanel");

	// Initial Section:
	section_initial_frame.add(section_initial);
	section_initial_frame.set_label_align(Gtk::ALIGN_CENTER);
	attach(section_initial_frame, 0, 0, 1, 1);
	LauncherUtility_setGridSettings(&section_initial);

	
	section_initial.attach(btn_addExisting, 0, 0, 1, 1);
	btn_addExisting.set_tooltip_text("Check if adding an existing engine.");
	
	btn_addExisting.signal_clicked().connect(sigc::mem_fun(*this, &EngineAdd::btn_addExisting_changed));

	section_initial.attach(btn_startInstallAfterFinished, 0, 1, 1, 1);
	btn_startInstallAfterFinished.set_tooltip_text("If checked, the install process will start immediately after pressing CONFIRM.");

	// Commits Section:
	section_commits_frame.add(section_commits);
	section_commits_frame.set_label_align(Gtk::ALIGN_CENTER);
	v_revealer_online.add(section_commits_frame);
	attach(v_revealer_online, 0, 1, 1, 1);
	LauncherUtility_setGridSettings(&section_commits);
	
	section_commits.attach(commits_toggleGrid, 0, -1, 2, 1);
	
	commits_toggleGrid.attach(btn_toggle_showTags, 0, 0, 1, 1);
		btn_toggle_showTags.set_tooltip_text("Click to use tagged commit selection.");
	commits_toggleGrid.attach(btn_toggle_showCommits, 1, 0, 1, 1);
		btn_toggle_showCommits.set_tooltip_text("Click to use commit selection.");
		btn_toggle_showCommits.join_group(btn_toggle_showTags);

	section_commits.attach(txt_chooser_taggedCommits, 0, 1, 1, 1);
		txt_chooser_taggedCommits.set_halign(Gtk::ALIGN_START);
	section_commits.attach(btn_taggedCommitSelector, 1, 1, 1, 1);
		btn_taggedCommitSelector.set_tooltip_text("Use to choose the tagged commit which the new engine will be built from. \nNOTE: If 'Show Commit From Branch' is enabled, changing the branch may cause a temporary UI freeze while the Commits are processed.");
		btn_taggedCommitSelector.set_hexpand(false);
		btn_taggedCommitSelector.set_button_sensitivity(Gtk::SENSITIVITY_AUTO);
		btn_taggedCommitSelector.signal_changed().connect(sigc::mem_fun(*this, &EngineAdd::btn_taggedCommitSelector_changed));

	section_commits.attach(txt_chooser_commits, 0, 2, 1, 1);
		txt_chooser_commits.set_halign(Gtk::ALIGN_START);
	section_commits.attach(btn_commitSelector, 1, 2, 1, 1);
//		btn_commitSelector.set_size_request(175, -1);
		btn_commitSelector.set_tooltip_text("Use to choose the commit which the new engine will be built from.");
		btn_commitSelector.set_hexpand(true);
		btn_commitSelector.set_button_sensitivity(Gtk::SENSITIVITY_AUTO);
		btn_commitSelector.signal_changed().connect(sigc::mem_fun(*this, &EngineAdd::btn_selectorChanged));
		
	section_commits.attach(btn_showCommitsAfterTaggedCommit, 0, 3, 2, 1);
		btn_showCommitsAfterTaggedCommit.set_tooltip_text("If checked, the commit selector will show commits reverse chronologically after the chosen tagged commit.\n*THIS IS CURRENTLY IN REVERSE, AND SHOWS COMMITS -BEFORE- THE TAGGED COMMIT!");



	Gtk::Separator *section_commits_seperator = Gtk::manage(new Gtk::Separator(Gtk::ORIENTATION_HORIZONTAL));
	section_commits_seperator->set_margin_top(2);
	section_commits_seperator->set_margin_bottom(5);
	section_commits_seperator->set_hexpand(true);
	section_commits.attach(*section_commits_seperator, 0, 4, 2, 1);
		btn_manageLauncherRepo.signal_clicked().connect(sigc::mem_fun(*this, &EngineAdd::btn_manageLauncherRepo_clicked));
	
	section_commits.attach(btn_initial_updateLists, 0, 5, 2, 1);
		btn_initial_updateLists.set_tooltip_text("Refreshes the commit selectors.");
	section_commits.attach(btn_manageLauncherRepo, 0, 6, 2, 1);
		btn_manageLauncherRepo.set_tooltip_text("Opens the repo management settings.");
	
		
	btn_toggle_showTags.signal_clicked().connect(sigc::mem_fun(*this, &EngineAdd::btn_toggle_showCommitsFilter));
	btn_toggle_showTags.set_tooltip_text("Show tagged commits. \nTagged Commits are git commits which Epic have tagged.\n\nUse this if you're unfamiliar with Git/Commits.");
	btn_toggle_showCommits.signal_clicked().connect(sigc::mem_fun(*this, &EngineAdd::btn_toggle_showCommitsFilter));
	btn_toggle_showCommits.set_tooltip_text("Show all commits.\nEnable 'show commits after tagged' to fine tune the selection.");
	btn_showCommitsAfterTaggedCommit.signal_clicked().connect(sigc::mem_fun(*this, &EngineAdd::btn_showCommitsAfterBranch_changed));
	btn_initial_updateLists.signal_clicked().connect(sigc::mem_fun(*this, &EngineAdd::btn_initial_updateLists_clicked));





	// Directory Section:
/*
	section_directories_frame.add(section_directories);
	section_directories_frame.set_label_align(Gtk::ALIGN_CENTER);
	attach(section_directories_frame, 0, 2, 1, 1);
	LauncherUtility_setGridSettings(&section_directories);
	
	section_directories.attach(txt_chooser_codeEditor, 0, -3, 1, 1);
		txt_chooser_codeEditor.set_hexpand(false);
		txt_chooser_codeEditor.set_halign(Gtk::ALIGN_END);
	section_directories.attach(btn_chooser_codeEditor, 1, -3, 1, 1);
		btn_chooser_codeEditor.set_hexpand(true);
//		btn_chooser_codeEditor.set_halign(Gtk::ALIGN_START);
		btn_chooser_codeEditor.set_show_dialog_item(true);
		btn_chooser_codeEditor.signal_changed().connect(sigc::mem_fun(*this, &EngineAdd::btn_chooser_codeEditor_changed));
*/


	// Label & Custom Image Section
	section_labelAndImage_frame.add(section_labelAndImage);
	section_labelAndImage_frame.set_label_align(Gtk::ALIGN_CENTER);
	attach(section_labelAndImage_frame, 0, 3, 1, 1);
	LauncherUtility_setGridSettings(&section_labelAndImage);
	
	section_labelAndImage.attach(btn_appendLabelToInstallDir, 0, 0, 2, 1);
		btn_appendLabelToInstallDir.set_tooltip_text("If checked, the install folder will be created inside the folder specified, named using the label below.");

	section_labelAndImage.attach(btn_labelEntry, 0, 1, 2, 1);
	btn_labelEntry.set_placeholder_text("Engine Label");
	btn_labelEntry.set_max_length(30);
	btn_labelEntry.set_tooltip_text("The label to be used for the new engine block.\nWARNING: IF LABEL IS BEING APPENDED, THIS MUST NOT INCLUDE ILLEGAL CHARACTERS, OR HAVE SPACES!");
	btn_labelEntry.signal_changed().connect(sigc::mem_fun(*this, &EngineAdd::btn_labelEntry_changed));

	section_labelAndImage.attach(txt_chooser_installFolder, 0, 2, 1, 1);
		txt_chooser_installFolder.set_halign(Gtk::ALIGN_END);
	section_labelAndImage.attach(btn_chooser_installFolder, 1, 2, 1, 1);
		btn_chooser_installFolder.set_action(Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
		btn_chooser_installFolder.set_hexpand();

	
	btn_appendLabelToInstallDir.signal_clicked().connect(sigc::mem_fun(*this, &EngineAdd::btn_appendLabelToInstallDir_changed));
	btn_chooser_installFolder.signal_selection_changed().connect(sigc::mem_fun(*this, &EngineAdd::btn_chooser_installFolder_changed));
	
	
	
	section_labelAndImage.attach(txt_chooser_customImage, 0, 3, 1, 1);
	section_labelAndImage.attach(btn_chooser_customImage, 1, 3, 1, 1);
		btn_chooser_customImage.set_action(Gtk::FILE_CHOOSER_ACTION_OPEN);
		auto btn_chooser_customImage_filter = Gtk::FileFilter::create();
		btn_chooser_customImage_filter->add_pixbuf_formats();
		btn_chooser_customImage.set_filter(btn_chooser_customImage_filter);
		btn_chooser_customImage.set_hexpand(true);
		btn_chooser_customImage.set_tooltip_text("Select a custom image to be used for the engine block.");

	section_labelAndImage.attach(btn_makeCopyOfImage, 0, 4, 2, 1);
		btn_makeCopyOfImage.set_tooltip_text("If checked, the image will be copied to an isolated folder.");



	// Confirmation Section
	section_confirm_frame.add(section_confirm);
	section_confirm_frame.set_label_align(Gtk::ALIGN_CENTER);
	attach(section_confirm_frame, 0, 4, 1, 1);
	LauncherUtility_setGridSettings(&section_confirm);
	
	
	Gtk::Separator *section_confirm_seperator = Gtk::manage(new Gtk::Separator(Gtk::ORIENTATION_HORIZONTAL));
	section_commits_seperator->set_margin_top(2);
	section_commits_seperator->set_margin_bottom(5);
	section_commits_seperator->set_hexpand(true);

	section_confirm.attach(txt_confirm_commit_label, 0, 0, 1, 1);
	section_confirm.attach(txt_confirm_commit, 1, 0, 1, 1);
		SetConfirmTextSettings(&txt_confirm_commit);
		
	section_confirm.attach(txt_confirm_installFolder_label, 0, 1, 1, 1);
	section_confirm.attach(txt_confirm_installFolder, 1, 1, 1, 1);
		SetConfirmTextSettings(&txt_confirm_installFolder);
/*
	section_confirm.attach(txt_confirm_codeEditor_label, 0, 2, 1, 1);
	section_confirm.attach(txt_confirm_codeEditor, 1, 2, 1, 1);
*/
	section_confirm.attach(*section_confirm_seperator, 0, 3, 2, 1);

	section_confirm.attach(txt_confirm_helper, 0, 4, 2, 1);
		txt_confirm_helper.set_halign(Gtk::ALIGN_START);
		txt_confirm_helper.set_hexpand(true);
		txt_confirm_helper.set_line_wrap(true);
		txt_confirm_helper.set_lines(5);
		txt_confirm_helper.set_max_width_chars(1);
		txt_confirm_helper.set_size_request(280, -1);
		
	
	Gtk::ButtonBox *btn_confirmCancelButtonbox = Gtk::manage(new Gtk::ButtonBox(Gtk::ORIENTATION_HORIZONTAL));
	btn_confirmCancelButtonbox->pack_start(btn_cancel, Gtk::PACK_EXPAND_WIDGET, 0);
	btn_confirmCancelButtonbox->pack_start(btn_confirm, Gtk::PACK_EXPAND_WIDGET, 0);
	btn_confirmCancelButtonbox->set_layout(Gtk::BUTTONBOX_EXPAND);
	btn_confirmCancelButtonbox->set_hexpand(true);
	section_confirm.attach(*btn_confirmCancelButtonbox, 0, 10, 2, 1);
	
	btn_cancel.signal_clicked().connect(sigc::mem_fun(*this, &EngineAdd::btn_cancel_clicked));
	btn_confirm.signal_clicked().connect(sigc::mem_fun(*this, &EngineAdd::btn_confirm_clicked));
	
	btn_confirm.set_sensitive(false);
//	EngineAdd_reset();
} // END - Constructor.

EngineAdd::~EngineAdd(){
}

void EngineAdd::EngineAdd_reset(){ // Resets the sidebar.
	// Initial Options:
	btn_addExisting.set_active(false);
	btn_addExisting_changed();
	v_revealer_online.set_reveal_child(true);
	btn_showCommitsAfterTaggedCommit.set_active(false);
	
	btn_labelEntry.set_text("");
	
	btn_appendLabelToInstallDir.set_active(true);
	
	btn_chooser_customImage.unselect_all();
	
	btn_chooser_codeEditor.unset_active();
	
	
	installData.engineLabel = "";
	installData.installDir = "";
	installData.customImage = "";
	installData.commitID = "";

	CSimpleIniCaseA ini;
	string iniFileDir = UnrealatedLauncherGlobal::launcherConfig.c_str();
	SI_Error temp_errorCheck = ini.LoadFile(iniFileDir.c_str());
	if(temp_errorCheck != 0)return;

	// Directories & labels:
	btn_chooser_installFolder.set_filename(ini.GetValue("Engines", "defaultInstallDir"));
	btn_commitSelector.set_wrap_width(ini.GetDoubleValue("Engines", "commitWrap"));
	
	bool temp_showTaggedCommits = ini.GetBoolValue("Engines", "defaultShowTaggedCommits");
		// Show tagged commits or commits by default:
		btn_toggle_showCommits.set_active(!temp_showTaggedCommits);
		btn_toggle_showTags.set_active(temp_showTaggedCommits);
		txt_chooser_taggedCommits.set_visible(temp_showTaggedCommits);
		btn_taggedCommitSelector.set_visible(temp_showTaggedCommits);
		txt_chooser_commits.set_visible(!temp_showTaggedCommits);
		btn_commitSelector.set_visible(!temp_showTaggedCommits);
		btn_showCommitsAfterTaggedCommit.set_visible(!temp_showTaggedCommits);
	
	commits_normalIterations = ini.GetDoubleValue("Engines", "maxCommits");
	commits_taggedIterations = ini.GetDoubleValue("Engines", "maxTaggedCommits");
	
} // END - Reset.


				// BUTTON FUNCTIONS:

void EngineAdd::btn_addExisting_changed(){
	v_revealer_online.set_reveal_child(!btn_addExisting.get_active());
	
	btn_appendLabelToInstallDir.set_visible(!btn_addExisting.get_active());
	txt_confirm_commit.set_visible(!btn_addExisting.get_active());
	txt_confirm_commit_label.set_visible(!btn_addExisting.get_active());
	
	string temp_installChooserTooltip = "";
	if(btn_addExisting.get_active()){
		// Add Existing = true: remove values
		temp_lastInstallDirectory = btn_chooser_installFolder.get_uri();
		
		btn_chooser_installFolder.unselect_all();
		temp_installChooserTooltip = "Specify the root folder of an existing installation.";
	} else{
		// False: reset values:
		btn_chooser_installFolder.set_uri(temp_lastInstallDirectory);
		temp_installChooserTooltip = "Specify the folder where the engine will be installed.\nWARNING: Spaces in the path may cause issues!";
	}
	
	btn_chooser_installFolder.set_tooltip_text( temp_installChooserTooltip ); 
	EngineAdd_CanContinue();
}

void EngineAdd::btn_initial_updateLists_clicked(){

	string temp_errorMessage = ""; 	// Displays help text in event of errors.
	string temp_fileDirectory = UnrealatedLauncherGlobal::launcherHomeDir + "/lists/tags.txt";	// Directory of file to check.
	
	// Tagged List:
	if( !EngineAdd_populateSelector(&btn_taggedCommitSelector, commits_taggedIterations, temp_fileDirectory, true) ){
		temp_errorMessage = "Unable to find tag list.  Consider Generating them in the manager.\n";
	}

	
	// All Commits
	temp_fileDirectory = UnrealatedLauncherGlobal::launcherHomeDir + "/lists/all.txt";
	if( !EngineAdd_populateSelector(&btn_commitSelector, commits_normalIterations, temp_fileDirectory, false) ){
		temp_errorMessage = "Unable to find commit list.  Consider Generating them in the manager.\n";
	}
	
	// Run changed to prevent size issues:
	btn_taggedCommitSelector_changed();
	btn_selectorChanged();
	
	txt_confirm_helper.set_text(temp_errorMessage);
}

void EngineAdd::btn_showCommitsAfterBranch_changed(){
	txt_chooser_taggedCommits.set_visible(btn_showCommitsAfterTaggedCommit.get_active());
	btn_taggedCommitSelector.set_visible(btn_showCommitsAfterTaggedCommit.get_active());
	
	btn_commitSelector.set_active(-1);
	btn_taggedCommitSelector.set_active(-1);
}

void EngineAdd::btn_manageLauncherRepo_clicked(){
	v_tabReference->middleMan_openRepoManager_bool = true;
} // END - Manage launcher repo clicked.

void EngineAdd::btn_toggle_showCommitsFilter(){
	// Hides/Shows the appropriate widgets relating to the selected radio button.

	txt_chooser_taggedCommits.set_visible(btn_toggle_showTags.get_active());
	btn_taggedCommitSelector.set_visible(btn_toggle_showTags.get_active());
	
	txt_chooser_commits.set_visible(!btn_toggle_showTags.get_active());
	btn_commitSelector.set_visible(!btn_toggle_showTags.get_active());
	
	btn_showCommitsAfterTaggedCommit.set_visible(!btn_toggle_showTags.get_active());
	
	if(btn_toggle_showCommits.get_active() && btn_showCommitsAfterTaggedCommit.get_active()){
		txt_chooser_taggedCommits.set_visible(btn_showCommitsAfterTaggedCommit.get_active());
		btn_taggedCommitSelector.set_visible(btn_showCommitsAfterTaggedCommit.get_active());
	} // END - If show commits and show commits after tagged is enabled.
	
	if(btn_toggle_showCommits.get_active()){
		txt_confirm_commit.set_text(btn_commitSelector.get_active_id());
	}else{
		txt_confirm_commit.set_text(btn_taggedCommitSelector.get_active_id());
	}
	
	EngineAdd_CanContinue();
} // END - Toggle show Tagged/Commit filter.

void EngineAdd::btn_chooser_installFolder_changed(){
	btn_labelEntry_changed();
}


void EngineAdd::btn_chooser_customImage_changed(){
	btn_chooser_customImage.set_width_chars(10);
	cout << "changed." << endl;
} // END - Custom image chooser changed.

void EngineAdd::btn_cancel_clicked(){
	v_tabReference->CloseAddWizard();
	EngineAdd_reset();
}

void EngineAdd::btn_confirm_clicked(){
	v_tabReference->CloseAddWizard();
	
	// SET DATA:
	installData.engineLabel = btn_labelEntry.get_text();
	installData.installDir = txt_confirm_installFolder.get_text();
	
	string temp_imageDirFixed = btn_chooser_customImage.get_uri().erase(0, 7);
	
	if( !temp_imageDirFixed.empty() ){
		installData.customImage = LauncherUtility_removePercent20( temp_imageDirFixed );
		cout << "DEBUG:	Fixed image dir: " << temp_imageDirFixed << endl;
	}
	installData.commitID = txt_confirm_commit.get_text();
	
	EngineAdd_startInstallAfterFinished = btn_startInstallAfterFinished.get_active();
	
//	installData.codeEditor = txt_confirm_codeEditor.get_text();
	installData.codeEditor = "";
	
	v_tabReference->AddNewEngine();
}

void EngineAdd::btn_taggedCommitSelector_changed(){
	auto v_cellRenderer = (Gtk::CellRendererText*)btn_taggedCommitSelector.get_first_cell();
	v_cellRenderer->property_width_chars() = 1;
	v_cellRenderer->property_ellipsize() = Pango::ELLIPSIZE_END;
	v_cellRenderer->set_fixed_size(170, -1);
	
	if(btn_showCommitsAfterTaggedCommit.get_active()){
		btn_commitSelector.remove_all(); // Clear the selector.
		
		string temp_filePath = UnrealatedLauncherGlobal::launcherHomeDir + "/lists/" + btn_taggedCommitSelector.get_active_text() + ".txt";
		
		EngineAdd_populateSelector(&btn_commitSelector, commits_normalIterations, temp_filePath, false);
	} else{
		txt_confirm_commit.set_text( btn_taggedCommitSelector.get_active_id() );
		txt_confirm_commit.set_tooltip_text( btn_taggedCommitSelector.get_active_id() );
	} // END - If Show Commits after Tagged.
	
	EngineAdd_CanContinue();
} // END - Tagged commit changed.

void EngineAdd::btn_selectorChanged(){
	
	// Commit Selector:
	auto v_cellRenderer = (Gtk::CellRendererText*)btn_commitSelector.get_first_cell();
	v_cellRenderer->property_width_chars() = 1;
	v_cellRenderer->property_ellipsize() = Pango::ELLIPSIZE_END;
//	v_cellRenderer->set_fixed_size(170, -1);

	txt_confirm_commit.set_text( btn_commitSelector.get_active_id() );
	txt_confirm_commit.set_tooltip_text( btn_commitSelector.get_active_id() );

	EngineAdd_CanContinue();
} // END - Selector Changed.


void EngineAdd::btn_appendLabelToInstallDir_changed(){ // Proxy function
	btn_labelEntry_changed();
}

void EngineAdd::btn_labelEntry_changed(){	// Updates the confirm directories text. 
	string temp_text = "";
	string temp_label = "";
	
	// Remove any invalid characters from label:
	if(btn_appendLabelToInstallDir.get_active()){
		temp_label = LauncherUtility_removeElementFromString( btn_labelEntry.get_text(), " ", 1);
		btn_labelEntry.set_text(temp_label);
		temp_label = LauncherUtility_removeElementFromString( btn_labelEntry.get_text(), "/", 1);
		btn_labelEntry.set_text(temp_label);
		temp_label = LauncherUtility_removeElementFromString( btn_labelEntry.get_text(), "?", 1);
		btn_labelEntry.set_text(temp_label);
		temp_label = LauncherUtility_removeElementFromString( btn_labelEntry.get_text(), "'", 1);
		btn_labelEntry.set_text(temp_label);
		temp_label = LauncherUtility_removeElementFromString( btn_labelEntry.get_text(), "*", 1);
		btn_labelEntry.set_text(temp_label);
	} // Append label to install dir.
	
	if(btn_labelEntry.get_text().empty()){ // CHECK IF EMPTY.
		txt_confirm_helper.set_text("Label cannot be empty!");
	}
	
	if( btn_appendLabelToInstallDir.get_active() && ! btn_addExisting.get_active() ){
		temp_text = btn_chooser_installFolder.get_uri() + "/" + btn_labelEntry.get_text();
		txt_confirm_installFolder.set_text(temp_text.erase(0, 7));
	}else{
		temp_text = btn_chooser_installFolder.get_uri();
		txt_confirm_installFolder.set_text(temp_text.erase(0, 7));
	}
	txt_confirm_installFolder.set_tooltip_text( temp_text );
	
	EngineAdd_CanContinue();
	
} // END - Label Entry changed.

void EngineAdd::btn_chooser_codeEditor_changed(){
	if(btn_chooser_codeEditor.get_active()){
		Glib::RefPtr<Gio::AppInfo> temp_AppInfo = btn_chooser_codeEditor.get_app_info();
		txt_confirm_codeEditor.set_text( temp_AppInfo->get_executable() );
	}
} // END - Code Editor Changed.

				// END -- BUTTON FUNCTIONS
bool EngineAdd::EngineAdd_populateSelector(Gtk::ComboBoxText* p_selector, int p_iterations, string p_path, bool p_removeTagPrefix){
	p_selector->remove_all();
	
	ifstream stream_file;
	string	temp_line = "",
			temp_objectID = "",
			temp_objectMessage = "";
	int loop_iterations = 0;
	bool loop_objectID = true; // First item is object ID.
	

	// Tagged List:
	if(LauncherUtility_checkFileExists(p_path)){

		cout << "DEBUG:	File:" << p_path << " exists!" << endl;
		stream_file.open(p_path.c_str());
		
		while(getline(stream_file, temp_line) && loop_iterations <= p_iterations){
			
			if(loop_objectID){  // Obtaining Object ID:
				loop_objectID = false;
				temp_objectID = temp_line;
			}else{ // Obtaining Object Message:
				loop_objectID = true;
				temp_objectMessage = temp_line;

				if(p_removeTagPrefix){
					p_selector->prepend(temp_objectID, temp_objectMessage.erase(0, 10));
				} else{
					p_selector->append(temp_objectID, temp_objectMessage);
				}
			} // END - objectID/message if.
			
			++loop_iterations;
		} // END - While loop.
		
		stream_file.close();
		
	} else{
		cout << "DEBUG:	File:" << p_path << " NOT FOUND!" << endl;
		return false;
	}
	
	return true;
} // END - Populate Selector.

void EngineAdd::SetConfirmTextSettings(Gtk::Label* p_label){
	p_label->set_halign(Gtk::ALIGN_START);
	p_label->set_hexpand();
	p_label->set_line_wrap();
	p_label->set_lines(1);
	p_label->set_max_width_chars(1);
	p_label->set_size_request(220, -1);
	p_label->set_ellipsize(Pango::ELLIPSIZE_START);
} // END - Set confirm text settings.

void EngineAdd::EngineAdd_CanContinue(){
// set button to false:
	btn_confirm.set_sensitive(false);
	txt_confirm_helper.set_text("");
	
	string helpText = "";
	bool temp_loopCheck = true;

	if(btn_labelEntry.get_text().empty()){
		helpText = "Label cannot be empty!\n";
		temp_loopCheck = false;
	}
	
	for(EngineBlock* engineBlockObject : v_tabReference->v_EngineBlockArray){
		if(engineBlockObject->v_EngineLabel == btn_labelEntry.get_text()) temp_loopCheck = false;;
			if( engineBlockObject->v_EngineInstallDir == txt_confirm_installFolder.get_text() ){
				helpText = txt_confirm_installFolder.get_text() + "\nDirectory used by: " + engineBlockObject->v_EngineLabel;
				txt_confirm_installFolder.set_text(helpText);
				temp_loopCheck = false;
			} // END - If engine install folder is used by another engine.
	} // END - For loop


	if(btn_addExisting.get_active()){	// ADD EXISTING:
		// Maybe add checker in here for directory.
		
	} else{								// ADD NEW:
			if(btn_toggle_showCommits.get_active()){ // SHOW COMMITS:
				if(btn_commitSelector.get_active_row_number() == -1) temp_loopCheck = false;;
			}else{ // SHOW TAGGED COMMITS:
				if(btn_taggedCommitSelector.get_active_row_number() == -1) temp_loopCheck = false;
			}
	} // END - AddExisting/AddNew
	
	// Set button to boolean value. If not changed from checks, will be true.
	txt_confirm_helper.set_text( helpText );
	btn_confirm.set_sensitive(temp_loopCheck);
} // END - Can Continue.