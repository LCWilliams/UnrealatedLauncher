//#include <gtkmm.h>
#include <gtkmm/application.h>
#include <headers/UnrealatedLauncherWindow.h>
//#include <headers/LauncherSettings.h>


int main(int argc, char *argv[]){
	Glib::RefPtr<Gtk::Application> UnrealatedLauncherApplication = Gtk::Application::create(argc, argv, "LCWilliams.UnrealatedLauncher");
	UnrealatedLauncher::UnrealatedLauncherWindow window;
	return  UnrealatedLauncherApplication->run(window);
} // END - Main Function.