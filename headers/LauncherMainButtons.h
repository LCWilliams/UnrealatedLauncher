#ifndef LAUNCHERMAINBUTTONS
#define LAUNCHERMAINBUTTONS
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/label.h>

namespace UnrealatedLauncher{
	
	class LauncherMainButton : public Gtk::Button{
	public: 
	LauncherMainButton();
	virtual ~LauncherMainButton();
	void SetButtonText(Glib::ustring p_Text);

	protected:
	Gtk::ProgressBar v_ButtonProgressBar;
	Gtk::Grid v_ButtonGridContainer;
	Gtk::Label v_ButtonLabel;
	}; // END -- LauncherMainButton Class
	
} // END - Unrealated Launcher namespace.
#endif