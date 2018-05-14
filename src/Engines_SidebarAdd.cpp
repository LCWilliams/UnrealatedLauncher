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
	btn_showCommitsAfterTaggedCommit("Show commits after tagged commit"),
	btn_appendLabelToInstallDir("Append label to install directory"),
	btn_appendLabelToSourceDir("Append label to source directory"),
	btn_makeCopyOfImage("Make copy of image"),
	
// Buttons:
	btn_cancel("Cancel"),
	btn_confirm("Confirm"),
	btn_manageLauncherRepo("Manage Launcher Repository"),
	
// Labels:
	txt_chooser_taggedCommits("Tagged Commit:"),
	txt_chooser_commits("Commit:"),
	txt_chooser_installFolder("Install Folder:"),
	txt_chooser_sourceFolder("Source Folder:"),
	txt_chooser_customImage("Custom Image:")

	
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


	// Commits Section:
	section_commits_frame.add(section_commits);
	section_commits_frame.set_label_align(Gtk::ALIGN_CENTER);
	v_revealer_online.add(section_commits_frame);
	attach(v_revealer_online, 0, 1, 1, 1);
	LauncherUtility_setGridSettings(&section_commits);
	
	section_commits.attach(btn_toggle_showTags, 0, 0, 1, 1);
		btn_toggle_showTags.set_tooltip_text("Click to use tagged commit selection.");
	section_commits.attach(btn_toggle_showCommits, 1, 0, 1, 1);
		btn_toggle_showCommits.set_tooltip_text("Click to use commit selection.");
		btn_toggle_showCommits.join_group(btn_toggle_showTags);

	section_commits.attach(txt_chooser_taggedCommits, 0, 1, 1, 1);
	section_commits.attach(btn_taggedCommitSelector, 1, 1, 1, 1);
		btn_taggedCommitSelector.set_tooltip_text("Use to choose the tagged commit which the new engine will be built from. \nPLEASE NOTE: If 'Show Commit From Branch' is enabled, changing the branch may cause a temporary UI freeze while the Commits are processed.");
		btn_taggedCommitSelector.set_hexpand(true);

	section_commits.attach(txt_chooser_commits, 0, 2, 1, 1);
	section_commits.attach(btn_commitSelector, 1, 2, 1, 1);
		btn_commitSelector.set_tooltip_text("Use to choose the commit which the new engine will be built from.");
		btn_commitSelector.set_hexpand(true);
		
	section_commits.attach(btn_showCommitsAfterTaggedCommit, 0, 3, 2, 1);
		btn_showCommitsAfterTaggedCommit.set_tooltip_text("If checked, the commit selector will show commits reverse chronologically after the chosen tagged commit.");
	
	Gtk::Separator *section_commits_seperator = Gtk::manage(new Gtk::Separator(Gtk::ORIENTATION_HORIZONTAL));
	section_commits_seperator->set_margin_top(2);
	section_commits_seperator->set_margin_bottom(5);
	section_commits_seperator->set_hexpand(true);
	section_commits.attach(*section_commits_seperator, 0, 4, 2, 1);
	
	section_commits.attach(btn_manageLauncherRepo, 0, 5, 2, 1);
		btn_manageLauncherRepo.set_tooltip_text("Opens the repo management settings.");
		
	btn_toggle_showTags.signal_clicked().connect(sigc::mem_fun(*this, &EngineAdd::btn_toggle_showCommitsFilter));
	btn_toggle_showCommits.signal_clicked().connect(sigc::mem_fun(*this, &EngineAdd::btn_toggle_showCommitsFilter));
	btn_showCommitsAfterTaggedCommit.signal_clicked().connect(sigc::mem_fun(*this, &EngineAdd::btn_showCommitsAfterBranch_changed));



	// Directory Section:
	section_directories_frame.add(section_directories);
	section_directories_frame.set_label_align(Gtk::ALIGN_CENTER);
	attach(section_directories_frame, 0, 2, 1, 1);
	LauncherUtility_setGridSettings(&section_directories);
	
	section_directories.attach(btn_appendLabelToInstallDir, 0, 1, 2, 1);
		btn_appendLabelToInstallDir.set_tooltip_text("If checked, the install folder will be created inside the folder specified, named using the label below.");
	
	section_directories.attach(txt_chooser_installFolder, 0, 0, 1, 1);
	section_directories.attach(btn_chooser_installFolder, 1, 0, 1, 1);
		btn_chooser_installFolder.set_action(Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
		btn_chooser_installFolder.set_hexpand();
		btn_chooser_installFolder.set_tooltip_text("Specify where the engine will be installed too after being built.");
	
	section_directories.attach(btn_appendLabelToSourceDir, 0, 3, 2, 1);
		btn_appendLabelToSourceDir.set_tooltip_text("If checked, the source folder will be created inside the folder specified, named using the label specified below.");
	
	section_directories.attach(txt_chooser_sourceFolder, 0, 2, 1, 1);
	section_directories.attach(btn_chooser_sourceFolder, 1, 2, 1, 1);
		btn_chooser_sourceFolder.set_action(Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
		btn_chooser_sourceFolder.set_hexpand();
		btn_chooser_sourceFolder.set_tooltip_text("Specify where the engine source will be stored.");
		
	btn_chooser_sourceFolder.signal_selection_changed().connect(sigc::mem_fun(*this, &EngineAdd::btn_chooser_sourceFolder_changed));
	btn_chooser_installFolder.signal_selection_changed().connect(sigc::mem_fun(*this, &EngineAdd::btn_chooser_installFolder_changed));


	// Label & Custom Image Section
	section_labelAndImage_frame.add(section_labelAndImage);
	section_labelAndImage_frame.set_label_align(Gtk::ALIGN_CENTER);
	attach(section_labelAndImage_frame, 0, 3, 1, 1);
	LauncherUtility_setGridSettings(&section_labelAndImage);
	
	section_labelAndImage.attach(btn_labelEntry, 0, 0, 2, 1);
	btn_labelEntry.set_placeholder_text("Engine Label");
	btn_labelEntry.set_max_length(30);
	btn_labelEntry.set_tooltip_text("The label to be used for the new engine block.");
	
	section_labelAndImage.attach(txt_chooser_customImage, 0, 1, 1, 1);
	section_labelAndImage.attach(btn_chooser_customImage, 1, 1, 1, 1);
		btn_chooser_customImage.set_action(Gtk::FILE_CHOOSER_ACTION_OPEN);
		auto btn_chooser_customImage_filter = Gtk::FileFilter::create();
		btn_chooser_customImage_filter->add_pixbuf_formats();
		btn_chooser_customImage.set_filter(btn_chooser_customImage_filter);
		btn_chooser_customImage.set_hexpand(true);
		btn_chooser_customImage.set_tooltip_text("Select a custom image to be used for the engine block.");

	section_labelAndImage.attach(btn_makeCopyOfImage, 0, 2, 2, 1);
		btn_makeCopyOfImage.set_tooltip_text("If checked, the image will be copied to an isolated folder.");



	// Confirmation Section
	section_confirm_frame.add(section_confirm);
	section_confirm_frame.set_label_align(Gtk::ALIGN_CENTER);
	attach(section_confirm_frame, 0, 4, 1, 1);
	LauncherUtility_setGridSettings(&section_confirm);
	
	
	section_confirm.attach(txt_confirm_commit, 0, 0, 2, 1);
		SetConfirmTextSettings(&txt_confirm_commit);
	section_confirm.attach(txt_confirm_installFolder, 0, 1, 2, 1);
		SetConfirmTextSettings(&txt_confirm_installFolder);
	section_confirm.attach(txt_confirm_sourceFolder, 0, 2, 2, 1);
		SetConfirmTextSettings(&txt_confirm_sourceFolder);
	section_confirm.attach(txt_confirm_helper, 0, 3, 2, 1);
		SetConfirmTextSettings(&txt_confirm_helper);
	
	
	Gtk::ButtonBox *btn_confirmCancelButtonbox = Gtk::manage(new Gtk::ButtonBox(Gtk::ORIENTATION_HORIZONTAL));
	btn_confirmCancelButtonbox->pack_start(btn_cancel, Gtk::PACK_EXPAND_WIDGET, 0);
	btn_confirmCancelButtonbox->pack_start(btn_confirm, Gtk::PACK_EXPAND_WIDGET, 0);
	btn_confirmCancelButtonbox->set_layout(Gtk::BUTTONBOX_EXPAND);
	btn_confirmCancelButtonbox->set_hexpand(true);
	section_confirm.attach(*btn_confirmCancelButtonbox, 0, 10, 2, 1);
	
} // END - Constructor.

EngineAdd::~EngineAdd(){
}

void EngineAdd::EngineAdd_reset(){ // Resets the sidebar.
	CSimpleIniCaseA ini;
	string iniFileDir = "./config/UnrealatedLauncher.ini";
	SI_Error temp_errorCheck = ini.LoadFile(iniFileDir.c_str());
	if(temp_errorCheck != 0)return;
//	v_maxCommits = ini.GetDoubleValue("Engines", "maxCommits");


	// Initial Options:
	btn_addExisting.set_active(false);
	v_revealer_online.set_reveal_child(true);
	
	// Directories & labels:
	btn_chooser_installFolder.set_filename(ini.GetValue("Engines", "defaultInstallDir"));
	btn_chooser_sourceFolder.set_filename(ini.GetValue("Engines", "defaultSourceDir"));
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

	btn_showCommitsAfterTaggedCommit.set_active(false);
	
	btn_labelEntry.set_text("");
	
	btn_appendLabelToInstallDir.set_active(true);
	btn_appendLabelToSourceDir.set_active(true);
	
	btn_chooser_customImage.unselect_all();
	
} // END - Reset.


				// BUTTON FUNCTIONS:

void EngineAdd::btn_addExisting_changed(){
	v_revealer_online.set_reveal_child(!btn_addExisting.get_active());
}

void EngineAdd::btn_showCommitsAfterBranch_changed(){
	txt_chooser_taggedCommits.set_visible(btn_showCommitsAfterTaggedCommit.get_active());
	btn_taggedCommitSelector.set_visible(btn_showCommitsAfterTaggedCommit.get_active());
}

void EngineAdd::btn_manageLauncherRepo_clicked(){}

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
} // END - Toggle show Tagged/Commit filter.

