#include <headers/UnrealatedLauncherWindow.h>
#include <iostream>

using namespace std;
using namespace UnrealatedLauncher;

UnrealatedLauncherWindow::UnrealatedLauncherWindow():

	btn_link_help("https://docs.unrealengine.com/latest/INT/", "GIB MUNNIES PLZ"),
	menuItem_Launcher_ToggleUtilityBar("Utility Bar"),
	menuItem_Launcher_About("About"),
	menuItem_Launcher_Quit("Quit"),
	menuItem_Launcher_Settings("Settings"),
	menuItem_Launcher_RepoManager("Repo Manager")

{		// UNREALATED LAUNCHER WINDOW
	set_default_size(1200, 800);
	set_title("Unrealated Launcher");
	
	// Main Window Grid.
	Gtk::Grid *v_MainWindowGrid = Gtk::manage(new Gtk::Grid);
	v_MainWindowGrid->set_row_homogeneous(false);
	v_MainWindowGrid->set_column_homogeneous(false);
	add(*v_MainWindowGrid); // Add to window
	
	// CREATE ALL WINDOWS, SET GTK TO MANAGE:	
	UnrealatedLauncher::Launcher_ProjectTab *v_ProjectTab = Gtk::manage(new UnrealatedLauncher::Launcher_ProjectTab);
		ref_projectTab = v_ProjectTab;
	UnrealatedLauncher::Launcher_EngineTab *v_EngineTab = Gtk::manage(new UnrealatedLauncher::Launcher_EngineTab);
		ref_engineTab = v_EngineTab;
		v_EngineTab->ref_mainWindow = this;
	UnrealatedLauncher::Launcher_MarketTab *v_MarketTab = Gtk::manage(new UnrealatedLauncher::Launcher_MarketTab);
		ref_marketTab = v_MarketTab;
	UnrealatedLauncher::Launcher_CommunityTab *v_CommunityTab = Gtk::manage(new UnrealatedLauncher::Launcher_CommunityTab);
		ref_communityTab = v_CommunityTab;
	
	UnrealatedSettings *ref_settings = Gtk::manage(new UnrealatedSettings);
	UnrealatedLauncherRepoManager *ref_launcherRepoManager = Gtk::manage(new UnrealatedLauncherRepoManager);
	v_repoManagerRevealer.add(*ref_launcherRepoManager);
	ref_launcherRepoManager->launcherRepoManager_setSettingsReference(ref_settings);



	

//	LAUNCHER SETTINGS : Placed here for Z ordering.
	v_MainWindowGrid->attach(v_settingsRevealer, 1, 1, 1, 1);
	v_settingsRevealer.set_transition_type(Gtk::REVEALER_TRANSITION_TYPE_SLIDE_DOWN);
	v_settingsRevealer.set_transition_duration(750);
	
	// Pass settings reference to window object;
	ref_settings->ref_window = this;
	v_settingsRevealer.add(*ref_settings);
	
//	REPO MANAGER:
	v_MainWindowGrid->attach(v_repoManagerRevealer, 1, 2, 1, 1);
	v_repoManagerRevealer.set_transition_type(Gtk::REVEALER_TRANSITION_TYPE_SLIDE_DOWN);
	v_repoManagerRevealer.set_transition_duration(750);
	ref_launcherRepoManager->ref_window = this;

	v_MainWindowGrid->attach(v_repoManagerProgressBar, 1, 3, 1, 1);
	v_repoManagerProgressBar.set_name("PROGRESSBAR_SPECIAL");

//	END LAUNCHER SETTINGS 





// MAIN BAR:
		// Grid Container for Button Layout management: 
	Gtk::Grid *v_LauncherButtonGrid = Gtk::manage(new Gtk::Grid);
	v_LauncherButtonGrid->set_hexpand(true);
	v_LauncherButtonGrid->set_column_homogeneous(false);

		// Create ButtonBox for buttons [Styling]
	Gtk::ButtonBox *v_MainButtonBox = Gtk::manage(new Gtk::ButtonBox);
	v_MainButtonBox->set_hexpand(true);
	v_MainButtonBox->set_size_request(-1, 60);
	v_MainButtonBox->set_layout(Gtk::ButtonBoxStyle::BUTTONBOX_EXPAND);
	
	Gtk::StackSwitcher *v_MainButtonSwitcher = Gtk::manage(new Gtk::StackSwitcher);
	v_MainButtonSwitcher->set_homogeneous(); // <- This bitch.
	
		// Add buttons to Contianer
	v_LauncherButtonGrid->attach(*v_MainButtonSwitcher, 0, 0, 4, 1);
		// Progress Bars:
	v_LauncherButtonGrid->attach(v_ProjectsProgressBar, 0, 1, 1, 1);
	v_LauncherButtonGrid->attach(v_EnginesProgressBar, 1, 1, 1, 1);
	v_LauncherButtonGrid->attach(v_MarketProgressBar, 2, 1, 1, 1);
	v_LauncherButtonGrid->attach(v_CommunityProgressBar, 3, 1, 1, 1);

	Gtk::Separator *launcherButtonGrid_Separator = Gtk::manage(new Gtk::Separator(Gtk::ORIENTATION_VERTICAL));
	v_LauncherButtonGrid->attach(*launcherButtonGrid_Separator, 4, 0, 1, 2);
//	auto img_GitStatus = Gtk::manage(new Gtk::Image("../img/icons/git_normal.svg"));
//	v_LauncherButtonGrid->attach(*img_GitStatus, 4, 0, 1, 2);
//	
//	auto img_EpicStatus = Gtk::manage(new Gtk::Image("../img/icons/epic_normal.svg"));
//	v_LauncherButtonGrid->attach(*img_EpicStatus, 5, 0, 1, 2);
	
	
		// Add Main Button Box to Launcher Button Grid, then Add LBGrid to Main Window Grid
	v_LauncherButtonGrid->attach(*v_MainButtonBox, 0, 0, 4, 1);
	v_LauncherButtonGrid->attach(btn_LauncherPageStack, 0, 0, 3, 1);
	v_LauncherButtonGrid->attach(btn_Launcher, 6, 0, 1, 2);
	v_MainWindowGrid->attach(*v_LauncherButtonGrid, 1, 0, 1, 1);




//LAUNCHER BUTTON MENU:
//	v_LauncherMenu.set_halign(Gtk::ALIGN_END);


	Gtk::SeparatorMenuItem *menuItem_Launcher_Separator = Gtk::manage(new Gtk::SeparatorMenuItem);
	Gtk::SeparatorMenuItem *menuItem_Launcher_Separator1 = Gtk::manage(new Gtk::SeparatorMenuItem);


	v_LauncherMenu.append(menuItem_Launcher_ToggleUtilityBar);

	v_LauncherMenu.append(*menuItem_Launcher_Separator);

	v_LauncherMenu.append(menuItem_Launcher_RepoManager);
	v_LauncherMenu.append(menuItem_Launcher_Settings);

	v_LauncherMenu.append(*menuItem_Launcher_Separator1);

	v_LauncherMenu.append(menuItem_Launcher_About);
	v_LauncherMenu.append(menuItem_Launcher_Quit);
	
	menuItem_Launcher_Quit.signal_activate().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::on_QuitClicked));
	menuItem_Launcher_About.signal_activate().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::on_AboutClicked));
	menuItem_Launcher_ToggleUtilityBar.signal_toggled().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::on_ToggleUtilityBar_Clicked));
	menuItem_Launcher_Settings.signal_activate().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::on_Settings_Clicked));
	menuItem_Launcher_RepoManager.signal_activate().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::menuItem_Launcher_RepoManager_clicked));

	btn_Launcher.set_popup(v_LauncherMenu);
	v_LauncherMenu.show_all();
