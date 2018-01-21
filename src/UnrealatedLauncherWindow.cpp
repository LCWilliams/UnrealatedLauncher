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
	UnrealatedLauncher::Launcher_EngineTab *v_EngineTab = Gtk::manage(new UnrealatedLauncher::Launcher_EngineTab);
	UnrealatedLauncher::Launcher_MarketTab *v_MarketTab = Gtk::manage(new UnrealatedLauncher::Launcher_MarketTab);
	UnrealatedLauncher::Launcher_CommunityTab *v_CommunityTab = Gtk::manage(new UnrealatedLauncher::Launcher_CommunityTab);

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
//	Gtk::CheckMenuItem *menuItem_Launcher_ToggleUtilityBar = Gtk::manage(new Gtk::CheckMenuItem("_Utility Bar", true));
	menuItem_Launcher_ToggleUtilityBar.set_label("Utility Bar");
	v_LauncherMenu.append(menuItem_Launcher_ToggleUtilityBar);
	v_LauncherMenu.append(*menuItem_Launcher_About);
	v_LauncherMenu.append(*menuItem_Launcher_Quit);
	
	menuItem_Launcher_Quit->signal_activate().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::on_QuitClicked));
	menuItem_Launcher_About->signal_activate().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::on_AboutClicked));
	menuItem_Launcher_ToggleUtilityBar.signal_toggled().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::on_ToggleUtilityBar_Clicked));

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
	// Attach to main grid:
	v_MainWindowGrid->attach(v_UtilityBar, 0, 0, 1, 3);
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
} // END - Unrealated Window

// Unrealated Launcher Window Definitions
UnrealatedLauncher::UnrealatedLauncherWindow::~UnrealatedLauncherWindow(){
} // END - UnrealatedlauncherWindow Destructor.

void UnrealatedLauncher::UnrealatedLauncherWindow::on_QuitClicked(){
	hide();
}

void UnrealatedLauncher::UnrealatedLauncherWindow::on_AboutClicked(){
	v_aboutDialogue.set_transient_for(*this);
	v_aboutDialogue.set_program_name("Unrealated Launcher");
	v_aboutDialogue.set_version("11.2017");
	v_aboutDialogue.set_copyright("Lee Connor Williams");
	v_aboutDialogue.set_comments("An Unreal Engine Launcher for Linux, empowering creativity");
	v_aboutDialogue.set_license("LICENSE INFORMATION BULLSHIT");
	
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

// BUTTON FUNCTIONS

void UnrealatedLauncherWindow::on_ToggleUtilityBar_Clicked(){
		// If bool is true, show...
	if(menuItem_Launcher_ToggleUtilityBar.get_active()){
		v_UtilityBar.show_all();
	} else{ // ... else, hide.
		v_UtilityBar.hide();
	} // END - If else.
} // END - Utility Bar Toggle clicked


void UnrealatedLauncherWindow::on_QuickLaunch_clicked(){
	// Grab quicklaunch engine and run.
} // END - On Quicklaunch Clicked.
// END -- Button Functions



/*LEGACY
 * 
 * 	//Main Menu Bar
	Gtk::MenuBar *v_mainMenuBar = Gtk::manage(new Gtk::MenuBar());
	v_mainWindowBox->pack_start(*v_mainMenuBar, Gtk::PACK_SHRINK, 0);
	
		// MENU : FILE
	Gtk::MenuItem *v_menuItem_Launcher = Gtk::manage(new Gtk::MenuItem("_Launcher", true));
	v_mainMenuBar->append(*v_menuItem_Launcher);
	
	Gtk::Menu *v_fileMenu = Gtk::manage(new Gtk::Menu());
	v_menuItem_Launcher->set_submenu(*v_fileMenu);

		// MENU :: ABOUT
	Gtk::MenuItem *v_MenuItem_About = Gtk::manage(new Gtk::MenuItem("_About", true));
	v_fileMenu->append(*v_MenuItem_About);
	v_MenuItem_About->signal_activate().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::on_AboutClicked));

	
	Gtk::MenuItem *v_MenuItem_Quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
	v_fileMenu->append(*v_MenuItem_Quit);
	v_MenuItem_Quit->signal_activate().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::on_QuitClicked));
 * 
void UnrealatedLauncher::UnrealatedLauncherWindow::on_ButtonClicked(){
}

 * 	Gtk::Notebook *mainTabNB = Gtk::manage(new Gtk::Notebook);
	v_mainWindowBox->add(*mainTabNB);
	mainTabNB->append_page(*v_ProjectsWindow, Glib::ustring("PROJECTS"));
	
	Gtk::Box *v_TestBox = Gtk::manage(new Gtk::Box);
	mainTabNB->append_page(*v_TestBox, "TEST");
	
//	mainTabNB->set_tab_pos(Gtk::POS_LEFT);
 * 
void UnrealatedLauncher::UnrealatedLauncherWindow::dialog(Glib::ustring p_message){
	Gtk::MessageDialog v_dialog(p_message, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
	v_dialog.set_title("Dialoge Window!");
	v_dialog.run();
} // END - Dialogue
*/


// BUTTON/IMAGE STUFF:
//auto image = Gtk::manage(new Gtk::Image("path/to/image.png"));
//button->add(*image);

//image->set(image->get_pixbuf()->scale_simple(32, 37, Gdk::InterpType::INTERP_BILINEAR));
