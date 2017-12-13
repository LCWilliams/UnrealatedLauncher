#include <headers/UnrealatedLauncherWindow.h>
#include <iostream>
#include <gtkmm.h>

using namespace std;
using namespace UnrealatedLauncher;

UnrealatedLauncherWindow::UnrealatedLauncherWindow(){
	set_default_size(800, 500);
	set_title("Unrealated Launcher");
	
	Gtk::Grid *v_MainWindowGrid = Gtk::manage(new Gtk::Grid);
	v_MainWindowGrid->set_row_homogeneous(false);
	add(*v_MainWindowGrid);

	// Create Container for buttons:
	Gtk::ButtonBox *v_MainButtonBox = Gtk::manage(new Gtk::ButtonBox);

	// Projects, Engines, Market, Community buttons:
	btn_Projects.add_label("PROJECTS");
	btn_Engines.add_label("ENGINES");
	btn_Market.add_label("MARKET");
	btn_Community.add_label("COMMUNITY");
	
	btn_Test.SetButtonText("TEST");
	
	// Add buttons to Contianer
	v_MainButtonBox->add(btn_Projects);
	v_MainButtonBox->add(btn_Engines);
	v_MainButtonBox->add(btn_Market);
	v_MainButtonBox->add(btn_Community);
//	v_MainButtonBox->add(btn_Test);
	// Button Bindings:
	btn_Projects.signal_clicked().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::btn_ProjectsClicked));
	btn_Engines.signal_clicked().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::btn_EnginesClicked));
	btn_Market.signal_clicked().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::btn_MarketClicked));
	btn_Community.signal_clicked().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::btn_CommunityClicked));
	
	// Add container to main grid:
	v_MainWindowGrid->attach(*v_MainButtonBox, 0, 0, 1, 1);
	v_MainButtonBox->set_hexpand(true);
	v_MainButtonBox->set_layout(Gtk::ButtonBoxStyle::BUTTONBOX_EXPAND);
//	Gtk::Revealer *v_MainWindow = Gtk::manage(new Gtk::Revealer);
//	v_MainWindow->add(v_ProjectsWindow);


// CREATE AS CLASS VARIABLES
	Gtk::Image *img_GitStatus = Gtk::manage(new Gtk::Image);
	Gtk::Image *img_EpicStatus = Gtk::manage(new Gtk::Image);
	Gtk::Button *btn_Launcher = Gtk::manage(new Gtk::Button("LAUNCHER"));

	v_MainWindowGrid->attach(*img_GitStatus, 1, 0, 1, 1);
	v_MainWindowGrid->attach(*img_EpicStatus, 1, 0, 1, 1);
	v_MainWindowGrid->attach(*btn_Launcher, 1, 0, 1, 1);
//	v_MainWindowGrid->attach(btn_Test, 2, 0, 1, 1);


//	Gtk::ProgressBar *v_MainProgressBar = Gtk::manage(new Gtk::ProgressBar);
//	v_MainWindowGrid->attach(*v_MainProgressBar, 0, 1, 2, 1);
//	UnrealatedLauncher::ProjectTabContainer *v_ProjectsWindow = Gtk::manage(new UnrealatedLauncher::ProjectTabContainer);
	v_MainWindowGrid->attach(v_ProjectsWindow, 0, 2, 2, 1);

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
		break;
		default:
		break;
	} // END - Switch
} // END - onAboutWindowClose

// BUTTON FUNCTIONS
void UnrealatedLauncherWindow::btn_ProjectsClicked(){
	 UpdateMainWindow(1);
} // END - Projects Button Clicked

void UnrealatedLauncherWindow::btn_EnginesClicked(){
	UpdateMainWindow(2);
} // END - Engine button Clicked.

void UnrealatedLauncherWindow::btn_MarketClicked(){
	UpdateMainWindow(3);
} // END - Market button clicked.

void UnrealatedLauncherWindow::btn_CommunityClicked(){
	UpdateMainWindow(4);
} // END - Community Button Clicked
// END -- Button Functions

void UnrealatedLauncherWindow::ToggleMainButtons(bool p_Enable){
// Disable, or Enable all the main buttons.
	if(p_Enable){
		btn_Projects.set_sensitive(true);
		btn_Projects.set_state_flags(Gtk::STATE_FLAG_NORMAL);
		btn_Engines.set_sensitive(true);
		btn_Engines.set_state_flags(Gtk::STATE_FLAG_NORMAL);
		btn_Market.set_sensitive(true);
		btn_Market.set_state_flags(Gtk::STATE_FLAG_NORMAL);
		btn_Community.set_sensitive(true);
		btn_Community.set_state_flags(Gtk::STATE_FLAG_NORMAL);
	} else{
		UnrealatedLauncherWindow::btn_Projects.set_sensitive(false);
		UnrealatedLauncherWindow::btn_Engines.set_sensitive(false);
		UnrealatedLauncherWindow::btn_Market.set_sensitive(false);
		UnrealatedLauncherWindow::btn_Community.set_sensitive(false);
	} // END - If/Else
} // END - Toggle Main Button

void UnrealatedLauncherWindow::UpdateMainWindow(int p_NewPage){
	// Enable Main Buttons
	ToggleMainButtons(true);
	//  Hide all screens:
	v_ProjectsWindow.set_visible(false);
	//Engines.SetVisible.False
	//Market.SetVisible.false
	//Community.SetVisible.false

	switch (p_NewPage){
		case 0:
		break;
		// ORDER OF OPERATION:
		// Button sensitive: Disable button from being pressed repeatedly.
		// SEMIOTIC: Show the current "tab" using button state flag
		// Show the window
		case 1: // Projects
			btn_Projects.set_sensitive(false); 
			btn_Projects.set_state_flags(Gtk::STATE_FLAG_CHECKED);
			v_ProjectsWindow.set_visible(true);
		break;
		
		case 2: // Engines
			btn_Engines.set_sensitive(false);
			btn_Engines.set_state_flags(Gtk::STATE_FLAG_CHECKED);
		break;
		
		case 3: // Market
			btn_Market.set_sensitive(false);
			btn_Market.set_state_flags(Gtk::STATE_FLAG_CHECKED);
		break;
		
		case 4: // Community
			btn_Community.set_sensitive(false);
			btn_Community.set_state_flags(Gtk::STATE_FLAG_CHECKED);
		break;
		
		default: std::cout << "NOPE!";
	} // END - NewPage Case
} // END - Update Main Window

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