// END -- MAIN MENU BAR



// LAUNCHER TAB STACK
	v_MainButtonSwitcher->set_stack(v_LauncherPageStack);
	v_MainWindowGrid->set_hexpand(true);
	
	v_MainWindowGrid->attach(v_LauncherPageStack, 1, 5, 1, 1);
	v_LauncherPageStack.set_transition_type(Gtk::STACK_TRANSITION_TYPE_CROSSFADE);
	v_LauncherPageStack.add(*v_ProjectTab, "Projects", "PROJECTS");
	v_LauncherPageStack.add(*v_EngineTab, "Engines", "ENGINES");
	v_LauncherPageStack.add(*v_MarketTab, "Market", "MARKET");
	v_LauncherPageStack.add(*v_CommunityTab, "Community", "COMMUNITY");
// END TAB STACK




// UTILITY BAR
	v_UtilityBar.set_name("LAUNCHERUTILITYBAR");
//	v_UtilityBar.set_border_width(3);
	// Attach to revealer:
	v_UtilityBarRevealer.add(v_UtilityBar);
	v_UtilityBarRevealer.set_transition_type(Gtk::REVEALER_TRANSITION_TYPE_SLIDE_LEFT);
	v_UtilityBarRevealer.set_transition_duration(500);
	
	// Attach Revealer to main grid:
	v_MainWindowGrid->attach(v_UtilityBarRevealer, 0, 0, 1, 6);
	// Settings:
	v_UtilityBar.set_size_request(300, -1);
	v_UtilityBar.set_vexpand();
	v_UtilityBar.set_hexpand(false);
	
	// QuicKLaunch Button
	v_UtilityBar.attach(btn_QuickLaunch, 0, 0, 1, 1);
	btn_QuickLaunch.set_size_request(-1, 80);
	btn_QuickLaunch.set_hexpand();
	btn_QuickLaunch.set_border_width(10);
	btn_QuickLaunch.signal_clicked().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::on_QuickLaunch_clicked));
	// DEBUG: set name
	btn_QuickLaunch.set_label("_NO ENGINE SET");
	
	// HelpLink
	v_UtilityBar.attach(btn_link_help, 0, 1, 1, 1);
	btn_link_help.set_valign(Gtk::ALIGN_FILL);
	btn_link_help.set_hexpand();

