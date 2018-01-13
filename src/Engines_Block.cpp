#include <Engines_Block.h>

using namespace UnrealatedLauncher;

EngineBlock::EngineBlock(){
	Gtk::ButtonBox *v_ButtonBox = Gtk::manage(new Gtk::ButtonBox);

// Grid settings:
	set_border_width(5);
	set_name("EngineBlock"); // for CSS styling
	set_hexpand(false);
	set_vexpand(false);
//	set_halign(Gtk::ALIGN_FILL);
	set_valign(Gtk::ALIGN_START);

	
// DEBUG/TESTING PRESET:
	img_EngineImage.set("../img/guiElement/engine_image_default.svg");
	v_DisplayedEngineLabel.set_label("ENGINE [Null]");
//	img_EngineTypeIndicator.Image("../img/guiElement/engine_type_source.svg");
	img_EngineTypeIndicator.set("../img/guiElement/engine_type_source.svg");

// ELEMENT LAYOUT:
	// engine type image
	attach(img_EngineTypeIndicator, 0, 0, 1, 2);
	img_EngineTypeIndicator.set_vexpand();

	// Engine label
	attach(v_DisplayedEngineLabel, 1, 1, 2, 1);
	v_DisplayedEngineLabel.set_valign(Gtk::ALIGN_END);
	v_DisplayedEngineLabel.set_halign(Gtk::ALIGN_START);
	
	// engine decorative image
	attach(img_EngineImage, 1, 0, 1, 2);

	// Buttons
	attach(*v_ButtonBox, 0, 2, 2, 1);
	v_ButtonBox->set_hexpand();
	v_ButtonBox->set_layout(Gtk::BUTTONBOX_EXPAND);
	v_ButtonBox->set_homogeneous(false);
	v_ButtonBox->pack_start(btn_EngineLaunch, Gtk::PACK_EXPAND_WIDGET, 0);
	v_ButtonBox->pack_end(btn_Options, Gtk::PACK_SHRINK, 0);

	btn_EngineLaunch.set_label("LAUNCH");
	btn_Options.set_label("OPTIONS");
// END Element Layout

} // END - Engine Block Constructor

UnrealatedLauncher::EngineBlock::~EngineBlock(){
}// END - Engine block Destructor

// BUTTON FUNCTIONS:
void UnrealatedLauncher::EngineBlock::btn_EngineLaunch_Clicked(){
	
} // END - EngineLaunch Btn Clicked.