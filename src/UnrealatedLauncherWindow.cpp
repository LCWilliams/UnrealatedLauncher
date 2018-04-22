#include <headers/UnrealatedLauncherWindow.h>
#include <iostream>

using namespace std;
using namespace UnrealatedLauncher;

UnrealatedLauncherWindow::UnrealatedLauncherWindow(){
	set_default_size(1200, 800);
	set_title("Unrealated Launcher");
	
	// Main Window Grid.
	Gtk::Grid *v_MainWindowGrid = Gtk::manage(new Gtk::Grid);
	v_MainWindowGrid->set_row_homogeneous(false);
	v_MainWindowGrid->set_column_homogeneous(false);
	add(*v_MainWindowGrid); // Add to window
	
	// CREATE ALL WINDOWS, SET GTK TO MANAGE:	
	UnrealatedLauncher::Launcher_ProjectTab *v_ProjectTab = Gtk::manage(new UnrealatedLauncher::Launcher_ProjectTab);
	v_projectsTabRef = v_ProjectTab;
	UnrealatedLauncher::Launcher_EngineTab *v_EngineTab = Gtk::manage(new UnrealatedLauncher::Launcher_EngineTab);
	v_enginesTabRef = v_EngineTab;
	UnrealatedLauncher::Launcher_MarketTab *v_MarketTab = Gtk::manage(new UnrealatedLauncher::Launcher_MarketTab);
	v_marketTabRef = v_MarketTab;
	UnrealatedLauncher::Launcher_CommunityTab *v_CommunityTab = Gtk::manage(new UnrealatedLauncher::Launcher_CommunityTab);
	v_communityTabRef = v_CommunityTab;
	UnrealatedSettings *v_settingsGrid = Gtk::manage(new UnrealatedSettings);


//	LAUNCHER SETTINGS : Placed here for Z ordering.
	v_MainWindowGrid->attach(v_settingsRevealer, 1, 1, 1, 1);
	v_settingsRevealer.set_transition_type(Gtk::REVEALER_TRANSITION_TYPE_SLIDE_DOWN);
	v_settingsRevealer.set_transition_duration(750);
	
	// Pass settings reference to window object;
	v_settingsGrid->v_windowRef = this;
	v_settingsRevealer.add(*v_settingsGrid);
	
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

	auto img_GitStatus = Gtk::manage(new Gtk::Image("../img/icons/git_normal.svg"));
	v_LauncherButtonGrid->attach(*img_GitStatus, 4, 0, 1, 2);
	
	auto img_EpicStatus = Gtk::manage(new Gtk::Image("../img/icons/epic_normal.svg"));
	v_LauncherButtonGrid->attach(*img_EpicStatus, 5, 0, 1, 2);
	
	
		// Add Main Button Box to Launcher Button Grid, then Add LBGrid to Main Window Grid
	v_LauncherButtonGrid->attach(*v_MainButtonBox, 0, 0, 4, 1);
	v_LauncherButtonGrid->attach(btn_LauncherPageStack, 0, 0, 3, 1);
	v_LauncherButtonGrid->attach(btn_Launcher, 6, 0, 1, 2);
	v_MainWindowGrid->attach(*v_LauncherButtonGrid, 1, 0, 1, 1);
	
//LAUNCHER BUTTON MENU:
	v_LauncherMenu.set_halign(Gtk::ALIGN_END);
//	v_LauncherMenu.set_size_request(100, -1);
	
	Gtk::MenuItem *menuItem_Launcher_About = Gtk::manage(new Gtk::MenuItem("_About", true));
	Gtk::MenuItem *menuItem_Launcher_Quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
//	Gtk::MenuItem *menuItem_Launcher_Settings = Gtk::manage(new Gtk::MenuItem("_Settings", true));
//	Gtk::CheckMenuItem *menuItem_Launcher_ToggleUtilityBar = Gtk::manage(new Gtk::CheckMenuItem("_Utility Bar", true));
	menuItem_Launcher_ToggleUtilityBar.set_label("Utility Bar");
	menuItem_Launcher_Settings.set_label("Settings");
	v_LauncherMenu.append(menuItem_Launcher_Settings);
	v_LauncherMenu.append(menuItem_Launcher_ToggleUtilityBar);
	v_LauncherMenu.append(*menuItem_Launcher_About);
	v_LauncherMenu.append(*menuItem_Launcher_Quit);
	
	menuItem_Launcher_Quit->signal_activate().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::on_QuitClicked));
	menuItem_Launcher_About->signal_activate().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::on_AboutClicked));
	menuItem_Launcher_ToggleUtilityBar.signal_toggled().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::on_ToggleUtilityBar_Clicked));
	menuItem_Launcher_Settings.signal_activate().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::on_Settings_Clicked));

	btn_Launcher.set_popup(v_LauncherMenu);
	v_LauncherMenu.show_all();