// END - UTILITY BAR

	

	show_all();
	
	ReadPreferences();
	ref_launcherRepoManager->launcherRepoManager_setup();
	v_repoManagerProgressBar.hide();
	
	// IDLES:
	Glib::signal_timeout().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::launcherIdleCheck), 500);
	Glib::signal_timeout().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::idle_middleMen), 500);
	
	
} // END - Unrealated Window

// Unrealated Launcher Window Definitions
UnrealatedLauncher::UnrealatedLauncherWindow::~UnrealatedLauncherWindow(){
} // END - UnrealatedlauncherWindow Destructor.

															// BUTTON FUNCTIONS

void UnrealatedLauncher::UnrealatedLauncherWindow::on_QuitClicked(){
	ref_application->release();
//	hide();
}

void UnrealatedLauncher::UnrealatedLauncherWindow::on_AboutClicked(){
	v_aboutDialogue.set_transient_for(*this);
	v_aboutDialogue.set_program_name("Unrealated Launcher");
	v_aboutDialogue.set_version("11.2017");
	v_aboutDialogue.set_copyright("Lee Connor Williams");
	v_aboutDialogue.set_comments("Bringing the Unreal Engine to Linux!");
	
	std::ifstream fileStream("License.txt");
	std::string fileContents( (std::istreambuf_iterator<char>(fileStream)), (std::istreambuf_iterator<char>()));
	if(!fileContents.empty()){
		v_aboutDialogue.set_license(fileContents);
	}else{
		v_aboutDialogue.set_license("License Info missing!");
	}
	
	std::vector<Glib::ustring> author_list;
	author_list.push_back("Lee Connor Williams");
	// SHOW LIST:
	v_aboutDialogue.set_authors(author_list);
	v_aboutDialogue.set_modal(true);
	v_aboutDialogue.signal_response().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::On_AboutWindow_Close));
	v_aboutDialogue.run();
} // END - On AboutClicked

