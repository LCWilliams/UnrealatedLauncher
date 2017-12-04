#include <headers/UnrealatedLauncherWindow.h>

UnrealatedLauncher::UnrealatedLauncherWindow::UnrealatedLauncherWindow(){
	
	set_default_size(400, 200);
	set_title("Unrealated Launcher");
	
	Gtk::Box *v_mainWindowBox = Gtk::manage(new  Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0)); // Main Box: Vertical.
	add(*v_mainWindowBox);
	
	
	//Main Menu Bar
	Gtk::MenuBar *v_mainMenuBar = Gtk::manage(new Gtk::MenuBar());
	v_mainWindowBox->pack_start(*v_mainMenuBar, Gtk::PACK_SHRINK, 0);
	
		// MENU : FILE
	Gtk::MenuItem *v_menuItem_File = Gtk::manage(new Gtk::MenuItem("_File", true));
	v_mainMenuBar->append(*v_menuItem_File);
	
	Gtk::Menu *v_fileMenu = Gtk::manage(new Gtk::Menu());
	v_menuItem_File->set_submenu(*v_fileMenu);
	
	Gtk::MenuItem *v_MenuItem_Quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
	v_fileMenu->append(*v_MenuItem_Quit);
	v_MenuItem_Quit->signal_activate().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::on_QuitClicked));
	
		// MENU :: ABOUT
	Gtk::MenuItem *v_MenuItem_About = Gtk::manage(new Gtk::MenuItem("_About", true));
	v_mainMenuBar->append(*v_MenuItem_About);
	
	
		// GRID
	Gtk::Grid *v_mainGrid = Gtk::manage(new Gtk::Grid);
	v_mainGrid->set_border_width(10);
	v_mainWindowBox->add(*v_mainGrid);
	
		// BUTTON, because I'm lazy.
	Gtk::Button *v_Button1 = Gtk::manage(new Gtk::Button("Button! :D"));
	v_Button1->set_hexpand(true);
	v_Button1->set_vexpand(true);
	v_mainGrid->attach(*v_Button1, 0, 0, 1, 1);
	v_Button1->signal_clicked().connect(sigc::mem_fun(*this, &UnrealatedLauncherWindow::on_ButtonClicked));
	
	v_mainWindowBox->show_all();
}

// Unrealated Launcher Window Definitions
UnrealatedLauncher::UnrealatedLauncherWindow::~UnrealatedLauncherWindow(){
} // END - UnrealatedlauncherWindow Destructor.

void UnrealatedLauncher::UnrealatedLauncherWindow::on_QuitClicked(){
	hide();
}

void UnrealatedLauncher::UnrealatedLauncherWindow::on_ButtonClicked(){
	dialog("Button pressed");
}

void UnrealatedLauncher::UnrealatedLauncherWindow::dialog(Glib::ustring p_message){
	Gtk::MessageDialog v_dialog(p_message, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
	v_dialog.set_title("Dialoge Window!");
	v_dialog.run();
}