// END -- MAIN MENU BAR



// LAUNCHER TAB STACK
	v_MainButtonSwitcher->set_stack(v_LauncherPageStack);
	v_MainWindowGrid->set_hexpand(true);
	
	v_MainWindowGrid->attach(v_LauncherPageStack, 1, 2, 1, 1);
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
	v_MainWindowGrid->attach(v_UtilityBarRevealer, 0, 0, 1, 3);
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
	btn_link_help.set_valign(Gtk::ALIGN_END);
	btn_link_help.set_hexpand();
	btn_link_help.set_label("GIB MONEH PLZ");
	btn_link_help.set_uri("https://docs.unrealengine.com/latest/INT/");

// END - UTILITY BAR

	

	show_all();
	
	ReadPreferences();
	
	Glib::signal_timeout().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::launcherIdleCheck), 500);
	
} // END - Unrealated Window

// Unrealated Launcher Window Definitions
UnrealatedLauncher::UnrealatedLauncherWindow::~UnrealatedLauncherWindow(){
} // END - UnrealatedlauncherWindow Destructor.

															// BUTTON FUNCTIONS

void UnrealatedLauncher::UnrealatedLauncherWindow::on_QuitClicked(){
	hide();
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
//	v_settingsRef->readPreferences();
}






															// END -- Button Functions






void UnrealatedLauncherWindow::ReadPreferences(){
	CSimpleIniCaseA ini;
	string temp_saveData;
	string iniFileDir = "./config/UnrealatedLauncher.ini";
//	SI_Error temp_errorCheck = ini.SetValue("EngineGeneral", "EngineDir", p_installDir.c_str());

	SI_Error temp_errorCheck = ini.LoadFile(iniFileDir.c_str());
	
	if(temp_errorCheck < 0){
		// File doesn't exist
		v_settingsRef->missingPrefs();

	} else if (ini.GetBoolValue("General", "FirstRun")){
		ini.SetBoolValue("General", "FirstRun", false);
		temp_errorCheck = ini.Save(temp_saveData);
		if(temp_errorCheck < 0) return;
		
		temp_errorCheck = ini.SaveFile(iniFileDir.c_str());
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
	menuItem_Launcher_Settings.set_sensitive(true);
	v_settingsRevealer.set_reveal_child(false);
}

bool UnrealatedLauncherWindow::launcherIdleCheck(){ // Runs every full second to check and then connect LauncherIdle.
	int totalTasks = v_projectsTabRef->GetPageTasks(); // + other pages;
	totalTasks += v_enginesTabRef->GetPageTasks();
	totalTasks += v_marketTabRef->GetPageTasks();
	totalTasks += v_communityTabRef->GetPageTasks();
	
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
	
}

bool UnrealatedLauncherWindow::launcherIdle(){ // Idle Update.
	int totalTasks = 0; // Total count.
	int pageTasks = 0; // Set per each page.
	
	// Project Tab:
	pageTasks = v_projectsTabRef->GetPageTasks();
	totalTasks += pageTasks;
	if(pageTasks != 0){
		if(pageTasks == 1 && v_projectsTabRef->GetPageTaskProgress() != 0){
			v_ProjectsProgressBar.set_fraction(v_projectsTabRef->GetPageTaskProgress());
		} else{
			v_ProjectsProgressBar.pulse();
		}
	} // END - Project Tab

	
	// Engine Tab:
	pageTasks = v_enginesTabRef->GetPageTasks();
	totalTasks += pageTasks;
	if(pageTasks != 0){
//		v_EnginesProgressBar.set_fraction(0);
		if(pageTasks == 1 && v_enginesTabRef->GetPageTaskProgress() != 0){
			v_EnginesProgressBar.set_fraction(v_enginesTabRef->GetPageTaskProgress());
		} else{
			v_EnginesProgressBar.pulse();
		}
	}  // END - Engine Tab tasks. 
	
	// Market Tab:
	pageTasks = v_marketTabRef->GetPageTasks();
	totalTasks += pageTasks;
	if(pageTasks != 0){ // If page has tasks:
		if(pageTasks > 1){ // If tasks is higher than 1, pulse.
			v_MarketProgressBar.pulse();
		}else{
			v_MarketProgressBar.set_fraction(v_marketTabRef->GetPageTaskProgress());
		} // End - Else.
	} // END - Market tab tasks

	// Community Tab:
	pageTasks = v_communityTabRef->GetPageTasks();
	totalTasks += pageTasks;
	if(pageTasks != 0){ // If page has tasks:
		if(pageTasks > 1){ // If tasks is higher than 1, pulse.
			v_CommunityProgressBar.pulse();
		}else{
			v_CommunityProgressBar.set_fraction(v_communityTabRef->GetPageTaskProgress());
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