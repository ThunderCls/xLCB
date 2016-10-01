#include <windows.h>

//functions
bool ExportDlg(LPSTR locFile, LPSTR title);
bool ImportDlg(LPSTR locFile, LPSTR title);
bool cbCommentsExport(int argc, char* argv[]);
bool cbCommentsImport(int argc, char* argv[]);
bool cbCommentsClear(int argc, char* argv[]);
bool cbLabelsExport(int argc, char* argv[]);
bool cbLabelsImport(int argc, char* argv[]);
bool cbLabelsClear(int argc, char* argv[]);
bool cbBPExport(int argc, char* argv[]);
bool cbBPImport(int argc, char* argv[]);