void UnrealatedLauncher::UnrealatedLauncherWindow::On_AboutWindow_Close(int p_response_id){
	switch (p_response_id){
		case Gtk::RESPONSE_CLOSE:
		case Gtk::RESPONSE_CANCEL:
		case Gtk::RESPONSE_DELETE_EVENT:
			v_aboutDialogue.hide();
		break; // END: Case Response Close|Cancel|Delete
		default: break;
	} // END - Switch
} // END - onAboutWindowClose


void UnrealatedLauncherWindow::on_ToggleUtilityBar_Clicked(){
		// If revealer is open, close...
	if(v_UtilityBarRevealer.get_child_revealed()){
		v_UtilityBarRevealer.set_reveal_child(false);
	} else{ // ... else, hide.
		v_UtilityBarRevealer.set_reveal_child(true);
	} // END - If else.
	menuItem_Launcher_ToggleUtilityBar.set_active(v_UtilityBarRevealer.get_reveal_child());
} // END - Utility Bar Toggle clicked


void UnrealatedLauncherWindow::on_QuickLaunch_clicked(){
	// Grab quicklaunch engine and run.
} // END - On Quicklaunch Clicked.

void UnrealatedLauncherWindow::on_Settings_Clicked(){
	v_settingsRevealer.set_reveal_child(true);
	menuItem_Launcher_Settings.set_sensitive(false);
	menuItem_Launcher_RepoManager.set_sensitive(false);
//	v_settingsRef->readPreferences();
}

void UnrealatedLauncherWindow::menuItem_Launcher_RepoManager_clicked(){
	v_repoManagerRevealer.set_reveal_child(true);
	menuItem_Launcher_Settings.set_sensitive(false);
	menuItem_Launcher_RepoManager.set_sensitive(false);
//	v_launcherRepoManagerRef->launcherRepoManager_setup();
	// MIDDLEMAN: EngineAdd- sets sensitivity.
	ref_engineTab->middleMan_openRepoManager_bool = true;
}






															// END -- Button Functions


void UnrealatedLauncherWindow::ReadPreferences(){
	CSimpleIniCaseA ini;
	string temp_saveData;
//	SI_Error temp_errorCheck = ini.SetValue("EngineGeneral", "EngineDir", p_installDir.c_str());

	SI_Error temp_errorCheck = ini.LoadFile(UnrealatedLauncherGlobal::launcherConfig.c_str());
	
	if(temp_errorCheck < 0){
		// File doesn't exist
		ref_settings->missingPrefs();

	} else if (ini.GetBoolValue("General", "FirstRun")){
		ini.SetBoolValue("General", "FirstRun", false);
		temp_errorCheck = ini.Save(temp_saveData);
		if(temp_errorCheck < 0) return;
		
		temp_errorCheck = ini.SaveFile(UnrealatedLauncherGlobal::launcherConfig.c_str());
		if(temp_errorCheck < 0) return;
	}
		// Read data:
		
//		ini.GetValue("General", "utilityBarOpen", NULL);
		v_UtilityBarRevealer.set_reveal_child(ini.GetBoolValue("General", "utilityBarOpen", true));
		menuItem_Launcher_ToggleUtilityBar.set_active(v_UtilityBarRevealer.get_reveal_child()); // Set menu bar active state to match.
		
		int defaultPage = ini.GetDoubleValue("General", "DefaultPage");
		switch(defaultPage){
			case 0: v_LauncherPageStack.set_visible_child("Projects");
			break;
			
			case 1: v_LauncherPageStack.set_visible_child("Engines");
			break;
			
			case 2: v_LauncherPageStack.set_visible_child("Market");
			break;
			
			case 3: v_LauncherPageStack.set_visible_child("Community");
			break;
		}

} // END - ReadPreferences.


void UnrealatedLauncherWindow::settings_closed(){
	menuItem_Launcher_RepoManager.set_sensitive(true);
	menuItem_Launcher_Settings.set_sensitive(true);
	v_settingsRevealer.set_reveal_child(false);
}

void UnrealatedLauncherWindow::repoManager_open(){
	v_settingsRevealer.set_reveal_child(false); // Closes the settings revealer if it was open.
	menuItem_Launcher_RepoManager_clicked();
}

