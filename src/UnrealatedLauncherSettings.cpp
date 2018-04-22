#include <headers/UnrealatedLauncherWindow.h>

using namespace UnrealatedLauncher;

UnrealatedSettings::UnrealatedSettings():
	btn_confirmSettings("Confirm"),
	btn_cancelSettings("Cancel"),
	btn_resetAll("Reset All"),
	
	// GENERAL:
	page_general_interface_frame("Interface"),
	
	txt_useSysTheme("Use system theme:"), 
	txt_utilityOpenOnDefault("Utility bar Open on default:"), 
	txt_showLauncherRepoStatus("Show Repo Status in the Utility Bar:"), 
	txt_showLatestCommit("Show latest commit in the Utility Bar:"),
	txt_defaultPage("Default page:"),
	btn_defaultPage(false), // Doesn't have entry.
	
	// PROJECTS
	
	// ENGINES:
	page_engines_general_frame("General"),
	page_engines_directories_frame("Directories"),
	page_engines_addOptions_frame("Add Engine Options"),
	page_engines_manageLauncherRepo_frame("Manage Launcher Repository"),
	
	txt_backgroundSync("Background repo sync:"),
	txt_launcherRepoUpdateInterval("Background Sync Interval:"),
	txt_defaultShowBranches("Show branches initially:"),
	txt_RepoDirLabel("Launcher repository directory:"),
	txt_defaultInstallDirLabel("Default install directory:"),
	txt_defaultSourceDirLabel("Default source directory:"),
	txt_maxBranches("Max branches:"),
	txt_maxCommits("Max Commits:"),
	txt_commitWrap("Commit Wrap:")
	
	// MARKET
	
	// COMMUNITY
	
