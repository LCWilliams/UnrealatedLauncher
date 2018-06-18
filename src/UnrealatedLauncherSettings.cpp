#include <headers/UnrealatedLauncherWindow.h>

using namespace UnrealatedLauncher;
using namespace LauncherUtility;

UnrealatedSettings::UnrealatedSettings():
	btn_confirmSettings("Confirm"),
	btn_cancelSettings("Cancel"),
	btn_resetAll("Reset All"),
	
	// GENERAL:

	page_general_interface_frame("Interface"),

	txt_defaultPage("Default page:"),
	
	btn_useSystemTheme("Use system theme"),
	btn_utilityOpenOnDefault("Utility Bar open by default"),
	btn_showLauncherRepoStatus("Show launcher repo status in Utility Bar"),
	btn_showLatestCommit("Show latest commit in the Utility Bar"),
	
	btn_defaultPage(false), // Doesn't have entry.
	
	// PROJECTS
	
	// ENGINES:
	page_engines_general_frame("General"),
	page_engines_directories_frame("Directories"),
	page_engines_addOptions_frame("Add Engine Options"),
	page_engines_manageLauncherRepo_frame("Launcher Repository"),
	
	btn_backgroundSync("Background Repo Sync"),
	btn_backgroundSync_regenLists("Regenerate Lists on sync"),
	btn_defaultShowTaggedCommits("Show tagged Commits by default"),
	txt_launcherRepoUpdateInterval("Background Sync Interval:"),
	txt_RepoDirLabel("Launcher repository directory:"),
	txt_defaultInstallDirLabel("Default install directory:"),
	txt_maxTaggedCommits("Max tagged commits:"),
	txt_maxCommits("Max Commits:"),
	txt_commitWrap("Commit Wrap:")
	
	// MARKET
	
	// COMMUNITY
	