void UnrealatedLauncherWindow::repoManager_closed(){
	menuItem_Launcher_RepoManager.set_sensitive(true);
	menuItem_Launcher_Settings.set_sensitive(true);
	v_repoManagerRevealer.set_reveal_child(false);
}

// IDLES:

bool UnrealatedLauncherWindow::launcherIdleCheck(){ // Runs every full second to check and then connect LauncherIdle.
	int totalTasks = ref_projectTab->GetPageTasks(); // + other pages;
	totalTasks += ref_engineTab->GetPageTasks();
	totalTasks += ref_marketTab->GetPageTasks();
	totalTasks += ref_communityTab->GetPageTasks();
	
	if(totalTasks != 0){ 
		Glib::signal_timeout().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::launcherIdle), 50);
		return 0;
	}else{
		v_ProjectsProgressBar.set_fraction(0);
		v_EnginesProgressBar.set_fraction(0);
		v_MarketProgressBar.set_fraction(0);
		v_CommunityProgressBar.set_fraction(0);
		return 1;
	}
	
} // END - launcher idle check.

bool UnrealatedLauncherWindow::launcherIdle(){ // Idle Update.
	int totalTasks = 0; // Total count.
	int pageTasks = 0; // Set per each page.
	
	// Project Tab:
	pageTasks = ref_projectTab->GetPageTasks();
	totalTasks += pageTasks;
	if(pageTasks != 0){
		if(pageTasks == 1 && ref_projectTab->GetPageTaskProgress() != 0){
			v_ProjectsProgressBar.set_fraction(ref_projectTab->GetPageTaskProgress());
		} else{
			v_ProjectsProgressBar.pulse();
		}
	} // END - Project Tab

	
	// Engine Tab:
	pageTasks = ref_engineTab->GetPageTasks();
	totalTasks += pageTasks;
	if(pageTasks != 0){
//		v_EnginesProgressBar.set_fraction(0);
		if(pageTasks == 1 && ref_engineTab->GetPageTaskProgress() != 0){
			v_EnginesProgressBar.set_fraction(ref_engineTab->GetPageTaskProgress());
		} else{
			v_EnginesProgressBar.pulse();
		}
	}  // END - Engine Tab tasks. 
	
	// Market Tab:
	pageTasks = ref_marketTab->GetPageTasks();
	totalTasks += pageTasks;
	if(pageTasks != 0){ // If page has tasks:
		if(pageTasks > 1){ // If tasks is higher than 1, pulse.
			v_MarketProgressBar.pulse();
		}else{
			v_MarketProgressBar.set_fraction(ref_marketTab->GetPageTaskProgress());
		} // End - Else.
	} // END - Market tab tasks

	// Community Tab:
	pageTasks = ref_communityTab->GetPageTasks();
	totalTasks += pageTasks;
	if(pageTasks != 0){ // If page has tasks:
		if(pageTasks > 1){ // If tasks is higher than 1, pulse.
			v_CommunityProgressBar.pulse();
		}else{
			v_CommunityProgressBar.set_fraction(ref_communityTab->GetPageTaskProgress());
		} // End - Else.
	} // END - Community tab tasks
	
	if(totalTasks == 0){
		// If total tasks is 0, restart the first check.
		Glib::signal_timeout().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::launcherIdleCheck), 500);
		cout << "No tasks left. Restarting Checker." << endl;
		return totalTasks;
	}else{
		return totalTasks;
	}
} // END - Launcher Idle.

bool UnrealatedLauncherWindow::idle_middleMen(){	// Idle Middleman that checks middleman variables.
// Engine Tab:
	// Repo Manager:
	if(ref_engineTab->middleMan_openRepoManager_bool){
		// Open repo manager from EngineAdd:Sidebar.
		menuItem_Launcher_RepoManager_clicked(); // Open Repo Manager.
		v_settingsRevealer.set_reveal_child(false);	// Hide settings if they were open.
		ref_engineTab->ref_EngineAdd->set_sensitive(false);
	} else {
		ref_engineTab->ref_EngineAdd->set_sensitive(true);
	}
	
	
	// Endless repeat:
	return true;
} // END - Middelman Idle.