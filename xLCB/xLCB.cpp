#include "xLCB.h"
#include "plugin.h"

// function prototypes


// Variables
const char *szxLCBInfo = "xLCB v1 plugin by ThunderCls - 2016\n"
						 "Blog: http://reversec0de.wordpress.com\n"
						 "Features & Usage:\n"
						 " - Export/Import/Clear User-defined Comments & Labels\n"
						 " - Export/Import Breakpoints\n"
						 " - Fully compatible with LCB OllyDbg Plugin by scherzo\n\n";


// Plugin SDK required variables
#define plugin_name "xLCB" // rename to your plugins name 
#define plugin_version 1

// GLOBAL Plugin SDK variables
int pluginHandle;
HWND hwndDlg;
int hMenu;
int hMenuDisasm;
int hMenuDump;
int hMenuStack;


/*====================================================================================
  Main entry function for a DLL file  - required.
--------------------------------------------------------------------------------------*/
extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    return TRUE;
}


/*====================================================================================
  pluginit - Called by debugger when plugin.dp32 is loaded - needs to be EXPORTED
  
  Arguments: initStruct - a pointer to a PLUG_INITSTRUCT structure

  Notes:     you must fill in the pluginVersion, sdkVersion and pluginName members. 
             The pluginHandle is obtained from the same structure - it may be needed in
             other function calls.
 
             you can call your own setup routine from within this function to setup 
             menus and commands, and pass the initStruct parameter to this function.
 
--------------------------------------------------------------------------------------*/
DLL_EXPORT bool pluginit(PLUG_INITSTRUCT* initStruct)
{
    initStruct->pluginVersion = plugin_version;
    initStruct->sdkVersion = PLUG_SDKVERSION;
    strcpy(initStruct->pluginName, plugin_name);
    pluginHandle = initStruct->pluginHandle;

	// place any additional initialization code here
	pluginInit(initStruct);
    return true;
}


/*====================================================================================
  plugstop - Called by debugger when the plugin.dp32 is unloaded - needs to be EXPORTED
 
  Arguments: none
  
  Notes:     perform cleanup operations here, clearing menus and other housekeeping
 
--------------------------------------------------------------------------------------*/
DLL_EXPORT bool plugstop()
{
    _plugin_menuclear(hMenu);

	// place any cleanup code here
	pluginStop();
    return true;
}


/*====================================================================================
  plugsetup - Called by debugger to initialize your plugins setup - needs to be EXPORTED
 
  Arguments: setupStruct - a pointer to a PLUG_SETUPSTRUCT structure
  
  Notes:     setupStruct contains useful handles for use within x64_dbg, mainly Qt 
             menu handles (which are not supported with win32 api) and the main window
             handle with this information you can add your own menus and menu items 
             to an existing menu, or one of the predefined supported right click 
             context menus: hMenuDisam, hMenuDump & hMenuStack
             
             plugsetup is called after pluginit. 
--------------------------------------------------------------------------------------*/
DLL_EXPORT void plugsetup(PLUG_SETUPSTRUCT* setupStruct)
{
    hwndDlg = setupStruct->hwndDlg;
    hMenu = setupStruct->hMenu;
    hMenuDisasm = setupStruct->hMenuDisasm;
    hMenuDump = setupStruct->hMenuDump;
    hMenuStack = setupStruct->hMenuStack;
    
	GuiAddLogMessage(szxLCBInfo);
	// place any additional setup code here
	pluginSetup();
}


/*====================================================================================
  CBMENUENTRY - Called by debugger when a menu item is clicked - needs to be EXPORTED
 
  Arguments: cbType
             cbInfo - a pointer to a PLUG_CB_MENUENTRY structure. The hEntry contains 
             the resource id of menu item identifiers
   
  Notes:     hEntry can be used to determine if the user has clicked on your plugins
             menu item(s) and to do something in response to it.
             
--------------------------------------------------------------------------------------*/
extern "C" __declspec(dllexport) void CBMENUENTRY(CBTYPE cbType, PLUG_CB_MENUENTRY* info)
{
	switch (info->hEntry)
	{
		//----------------------------------------------
		// Export/Import/Clear comments functionality
		//----------------------------------------------
	case MENU_COMMENTS_EXPORT:
	case MENU_COMMENTS_EXPORT_DISASM:
		DbgCmdExec("ExportComments");
		break;
	case MENU_COMMENTS_IMPORT:
	case MENU_COMMENTS_IMPORT_DISASM:
		DbgCmdExec("ImportComments");
		break;
	case MENU_COMMENTS_CLEAR:
	case MENU_COMMENTS_CLEAR_DISASM:
		DbgCmdExec("ClearComments");
		break;
		//----------------------------------------------
		// Export/Import/Clear labels functionality
		//----------------------------------------------
	case MENU_LABELS_EXPORT:
	case MENU_LABELS_EXPORT_DISASM:
		DbgCmdExec("ExportLabels");
		break;
	case MENU_LABELS_IMPORT:
	case MENU_LABELS_IMPORT_DISASM:
		DbgCmdExec("ImportLabels");
		break;
	case MENU_LABELS_CLEAR:
	case MENU_LABELS_CLEAR_DISASM:
		DbgCmdExec("ClearLabels");
		break;
		//----------------------------------------------
		// Export/Import BP functionality
		//----------------------------------------------
	case MENU_BP_EXPORT:
	case MENU_BP_EXPORT_DISASM:
		DbgCmdExec("ExportBP");
		break;
	case MENU_BP_IMPORT:
	case MENU_BP_IMPORT_DISASM:
		DbgCmdExec("ImportBP");
		break;
		//----------------------------------------------
	case MENU_ABOUT:
	case MENU_ABOUT_DISASM:
		MessageBox(hwndDlg, "------------------------------------------------\n"
							"\t          [ xLCB v1 ]\n"
							" Manage Labels, Comments and Breakpoints\n"
							"            Coded By: ThunderCls - 2016\n"
							"       http://reversec0de.wordpress.com"
							"\n------------------------------------------------",
							"About...", MB_ICONINFORMATION);
		break;
	}
}


/*====================================================================================
  CBINITDEBUG - Called by debugger when a program is debugged - needs to be EXPORTED

  Arguments: cbType
             cbInfo - a pointer to a PLUG_CB_INITDEBUG structure. 
             The szFileName item contains name of file being debugged. 

--------------------------------------------------------------------------------------*/
extern "C" __declspec(dllexport) void CBINITDEBUG(CBTYPE cbType, PLUG_CB_INITDEBUG* info)
{

}



/*====================================================================================
  CBSYSTEMBREAKPOINT - Called by debugger at system breakpoint - needs to be EXPORTED
 
  Arguments: cbType
             cbInfo - reserved 

--------------------------------------------------------------------------------------*/
extern "C" __declspec(dllexport) void CBSYSTEMBREAKPOINT(CBTYPE cbType, PLUG_CB_SYSTEMBREAKPOINT* info)
{

}