{						//UNREALATED LAUNCHER SETTINGS{
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
	
	btn_resetAll.set_tooltip_text("Resets all settings to default. \nDoes not save to file.");
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
		LauncherUtility_setFlowboxSettings(&page_general_flowBox);
	page_projects_scrollWindow.add(page_projects_flowBox);
		LauncherUtility_setFlowboxSettings(&page_projects_flowBox);
	page_engines_scrollWindow.add(page_engines_flowBox);
		LauncherUtility_setFlowboxSettings(&page_engines_flowBox);
	page_market_scrollWindow.add(page_market_flowBox);
		LauncherUtility_setFlowboxSettings(&page_market_flowBox);
	page_community_scrollWindow.add(page_community_flowBox);
		LauncherUtility_setFlowboxSettings(&page_community_flowBox);


		// Pages to notebook:
	v_settingsNotebook.append_page(page_general_scrollWindow, "General", "GENERAL", true);
	v_settingsNotebook.append_page(page_projects_scrollWindow, "Projects", "PROJECTS", true);
	v_settingsNotebook.append_page(page_engines_scrollWindow, "Engines", "ENGINES", true);
	v_settingsNotebook.append_page(page_market_scrollWindow, "Market", "MARKET", true);
	v_settingsNotebook.append_page(page_community_scrollWindow, "Community", "COMMUNITY", true);


	// GENERAL:
	page_general_interface_frame.add(page_general_interface);
	page_general_flowBox.add(page_general_interface_frame);
	LauncherUtility_setGridSettings(&page_general_interface);
	
//	page_General.attach(*widget, left, top, wid, height);
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

	page_general_interface.attach(btn_utilityOpenOnDefault, 1, 2, 1, 1);
		btn_utilityOpenOnDefault.set_tooltip_text("If checked, the utility bar will be open by default.");

	page_general_interface.attach(btn_showLauncherRepoStatus, 1, 3, 1, 1);
		btn_showLauncherRepoStatus.set_tooltip_text("If checked, the status of the launcher repo will be displayed in the utility bar.");

	page_general_interface.attach(btn_showLatestCommit, 1, 4, 1, 1);
		btn_showLatestCommit.set_tooltip_text("If checked, the latest commit of the launcher repo will be displayed in the utility bar.");



	// ENGINES:
		// Engine General:
	page_engines_general_frame.add(page_engines_general);
	page_engines_flowBox.add(page_engines_general_frame);
	LauncherUtility_setGridSettings(&page_engines_general);
	
	
	
		// Engine Directories:
	page_engines_directories_frame.add(page_engines_directories);
	page_engines_flowBox.add(page_engines_directories_frame);
	LauncherUtility_setGridSettings(&page_engines_directories);
	
	
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
		
	
		// Engine Add Options:
	page_engines_addOptions_frame.add(page_engines_addOptions);
	page_engines_flowBox.add(page_engines_addOptions_frame);
	LauncherUtility_setGridSettings(&page_engines_addOptions);

	page_engines_addOptions.attach(txt_maxTaggedCommits, 0, 0, 1, 1);
	page_engines_addOptions.attach(btn_maxTaggedCommits, 1, 0, 1, 1);
		txt_maxTaggedCommits.set_halign(Gtk::ALIGN_END);
		btn_maxTaggedCommits.set_range(5, 500);
		btn_maxTaggedCommits.set_increments(5, 10);
		btn_maxTaggedCommits.set_tooltip_text("Maximum number of tagged commits that will be shown in the selector.");
	
	page_engines_addOptions.attach(txt_maxCommits, 0, 1, 1, 1);
	page_engines_addOptions.attach(btn_maxCommits, 1, 1, 1, 1);
		txt_maxCommits.set_halign(Gtk::ALIGN_END);
		btn_maxCommits.set_range(10, 1000);
		btn_maxCommits.set_increments(1, 5);
		btn_maxCommits.set_tooltip_text("Maximum number of commits that will be shown in the selector.");
		
	page_engines_addOptions.attach(btn_defaultShowTaggedCommits, 0, 2, 2, 1);
		btn_defaultShowTaggedCommits.set_tooltip_text("If checked, the selector will show tagged commits by default.");
	
	page_engines_addOptions.attach(txt_commitWrap, 0, 3, 1, 1);
		txt_commitWrap.set_halign(Gtk::ALIGN_END);
	page_engines_addOptions.attach(btn_commitWrap, 1, 3, 1, 1);
		btn_commitWrap.set_tooltip_text("How many columns the commit selector will span. \nHigher numbers will show more commits at once, but limit readability of longer commits.");
		btn_commitWrap.set_wrap(true);
		btn_commitWrap.set_range(1, 10);
		btn_commitWrap.set_increments(1, 3);

		// Engine Manage Launcher Repository
	page_engines_manageLauncherRepo_frame.add(page_engines_manageLauncherRepo);
	page_engines_flowBox.add(page_engines_manageLauncherRepo_frame);
	LauncherUtility_setGridSettings(&page_engines_manageLauncherRepo);
	
	page_engines_manageLauncherRepo.attach(btn_backgroundSync, 0, 0, 2, 1);
		btn_backgroundSync.set_tooltip_text("If checked, the launcher repository will be updated periodically.");
	
	page_engines_manageLauncherRepo.attach(btn_backgroundSync_regenLists, 0, 1, 2, 1);
		btn_backgroundSync_regenLists.set_tooltip_text("If checked, the lists used by the launcher UI will be updated after synchronising.");
	
	page_engines_manageLauncherRepo.attach(txt_launcherRepoUpdateInterval, 0, 2, 1, 1);
		txt_launcherRepoUpdateInterval.set_halign(Gtk::ALIGN_END);
	
	page_engines_manageLauncherRepo.attach(btn_launcherRepoUpdateInterval, 1, 2, 1, 1);
		btn_launcherRepoUpdateInterval.set_tooltip_text("Interval, in minutes, in which the repository is synced.");
		btn_launcherRepoUpdateInterval.set_range(1, 120);
		btn_launcherRepoUpdateInterval.set_increments(1, 5);


	show_all();
	readPreferences();
	
} // END - Constructor

