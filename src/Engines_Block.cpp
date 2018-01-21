#include <Engines_Block.h>

using namespace UnrealatedLauncher;

EngineBlock::EngineBlock(string p_installDir, string p_SourceDir, string p_customImageDir, string p_CustomLabel, int p_versionNumber, int p_hotfixNumber){
//	Gtk::ButtonBox *v_ButtonBox = Gtk::manage(new Gtk::ButtonBox);

// Grid settings:
//	set_size_request(300, 200);
	set_border_width(0);
	set_hexpand(false);
	set_vexpand(false);
	
	// Options Grid:
	v_OptionsGrid.set_name("engineBlockOptionsGrid");
	v_OptionsGrid.set_hexpand();


	v_EngineInstallDir = p_installDir;


// Custom Image Dir:
	if(p_customImageDir != "" && checkImageExists(p_customImageDir)){ // Check if a custom image was set...
		v_CustomEngineImageDir = p_customImageDir;
		img_EngineImage.set(p_customImageDir);
		img_EngineImage.set(img_EngineImage.get_pixbuf()->scale_simple(300, 175, Gdk::INTERP_BILINEAR));
	} else { // If not, use default
		img_EngineImage.set("../img/guiElement/engine_image_default.svg");
		img_EngineImage.set(img_EngineImage.get_pixbuf()->scale_simple(300, 175, Gdk::INTERP_BILINEAR));
	} // END - custom image dir.


	v_EngineLabel = to_string(p_versionNumber) + "." + to_string(p_hotfixNumber) + "\n" + p_CustomLabel;
	v_DisplayedEngineLabel.set_label(v_EngineLabel);


// CSS STYLING:
	if(p_SourceDir != ""){ // Check if source directory is set, then change name of the block to correspond. 
		v_EngineSourceDir = p_SourceDir;
		set_name("SourceEngineBlock");
		v_EngineIsBinary = true;
	} else {
		set_name("BinaryEngineBlock");
		v_EngineIsBinary = false;
	}
	btn_EngineLaunch.set_name("EngineLaunchButton");
	btn_Options.set_name("BlockOptionsButton");


// Attachment:
	attach(v_DisplayedEngineLabel, 0, 0, 1, 1);
	attach(img_EngineImage, 0, 0, 1, 1);
	attach(v_ProgressBar, 0, 1, 1, 1);
	attach(v_buttonBox, 0, 2, 1, 1);


// Buttons
//	v_buttonBox.set_hexpand();
	v_buttonBox.set_size_request(-1, 50);
	v_buttonBox.set_layout(Gtk::BUTTONBOX_EXPAND);
	v_buttonBox.set_homogeneous(false);
	v_buttonBox.pack_start(btn_EngineLaunch, Gtk::PACK_EXPAND_WIDGET, 0);
	v_buttonBox.pack_end(btn_Options, Gtk::PACK_SHRINK, 0);


// LABELS:
	v_DisplayedEngineLabel.set_hexpand();
	v_DisplayedEngineLabel.set_line_wrap();
	v_DisplayedEngineLabel.set_lines(2);
	v_DisplayedEngineLabel.set_size_request(280, -1);
	v_DisplayedEngineLabel.set_max_width_chars(1);
	v_DisplayedEngineLabel.set_ellipsize(Pango::ELLIPSIZE_END);
	v_DisplayedEngineLabel.set_valign(Gtk::ALIGN_END);
	v_DisplayedEngineLabel.set_halign(Gtk::ALIGN_END);
	
	btn_EngineLaunch.set_label("LAUNCH");
//	btn_Options.set_label("OPTIONS");


	// Options Menu
	btn_Options.set_menu(v_optionsMenu);
	
	v_optionsMenu.append(menuItem_openPreferences);
	menuItem_openPreferences.set_label("Preferences");
	
	v_optionsMenu.show_all();

	// Button Signal Handlers.
	menuItem_openPreferences.signal_activate().connect(sigc::mem_fun(*this, &EngineBlock::menuItem_openPreferences_clicked));
	btn_EngineLaunch.signal_clicked().connect(sigc::mem_fun(*this, &EngineBlock::btn_EngineLaunch_Clicked));


// SET VARIABLES... also still probably pointless.
} // END - Engine Block Constructor

EngineBlock::~EngineBlock(){
}// END - Engine block Destructor

// BUTTON FUNCTIONS:
void EngineBlock::btn_EngineLaunch_Clicked(){
	
} // END - EngineLaunch Btn Clicked.

void EngineBlock::menuItem_openPreferences_clicked(){
	EngineBlockOptions *window_blockOptions = new EngineBlockOptions;
	window_blockOptions->show_all();
}

// END - Button Functions

// CHECKERS:
bool EngineBlock::checkImageExists(const string& p_imageDir){
	ifstream file(p_imageDir.c_str());
	return (bool)file;
} // END - CheckImageExists.