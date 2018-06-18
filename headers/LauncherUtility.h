// COPYRIGHT © 2018
// AUTHOR(S):	Lee Connor Williams
// All Rights Reserved


#ifndef UNREALATEDLAUNCHERUTILITY
#define UNREALATEDLAUNCHERUTILITY

#include <gtkmm-3.0/gtkmm.h>
#include <string>

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>


namespace LauncherUtility{
	using namespace std;
	
// FORWARD DECLARATIONS:
	static void LauncherUtility_setGridSettings(Gtk::Grid* p_grid);
	static void LauncherUtility_setFlowboxSettings(Gtk::FlowBox* p_flowbox);
	static void LauncherUtility_setLabelWrapSettings(Gtk::Label* p_label, int p_lines ,int p_width, Pango::EllipsizeMode p_ellipsizeMode);
	static string LauncherUtility_removeFileFromString(string p_string);
	static string LauncherUtility_realPathFromUI(string p_path);
	static string LauncherUtility_realPath(string p_path);
	static bool LauncherUtility_checkFileExists(const string p_path);
	static void LauncherUtility_debug(string p_debugMessage);
	static string LauncherUtility_removePercent20(string p_path);	// Removes %20 from a path string.
	static string LauncherUtility_removeElementFromString(string p_stringToModify, string p_charactersToRemove, unsigned int p_length);	/*
	 * @p_stringToModify The string which is being modified.
	 * @p_charactersToRemove What characters to search for and remove.
	 * @p_length The size of the characters in which to remove.
	 */

// VOID/NON RETURN UTILITIES:

	static void LauncherUtility_setGridSettings(Gtk::Grid* p_grid){	// Persistent grid settings.  Used primarily for flowbox child grids.
		p_grid->set_border_width(10);
		p_grid->set_hexpand(false);
		p_grid->set_column_homogeneous(false);
		p_grid->set_row_homogeneous(false);
		p_grid->set_row_spacing(3);
		p_grid->set_column_spacing(7);
	} // END - Set Grid Settings.

	static void LauncherUtility_setFlowboxSettings(Gtk::FlowBox* p_flowbox){	// Persistent flowbox settings.  Used primarily for parent flowboxes.
		p_flowbox->set_hexpand(true);
		p_flowbox->set_vexpand(false);
		p_flowbox->set_homogeneous(false);
		p_flowbox->set_row_spacing(15);
		p_flowbox->set_column_spacing(5);
		p_flowbox->set_border_width(5);
	} // END - Flowbox settings.

	static void LauncherUtility_setLabelWrapSettings(Gtk::Label* p_label, int p_lines ,int p_width, Pango::EllipsizeMode p_ellipsizeMode){
	/*Label settings.
	* Used for simplifying repetative code.  
	* @parameter p_width: The width used for setting size request.
	* @parameter p_lines: The number of lines to span the label.
	* @parameter p_ellipsizeMode: The Pango Ellipsize mode to use.
	*/
		p_label->set_hexpand(true);
		p_label->set_line_wrap(true);
		p_label->set_lines(p_lines);
		p_label->set_size_request(p_width, -1);
		p_label->set_max_width_chars(1);
		p_label->set_ellipsize(p_ellipsizeMode);
	} // END - Set label wrap settings.




// RETURN UTILITIES:

	static string LauncherUtility_removeFileFromString(string p_string){ // Removes "file://" from a string.  Used when obtaining URIs from UI.
		return p_string.erase(7);
	} // END - remove file from string.


	static string LauncherUtility_realPathFromUI(string p_path){	// Combines "remove file from string" and realpath.  Must be given a path.
		if(!p_path.empty()){
			string temp_removedFile = LauncherUtility_removeFileFromString(p_path).c_str();
			string temp_path = LauncherUtility_realPath(temp_removedFile);
			return temp_path;
		}else{
			cerr << "WARNING:	RealPathFromUI: An Empty path was given!" << endl;
			return "";
		}
	} // END - RealPath from UI.
	
	static string LauncherUtility_realPath(string p_path){	// Returns the real (expanded, non-symlinked) path.
		char temp_resolvedPath[PATH_MAX];
		string temp_path = "";
		temp_path = realpath(p_path.c_str(), temp_resolvedPath);
		return temp_path;
	}

	static bool LauncherUtility_checkFileExists(const string p_path){	// Checks if a file exists.  Preferably; pass a string that has been ran through "realPath".
		ifstream file(p_path.c_str());
		return (bool)file;
	} // END - Check file exists.

	static void LauncherUtility_debug(string p_debugMessage){
		cout << "DEBUG:	" << p_debugMessage << endl;
	} // END- Debug.

	static string LauncherUtility_removePercent20(string p_path){	// Removes %20 from a path string.
		string stringToChange = p_path;
		for (size_t position = stringToChange.find("%20"); 
			position != string::npos; 
			position = stringToChange.find("%20", position) ){
			stringToChange.replace(position, 3, " ");
		}
		return stringToChange;
	}
	
	static string LauncherUtility_removeElementFromString(string p_stringToModify, string p_charactersToRemove, unsigned int p_length){
		string stringToChange = p_stringToModify;
		for (size_t position = stringToChange.find(p_charactersToRemove); 
			position != string::npos; 
			position = stringToChange.find(p_charactersToRemove, position) ){
			stringToChange.replace(position, p_length, "");
		}
		return stringToChange;
	} // END - Remove element from string.
	
} // END - Namespace.

#endif