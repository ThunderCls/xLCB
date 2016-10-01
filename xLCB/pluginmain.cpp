#include "pluginmain.h"
#include "plugin.h"
#include <windows.h>
#include <stdio.h>
#include <psapi.h>
#include "pluginsdk\bridgemain.h"
#include "pluginsdk\_scriptapi_comment.h"
#include "pluginsdk\_scriptapi_label.h"
#include "pluginsdk\_scriptapi_debug.h"
#include "pluginsdk\_scriptapi_module.h"

#define LINE_SIZE 1024

bool cbCommentsExport(int argc, char* argv[])
{
	using namespace Script;
	char locFile[MAX_PATH] = { 0 };
	FILE *hFile;
	int counter = 0;
	char message_text[MAX_PATH] = { 0 };

	BridgeList<Comment::CommentInfo> lstCmt;

	if (ExportDlg(locFile, "Export Comments"))
	{
		if (Comment::GetList(&lstCmt))
		{
			hFile = fopen(locFile, "wb");
			if (hFile != NULL)
			{
				for (int i = 0; i < lstCmt.Count(); i++)
				{
					if (fprintf(hFile, "%s\t%x\t%s\n", lstCmt[i].mod, lstCmt[i].rva, lstCmt[i].text) > 0)
						counter++;
				}

				sprintf_s(message_text, MAX_PATH, "%d of %d comments successfully exported!", counter, lstCmt.Count());
				MessageBox(hwndDlg, message_text, "Correct", MB_ICONINFORMATION);
				lstCmt.Cleanup();
				fclose(hFile);
				return true;
			}
		}

		MessageBox(hwndDlg, "Comments couldn't be exported.", "Error", MB_ICONERROR);
	}

	return false;
}

bool cbCommentsImport(int argc, char* argv[])
{
	using namespace Script;
	char locFile[MAX_PATH] = { 0 };
	char message_text[MAX_PATH] = { 0 };
	char comment_text[MAX_COMMENT_SIZE] = { 0 };
	char module_name[MAX_MODULE_SIZE] = { 0 };
	duint comment_rva = 0;
	int counter = 0;
	int total = 0;
	FILE *hFile;
	Comment::CommentInfo *cmtInfo;

	if (ImportDlg(locFile, "Import Comments"))
	{
		hFile = fopen(locFile, "rb");
		if (hFile != NULL)
		{
			fseek(hFile, 0L, SEEK_SET);
			char *line_buffer = new char[LINE_SIZE];

			while (fgets(line_buffer, LINE_SIZE, hFile) != NULL)
			{
				if (sscanf(line_buffer, "%[\x20-\x7e] %x %[\x20-\x7e]", module_name, &comment_rva, comment_text) == 3)
				{
					cmtInfo = new Comment::CommentInfo;
					cmtInfo->manual = true;
					cmtInfo->rva = comment_rva;
					strcpy(cmtInfo->text, comment_text);
					strcpy(cmtInfo->mod, module_name);

					if (Comment::Set(cmtInfo))
						counter++;

					delete cmtInfo;
					total++;
				}
			}

			sprintf_s(message_text, MAX_PATH, "%d of %d comments successfully imported!", counter, total);
			MessageBox(hwndDlg, message_text, "Correct", MB_ICONINFORMATION);
			fclose(hFile);
			delete[] line_buffer;
			return true;
		}

		MessageBox(hwndDlg, "Comments couldn't be imported.", "Error", MB_ICONERROR);
	}

	return false;
}

