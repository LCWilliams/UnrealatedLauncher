#include <headers/LauncherMainPages.h>

using namespace UnrealatedLauncher;

Launcher_MarketTab::Launcher_MarketTab(){
	// Market Tab Grid settings:
	set_row_homogeneous(false);
	set_column_homogeneous(false);
//	set_hexpand();
//	set_vexpand();
	
	// DEBUG JUST TO SHOW SOMETHING
	Gtk::Button *btn_FILL = Gtk::manage(new Gtk::Button("FILL", false));
	attach(*btn_FILL, 0, 0, 1, 1);
	btn_FILL->set_hexpand();
	btn_FILL->set_vexpand();

} // END - Constructor.

Launcher_MarketTab::~Launcher_MarketTab(){
} // END -- Destructor.