UnrealatedSettings::~UnrealatedSettings(){
} // END - Destructor.

															// BUTTON FUNCTIONS:
void UnrealatedSettings::btn_cancelSettings_clicked(){
	ref_window->settings_closed();
	readPreferences();
} // END - Cancel.

void UnrealatedSettings::btn_confirmSettings_clicked(){
	
	// INI WRITER:
	CSimpleIniCaseA ini;
	string dataString;
	string temp_Conversion; // Used for modifying strings before using them to save data.
	SI_Error temp_errorCheck;
//	if(temp_errorCheck < 0) return;
	
	
	// Write General:
//		ini.SetBoolValue("General", "FirstRun", true);
		ini.SetBoolValue("General", "UseSystemTheme", btn_useSystemTheme.get_active());
		ini.SetBoolValue("General", "utilityBarOpen", btn_utilityOpenOnDefault.get_active());
		ini.SetBoolValue("General", "UtilBar_ShowLauncherRepoStatus", btn_showLauncherRepoStatus.get_active());
		ini.SetBoolValue("General", "UtilBar_ShowLatestCommit", btn_showLatestCommit.get_active());
		ini.SetDoubleValue("General", "DefaultPage", btn_defaultPage.get_active_row_number());
		ini.SetBoolValue("General", "RememberGitLogin", UnrealatedLauncherGlobal::repoManagerRememberLogin);
	
	// Write Projects:
	
	// Write Engines:
		ini.SetBoolValue("Engines", "BackgroundRepoSync", btn_backgroundSync.get_active());
		ini.SetBoolValue("Engines", "BackgroundRepoSync_RegenList", btn_backgroundSync_regenLists.get_active());
		ini.SetDoubleValue("Engines", "BackgroundRepoSyncInterval", btn_launcherRepoUpdateInterval.get_value());
		
		temp_Conversion = btn_launcherRepoDir.get_uri().erase(0, 7); 
		ini.SetValue("Engines", "launcherRepo", temp_Conversion.c_str());
		
		temp_Conversion = btn_defaultInstallDir.get_uri().erase(0, 7); 
		ini.SetValue("Engines", "defaultInstallDir", temp_Conversion.c_str());

		
		ini.SetDoubleValue("Engines", "maxTaggedCommits", btn_maxTaggedCommits.get_value());
		ini.SetDoubleValue("Engines", "maxCommits", btn_maxCommits.get_value());
		ini.SetBoolValue("Engines", "defaultShowTaggedCommits", btn_defaultShowTaggedCommits.get_active());
		ini.SetDoubleValue("Engines", "commitWrap", btn_commitWrap.get_value());
	// Write Market:
	
	// Write Community:
	
	// Save & Close Tab:
	temp_errorCheck = ini.Save(dataString);
	if(temp_errorCheck < 0) return;
	
	temp_errorCheck = ini.SaveFile(UnrealatedLauncherGlobal::launcherConfig.c_str());
	if(temp_errorCheck < 0) return;
	
	ref_window->settings_closed();
	
	settings_writeSettingsVariables();
	
} // END - Confirm settings.

void UnrealatedSettings::btn_resetAll_clicked(){	
	// GENERAL:
	btn_useSystemTheme.set_active(false);
	btn_utilityOpenOnDefault.set_active(true);
	btn_showLauncherRepoStatus.set_active(true);
	btn_showLatestCommit.set_active(true);
	btn_defaultPage.set_active(1);
	
	// ENGINES:
	btn_backgroundSync.set_active(true);
	btn_backgroundSync_regenLists.set_active(true);
	btn_launcherRepoUpdateInterval.set_value(10);
	btn_launcherRepoDir.set_filename("./launcherRepo");
	btn_defaultInstallDir.set_filename("./engines");
	btn_maxTaggedCommits.set_value(200);
	btn_maxCommits.set_value(300);
	btn_defaultShowTaggedCommits.set_active(true);
	btn_commitWrap.set_value(1);
		// Write Market:
		
		// Write Community:
} // END - reset all.