void EngineAdd::btn_chooser_installFolder_changed(){
	string temp_textToShow = "INSTALL FOLDER:\n";
	if(btn_appendLabelToInstallDir.get_active()){ // Append label to directory.
		temp_textToShow += btn_chooser_installFolder.get_uri() + "/" + btn_labelEntry.get_text().c_str();
	}else{
		temp_textToShow += btn_chooser_installFolder.get_uri();
	}
	txt_confirm_installFolder.set_text(temp_textToShow);
}

void EngineAdd::btn_chooser_sourceFolder_changed(){
	string temp_textToShow = "SOURCE FOLDER:\n";
	if(btn_appendLabelToSourceDir.get_active()){ // Append label to directory.
		temp_textToShow += btn_chooser_sourceFolder.get_uri() + "/" + btn_labelEntry.get_text().c_str();
	}else{
		temp_textToShow += btn_chooser_sourceFolder.get_uri();
	}
	txt_confirm_sourceFolder.set_text(temp_textToShow);
}

void EngineAdd::btn_chooser_customImage_changed(){
	btn_chooser_customImage.set_width_chars(10);
	cout << "changed." << endl;
} // END - Custom image chooser changed.

				// END -- BUTTON FUNCTIONS


void EngineAdd::SetConfirmTextSettings(Gtk::Label* p_label){
	p_label->set_halign(Gtk::ALIGN_START);
	p_label->set_hexpand();
	p_label->set_line_wrap();
	p_label->set_lines(1);
	p_label->set_max_width_chars(1);
	p_label->set_size_request(280, -1);
	p_label->set_ellipsize(Pango::ELLIPSIZE_START);
} // END - Set confirm text settings.