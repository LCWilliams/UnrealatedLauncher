#include <gtkmm.h>
#include <headers/UnrealatedLauncherWindow.h>


int main(int argc, char *argv[]){
	Glib::RefPtr<Gtk::Application> UnrealatedLauncherApplication = Gtk::Application::create(argc, argv, "LCWilliams.UnrealatedLauncher");
	
	UnrealatedLauncher::UnrealatedLauncherWindow window;
//	Gtk::Window v_window;

	return  UnrealatedLauncherApplication->run(window);
} // END - Main Function.