{ 						// UNREALATED LAUNCHER SETTINGS{
	set_name("UNREALATEDLAUNCHERSETTINGS");

	// Button Signal handlers:
	btn_cancelSettings.signal_clicked().connect(sigc::mem_fun(*this, &UnrealatedSettings::btn_cancelSettings_clicked));
	btn_confirmSettings.signal_clicked().connect(sigc::mem_fun(*this, &UnrealatedSettings::btn_confirmSettings_clicked));
	btn_resetAll.signal_clicked().connect(sigc::mem_fun(*this, &UnrealatedSettings::btn_resetAll_clicked));
	btn_backgroundSync.signal_toggled().connect(sigc::mem_fun(*this, &UnrealatedSettings::btn_backgroundSync_clicked));


	// GENERIC SETUP:
	Gtk::ButtonBox *btn_CancelConfirmBox = Gtk::manage(new Gtk::ButtonBox);
	btn_CancelConfirmBox->add(btn_cancelSettings);
	btn_CancelConfirmBox->add(btn_resetAll);
	btn_CancelConfirmBox->add(btn_confirmSettings);
	btn_CancelConfirmBox->set_layout(Gtk::BUTTONBOX_EXPAND);
	btn_CancelConfirmBox->set_halign(Gtk::ALIGN_CENTER);
	btn_CancelConfirmBox->set_margin_bottom(2.5);
	
	btn_resetAll.set_tooltip_text("Resets all settings to default, then saves them.");
	btn_confirmSettings.set_tooltip_text("Saves the settings to file and closes the window.");
	btn_cancelSettings.set_tooltip_text("Discards any changes and closes the window.");
	
	v_settingsNotebook.set_hexpand(true);
	v_settingsNotebook.set_border_width(0);
	v_settingsNotebook.set_size_request(-1, 250);
	
	
	// ATTACHMENT:
	attach(*btn_CancelConfirmBox, 0, 1, 1, 1);
	attach(v_settingsNotebook, 0, 0, 1, 1);
		
		// Flowbox to page ScrollWindow.
	page_general_scrollWindow.add(page_general_flowBox);
		setPageFlowBoxSettings(&page_general_flowBox);
	page_projects_scrollWindow.add(page_projects_flowBox);
		setPageFlowBoxSettings(&page_projects_flowBox);
	page_engines_scrollWindow.add(page_engines_flowBox);
		setPageFlowBoxSettings(&page_engines_flowBox);
	page_market_scrollWindow.add(page_market_flowBox);
		setPageFlowBoxSettings(&page_market_flowBox);
	page_community_scrollWindow.add(page_community_flowBox);
		setPageFlowBoxSettings(&page_community_flowBox);


		// Pages to notebook:
	v_settingsNotebook.append_page(page_general_scrollWindow, "General", "GENERAL", true);
	v_settingsNotebook.append_page(page_projects_scrollWindow, "Projects", "PROJECTS", true);
	v_settingsNotebook.append_page(page_engines_scrollWindow, "Engines", "ENGINES", true);
	v_settingsNotebook.append_page(page_market_scrollWindow, "Market", "MARKET", true);
	v_settingsNotebook.append_page(page_community_scrollWindow, "Community", "COMMUNITY", true);


	// GENERAL:
	page_general_interface_frame.add(page_general_interface);
	page_general_flowBox.add(page_general_interface_frame);
	setPageGridSettings(&page_general_interface);
	
//	page_General.attach(*widget, left, top, wid, height);
	page_general_interface.attach(txt_useSysTheme, 0, 0, 1, 1);
	txt_useSysTheme.set_halign(Gtk::ALIGN_END);
	page_general_interface.attach(btn_useSystemTheme, 1, 0, 1, 1);
	btn_useSystemTheme.set_tooltip_text("If checked, the program will use the system theme rather than its own. \nRestart the program for this to take affect.");

	page_general_interface.attach(txt_defaultPage, 0, 1, 1, 1);
	txt_defaultPage.set_halign(Gtk::ALIGN_END);
	page_general_interface.attach(btn_defaultPage, 1, 1, 1, 1);
		// Page list:
		btn_defaultPage.insert(0, "Projects");
		btn_defaultPage.insert(1, "Engines");
		btn_defaultPage.insert(2, "Marketplace");
		btn_defaultPage.insert(3, "Community");
	btn_defaultPage.set_tooltip_text("Sets which page will be shown when the program is opened.");

	page_general_interface.attach(txt_utilityOpenOnDefault, 0, 2, 1, 1);
	txt_utilityOpenOnDefault.set_halign(Gtk::ALIGN_END);
	page_general_interface.attach(btn_utilityOpenOnDefault, 1, 2, 1, 1);
	btn_utilityOpenOnDefault.set_tooltip_text("If checked, the utility bar will be open by default.");

	page_general_interface.attach(txt_showLauncherRepoStatus, 0, 3, 1, 1);
	txt_showLauncherRepoStatus.set_halign(Gtk::ALIGN_END);
	page_general_interface.attach(btn_showLauncherRepoStatus, 1, 3, 1, 1);
	btn_showLauncherRepoStatus.set_tooltip_text("If checked, the status of the launcher repo will be displayed in the utility bar.");

	page_general_interface.attach(txt_showLatestCommit, 0, 4, 1, 1);
	txt_showLatestCommit.set_halign(Gtk::ALIGN_END);
	page_general_interface.attach(btn_showLatestCommit, 1, 4, 1, 1);
	btn_showLatestCommit.set_tooltip_text("If checked, the latest commit of the launcher repo will be displayed in the utility bar.");



	// ENGINES:
		// Engine General:
	page_engines_general_frame.add(page_engines_general);
	page_engines_flowBox.add(page_engines_general_frame);
	setPageGridSettings(&page_engines_general);
	
	page_engines_general.attach(txt_backgroundSync, 0, 0, 1, 1);
	txt_backgroundSync.set_halign(Gtk::ALIGN_END);
	page_engines_general.attach(btn_backgroundSync, 1, 0, 1, 1);
	btn_backgroundSync.set_tooltip_text("If checked, the launcher repository will be updated periodically.");
	
	page_engines_general.attach(txt_launcherRepoUpdateInterval, 0, 1, 1, 1);
	txt_backgroundSync.set_halign(Gtk::ALIGN_END);
	page_engines_general.attach(btn_launcherRepoUpdateInterval, 1, 1, 1, 1);
	btn_launcherRepoUpdateInterval.set_tooltip_text("Interval, in minutes, in which the repository is synced.");
	btn_launcherRepoUpdateInterval.set_range(1, 30);
	btn_launcherRepoUpdateInterval.set_increments(1, 5);
	
	
		// Engine Directories:
	page_engines_directories_frame.add(page_engines_directories);
	page_engines_flowBox.add(page_engines_directories_frame);
	setPageGridSettings(&page_engines_directories);
	
	
	page_engines_directories.attach(txt_RepoDirLabel, 0, 1, 1, 1);
	txt_RepoDirLabel.set_halign(Gtk::ALIGN_END);
	page_engines_directories.attach(btn_launcherRepoDir, 1, 1, 1, 1);
	btn_launcherRepoDir.set_action(Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
	btn_launcherRepoDir.set_tooltip_text("The folder where the launcher repository is stored.");

	page_engines_directories.attach(txt_defaultInstallDirLabel, 0, 2, 1, 1);
	txt_defaultInstallDirLabel.set_halign(Gtk::ALIGN_END);
	page_engines_directories.attach(btn_defaultInstallDir, 1, 2, 1, 1);
	btn_defaultInstallDir.set_action(Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
	btn_defaultInstallDir.set_tooltip_text("The default parent folder the engine is installed into.");
	
	page_engines_directories.attach(txt_defaultSourceDirLabel, 0, 3, 1, 1);
	txt_defaultSourceDirLabel.set_halign(Gtk::ALIGN_END);
	page_engines_directories.attach(btn_defaultSourceDir, 1, 3, 1, 1);
	btn_defaultSourceDir.set_action(Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
	btn_defaultSourceDir.set_tooltip_text("The default parent folder for the engine source files.");
	
	
		// Engine Add Options:
	page_engines_addOptions_frame.add(page_engines_addOptions);
	page_engines_flowBox.add(page_engines_addOptions_frame);
	setPageGridSettings(&page_engines_addOptions);

	page_engines_addOptions.attach(txt_maxBranches, 0, 0, 1, 1);
	page_engines_addOptions.attach(btn_maxBranches, 1, 0, 1, 1);
	txt_maxBranches.set_halign(Gtk::ALIGN_END);
	btn_maxBranches.set_range(5, 30);
	btn_maxBranches.set_increments(1, 5);
	btn_maxBranches.set_tooltip_text("Maximum number of branches that will be shown in the selector.");
	
	page_engines_addOptions.attach(txt_maxCommits, 0, 1, 1, 1);
	page_engines_addOptions.attach(btn_maxCommits, 1, 1, 1, 1);
	txt_maxCommits.set_halign(Gtk::ALIGN_END);
	btn_maxCommits.set_range(10, 1000);
	btn_maxCommits.set_increments(1, 5);
	btn_maxCommits.set_tooltip_text("Maximum number of commits that will be shown in the selector.");
	
	page_engines_addOptions.attach(txt_defaultShowBranches, 0, 2, 1, 1);
	txt_defaultShowBranches.set_halign(Gtk::ALIGN_END);
	page_engines_addOptions.attach(btn_defaultShowBranches, 1, 2, 1, 1);
	btn_defaultShowBranches.set_tooltip_text("If checked, the selector will show branches by default.");
	
	page_engines_addOptions.attach(txt_commitWrap, 0, 3, 1, 1);
	txt_commitWrap.set_halign(Gtk::ALIGN_END);
	page_engines_addOptions.attach(btn_commitWrap, 1, 3, 1, 1);
	btn_commitWrap.set_tooltip_text("How many columns the commit selector will span. \nIncrease to show more results on the screen at once.");
	btn_commitWrap.set_wrap(true);
	btn_commitWrap.set_range(1, 10);
	btn_commitWrap.set_increments(1, 3);

		// Engine Manage Launcher Repository
	page_engines_manageLauncherRepo_frame.add(page_engines_manageLauncherRepo);
	page_engines_flowBox.add(page_engines_manageLauncherRepo_frame);
	setPageGridSettings(&page_engines_manageLauncherRepo);
	
	Gtk::Label *temp_label = Gtk::manage(new Gtk::Label("Temporary. Probably going to be removed."));
	page_engines_manageLauncherRepo.attach(*temp_label, 0, 0, 1, 1);


	show_all();
	readPreferences();
	
} // END - Constructor

UnrealatedSettings::~UnrealatedSettings(){
} // END - Destructor.

															// BUTTON FUNCTIONS:
void UnrealatedSettings::btn_cancelSettings_clicked(){
	v_windowRef->settings_closed();
	readPreferences();
} // END - Cancel.

void UnrealatedSettings::btn_confirmSettings_clicked(){
	
	// INI WRITER:
	CSimpleIniCaseA ini;
	string dataString;
	string temp_Conversion; // Used for modifying strings before using them to save data.
	string iniFileDir = "./config/UnrealatedLauncher.ini";
	SI_Error temp_errorCheck;
//	if(temp_errorCheck < 0) return;
	
	
	// Write General:
//		ini.SetBoolValue("General", "FirstRun", true);
		ini.SetBoolValue("General", "UseSystemTheme", btn_useSystemTheme.get_active());
		ini.SetBoolValue("General", "utilityBarOpen", btn_utilityOpenOnDefault.get_active());
		ini.SetBoolValue("General", "UtilBar_ShowLauncherRepoStatus", btn_showLauncherRepoStatus.get_active());
		ini.SetBoolValue("General", "UtilBar_ShowLatestCommit", btn_showLatestCommit.get_active());
		ini.SetDoubleValue("General", "DefaultPage", btn_defaultPage.get_active_row_number());
	
	// Write Projects:
	
	// Write Engines:
		ini.SetBoolValue("Engines", "BackgroundRepoSync", btn_backgroundSync.get_active());
		ini.SetDoubleValue("Engines", "BackgroundRepoSyncInterval", btn_launcherRepoUpdateInterval.get_value());
		
		temp_Conversion = btn_launcherRepoDir.get_uri().erase(0, 7); 
		ini.SetValue("Engines", "launcherRepo", temp_Conversion.c_str());
		
		temp_Conversion = btn_defaultInstallDir.get_uri().erase(0, 7); 
		ini.SetValue("Engines", "defaultInstallDir", temp_Conversion.c_str());

		temp_Conversion = btn_defaultSourceDir.get_uri().erase(0, 7); 
		ini.SetValue("Engines", "defaultSourceDir", temp_Conversion.c_str());
		
		ini.SetDoubleValue("Engines", "maxBranches", btn_maxBranches.get_value());
		ini.SetDoubleValue("Engines", "maxCommits", btn_maxCommits.get_value());
		ini.SetBoolValue("Engines", "defaultShowBranches", btn_defaultShowBranches.get_active());
		ini.SetDoubleValue("Engines", "commitWrap", btn_commitWrap.get_value());
	// Write Market:
	
	// Write Community:
	
	// Save & Close Tab:
	temp_errorCheck = ini.Save(dataString);
	if(temp_errorCheck < 0) return;
	
	temp_errorCheck = ini.SaveFile(iniFileDir.c_str());
	if(temp_errorCheck < 0) return;
	
	v_windowRef->settings_closed();
	
} // END - Confirm settings.

void UnrealatedSettings::btn_resetAll_clicked(){
	CSimpleIniCaseA ini;
	string dataString;
	string temp_Conversion; // Used for modifying strings before using them to save data.
	string iniFileDir = "./config/UnrealatedLauncher.ini";
	SI_Error temp_errorCheck;
	
	// Write General:
	ini.SetBoolValue("General", "FirstRun", true);
	ini.SetBoolValue("General", "UseSystemTheme", false);
	ini.SetBoolValue("General", "utilityBarOpen", true);
	ini.SetBoolValue("General", "UtilBar_ShowLauncherRepoStatus", true);
	ini.SetBoolValue("General", "UtilBar_ShowLatestCommit", true);
	ini.SetDoubleValue("General", "DefaultPage", 1);
		
	// Write Projects:
	
	
	// Write Engines:
	ini.SetBoolValue("Engines", "BackgroundRepoSync", true);
	ini.SetDoubleValue("Engines", "BackgroundRepoSyncInterval", 10);
	
	ini.SetValue("Engines", "launcherRepo", "./launcherRepo");
	ini.SetValue("Engines", "defaultInstallDir", "./engines/install");
	ini.SetValue("Engines", "defaultSourceDir", "./engines/source");
	
	ini.SetDoubleValue("Engines", "maxBranches", 30);
	ini.SetDoubleValue("Engines", "maxCommits", 150);
	ini.SetBoolValue("Engines", "defaultShowBranches", true);
	ini.SetDoubleValue("Engines", "commitWrap", 3);
		// Write Market:
		
		// Write Community:
		
		// Save & Close Tab:
	temp_errorCheck = ini.Save(dataString);
	if(temp_errorCheck < 0) exit(-1);
	
	temp_errorCheck = ini.SaveFile(iniFileDir.c_str());
	if(temp_errorCheck < 0) exit(-1);
	
	readPreferences();
} // END - reset all.

void UnrealatedSettings::btn_backgroundSync_clicked(){
	txt_launcherRepoUpdateInterval.set_sensitive(btn_backgroundSync.get_active());
	btn_launcherRepoUpdateInterval.set_sensitive(btn_backgroundSync.get_active());
}


void UnrealatedSettings::readPreferences(){
	CSimpleIniCaseA ini;
	string iniFileDir = "./config/UnrealatedLauncher.ini";
	SI_Error temp_errorCheck = ini.LoadFile(iniFileDir.c_str());
	if(temp_errorCheck < 0)return;
	
	// GENERAL:
	btn_useSystemTheme.set_active(ini.GetBoolValue("General", "UseSystemTheme"));
	btn_utilityOpenOnDefault.set_active(ini.GetBoolValue("General", "utilityBarOpen"));
	btn_showLauncherRepoStatus.set_active(ini.GetBoolValue("General", "UtilBar_ShowLauncherRepoStatus"));
	btn_showLatestCommit.set_active(ini.GetBoolValue("General", "UtilBar_ShowLatestCommit"));
	btn_defaultPage.set_active(ini.GetDoubleValue("General", "DefaultPage"));
	
	// ENGINES:
	btn_backgroundSync.set_active(ini.GetBoolValue("Engines", "BackgroundRepoSync"));
	btn_launcherRepoUpdateInterval.set_value(ini.GetDoubleValue("Engines", "BackgroundRepoSyncInterval"));
	btn_launcherRepoDir.set_filename(ini.GetValue("Engines", "launcherRepo"));
	btn_defaultInstallDir.set_filename(ini.GetValue("Engines", "defaultInstallDir"));
	btn_defaultSourceDir.set_filename(ini.GetValue("Engines", "defaultSourceDir"));
	btn_maxBranches.set_value(ini.GetDoubleValue("Engines", "maxBranches"));
	btn_maxCommits.set_value(ini.GetDoubleValue("Engines", "maxCommits"));
	btn_defaultShowBranches.set_active(ini.GetBoolValue("Engines", "defaultShowBranches"));
	btn_commitWrap.set_value(ini.GetDoubleValue("Engines", "commitWrap"));
	
	
} // END - read preferences.


void UnrealatedSettings::setPageGridSettings(Gtk::Grid* p_grid){
	p_grid->set_border_width(10);
	p_grid->set_hexpand(false);
	p_grid->set_column_homogeneous(false);
	p_grid->set_row_homogeneous(false);
	p_grid->set_row_spacing(3);
	p_grid->set_column_spacing(7);
} // END - set page grid settings.

void UnrealatedSettings::setPageFlowBoxSettings(Gtk::FlowBox* p_flowbox){
	p_flowbox->set_hexpand(true);
	p_flowbox->set_vexpand(false);
	p_flowbox->set_homogeneous(false);
	p_flowbox->set_row_spacing(15);
	p_flowbox->set_column_spacing(5);
	p_flowbox->set_border_width(5);
} // END -- Set page flowbox settings.