void UnrealatedSettings::settings_writeSettingsVariables(){
	cout << "DEBUG:	" << "WriteSettingsVariables Called." << endl;
	CSimpleIniCaseA ini;
	SI_Error temp_errorCheck = ini.LoadFile(UnrealatedLauncherGlobal::launcherConfig.c_str());
	if(temp_errorCheck < 0){
		cout << "WARN: Failed to load settings [WriteNewSettings]" << endl;
		return;
	}
	
	// GENERAL:
	
	// ENGINES:
	UnrealatedLauncherGlobal::launcherRepositoryDir = ini.GetValue("Engines", "launcherRepo");
	cout << "DEBUG:	Launcher Repo Dir: " << UnrealatedLauncherGlobal::launcherRepositoryDir << endl;
	
	UnrealatedLauncherGlobal::repoManagerRememberLogin = ini.GetValue("General", "RememberGitLogin");
	
	
} // WriteNewSettings

void UnrealatedSettings::btn_backgroundSync_clicked(){
	txt_launcherRepoUpdateInterval.set_sensitive(btn_backgroundSync.get_active());
	btn_launcherRepoUpdateInterval.set_sensitive(btn_backgroundSync.get_active());
}


void UnrealatedSettings::readPreferences(){
	CSimpleIniCaseA ini; 
	SI_Error temp_errorCheck = ini.LoadFile(UnrealatedLauncherGlobal::launcherConfig.c_str());
	if(temp_errorCheck < 0)return;
	
	// GENERAL:
	btn_useSystemTheme.set_active(ini.GetBoolValue("General", "UseSystemTheme"));
	btn_utilityOpenOnDefault.set_active(ini.GetBoolValue("General", "utilityBarOpen"));
	btn_showLauncherRepoStatus.set_active(ini.GetBoolValue("General", "UtilBar_ShowLauncherRepoStatus"));
	btn_showLatestCommit.set_active(ini.GetBoolValue("General", "UtilBar_ShowLatestCommit"));
	btn_defaultPage.set_active(ini.GetDoubleValue("General", "DefaultPage"));
	
	// ENGINES:
	btn_backgroundSync.set_active(ini.GetBoolValue("Engines", "BackgroundRepoSync"));
	btn_backgroundSync_regenLists.set_active(ini.GetBoolValue("Engines", "BackgroundRepoSync_RegenList"));
	btn_launcherRepoUpdateInterval.set_value(ini.GetDoubleValue("Engines", "BackgroundRepoSyncInterval"));
	btn_launcherRepoDir.set_filename(ini.GetValue("Engines", "launcherRepo"));
	btn_defaultInstallDir.set_filename(ini.GetValue("Engines", "defaultInstallDir"));
	btn_maxTaggedCommits.set_value(ini.GetDoubleValue("Engines", "maxTaggedCommits"));
	btn_maxCommits.set_value(ini.GetDoubleValue("Engines", "maxCommits"));
	btn_defaultShowTaggedCommits.set_active(ini.GetBoolValue("Engines", "defaultShowTaggedCommits"));
	btn_commitWrap.set_value(ini.GetDoubleValue("Engines", "commitWrap"));
	
	settings_writeSettingsVariables();
} // END - read preferences.

bool UnrealatedSettings::LauncherSettings_Get_BackgroundSync(){	return btn_backgroundSync.get_active(); }
bool UnrealatedSettings::launcherSettings_Get_RegenLists(){	
	cout << "Debug return true" << endl;
//	cout << "DEBUG:	Regen List:" << btn_backgroundSync_regenLists.get_active() << endl;
//	return btn_backgroundSync_regenLists.get_active(); }
	return true;
}
int	 UnrealatedSettings::launcherSettings_get_syncInterval(){	return btn_launcherRepoUpdateInterval.get_value_as_int(); }