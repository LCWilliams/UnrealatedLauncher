#ifndef UNREALATEDLAUNCHERWINDOW
#define UNREALATEDLAUNCHERWINDOW

#include <gtkmm.h>

namespace UnrealatedLauncher{

class UnrealatedLauncherWindow : public Gtk::Window {
	
	public:
	UnrealatedLauncherWindow();
	virtual ~UnrealatedLauncherWindow();
	
	protected:
	void on_QuitClicked();
	void dialog(Glib::ustring message);
	void on_ButtonClicked();

}; // END - Class: Unrealated Launcher Window.

} // END - Namespace

#endif // UNREALATEDLAUNCHERWINDOW