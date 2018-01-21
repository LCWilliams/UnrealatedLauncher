#include <headers/Engines_Block.h>
//#include <headers/UnrealatedLauncherWindow.h>

using namespace UnrealatedLauncher;

EngineBlockOptions::EngineBlockOptions(){
// WINDOW SETTINGS:
//	set_transient_for(*p_parentWindow);
//	auto txt_windowTitle = "Settings | " + p_parentBlock.v_EngineLabel;
//	set_title(txt_windowTitle);
	set_default_size(600, 500);
	
	add(v_scrolledWindow);
	v_scrolledWindow.add(v_windowGrid);
	
	
	
} // End - Constructor.

EngineBlockOptions::~EngineBlockOptions(){
} // End - Destructor.