bool cbCommentsClear(int argc, char* argv[])
{
	using namespace Script;

	if (MessageBox(hwndDlg, "Are you sure you want to delete all the comments?", "Clear Comments", MB_ICONWARNING + MB_OKCANCEL) == IDOK)
	{
		Comment::Clear();
		MessageBox(hwndDlg, "All comments deleted.", "Correct", MB_ICONINFORMATION);
		return true;
	}

	return false;
}

 bool cbLabelsExport(int argc, char* argv[])
 {
	 using namespace Script;
	 char locFile[MAX_PATH] = { 0 };
	 FILE *hFile;
	 int counter = 0;
	 char message_text[MAX_PATH] = { 0 };

	 BridgeList<Label::LabelInfo> lstLbl;

	 if (ExportDlg(locFile, "Export Labels"))
	 {
		 if (Label::GetList(&lstLbl))
		 {
			 hFile = fopen(locFile, "wb");
			 if (hFile != NULL)
			 {
				 for (int i = 0; i < lstLbl.Count(); i++)
				 {
					 if (fprintf(hFile, "%s\t%x\t%s\n", lstLbl[i].mod, lstLbl[i].rva, lstLbl[i].text) > 0)
						 counter++;
				 }

				 sprintf_s(message_text, MAX_PATH, "%d of %d labels successfully exported!", counter, lstLbl.Count());
				 MessageBox(hwndDlg, message_text, "Correct", MB_ICONINFORMATION);
				 lstLbl.Cleanup();
				 fclose(hFile);
				 return true;
			 }
		 }

		 MessageBox(hwndDlg, "Labels couldn't be exported.", "Error", MB_ICONERROR);
	 }

	 return false;
 }
 
 bool cbLabelsImport(int argc, char* argv[])
 {
	 using namespace Script;
	 char locFile[MAX_PATH] = { 0 };
	 char message_text[MAX_PATH] = { 0 };
	 char label_text[MAX_COMMENT_SIZE] = { 0 };
	 char module_name[MAX_MODULE_SIZE] = { 0 };
	 duint label_rva = 0;
	 int counter = 0;
	 int total = 0;
	 FILE *hFile;
	 Label::LabelInfo *lblInfo;


	 if (ImportDlg(locFile, "Import Labels"))
	 {
		 hFile = fopen(locFile, "rb");
		 if (hFile != NULL)
		 {
			 fseek(hFile, 0L, SEEK_SET);
			 char *line_buffer = new char[LINE_SIZE];

			 while (fgets(line_buffer, LINE_SIZE, hFile) != NULL)
			 {
				 if (sscanf(line_buffer, "%[\x20-\x7e] %x %[\x20-\x7e]", module_name, &label_rva, label_text) == 3)
				 {
					 lblInfo = new Label::LabelInfo;
					 lblInfo->manual = true;
					 lblInfo->rva = label_rva;
					 strcpy(lblInfo->text, label_text);
					 strcpy(lblInfo->mod, module_name);

					 if (Label::Set(lblInfo))
						 counter++;

					 delete lblInfo;
					 total++;
				 }
			 }

			 sprintf_s(message_text, MAX_PATH, "%d of %d labels successfully imported!", counter, total);
			 MessageBox(hwndDlg, message_text, "Correct", MB_ICONINFORMATION);
			 fclose(hFile);
			 delete[] line_buffer;
			 return true;
		 }

		 MessageBox(hwndDlg, "Labels couldn't be imported.", "Error", MB_ICONERROR);
	 }

	 return false;
 }
 
 bool cbLabelsClear(int argc, char* argv[])
 {
	 using namespace Script;

	 if (MessageBox(hwndDlg, "Are you sure you want to delete all the labels?", "Clear Labels", MB_ICONWARNING + MB_OKCANCEL) == IDOK)
	 {
		 Label::Clear();
		 MessageBox(hwndDlg, "All labels deleted.", "Correct", MB_ICONINFORMATION);
		 return true;
	 }

	 return false;
 }
 
 bool cbBPExport(int argc, char* argv[])
 {
	 using namespace Script;
	 char locFile[MAX_PATH] = { 0 };
	 FILE *hFile;
	 int counter = 0;
	 duint bp_rva = 0;
	 char message_text[MAX_PATH] = { 0 };
	 BPMAP lstBP;

	 if (ExportDlg(locFile, "Export Breakpoints"))
	 {
		 if (DbgGetBpList(bp_normal, &lstBP) > 0)
		 {
			 hFile = fopen(locFile, "wb");
			 if (hFile != NULL)
			 {
				 for (int i = 0; i < lstBP.count; i++)
				 {
					 bp_rva = lstBP.bp[i].addr - Module::BaseFromName(lstBP.bp[i].mod);
					 if (fprintf(hFile, "%s\t%x\t%x\t%x\n", lstBP.bp[i].mod, bp_rva, lstBP.bp[i].type, lstBP.bp[i].hitCount) > 0)
						 counter++;
				 }

				 sprintf_s(message_text, MAX_PATH, "%d of %d breakpoints successfully exported!", counter, lstBP.count);
				 MessageBox(hwndDlg, message_text, "Correct", MB_ICONINFORMATION);
				 fclose(hFile);
				 return true;
			 }
		 }

		 MessageBox(hwndDlg, "Breakpoints couldn't be exported.", "Error", MB_ICONERROR);
	 }

	 return false;
 }
 
 bool cbBPImport(int argc, char* argv[])
 {
	 using namespace Script;
	 char locFile[MAX_PATH] = { 0 };
	 char message_text[MAX_PATH] = { 0 };
	 char module_name[MAX_MODULE_SIZE] = { 0 };
	 DWORD file_size = 0;
	 int counter = 0;
	 int total = 0;
	 duint bp_rva = 0;
	 duint bp_address = 0;
	 int bp_type = 0;
	 int bp_hitCount = 0;

	 FILE *hFile;

	 if (ImportDlg(locFile, "Import Breakpoints"))
	 {
		 hFile = fopen(locFile, "rb");
		 if (hFile != NULL)
		 {
			 fseek(hFile, 0L, SEEK_SET);
			 char *line_buffer = new char[LINE_SIZE];

			 while (fgets(line_buffer, LINE_SIZE, hFile) != NULL)
			 {
				 if (sscanf(line_buffer, "%[\x20-\x7e] %x %x %x", module_name, &bp_rva, &bp_type, &bp_hitCount) == 4)
				 {
					 bp_address = bp_rva + Module::BaseFromName(module_name);
					 if (Debug::SetBreakpoint(bp_address))
						 counter++;

					 total++;
				 }
			 }

			 sprintf_s(message_text, MAX_PATH, "%d of %d breakpoints successfully imported!", counter, total);
			 MessageBox(hwndDlg, message_text, "Correct", MB_ICONINFORMATION);
			 fclose(hFile);
			 delete[] line_buffer;
			 return true;
		 }

		 MessageBox(hwndDlg, "Breakpoints couldn't be imported.", "Error", MB_ICONERROR);
	 }

	 return false;
 }

bool ExportDlg(LPSTR locFile, LPSTR title)
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwndDlg;
	ofn.lpstrFilter = "xLCB Files (*.xlcb)\0*.xlcb\0All Files (*.*)\0*.*\0";
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFile = locFile;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = (LPCSTR)L"xlcb";
	ofn.lpstrTitle = title;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_EXPLORER | OFN_ENABLEHOOK;

	if (GetSaveFileName(&ofn))
		return true;

	return false;
}

bool ImportDlg(LPSTR locFile, LPSTR title)
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwndDlg;
	ofn.lpstrFilter = "xLCB Files (*.xlcb)\0*.xlcb\0All Files (*.*)\0*.*\0";
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFile = locFile;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	ofn.lpstrDefExt = (LPCSTR)L"xlcb";
	ofn.lpstrTitle = title;
	ofn.nFilterIndex = 1;

	if (GetOpenFileName(&ofn))
		return true;

	return false;
}