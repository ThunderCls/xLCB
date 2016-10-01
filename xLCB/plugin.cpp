#include "plugin.h"
#include <windows.h>
#include <stdio.h>
#include <psapi.h>
#include "icons.h"
#include "pluginmain.h"

void pluginInit(PLUG_INITSTRUCT* initStruct)
{
	_plugin_registercommand(pluginHandle, "ExportComments", cbCommentsExport, true);
	_plugin_registercommand(pluginHandle, "ImportComments", cbCommentsImport, true);
	_plugin_registercommand(pluginHandle, "ClearComments", cbCommentsClear, true);

	_plugin_registercommand(pluginHandle, "ExportLabels", cbLabelsExport, true);
	_plugin_registercommand(pluginHandle, "ImportLabels", cbLabelsImport, true);
	_plugin_registercommand(pluginHandle, "ClearLabels", cbLabelsClear, true);

	_plugin_registercommand(pluginHandle, "ExportBP", cbBPExport, true);
	_plugin_registercommand(pluginHandle, "ImportBP", cbBPImport, true);
}

void pluginStop()
{
	_plugin_unregistercommand(pluginHandle, "ExportComments");
	_plugin_unregistercommand(pluginHandle, "ImportComments");
	_plugin_unregistercommand(pluginHandle, "ClearComments");

	_plugin_unregistercommand(pluginHandle, "ExportLabels");
	_plugin_unregistercommand(pluginHandle, "ImportLabels");
	_plugin_unregistercommand(pluginHandle, "ClearLabels");

	_plugin_unregistercommand(pluginHandle, "ExportBP");
	_plugin_unregistercommand(pluginHandle, "ImportBP");

	_plugin_menuclear(hMenu);
	_plugin_menuclear(hMenuDisasm);
	_plugin_menuclear(hMenuDump);
	_plugin_menuclear(hMenuStack);
}

void pluginSetup()
{
	ICONDATA xlcb;
	xlcb.data = icon_xlcb;
	xlcb.size = sizeof(icon_xlcb);

	// Plugin Menu
	_plugin_menuseticon(hMenu, &xlcb);

	_plugin_menuaddentry(hMenu, MENU_COMMENTS_EXPORT, "&Export Comments...");
	_plugin_menuaddentry(hMenu, MENU_COMMENTS_IMPORT, "&Import Comments...");
	_plugin_menuaddentry(hMenu, MENU_COMMENTS_CLEAR, "&Clear all Comments...");
	_plugin_menuaddseparator(hMenu);
	_plugin_menuaddentry(hMenu, MENU_LABELS_EXPORT, "&Export Labels...");
	_plugin_menuaddentry(hMenu, MENU_LABELS_IMPORT, "&Import Labels...");
	_plugin_menuaddentry(hMenu, MENU_LABELS_CLEAR, "&Clear all Labels...");
	_plugin_menuaddseparator(hMenu);
	_plugin_menuaddentry(hMenu, MENU_BP_EXPORT, "&Export Breakpoints...");
	_plugin_menuaddentry(hMenu, MENU_BP_IMPORT, "&Import Breakpoints...");
	_plugin_menuaddseparator(hMenu);
	_plugin_menuaddentry(hMenu, MENU_ABOUT, "&About...");

	// Disasm Window
	_plugin_menuseticon(hMenuDisasm, &xlcb);

	_plugin_menuaddentry(hMenuDisasm, MENU_COMMENTS_EXPORT_DISASM, "&Export Comments...");
	_plugin_menuaddentry(hMenuDisasm, MENU_COMMENTS_IMPORT_DISASM, "&Import Comments...");
	_plugin_menuaddentry(hMenuDisasm, MENU_COMMENTS_CLEAR_DISASM, "&Clear all Comments...");
	_plugin_menuaddseparator(hMenuDisasm);
	_plugin_menuaddentry(hMenuDisasm, MENU_LABELS_EXPORT_DISASM, "&Export Labels...");
	_plugin_menuaddentry(hMenuDisasm, MENU_LABELS_IMPORT_DISASM, "&Import Labels...");
	_plugin_menuaddentry(hMenuDisasm, MENU_LABELS_CLEAR_DISASM, "&Clear all Labels...");
	_plugin_menuaddseparator(hMenuDisasm);
	_plugin_menuaddentry(hMenuDisasm, MENU_BP_EXPORT_DISASM, "&Export Breakpoints...");
	_plugin_menuaddentry(hMenuDisasm, MENU_BP_IMPORT_DISASM, "&Import Breakpoints...");
	_plugin_menuaddseparator(hMenuDisasm);
	_plugin_menuaddentry(hMenuDisasm, MENU_ABOUT_DISASM, "&About...");
}