/****************************************************************************/
/*                                                                          */
/*   metapad 3.6+                                                           */
/*                                                                          */
/*   Copyright (C) 2021-2024 SoBiT Corp                                     */
/*   Copyright (C) 2013 Mario Rugiero                                       */
/*   Copyright (C) 1999-2011 Alexander Davidson                             */
/*                                                                          */
/*   This program is free software: you can redistribute it and/or modify   */
/*   it under the terms of the GNU General Public License as published by   */
/*   the Free Software Foundation, either version 3 of the License, or      */
/*   (at your option) any later version.                                    */
/*                                                                          */
/*   This program is distributed in the hope that it will be useful,        */
/*   but WITHOUT ANY WARRANTY; without even the implied warranty of         */
/*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          */
/*   GNU General Public License for more details.                           */
/*                                                                          */
/*   You should have received a copy of the GNU General Public License      */
/*   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */
/*                                                                          */
/****************************************************************************/


#include "include/metapad.h"
#include <commctrl.h>
#ifdef UNICODE
#include <wchar.h>
#endif


#define WS_EX_LAYOUTRTL	0x00400000L


static HINSTANCE hinstLang = NULL;


static const CHAR strings[] = ""
/*		1		IDS_VERSION_SYNCH				*/	"\0" VI_VERSYNC
/*		2		IDS_PLUGIN_LANGUAGE				*/	"\0"
/*		3		IDS_PLUGIN_RELEASE				*/	"\0"
/*		4		IDS_PLUGIN_TRANSLATOR			*/	"\0"
/*		5		IDS_PLUGIN_EMAIL				*/	"\0"
/*		8		IDS_DEFAULT_FILTER				*/	"\0All Textual File Types|*.txt;*.htm;*.html;*.c;*.cpp;*.h;*.java|Text Files (*.txt)|*.txt|HTML (*.html; *.htm)|*.html;*.htm|Source Code (*.c; *.cpp; *.h; *.java)|*.c;*.cpp;*.h;*.java|All Files (*.*)|*.*|"
/*		9		IDS_DIRTYFILE					*/	"\0Save changes to %s?"
/*		10		IDS_ERROR_LOCKED				*/	"\0Error writing to file - it may be locked or read only."
/*		11		IDS_ERROR_SEARCH				*/	"\0Search string not found."
/*		12		IDS_LAUNCH_WARNING				*/	"\0Warning - you have chosen not to save AND to close metapad on external launch.\n\nThis could cause you to lose data!"
/*		13		IDS_READONLY_INDICATOR			*/	"\0(read only)"
/*		15		IDS_ERROR_FAVOURITES			*/	"\0Error in favorites file. It may have been modified and is not synchronized."
/*		16		IDS_FILE_LOADING				*/	"\0Loading file..."
/*		17		IDS_READONLY_WARNING			*/	"\0This file is read only. You must save to a different file."
/*		18		IDS_PRINTER_NOT_FOUND			*/	"\0Printer not found!\n(Perhaps try reinstalling the printer.)"
/*		19		IDS_PRINT_INIT_ERROR			*/	"\0Error initializing printing. (CommDlgExtendedError: %#04x)"
/*		20		IDS_PRINT_ABORT_ERROR			*/	"\0Error aborting printing"
/*		21		IDS_PRINT_START_ERROR			*/	"\0StartDoc printing error. Printing canceled."
/*		22		IDS_DRAWTEXT_ERROR				*/	"\0Error calling DrawText."
/*		23		IDS_PRINT_ERROR					*/	"\0There was an error during printing. Print canceled."
/*		24		IDS_VIEWER_ERROR				*/	"\0Error launching external viewer"
/*		26		IDS_VIEWER_MISSING				*/	"\0External viewer is not configured."
/*		28		IDS_NO_DEFAULT_VIEWER			*/	"\0No viewer associated with this file type."
/*		30		IDS_REGISTRY_WINDOW_ERROR		*/	"\0Missing window placement registry values - using default settings."
/*		33		IDS_CREATE_FILE_MESSAGE			*/	"\0\"%s\" not found. Create it?"
/*		34		IDS_FILE_CREATE_ERROR			*/	"\0File creation error."
/*		35		IDS_FILE_NOT_FOUND				*/	"\0File not found."
/*		36		IDS_FILE_LOCKED_ERROR			*/	"\0File is locked by another process."
#ifdef UNICODE
"\0\0"
#else
/*	A	37		IDS_UNICODE_CONVERT_ERROR		*/	"\0Error converting from Unicode file"
/*	A	38		IDS_UNICODE_CHARS_WARNING		*/	"\0Detected non-ANSI characters in this Unicode file.\n\nData will be lost if this file is saved!"
#endif
/*		39		IDS_BINARY_FILE_WARNING			*/	"\0This is a binary file.\nConvert any NULL terminators to spaces and load anyway?"
#ifdef UNICODE
"\0"
#else
/*	A	40		IDS_UNICODE_STRING_ERROR		*/	"\0Error converting to Unicode string"
#endif
/*		41		IDS_WRITE_BOM_ERROR				*/	"\0Error writing BOM"
#ifdef USE_RICH_EDIT
/*	R	42		IDS_FONT_UNDO_WARNING			*/	"\0Applying new font settings. This action will empty the undo buffer."
#else
"\0"
#endif
/*		43		IDS_CHAR_WIDTH_ERROR			*/	"\0Couldn't get char width."
/*		44		IDS_PARA_FORMAT_ERROR			*/	"\0Couldn't set para format."
/*		45		IDS_QUERY_SEARCH_TOP			*/	"\0Reached end of file. Continue searching from the top?"
/*		46		IDS_QUERY_SEARCH_BOTTOM			*/	"\0Reached beginning of file. Continue searching from the bottom?"
/*		47		IDS_RECENT_MENU					*/	"\0&Recent"
/*		49		IDS_MAX_RECENT_WARNING			*/	"\0Enter a maximum Recent File size between 0 and 16"
/*		50		IDS_STICKY_MESSAGE				*/	"\0Main window will now always start up with its current size and position."
/*		51		IDS_CLEAR_FIND_WARNING			*/	"\0This action will clear find, replace, and insert histories."
/*		52		IDS_CLEAR_RECENT_WARNING		*/	"\0This action will clear the recent files history"
/*		53		IDS_SELECT_PLUGIN_WARNING		*/	"\0Select a language plugin or choose Default (English)."
/*		55		IDS_MARGIN_WIDTH_WARNING		*/	"\0Enter a margin width between 0 and 300"
/*		56		IDS_TRANSPARENCY_WARNING		*/	"\0Enter a transparency mode percent between 1 and 99"
/*		57		IDS_TAB_SIZE_WARNING			*/	"\0Enter a tab size between 1 and 100"
/*		59		IDS_TB_NEWFILE					*/	"\0New File"
/*		60		IDS_TB_OPENFILE					*/	"\0Open File"
/*		61		IDS_TB_SAVEFILE					*/	"\0Save File"
/*		62		IDS_TB_PRINT					*/	"\0Print"
/*		63		IDS_TB_FIND						*/	"\0Find"
/*		64		IDS_TB_REPLACE					*/	"\0Replace"
/*		65		IDS_TB_CUT						*/	"\0Cut"
/*		66		IDS_TB_COPY						*/	"\0Copy"
/*		67		IDS_TB_PASTE					*/	"\0Paste"
/*		68		IDS_TB_UNDO						*/	"\0Undo"
#ifdef USE_RICH_EDIT
/*	R	69		IDS_TB_REDO						*/	"\0Redo"
#else
"\0"
#endif
/*		70		IDS_TB_SETTINGS					*/	"\0Settings"
/*		71		IDS_TB_REFRESH					*/	"\0Refresh/Revert"
/*		72		IDS_TB_WORDWRAP					*/	"\0Word Wrap"
/*		73		IDS_TB_PRIMARYFONT				*/	"\0Primary Font"
/*		74		IDS_TB_ONTOP					*/	"\0Always On Top"
/*		75		IDS_TB_PRIMARYVIEWER			*/	"\0Launch Primary Viewer"
/*		76		IDS_TB_SECONDARYVIEWER			*/	"\0Launch Secondary Viewer"
#ifdef USE_RICH_EDIT
/*	R	77		IDS_CANT_UNDO_WARNING			*/	"\0Can't undo this action!"
/*	R	78		IDS_MEMORY_LIMIT				*/	"\0Reached memory limit at %s bytes!"
"\0\0"
/*	R	81		IDS_UNDO_HYPERLINKS_WARNING		*/	"\0Updating hyperlinks. This action will empty the undo buffer."
#else
"\0\0"
/*	L	79		IDS_QUERY_LAUNCH_VIEWER			*/	"\0This version of Windows does not support loading files this large into an Edit window.\nLaunch in external viewer?"
/*	L	80		IDS_LE_MEMORY_LIMIT				*/	"\0Reached memory limit!\nSave file now and use another editor (metapad full not LE)!"
"\0"
#endif
/*		82		IDS_CHANGE_READONLY_ERROR		*/	"\0Unable to change the readonly attribute for this file."
/*		83		IDS_SETTINGS_TITLE				*/	"\0Settings"
/*		84		IDS_NO_SELECTED_TEXT			*/	"\0No selected text."
/*		86		IDS_ITEMS_REPLACED				*/	"\0Replaced %s item(s)."
/*		87		IDS_MENU_LANGUAGE_PLUGIN		*/	"\0&Language Plugin..."
#ifdef USE_RICH_EDIT
/*	R	88		IDS_RICHED_MISSING_ERROR		*/	"\0metapad requires RICHED20.DLL to be installed on your system.\n\nSee the FAQ on the website for further information."
#else
"\0"
#endif
/*		89		IDS_COMMAND_LINE_OPTIONS		*/	"\0Usage: metapad [/i | /m | /v | /s] [/p | /g row:col | /e] [filename]\n\nOption descriptions:\n\n\t/i - force INI mode for settings\n\t/m - migrate all registry settings to INI file\n\t/g row:col - goto position at row and column\n\t/e - goto end of file\n\t/p - print file\n\t/v - disable plugin version checking\n\t/s - skip loading language plugin"
/*		90		IDS_GLOBALLOCK_ERROR			*/	"\0GlobalLock failed"
/*		91		IDS_CLIPBOARD_UNLOCK_ERROR		*/	"\0Error unlocking clipboard memory."
/*		92		IDS_CLIPBOARD_OPEN_ERROR		*/	"\0Error opening clipboard."
/*		93		IDS_FILE_READ_ERROR				*/	"\0Error reading file."
#ifdef USE_RICH_EDIT
/*	R	94		IDS_RESTART_HIDE_SB				*/	"\0The change in \"Hide scrollbars when possible\" will be reflected upon restarting the program."
#else
"\0"
#endif
"\0\0"
/*		97		IDS_INVALID_PLUGIN_ERROR		*/	"\0Error loading language plugin. It is probably not a valid metapad language plugin."
/*		98		IDS_BAD_STRING_PLUGIN_ERROR		*/	"\0Error fetching version string resource from plugin. It is probably not a valid metapad language plugin."
/*		99		IDS_PLUGIN_MISMATCH_ERROR		*/	"\0Your language plugin is for metapad %s, but you are running metapad %s.\n\nSome menu or dialog texts may not be translated."
/*		100		IDS_ALLRIGHTS					*/	"\0All Rights Reserved"
/*		102		IDS_DEFAULT_FILTER_TEXT			*/	"\0Text (*.*)|*.*|"
/*		103		IDS_NEW_FILE					*/	"\0new file"
/*		104		IDS_MACRO_LENGTH_ERROR			*/	"\0Selection is larger than maximum quick buffer length."
/*		112		IDD_PROPPAGE_GENERAL			*/	"\0General"
/*		114		IDD_GOTO						*/	"\0Go To Line"
/*		124		IDD_PROPPAGE_VIEW				*/	"\0View"
/*		128		IDD_FAV_NAME					*/	"\0Add Favorite"
/*		199		IDS_ERROR						*/	"\0Error"
/*		200		IDS_ERROR_MSG					*/	"\0\nError 0x%08X"
/*		201		IDS_UNICODE_SAVE_TRUNCATION		*/	"\0Some characters in this text cannot be saved in the selected encoding!\n\nWould you like to save this file as UTF-8?"
/*		202		IDS_UNICODE_LOAD_ERROR			*/	"\0Error converting file to Unicode"
/*		203		IDS_UNICODE_LOAD_TRUNCATION		*/	"\0Detected unsupported or invalid code points.\n\nData will be lost if this file is saved!"
/*		204		IDS_BINARY_FILE_WARNING_SAFE	*/	"\0This is a binary file. Load anyway?\nNull terminators will be preserved unless the File Format is changed."
/*		205		IDS_LARGE_FILE_WARNING			*/	"\0This file is very large ( >16 MB). Loading it may take a long time.\nLoad anyway?"
/*		206		IDS_UNICODE_CONV_ERROR			*/	"\0Error converting string to Unicode"
/*		207		IDS_ESCAPE_ERROR				*/	"\0%s in '%s' near:\n"
/*		208		IDS_ESCAPE_BADCHARS				*/	"\0Invalid characters in base-%d string"
/*		209		IDS_ESCAPE_BADALIGN				*/	"\0The base-%d string is not a multiple of %d characters"
/*		210		IDS_ESCAPE_EXPECTED				*/	"\0Expected base-%d string"
/*		211		IDS_ESCAPE_CTX_FIND				*/	"\0Find what"
/*		212		IDS_ESCAPE_CTX_REPLACE			*/	"\0Replace with"
/*		213		IDS_ESCAPE_CTX_INSERT			*/	"\0Insert Text"
/*		214		IDS_ESCAPE_CTX_CLIPBRD			*/	"\0Clipboard"
/*		215		IDS_ESCAPE_CTX_MACRO			*/	"\0Macro"
/*		216		IDS_ESCAPE_CTX_QUOTE			*/	"\0Quote string"
/*		217		IDS_LARGE_PASTE_WARNING			*/	"\0About to insert %s characters of text.\nThis may take a very long time!\nContinue?"
/*		218		IDS_ITEMS_REPLACED_ITER			*/	"\0Replaced %s item(s) in %s iteration(s)."
/*		219		IDS_ENC_REINTERPRET				*/	"\0Reinterpret the current text as %s?"
/*		220		IDS_LFMT_MIXED					*/	"\0This text has mixed line endings.\nYou can normalize the line endings in the File > Format menu."
/*		221		IDS_LFMT_FIXED					*/	"\0Mixed line endings have been normalized.\nYou can change this function in the File > Format menu."
/*		222		IDS_SETDEF_FORMAT_WARN			*/	"\0Note that all files without a Byte-Order Mark will now be interpreted as %s!"
/*		223		IDS_ENC_BAD						*/	"\0This codepage is not available on your system."
/*		224		IDS_ENC_FAILED					*/	"\0Error converting to the selected codepage!\nThe data was instead saved as ANSI."
/*		225		IDS_FILE_SAVING					*/	"\0Saving file..."
/*		226		IDS_LFMT_NORMALIZE				*/	"\0Normalize line endings now?"
/*		430		IDS_UTILS_NOMEM					*/	"\0Out of memory!"
/*		441		IDS_DECODEBASE_BADLEN			*/	"\0Invalid code string length!"
/*		442		IDS_DECODEBASE_BADCHAR			*/	"\0Invalid code characters!"
/*		490		IDS_MIGRATED					*/	"\0Migration to INI completed."
/*		491		IDS_STATFMT_BYTES				*/	"\0 Bytes: %s "
/*		492		IDS_STATFMT_LINES				*/	"\0 Lines: %s "
/*		493		IDS_STATFMT_SEL					*/	"\0 Selected %s:%d  ->  %s:%d  %s  %s"
/*		494		IDS_STATFMT_LINE				*/	"\0 Line: %s/%s"
/*		495		IDS_STATFMT_COL					*/	"\0 Col: %d"
#ifdef USE_RICH_EDIT
/*	R	498		IDS_STATFMT_INS					*/	"\0 INS"
/*	R	499		IDS_STATFMT_OVR					*/	"\0OVR"
#else
"\0\0"
#endif
/*		500		STR_METAPAD						*/	"\0" VI_NAME
/*		501		STR_CAPTION_FILE				*/	"\0 - " VI_NAME " "
/*	!	502		STR_ABOUT						*/	"\0" VI_FULLNAME " " VI_VER
/*		506		STR_FAV_FILE					*/	"\0metafav.ini"
/*		507		STR_INI_FILE					*/	"\0" VI_NAME ".ini"
/*		508		STR_URL							*/	"\0http://liquidninja.com/metapad"
/*		509		STR_REGKEY						*/	"\0SOFTWARE\\" VI_NAME
/*		510		STR_FAV_APPNAME					*/	"\0Favourites"
/*		511		STR_OPTIONS						*/	"\0Options"
/*		512		STR_COPYRIGHT					*/	"\0" VI_COPY
/*		513		IDS_PLUGIN_ERRFIND				*/	"\0Could not find the language plugin."
/*		514		IDS_PLUGIN_ERR					*/	"\0Temporarily reverting language to Default (English)\n\nCheck the language plugin setting."
/*		518		IDS_FILTER_EXEC					*/	"\0Executable Files (*.exe)|*.exe|All Files (*.*)|*.*|"
/*		519		IDS_FILTER_PLUGIN				*/	"\0metapad language plugins (*.lng, *.dll)|*.lng;*.dll|All Files (*.*)|*.*|"
/*		520		IDS_LOADLNG_ERROR				*/	"\0Error loading language plugin on line %s: ID number missing or out of range or invalid escape sequence"
/*		590		STR_DEBUG_PATH					*/	"\0R:\\TEMP\\metapadd.log"
/*		591		STR_DEBUG_BADFREE				*/	"\0BAD FREE%d %08X:%08X:"
/*		600		IDSS_WSTATE						*/	"\0w_WindowState"
/*		601		IDSS_WLEFT						*/	"\0w_Left"
/*		602		IDSS_WTOP						*/	"\0w_Top"
/*		603		IDSS_WWIDTH						*/	"\0w_Width"
/*		604		IDSS_WHEIGHT					*/	"\0w_Height"
/*		605		IDSS_MRU						*/	"\0mru_%d"
/*		606		IDSS_MRUTOP						*/	"\0mru_Top"
/*		607		IDSS_HIDEGOTOOFFSET				*/	"\0bHideGotoOffset"
/*		608		IDSS_SYSTEMCOLOURS				*/	"\0bSystemColours"
/*		609		IDSS_SYSTEMCOLOURS2				*/	"\0bSystemColours2"
/*		610		IDSS_NOSMARTHOME				*/	"\0bNoSmartHome"
/*		611		IDSS_NOAUTOSAVEEXT				*/	"\0bNoAutoSaveExt"
/*		612		IDSS_CONTEXTCURSOR				*/	"\0bContextCursor"
/*		613		IDSS_CURRENTFINDFONT			*/	"\0bCurrentFindFont"
/*		614		IDSS_PRINTWITHSECONDARYFONT		*/	"\0bPrintWithSecondaryFont"
/*		615		IDSS_NOSAVEHISTORY				*/	"\0bNoSaveHistory"
/*		616		IDSS_NOFINDAUTOSELECT			*/	"\0bNoFindAutoSelect"
/*		617		IDSS_RECENTONOWN				*/	"\0bRecentOnOwn"
/*		618		IDSS_DONTINSERTTIME				*/	"\0bDontInsertTime"
/*		619		IDSS_NOWARNINGPROMPT			*/	"\0bNoWarningPrompt"
/*		620		IDSS_UNFLATTOOLBAR				*/	"\0bUnFlatToolbar"
/*		621		IDSS_STICKYWINDOW				*/	"\0bStickyWindow"
/*		622		IDSS_READONLYMENU				*/	"\0bReadOnlyMenu"
/*		623		IDSS_SELECTIONMARGINWIDTH		*/	"\0nSelectionMarginWidth"
/*		624		IDSS_MAXMRU						*/	"\0nMaxMRU"
/*		625		IDSS_FORMAT						*/	"\0nFormat"
/*		626		IDSS_TRANSPARENTPCT				*/	"\0nTransparentPct"
/*		627		IDSS_NOCAPTIONDIR				*/	"\0bNoCaptionDir"
/*		628		IDSS_AUTOINDENT					*/	"\0bAutoIndent"
/*		629		IDSS_INSERTSPACES				*/	"\0bInsertSpaces"
/*		630		IDSS_FINDAUTOWRAP				*/	"\0bFindAutoWrap"
/*		631		IDSS_QUICKEXIT					*/	"\0bQuickExit"
/*		632		IDSS_SAVEWINDOWPLACEMENT		*/	"\0bSaveWindowPlacement"
/*		633		IDSS_SAVEMENUSETTINGS			*/	"\0bSaveMenuSettings"
/*		634		IDSS_SAVEDIRECTORY				*/	"\0bSaveDirectory"
/*		635		IDSS_LAUNCHCLOSE				*/	"\0bLaunchClose"
/*		636		IDSS_NOFAVES					*/	"\0bNoFaves"
#ifndef USE_RICH_EDIT
/*	L	637		IDSS_DEFAULTPRINTFONT			*/	"\0bDefaultPrintFont"
/*	L	638		IDSS_ALWAYSLAUNCH				*/	"\0bAlwaysLaunch"
"\0\0\0"
#else
"\0\0"
/*	R	639		IDSS_LINKDOUBLECLICK			*/	"\0bLinkDoubleClick"
/*	R	640		IDSS_HIDESCROLLBARS				*/	"\0bHideScrollbars"
/*	R	641		IDSS_SUPPRESSUNDOBUFFERPROMPT	*/	"\0bSuppressUndoBufferPrompt"
#endif
/*		642		IDSS_LAUNCHSAVE					*/	"\0nLaunchSave"
/*		643		IDSS_TABSTOPS					*/	"\0nTabStops"
/*		644		IDSS_NPRIMARYFONT				*/	"\0nPrimaryFont"
/*		645		IDSS_NSECONDARYFONT				*/	"\0nSecondaryFont"
#ifdef UNICODE
/*	!	648		IDSS_PRIMARYFONT				*/	"\0PrimaryFontU"
/*	!	648		IDSS_PRIMARYFONT				*/	"\0PrimaryFont"
#else
/*	!	649		IDSS_SECONDARYFONT				*/	"\0SecondaryFontU"
/*	!	649		IDSS_SECONDARYFONT				*/	"\0SecondaryFont"
#endif
/*		650		IDSS_BROWSER					*/	"\0szBrowser"
/*		651		IDSS_BROWSER2					*/	"\0szBrowser2"
/*		652		IDSS_LANGPLUGIN					*/	"\0szLangPlugin"
/*		653		IDSS_FAVDIR						*/	"\0szFavDir"
/*		654		IDSS_ARGS						*/	"\0szArgs"
/*		655		IDSS_ARGS2						*/	"\0szArgs2"
/*		656		IDSS_QUOTE						*/	"\0szQuote"
/*		657		IDSS_CUSTOMDATE					*/	"\0szCustomDate"
/*		658		IDSS_CUSTOMDATE2				*/	"\0szCustomDate2"
/*		659		IDSS_MACROARRAY					*/	"\0szMacroArray%d"
/*		660		IDSS_BACKCOLOUR					*/	"\0BackColour"
/*		661		IDSS_FONTCOLOUR					*/	"\0FontColour"
/*		662		IDSS_BACKCOLOUR2				*/	"\0BackColour2"
/*		663		IDSS_FONTCOLOUR2				*/	"\0FontColour2"
/*		664		IDSS_MARGINS					*/	"\0rMargins"
/*		665		IDSS_WORDWRAP					*/	"\0m_WordWrap"
/*		666		IDSS_FONTIDX					*/	"\0m_PrimaryFont"
/*		667		IDSS_SMARTSELECT				*/	"\0m_SmartSelect"
#ifdef USE_RICH_EDIT
/*	R	668		IDSS_HYPERLINKS					*/	"\0m_Hyperlinks"
#else
"\0"
#endif
/*		669		IDSS_SHOWSTATUS					*/	"\0m_ShowStatus"
/*		670		IDSS_SHOWTOOLBAR				*/	"\0m_ShowToolbar"
/*		671		IDSS_ALWAYSONTOP				*/	"\0m_AlwaysOnTop"
/*		672		IDSS_TRANSPARENT				*/	"\0m_Transparent"
/*		673		IDSS_CLOSEAFTERFIND				*/	"\0bCloseAfterFind"
/*		674		IDSS_CLOSEAFTERREPLACE			*/	"\0bCloseAfterReplace"
/*		675		IDSS_CLOSEAFTERINSERT			*/	"\0bCloseAfterInsert"
/*		676		IDSS_NOFINDHIDDEN				*/	"\0bNoFindHidden"
/*		677		IDSS_FILEFILTER					*/	"\0FileFilter"
/*		678		IDSS_FINDARRAY					*/	"\0szFindArray%d"
/*		679		IDSS_REPLACEARRAY				*/	"\0szReplaceArray%d"
/*		680		IDSS_INSERTARRAY				*/	"\0szInsertArray%d"
/*		681		IDSS_LASTDIRECTORY				*/	"\0szLastDirectory"
/*		682		IDSS_DIGITGRP					*/	"\0bDigitGrp"
/*		699		IDSS_DEBUG						*/	"\0bDebug"
/*		756		IDSD_QUOTE						*/	"\0> "
/*		757		IDSD_CUSTOMDATE					*/	"\0yyyyMMdd-HHmmss "
/*		1001	IDC_OK							*/	"\0OK"
/*		1002	IDC_CANCEL						*/	"\0Cancel"
/*		1013	IDC_BUTTON_BROWSE				*/	"\0\1"
/*		1015	IDC_BUTTON_BROWSE2				*/	"\0..."
/*		1037	ID_SMARTSELECT					*/	"\0S&mart Select"
/*		1040	IDC_FIND_MATCH_WORD				*/	"\0Match &whole word only"
/*		1041	IDC_FIND_MATCH_CASE				*/	"\0Match &case"
/*		1043	IDC_OFFSET_TEXT					*/	"\0&Offset:"
/*		1045	IDC_RADIO_SELECTION				*/	"\0&Selection"
/*		1046	IDC_RADIO_WHOLE					*/	"\0Wh&ole file"
/*		1076	IDC_CLOSE_AFTER_FIND			*/	"\0C&lose dialog after find"
/*		1078	IDC_NAME						*/	"\0&Favorite name:"
/*		1086	IDC_RADIO_LANG_DEFAULT			*/	"\0&Default (English)"
/*		1087	IDC_RADIO_LANG_PLUGIN			*/	"\0&Language plugin:"
/*		1088	IDC_TEXT_MACRO					*/	"\0Alt + &%d:"
/*		1089	IDC_CLOSE_AFTER_INSERT			*/	"\0C&lose dialog after insert"
/*		1090	IDC_CLOSE_AFTER_REPLACE			*/	"\0C&lose after replace all"
/*		1091	IDC_TEXT_FIND					*/	"\0Fi&nd what:"
/*		1092	IDC_TEXT_REPLACE				*/	"\0Re&place with:"
/*		1540	IDD_FIND						*/	"\0Find"
/*		1541	IDD_REPLACE						*/	"\0Replace"
/*		1546	IDD_PAGE_SETUP					*/	"\0Page Setup"
/*		1547	IDD_PROPPAGE_A1					*/	"\0Advanced"
/*		1549	IDD_PROPPAGE_A2					*/	"\0Buffers && Language"
/*		1550	IDD_ABOUT_PLUGIN				*/	"\0Language Plugin"
/*		1551	IDD_INSERT						*/	"\0Insert"
/*		1552	IDD_CP							*/	"\0Enter codepage number"
/*		2039	FC_LFMT_DOS						*/	"\0DOS"
/*		2040	FC_LFMT_UNIX					*/	"\0Unix"
/*		2048	FC_LFMT_MAC						*/	"\0Mac"
/*		2049	FC_LFMT_MIXED					*/	"\0RAW"
/*		2089	FC_ENC_UTF16					*/	"\0Unicode"
/*		2090	FC_ENC_UTF16BE					*/	"\0Unicode BE"
/*		2109	FC_ENC_UTF8						*/	"\0UTF-8"
/*		2111	FC_ENC_ANSI						*/	"\0ANSI"
/*		2112	FC_ENC_BIN						*/	"\0Binary"
/*		2118	FC_ENC_CODEPAGE					*/	"\0CP%d"
/*		21210	IDDC_PROPPAGE_GENERAL_BASE+IDC_CHECK_QUICKEXIT%100				*/	"\0&Enable quick exit (Esc key)"
/*		21211	IDDC_PROPPAGE_GENERAL_BASE+IDC_CHECK_SAVEWINDOWPLACEMENT%100	*/	"\0Save &window placement"
/*		21216	IDDC_PROPPAGE_GENERAL_BASE+IDC_CHECK_LAUNCH_CLOSE%100			*/	"\0E&xit metapad after viewer is launched"
/*		21230	IDDC_PROPPAGE_GENERAL_BASE+IDC_LAUNCH_SAVE0%100					*/	"\0Prompt to sa&ve"
/*		21231	IDDC_PROPPAGE_GENERAL_BASE+IDC_LAUNCH_SAVE1%100					*/	"\0Automatica&lly save"
/*		21232	IDDC_PROPPAGE_GENERAL_BASE+IDC_LAUNCH_SAVE2%100					*/	"\0Do&n't save"
/*		21233	IDDC_PROPPAGE_GENERAL_BASE+IDC_FIND_AUTO_WRAP%100				*/	"\0Aut&o-search at end of file "
/*		21234	IDDC_PROPPAGE_GENERAL_BASE+IDC_AUTO_INDENT%100					*/	"\0A&uto-indent text"
/*		21235	IDDC_PROPPAGE_GENERAL_BASE+IDC_INSERT_SPACES%100				*/	"\0&Insert tabs as spaces"
/*		21236	IDDC_PROPPAGE_GENERAL_BASE+IDC_NO_CAPTION_DIR%100				*/	"\0&Hide directory in caption"
/*		21238	IDDC_PROPPAGE_GENERAL_BASE+IDC_CHECK_SAVEMENUSETTINGS%100		*/	"\0Save options &menu states"
/*		21241	IDDC_PROPPAGE_GENERAL_BASE+IDC_CHECK_SAVEDIRECTORY%100			*/	"\0Remem&ber last folder"
/*		22418	IDDC_PROPPAGE_VIEW_BASE+IDC_FONT_PRIMARY%100					*/	"\0S&ystem fixed width"
/*		22419	IDDC_PROPPAGE_VIEW_BASE+IDC_FONT_SECONDARY%100					*/	"\0ANSI fi&xed width"
/*		22420	IDDC_PROPPAGE_VIEW_BASE+IDC_FONT_PRIMARY_2%100					*/	"\0&Custom:"
/*		22421	IDDC_PROPPAGE_VIEW_BASE+IDC_FONT_SECONDARY_2%100				*/	"\0Cust&om:"
/*		22423	IDDC_PROPPAGE_VIEW_BASE+IDC_BTN_FONT1%100						*/	"\0Font &1"
/*		22424	IDDC_PROPPAGE_VIEW_BASE+IDC_BTN_FONT2%100						*/	"\0Font &2"
/*		22450	IDDC_PROPPAGE_VIEW_BASE+IDC_SYSTEM_COLOURS%100					*/	"\0&Use system colors"
/*		22453	IDDC_PROPPAGE_VIEW_BASE+IDC_SYSTEM_COLOURS2%100					*/	"\0Us&e system colors"
/*		22456	IDDC_PROPPAGE_VIEW_BASE+IDC_STAT_WIND%100						*/	"\0\2"
/*		22457	IDDC_PROPPAGE_VIEW_BASE+IDC_STAT_FONT%100						*/	"\0\2"
/*		22458	IDDC_PROPPAGE_VIEW_BASE+IDC_STAT_WIND2%100						*/	"\0Background color:"
/*		22459	IDDC_PROPPAGE_VIEW_BASE+IDC_STAT_FONT2%100						*/	"\0Font color:"
/*		22466	IDDC_PROPPAGE_VIEW_BASE+IDC_FLAT_TOOLBAR%100					*/	"\0Use def&ault toolbar style"
/*		22467	IDDC_PROPPAGE_VIEW_BASE+IDC_DIGITGRP%100						*/	"\0Use digit &grouping"
/*		22481	IDDC_PROPPAGE_VIEW_BASE+IDC_STAT_TRANS%100						*/	"\0&Transparency %:"
/*		24001	IDDC_FIND_BASE+IDOK				*/	"\0\5"
/*		24002	IDDC_FIND_BASE+IDCANCEL			*/	"\0\5"
/*		24056	IDDC_FIND_BASE+56				*/	"\0&Up"
/*		24057	IDDC_FIND_BASE+57				*/	"\0&Down"
/*		24072	IDDC_FIND_BASE+72				*/	"\0Direction"
/*		24101	IDDC_REPLACE_BASE+IDOK			*/	"\0&Find Next"
/*		24102	IDDC_REPLACE_BASE+IDCANCEL		*/	"\0Close"
/*		24124	IDDC_REPLACE_BASE+24			*/	"\0&Replace"
/*		24125	IDDC_REPLACE_BASE+25			*/	"\0Replace &All"
/*		24126	IDDC_REPLACE_BASE+26			*/	"\0F&ull Replace"
/*		24602	IDDC_PAGE_SETUP_BASE+2			*/	"\0&Left:"
/*		24603	IDDC_PAGE_SETUP_BASE+3			*/	"\0&Right:"
/*		24604	IDDC_PAGE_SETUP_BASE+4			*/	"\0&Top:"
/*		24605	IDDC_PAGE_SETUP_BASE+5			*/	"\0&Bottom:"
/*		24675	IDDC_PAGE_SETUP_BASE+75			*/	"\0Margins"
/*		24736	IDDC_PROPPAGE_A1_BASE+IDC_GOTO_HIDE_OFFSET%100		*/	"\0Hide &go to offset"
/*		24741	IDDC_PROPPAGE_A1_BASE+IDC_NUM_MRU%100				*/	"\0Recent files to re&member:"
/*		24742	IDDC_PROPPAGE_A1_BASE+IDC_RECENT%100				*/	"\0&Separate recent files menu"
/*		24743	IDDC_PROPPAGE_A1_BASE+IDC_INSERT_TIME%100			*/	"\0Don't insert &time with date"
/*		24744	IDDC_PROPPAGE_A1_BASE+IDC_PROMPT_BINARY%100			*/	"\0Skip load &warning prompts"
#ifdef USE_RICH_EDIT
"\0"
#else
/*	L	24745	IDDC_PROPPAGE_A1_BASE+IDC_DEFAULT_PRINT%100			*/	"\0Use default &printer font"
#endif
/*		24746	IDDC_PROPPAGE_A1_BASE+IDC_CURRENT_FIND_FONT%100		*/	"\0F&ind/replace use current font"
/*		24747	IDDC_PROPPAGE_A1_BASE+IDC_STICKY_WINDOW%100			*/	"\0Use fi&xed window position:"
/*		24748	IDDC_PROPPAGE_A1_BASE+IDC_BUTTON_STICK%100			*/	"\0Sa&ve Window Position"
/*		24749	IDDC_PROPPAGE_A1_BASE+IDC_SECONDARY_PRINT_FONT%100	*/	"\0Pri&nt using secondary font"
/*		24759	IDDC_PROPPAGE_A1_BASE+IDC_SMARTHOME%100				*/	"\0Disable smart &home"
/*		24760	IDDC_PROPPAGE_A1_BASE+IDC_READONLY_MENU%100			*/	"\0&Enable read only menu item"
#ifdef USE_RICH_EDIT
"\0"
/*	R	24768	IDDC_PROPPAGE_A1_BASE+IDC_LINK_DC%100				*/	"\0H&yperlinks require doubleclick"
#else
/*	L	24767	IDDC_PROPPAGE_A1_BASE+IDC_ALWAYS_LAUNCH%100			*/	"\0&Launch viewer for large files"
"\0"
#endif
/*		24769	IDDC_PROPPAGE_A1_BASE+IDC_NO_SAVE_EXTENSIONS%100	*/	"\0Don't a&uto-save extensions"
/*		24770	IDDC_PROPPAGE_A1_BASE+IDC_CONTEXT_CURSOR%100		*/	"\0&Context menu moves cursor"
#ifdef USE_RICH_EDIT
/*	R	24771	IDDC_PROPPAGE_A1_BASE+IDC_SUPPRESS_UNDO_PROMPT%100	*/	"\0Su&ppress undo buffer prompt"
#else
"\0"
#endif
/*		24772	IDDC_PROPPAGE_A1_BASE+IDC_BUTTON_CLEAR_FIND%100		*/	"\0Clear &Find History..."
/*		24773	IDDC_PROPPAGE_A1_BASE+IDC_BUTTON_CLEAR_RECENT%100	*/	"\0Clear &Recent Files..."
/*		24774	IDDC_PROPPAGE_A1_BASE+IDC_BUTTON_FORMAT%100			*/	"\0Set &Default File Format...  "
#ifdef USE_RICH_EDIT
/*	R	24775	IDDC_PROPPAGE_A1_BASE+IDC_HIDE_SCROLLBARS%100		*/	"\0Hide scro&llbars when possible"
#else
"\0"
#endif
/*		24776	IDDC_PROPPAGE_A1_BASE+IDC_NO_SAVE_HISTORY%100		*/	"\0Don't s&ave find history"
/*		24777	IDDC_PROPPAGE_A1_BASE+IDC_NO_FAVES%100				*/	"\0Disa&ble favorites menu"
/*		24778	IDDC_PROPPAGE_A1_BASE+IDC_NO_FIND_SELECT%100		*/	"\0D&on't auto-select on find"
/*		25101	IDDC_INSERT_BASE+IDOK			*/	"\0&Insert"
/*		25102	IDDC_INSERT_BASE+IDCANCEL		*/	"\0Close"
/*		31208	IDDP_PROPPAGE_GENERAL_BASE+8	*/	"\0&Tab size:"
/*		31210	IDDP_PROPPAGE_GENERAL_BASE+10	*/	"\0&Quote with:"
/*		31212	IDDP_PROPPAGE_GENERAL_BASE+12	*/	"\0&Primary external viewer:"
/*		31215	IDDP_PROPPAGE_GENERAL_BASE+15	*/	"\0&Args:"
/*		31217	IDDP_PROPPAGE_GENERAL_BASE+17	*/	"\0&Secondary external viewer:"
/*		31220	IDDP_PROPPAGE_GENERAL_BASE+20	*/	"\0A&rgs:"
/*		31222	IDDP_PROPPAGE_GENERAL_BASE+22	*/	"\0When launching viewers:"
/*		31301	IDDP_ABORT_PRINT_BASE+1			*/	"\0Now printing"
/*		31400	IDDP_GOTO_BASE+0				*/	"\0&Line #:"
/*		32400	IDDP_PROPPAGE_VIEW_BASE+0		*/	"\0Primary font"
/*		32409	IDDP_PROPPAGE_VIEW_BASE+9		*/	"\0Secondary font"
/*		32418	IDDP_PROPPAGE_VIEW_BASE+18		*/	"\0Window"
/*		32419	IDDP_PROPPAGE_VIEW_BASE+19		*/	"\0&Selection margin width:"
/*		34109	IDDP_REPLACE_BASE+9				*/	"\0Replace all in"
/*		34900	IDDP_PROPPAGE_A2_BASE+0			*/	"\0Quick buffers (select text and set with Alt + Shift + number)"
/*		34921	IDDP_PROPPAGE_A2_BASE+21		*/	"\0Language for menus, dialogs and messages"
/*		34926	IDDP_PROPPAGE_A2_BASE+26		*/	"\0Custom date formats:"
/*		34927	IDDP_PROPPAGE_A2_BASE+27		*/	"\0&F12:"
/*		34929	IDDP_PROPPAGE_A2_BASE+29		*/	"\0&Ctrl+F12:"
/*		35001	IDDP_ABOUT_PLUGIN_BASE+1		*/	"\0Language:"
/*		35003	IDDP_ABOUT_PLUGIN_BASE+3		*/	"\0Release:"
/*		35005	IDDP_ABOUT_PLUGIN_BASE+5		*/	"\0Translator:"
/*		35007	IDDP_ABOUT_PLUGIN_BASE+7		*/	"\0Contact:"
/*		35100	IDDP_INSERT_BASE+0				*/	"\0&Text:"
/*		35103	IDDP_INSERT_BASE+3				*/	"\0&Repeat:"
/*		35105	IDDP_INSERT_BASE+5				*/	"\0time(s)"
/*		40002	ID_HELP_ABOUT					*/	"\0&About..."
/*		40003	ID_MYFILE_OPEN					*/	"\0&Open..."
/*		40004	ID_MYFILE_EXIT					*/	"\0E&xit"
/*		40009	ID_MYFILE_SAVEAS				*/	"\0Save &As..."
/*		40011	ID_EDIT_WORDWRAP				*/	"\0&Word Wrap"
/*		40012	ID_MYFILE_NEW					*/	"\0&New"
/*		40013	ID_MYFILE_SAVE					*/	"\0&Save"
/*		40017	ID_FILE_LAUNCHVIEWER			*/	"\0&Primary Viewer"
/*		40020	ID_VIEW_OPTIONS					*/	"\0&Settings..."
/*		40021	ID_DATE_TIME					*/	"\0&Short Format"
/*		40023	ID_FONT_PRIMARY					*/	"\0&Primary Font"
/*		40026	ID_FIND							*/	"\0&Find..."
/*		40027	ID_REPLACE						*/	"\0R&eplace..."
/*		40028	ID_FIND_NEXT					*/	"\0Find Ne&xt"
/*		40029	ID_MYEDIT_UNDO					*/	"\0&Undo"
/*		40030	ID_MYEDIT_CUT					*/	"\0Cu&t"
/*		40031	ID_MYEDIT_COPY					*/	"\0&Copy"
/*		40032	ID_MYEDIT_PASTE					*/	"\0&Paste"
/*		40033	ID_MYEDIT_SELECTALL				*/	"\0Select &All"
/*		40035	ID_PRINT						*/	"\0&Print..."
/*		40036	ID_EDIT_SELECTWORD				*/	"\0&Select Word"
/*		40037	ID_GOTOLINE						*/	"\0&Go To Line..."
/*		40038	ID_FIND_PREV					*/	"\0Find Pre&vious"
/*		40039	ID_LFMT_DOS						*/	"\0&DOS (CR+LF)"
/*		40040	ID_LFMT_UNIX					*/	"\0&Unix (LF)"
/*		40041	ID_INDENT						*/	"\0&Indent"
/*		40043	ID_UNINDENT						*/	"\0&Unindent"
/*		40048	ID_LFMT_MAC						*/	"\0Old &Mac (CR)"
/*		40049	ID_LFMT_MIXED					*/	"\0Unmana&ged"
/*		40051	ID_LFMT_UNKNOWN					*/	"\0Line Endings:"
/*		40052	ID_ENC_UNKNOWN					*/	"\0Text Encoding:"
/*		40053	ID_RELOAD_CURRENT				*/	"\0&Refresh/Revert"
#ifdef USE_RICH_EDIT
/*	R	40054	ID_MYEDIT_REDO					*/	"\0&Redo"
#else
"\0"
#endif
/*		40055	ID_READONLY						*/	"\0R&ead Only"
/*		40057	ID_SHOWSTATUS					*/	"\0Show Status &Bar"
/*		40058	ID_DATE_TIME_LONG				*/	"\0&Long Format"
/*		40059	ID_FIND_NEXT_WORD				*/	"\0Find Next &Word"
/*		40062	ID_STRIPCHAR					*/	"\0S&trip First Character"
/*		40063	ID_MAKE_OEM						*/	"\0&OEM/DOS Encoding"
/*		40064	ID_MAKE_ANSI					*/	"\0&ANSI/Windows Encoding"
/*		40065	ID_COMMIT_WORDWRAP				*/	"\0Co&mmit Word Wrap"
#ifdef USE_RICH_EDIT
/*	R	40067	ID_SHOWHYPERLINKS				*/	"\0Show Hyperlin&ks"
#else
"\0"
#endif
/*		40071	ID_PAGESETUP					*/	"\0Page Se&tup..."
/*		40072	ID_MAKE_UPPER					*/	"\0&Uppercase"
/*		40073	ID_MAKE_LOWER					*/	"\0&Lowercase"
/*		40074	ID_STRIP_CR						*/	"\0Un&wrap Lines"
/*		40075	ID_SHOWTOOLBAR					*/	"\0Show &Toolbar"
/*		40078	ID_TABIFY						*/	"\0Ta&bified"
/*		40079	ID_UNTABIFY						*/	"\0U&ntabified"
/*		40081	ID_NEW_INSTANCE					*/	"\0New W&indow"
/*		40082	ID_ALWAYSONTOP					*/	"\0&Always On Top"
/*		40084	ID_STRIP_CR_SPACE				*/	"\0Unwrap Lines (w/ S&pace)"
/*		40087	ID_LAUNCH_ASSOCIATED_VIEWER		*/	"\0&Default Viewer"
/*		40088	ID_STRIP_TRAILING_WS			*/	"\0&Strip Trailing Whitespace"
/*		40089	ID_ENC_UTF16					*/	"\0Un&icode"
/*		40090	ID_ENC_UTF16BE					*/	"\0Unicode (&Big Endian)"
/*		40091	ID_MYEDIT_DELETE				*/	"\0&Delete"
/*		40092	ID_FAV_ADD						*/	"\0&Add to Favorites..."
/*		40093	ID_FAV_EDIT						*/	"\0&Edit Favorites"
/*		40094	ID_FAV_RELOAD					*/	"\0&Reload Favorites"
/*		40095	ID_QUOTE						*/	"\0&Quote"
/*		40096	ID_MAKE_INVERSE					*/	"\0&Inverted Case"
/*		40097	ID_MAKE_SENTENCE				*/	"\0&Sentence Case"
/*		40098	ID_MAKE_TITLE					*/	"\0&Title Case"
/*		40099	ID_ESCAPE_NEWLINE				*/	"\0Newline"
/*		40100	ID_INSERT_FILE					*/	"\0&Insert File..."
/*		40101	ID_ESCAPE_BACKSLASH				*/	"\0Backslash"
/*		40102	ID_ESCAPE_DISABLE				*/	"\0Disabled"
/*		40105	ID_LAUNCH_SECONDARY_VIEWER		*/	"\0&Secondary Viewer"
/*		40109	ID_ENC_UTF8						*/	"\0UTF-&8"
/*		40110	ID_ESCAPE_TAB					*/	"\0Tab"
/*		40111	ID_ENC_ANSI						*/	"\0&ANSI"
/*		40112	ID_ENC_BIN						*/	"\0Bi&nary (Preserve NULLs)"
/*		40118	ID_ENC_CODEPAGE					*/	"\0Codepage %d"
/*		40119	ID_ENC_CUSTOM					*/	"\0Enter &Codepage..."
/*		40204	ID_DATE_TIME_CUSTOM				*/	"\0Custom Format &1"
/*		40205	ID_DATE_TIME_CUSTOM2			*/	"\0Custom Format &2"
/*		40206	ID_PASTE_MUL					*/	"\0Paste Mu&ltiple..."
/*		40207	ID_INSERT_TEXT					*/	"\0Insert Text..."
/*		40208	ID_COPY_HEX						*/	"\0&Copy As Hex"
/*		40209	ID_PASTE_HEX					*/	"\0&Paste As Hex"
/*		40210	ID_CLEAR_CLIPBRD				*/	"\0Clear clipboard"
/*		40211	ID_ESCAPE_HEX					*/	"\0Hex Value"
/*		40212	ID_ESCAPE_DEC					*/	"\0Decimal Value"
/*		40213	ID_ESCAPE_OCT					*/	"\0Octal Value"
/*		40214	ID_ESCAPE_BIN					*/	"\0Binary Value"
/*		40215	ID_ESCAPE_HEXU					*/	"\0Hex Value (Unicode)"
/*		40216	ID_ESCAPE_HEXS					*/	"\0Hex String"
/*		40217	ID_ESCAPE_HEXSU					*/	"\0Hex String (Unicode)"
/*		40218	ID_ESCAPE_B64S					*/	"\0Base-64 String"
/*		40219	ID_ESCAPE_B64SU					*/	"\0Base-64 String (Unicode)"
/*		40220	ID_COPY_B64						*/	"\0Copy As B&ase-64"
/*		40221	ID_PASTE_B64					*/	"\0Paste As &Base-64"
/*		40223	ID_ESCAPE_ANY					*/	"\0Any 1 Character"
/*		40224	ID_ESCAPE_RAND					*/	"\0Random Character"
/*		40225	ID_ESCAPE_WILD0					*/	"\0Any 0+ Characters"
/*		40226	ID_ESCAPE_WILD1					*/	"\0Any 1+ Characters"
/*		40227	ID_ESCAPE_REP0					*/	"\0""0+ of Preceding Character"
/*		40228	ID_ESCAPE_REP1					*/	"\0""1+ of Preceding Character"
/*		40229	ID_SCROLLTO_SELA				*/	"\0Go To Selection"
/*		40230	ID_SCROLLTO_SELE				*/	"\0Go To Caret"
/*		41110	IDM_MENU_BASE+10				*/	"\0&File"
/*		41111	IDM_MENU_BASE+11				*/	"\0&Launch"
/*		41112	IDM_MENU_BASE+12				*/	"\0F&ile Format"
/*		41113	IDM_MENU_BASE+13				*/	"\0Recent &Files"
/*		41120	IDM_MENU_BASE+20				*/	"\0&Edit"
/*		41121	IDM_MENU_BASE+21				*/	"\0E&ncoded text"
/*		41122	IDM_MENU_BASE+22				*/	"\0&Block"
/*		41123	IDM_MENU_BASE+23				*/	"\0C&onvert Selected"
/*		41124	IDM_MENU_BASE+24				*/	"\0Insert &Date/Time"
/*		41130	IDM_MENU_BASE+30				*/	"\0F&avorites"
/*		41140	IDM_MENU_BASE+40				*/	"\0&Options"
/*		41150	IDM_MENU_BASE+50				*/	"\0&Help"
/*		41211	IDM_POPUP_BASE+11				*/	"\0&Make"
/*		41212	IDM_POPUP_BASE+12				*/	"\0&Insert Date"
/*		44200	ID_TRANSPARENT					*/	"\0T&ransparent Mode"
"";
/* Excel:
	Import:	\n->\n/*\t		(~A->\t~A)		~A\t->		~B\t->\t\t\t*\/\t"\\0		\n->"\n		`->		(*\/->\t*\/)	(\t*\/->*\/)
	Export:
*/
static WORD stringsidx[] = {0,0,0,0,0,0,2,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,7,1,9,3,70,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,203,10,0,47,0,0,0,0,0,2,0,0,0,0,3,0,0,0,0,0,0,0,0,3,0,0,69,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,16,56,0,243,0,10,1,21,2,0,1,1,0,29,1,7,0,0,0,0,0,0,447,0,4,0,1,0,0,0,486,0,7,0,39,0,18,1,0,5,19091,0,4,13,0,0,0,0,0,0,1,2,1176,0,0,0,1,0,25,2,2,0,0,0,6,0,13,1519,0,53,0,14,28,0,21,0,0,475,0,0,0,69,60,4,0,0,0,0,0,0,0,0,9,0,6,0,0,0,0,0,0,0,0,0,0,0,322,0,6105,1,1,2,1,2,1,78,98,999,8,8,0,1689,790,20,4,0,1,71,1,1,1,92,2,1,4896,0,0,4,1,0,0,3,2,0,1,2,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,4,0,1,0,0,0,0,1,0,0,2,0,0,0,1,3,0,0,0,0,2,0,1,0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,0,0,0,5,0,84,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,879,0,0,0,6,0,0,0,0,5,9,9,60,0,2987};

static LPTSTR pstrings = NULL;
static WORD *pstringsidx = NULL, *pstringsofs = NULL;
static WORD *accCmds = NULL, *accKeys = NULL, accNum = 0;




//Currently only used by ID_SET_MACRO_x
BOOL EncodeWithEscapeSeqs(TCHAR* szText) {                     
	TCHAR szStore[MAXMACRO];
	INT i,j;
	for (i = 0, j = 0; i < MAXMACRO && szText[i]; ++i) {
		switch (szText[i]) {
		case _T('\n'):
			break;
		case _T('\r'):
			szStore[j++] = _T('\\');
			szStore[j++] = _T('n');
			break;
		case _T('\t'):
			szStore[j++] = _T('\\');
			szStore[j++] = _T('t');
			break;
		case _T('\\'):
			szStore[j++] = _T('\\');
			szStore[j++] = _T('\\');
			break;
		default:
			szStore[j++] = szText[i];
		}
		if (j >= MAXMACRO - 1) {
			return FALSE;
		}
	}
	szStore[j] = _T('\0');
	lstrcpy(szText, szStore);
	return TRUE;
}

BOOL ParseForEscapeSeqs(LPTSTR buf, LPBYTE* specials, LPCTSTR errContext) {
#ifdef UNICODE
	static const TCHAR spsub[] = {_T('\x332'), _T('\xFFFD'), _T('\xD7'), _T('\x2014'), _T('\x2026'), _T('\xFFFC')};
#endif
	LPTSTR op = buf, bout, end, szErr, szErr2, szErr3, dbuf;
	INT l, m, base = 0, mul = 3, uni = 0, str, expl = 0, dbufalloc = 0, spi = 0;
	DWORD p = 0;
	WORD enc = (nFormat >> 31 ? FC_ENC_CODEPAGE : (WORD)nFormat);

	if (!SCNUL(buf)[0]) return TRUE;
	kfree(specials);
	for (bout = buf; *buf; buf++, base = uni = expl = spi = 0, p++) {
		if (*buf == _T('\\')) {
			switch(*++buf){
			case _T('n'):
#ifdef USE_RICH_EDIT
				*bout++ = _T('\r');
#else
				*bout++ = _T('\r');
				*bout++ = _T('\n');
				p++;
#endif
				continue;
			case _T('R'): *bout++ = _T('\r'); continue;
			case _T('N'): *bout++ = _T('\n'); continue;
			case _T('t'): *bout++ = _T('\t'); continue;
			case _T('a'): *bout++ = _T('\a'); continue;
			case _T('e'): *bout++ = _T('\x1e'); continue;
			case _T('f'): *bout++ = _T('\f'); continue;
			case _T('v'): *bout++ = _T('\v'); continue;
			case _T('_'): if (!spi) spi = 1;
			case _T('?'): if (!spi) spi = 2;
			case _T('*'): if (!spi) spi = 3;
			case _T('-'): if (!spi) spi = 4;
			case _T('+'): if (!spi) spi = 5;
			case _T('$'): if (!spi) spi = 6;
				if (specials) {
					if (!*specials) *specials = (LPBYTE)kallocz(lstrlen(op)+1);
					(*specials)[p] = spi;
				}
				if (spi == 6){
#ifdef UNICODE
					if (enc == FC_ENC_UTF16 || enc == FC_ENC_UTF16BE)
						*bout++ = RAND()%0xffe0+0x20;
					else
#endif
						*bout++ = RAND()%0x60+0x20;
					continue;
				}
#ifdef UNICODE
				*bout++ = spsub[spi-1];
				continue;
#endif
				break;
			case _T('U'):
			case _T('u'): uni = 1; 
			case _T('X'):
			case _T('x'): if (!base) { base = 16; mul = 2; } if (!uni) uni = 2;
			case _T('W'):
			case _T('w'): if (!uni) uni = 1;
			case _T('S'): 
			case _T('s'): if (!base) { base = 64; mul = 4; }
			case _T('B'):
			case _T('b'): if (!base) { base = 2; mul = 8; }
			case _T('D'):
			case _T('d'): if (!base) base = 10;
			case _T('O'):
			case _T('o'): buf++; expl = 1;
			default:	  if (!base) base = 8;
				str = (expl && (*(buf-1) & _T('_')) == *(buf-1));
				end = buf;
				if (uni == 1) mul *= 2;
				if (sizeof(TCHAR) >= 2 && uni != 1) {
					if (!dbufalloc) {
						dbuf = kallocs(MAXFIND + 2);
						dbufalloc = 1;
					}
				} else
					dbuf = bout;
				l = DecodeBase(base, buf, (LPBYTE)dbuf, str ? -1 : mul, 1, str && base != 64 ? 0 : 1, FALSE, &end);
				if (l > 0) {
					m = l;
					if (sizeof(TCHAR) >= 2 && uni == 1){
						while (m % sizeof(TCHAR))
							*((LPBYTE)(dbuf)+(m++)) = 0;
						m /= sizeof(TCHAR);
					}
					buf = end;
					if (str && *buf && *buf != '\\') 
						l = -1;
#ifdef UNICODE
					else if (sizeof(TCHAR) >= 2 && uni != 1 && !(m = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)dbuf, m, bout, m * sizeof(TCHAR))))
						l = -3;
#endif
					else if (str && uni == 1 && l % sizeof(TCHAR))
						l = -2;
#ifdef UNICODE
					else if (uni == 1 && l >= 2 && enc != FC_ENC_UTF16BE)
						ReverseBytes((LPBYTE)bout, l * 2);
#endif
					if (!str) buf--;
				} else if (l == -2 && str && *end && *end != '\\') l = -1;
				if (l > 0) {
					p += m - 1;
#ifdef UNICODE
					for (; m; m--, bout++) {
						if (*bout == _T('\0'))
							*bout = _T('\x2400');
					}
#else
					bout += m;
#endif
					if (str && !*buf) buf--;
					continue;
				}
				if (l == 0 && !expl) break;
				if (!errContext) return FALSE;
				szErr2 = kallocs(MAXSTRING * 2 + 32);
				szErr3 = szErr2 + MAXSTRING * 2;
				lstrcpy(szErr3, errContext);
				switch(l) {
					case 0: szErr = (LPTSTR)GetString(IDS_ESCAPE_EXPECTED); break;
					case -1: szErr = (LPTSTR)GetString(IDS_ESCAPE_BADCHARS); break;
					case -2: szErr = (LPTSTR)GetString(IDS_ESCAPE_BADALIGN); break;
					case -3: szErr = (LPTSTR)GetString(IDS_UNICODE_CONV_ERROR); break;
					default: szErr = (LPTSTR)GetString(IDS_ERROR); break;
				}
				wsprintf(szErr2, szErr, base, mul);
				szErr = szErr2 + MAXSTRING;
				wsprintf(szErr, GetString(IDS_ESCAPE_ERROR), szErr2, szErr3);
				lstrcat(szErr, _T("\n'"));
				lstrcpyn(szErr3, &op[MAX(0, end-op-15)], MIN(end-op, 15)+1);
				lstrcat(szErr, szErr3);
				lstrcat(szErr, _T(" *** "));
				lstrcpyn(szErr3, end, 16);
				lstrcat(szErr, szErr3);
				lstrcat(szErr, _T("'"));
				ERROROUT(szErr);
				kfree(&szErr2);
				if (dbufalloc) kfree(&dbuf);
				return FALSE;
			}
		}
		if (*buf)	*bout++ = *buf;
		else		*buf--;
	}
	*bout = _T('\0');
	if (dbufalloc) kfree(&dbuf);
	return TRUE;
	// abcdefghijklmnopqrstuvwxyz _?*-+$
	// xM Mxx       XM  XMxMxMM  M123456
}






BOOL LoadLng(LPTSTR filename, LPTSTR* str, WORD** stridx, WORD** strofs){
	LPTSTR os, ds, np;
	TCHAR c, pc = _T(' '), err[MAXSTRING];
	LONG st, l, ct=0, smax=ARRLEN(stringsidx), lin=1;
	kfree(str);
	kfree(stridx);
	kfree(strofs);
	if (!LoadFile(filename, FALSE, FALSE, FALSE, 0, str) || !*str || !**str) return FALSE;
	*stridx = (WORD*)kallocz(smax * sizeof(WORD));
	*strofs = (WORD*)kallocz(smax * sizeof(WORD));
	for (st=0, os=ds=*str; *os && ct < smax; os++, pc=c) {
		if (st == 9) {
			wsprintf(err, GetString(IDS_LOADLNG_ERROR), FormatNumber(lin, options.bDigitGrp, 0, 0));
			ERROROUT(err);
			return FALSE;
		}
		if ((c = *os) == _T('\r') || c == _T('\n')) {
			if (pc == c || (pc != _T('\r') && pc != _T('\n'))) lin++;
			if (st == 4) {
				*ds++ = 0;
				ct++;
				if (!ParseForEscapeSeqs(np, NULL, kemptyStr)) { st = 9; continue; }
				ds = np+lstrlen(np)+1;
				//if ((*stridx)[ct++] == upto) break;
			}
			st = 0;
			continue;
		}
		switch(st){
			case 0:
				if (c == _T('\t') || c == _T(' ')) continue;
				else if (c == _T('#') || c == _T('/')) { st = 1; continue; }
				else if (c >= _T('0') && c <= _T('9')) { np = os; st = 2; continue; }
				st = 9;
				break;
			case 2:
				if (c >= _T('0') && c <= _T('9')) continue;
				st = 3;
				l = _ttol(np);
				if (l <= 0 || l >= 0xffff) {
					st = 9; break;
				}
				(*stridx)[ct] = (WORD)l;
				if ((l = ds-*str) > 0xffff) { st = 9; break; }
				(*strofs)[ct] = (WORD)l;
				os--;
				continue;
			case 3:
				if (c == _T('\t') || c == _T(' ')) continue;
				np = ds;
				st = 4;
				os--;
				continue;
			case 4:
				if (c == _T('`')) continue;
				*ds++ = *os;
				continue;
		}
	}
	for ( ; ct < smax; (*stridx)[ct++] = 0xffff) ;
	return TRUE;
}

BOOL HaveLanguagePlugin(){
	return pstringsidx || (hinstLang && hinstThis != hinstLang);
}
void UnloadLanguagePlugin(){
	kfree(&pstrings);
	kfree(&pstringsidx);
	kfree(&pstringsofs);
	if (hinstLang && hinstLang != hinstThis)
		FreeLibrary(hinstLang);
	hinstLang = NULL;
}
/**
 * Load and verify a language plugin.
 *
 * @param szPlugin Path to language plugin. 
 */
BOOL LoadAndVerifyLanguagePlugin(LPCTSTR szPlugin, BOOL checkver, HINSTANCE* hinstTemp){
	TCHAR plugVer[16] = {0}, szErr[MAXSTRING];
	LPCTSTR thisVer, pplugVer = (LPCTSTR)plugVer;
	LPTSTR pstr = NULL;
	WORD dlen = ARRLEN(stringsidx), *pstridx = NULL, *pstrofs = NULL;
	BOOL dll;
	if (dll = (szPlugin[lstrlen(szPlugin)-1] == _T('l')))
		*hinstTemp = LoadLibrary(szPlugin);
	else
		*hinstTemp = (HINSTANCE)LoadLng((LPTSTR)szPlugin, &pstr, &pstridx, &pstrofs);
	if (!*hinstTemp) {
		if (!dll) { kfree(&pstr); kfree(&pstridx); }
		ERROROUT(GetString(IDS_INVALID_PLUGIN_ERROR));
		return FALSE;
	}
	if (dll)
		LoadString(*hinstTemp, IDS_VERSION_SYNCH, plugVer, 16);
	else
		pplugVer = GetStringEx(IDS_VERSION_SYNCH, dlen, NULL, pstridx, pstrofs, pstr, &dlen, NULL);
	if (!pplugVer || !*pplugVer) {
		if (!dll) { kfree(&pstr); kfree(&pstridx); }
		else FreeLibrary(*hinstTemp);
		ERROROUT(GetString(IDS_BAD_STRING_PLUGIN_ERROR));
		return FALSE;
	}
	if (checkver && !g_bDisablePluginVersionChecking && lstrcmpi((thisVer = GetString(IDS_VERSION_SYNCH)), pplugVer) != 0) {
		wsprintf(szErr, GetString(IDS_PLUGIN_MISMATCH_ERROR), plugVer, thisVer);
		ERROROUT(szErr);
	}
	if (!dll) {
		*hinstTemp = 0;
		if (!checkver) {
			UnloadLanguagePlugin();
			pstrings = pstr;
			pstringsofs = pstrofs;
			pstringsidx = pstridx;
		}
	} else if (checkver) FreeLibrary(*hinstTemp);
	return TRUE;
}

/**
 * Find and load a language plugin.
 *
 * @note Plugin's path is stored in options.szLangPlugin.
 * @note Default to english if unable to load a plugin.
 */
void FindAndLoadLanguagePlugin(void) {
	WIN32_FIND_DATA FileData;
	HANDLE hSearch;
	HINSTANCE hinstTemp;
	UnloadLanguagePlugin();
	if (!SCNUL(options.szLangPlugin)[0])
		return;
	hSearch = FindFirstFile(options.szLangPlugin, &FileData);
	if (hSearch == INVALID_HANDLE_VALUE) {
		ERROROUT(GetString(IDS_PLUGIN_ERRFIND));
		goto badplugin;
	} else
		FindClose(hSearch);
	if (LoadAndVerifyLanguagePlugin(options.szLangPlugin, FALSE, &hinstTemp)) {
		if (hinstTemp) hinstLang = hinstTemp;
		return;
	}
badplugin:
	ERROROUT(GetString(IDS_PLUGIN_ERR));
}





BOOL ParseAccels(HACCEL acc) {
	INT i, j, n, p;
	LPACCEL acm;
	if (!acc) return FALSE;
	if (0 >= (n = CopyAcceleratorTable(acc, NULL, 0))) return FALSE;
	if (!(acm = kcalloc(n, sizeof(ACCEL)))) return FALSE;
	if (n > CopyAcceleratorTable(acc, acm, n)) return FALSE;
	if (!(accKeys = kcallocz(n, sizeof(WORD)))) return FALSE;
	if (!(accCmds = kcallocz(n, sizeof(WORD)))) return FALSE;
	for (i=0; i<n; i++) {
		p = kbinsearch((LPVOID*)accCmds, (LPVOID)acm[i].cmd, sizeof(WORD), 0, i, TRUE);
		for (j=i; j>p; j--) {
			accCmds[j] = accCmds[j-1];
			accKeys[j] = accKeys[j-1];
		}
		accCmds[p] = acm[i].cmd;
		accKeys[p] = (acm[i].fVirt << 8) | (acm[i].key & 0xff);
	}
	accNum = n;
	kfree(&acm);
	return TRUE;
}

BOOL GetAccelStr(WORD uID, LPTSTR buf){
	static const CHAR vkstr[] = "\0\0Shift\0Ctrl\0Alt\0\0\0\0Bksp\0Tab\0\0\0\0Enter\0\0\0\0\0\0Pause\0CapsLock\0\0\0\0\0\0\0Esc\0\0\0\0\0Space\0PgUp\0PgDn\0End\0Home\0Left\0Up\0Right\0Down\0\0\0\0\0Ins\0Del\0";
	static const BYTE vkmodord[] = {3,4,2};
	static TCHAR vkcache[sizeof(vkstr)];
	static WORD *vkstrofs = NULL, vkstrofspop = 0;
	INT i;
	WORD key;
	LPCTSTR sz;
	if (!accCmds || !accKeys || !buf) return FALSE;
	if (!vkstrofs && !(vkstrofs = kcallocz(MAXACCELKEYS, sizeof(WORD)))) return FALSE;
	if (0 > (i = kbinsearch((LPVOID*)accCmds, (LPVOID)uID, sizeof(WORD), 0, accNum, FALSE))) return FALSE;
	key = accKeys[i];
	*buf = '\0';
	for (i=0; i < ARRLEN(vkmodord); i++){
		if (((key >> (8+vkmodord[i])) & 1) && (sz = GetStringEx(vkmodord[i], MAXACCELKEYS, vkstr, NULL, vkstrofs, vkcache, &vkstrofspop, NULL)) && *sz) {
			lstrcat(buf, sz);
			buf += lstrlen(buf);
			*buf++ = '+';
			*buf = 0;
		}
	}
	if ((key &= 0xff) < MAXACCELKEYS) {
		if (!(sz = GetStringEx(key, MAXACCELKEYS, vkstr, NULL, vkstrofs, vkcache, &vkstrofspop, NULL)) || !*sz) return FALSE;
		lstrcat(buf, sz);
		return TRUE;
	} else if (key >= VK_F1 && key <= VK_F24) {
		key -= VK_F1-1;
		*buf++ = 'F';
		if (key / 10 > 0) *buf++ = '0'+key/10;
		*buf++ = '0'+key%10;
	} else
		*buf++ = key;
	*buf = 0;
	return TRUE;
}

BOOL AddMenuAccelStr(WORD uID, LPCTSTR* str, LPTSTR buf, LPTSTR vkbuf, BOOL rename){
	LPTSTR pch;
	if (!str) str = &buf;
	if (!*str || (uID && !GetAccelStr(uID, vkbuf)) || (vkbuf && !*vkbuf)) return FALSE;
	if (*str != buf) lstrcpy(buf, *str);
	if (rename && (pch = lstrchr(buf, _T('\t')))) pch++;
	else if (uID) {
		pch = buf + lstrlen(buf);
		*pch++ = _T('\t');
	} else return FALSE;
	*pch = 0;
	if (uID) lstrcat(pch, vkbuf);
	*str = buf;
	return TRUE;
}


LPCTSTR GetStringEx(WORD uID, WORD total, LPCSTR dict, WORD* dictidx, WORD* dictofs, LPTSTR dictcache, WORD* ofspop, LPCTSTR def){
	WORD i, j, idx;
	LPCSTR sp;
	LPTSTR cp;
	if (dictidx) {
		if (dictidx[0]>=dictidx[1])
			ExpandDifMap(dictidx, sizeof(*dictidx), total);
		if (0 > (SHORT)(idx = kbinsearch((LPVOID*)dictidx, (LPVOID)uID, sizeof(uID), 0, total, FALSE)))
			return def;
	} else idx = uID;
	while(1) {
		for (i = *ofspop, j = dictofs[i], sp = dict+j, cp = dictcache+j; i <= idx; i++) {
			for (j=1; *sp; j++)
				*cp++ = (BYTE)*sp++;
			*cp++ = *sp++;
			if (i+1 < total) dictofs[i+1] = dictofs[i] + j;
		}
		*ofspop = MAX(*ofspop, idx+1);
		if (dict && *(dict + dictofs[idx]) && (BYTE)*(dict + dictofs[idx]) < ' ' && !*(dict + dictofs[idx] + 1)){
			idx += *(dict + dictofs[idx]);
			continue;
		}
		return dictcache + dictofs[idx];
	}
}

LPCTSTR GetString(WORD uID) {
	static WORD l = ARRLEN(stringsidx), ofs[ARRLEN(stringsidx)] = {0}, ofspop = 0;
	static TCHAR strcache[sizeof(strings)];
	static LPTSTR szRsrc = NULL, szAcc = NULL;
	LPCTSTR sz = NULL;
	if (hinstLang && hinstThis != hinstLang && uID > IDS_VERSION_SYNCH && (uID < NONLOCALIZED_BASE || uID > NONLOCALIZED_END) && LoadString(hinstLang, uID, (LPTSTR)&sz, 0)) {
		if (!szRsrc) szRsrc = kallocs(MAXSTRING);
		LoadString(hinstLang, uID, szRsrc, MAXSTRING);
		return szRsrc;
	}
	if (pstringsidx && uID > IDS_VERSION_SYNCH && (uID < NONLOCALIZED_BASE || uID > NONLOCALIZED_END))
		sz = GetStringEx(uID, l, NULL, pstringsidx, pstringsofs, pstrings, &l, NULL);
	if (!sz || !*sz)
		sz = GetStringEx(uID, l, (LPSTR)strings, stringsidx, ofs, strcache, &ofspop, kemptyStr);
	if (uID < IDC_BASE) return sz;
	if (!szRsrc) {
		if (!(szRsrc = kallocs(MAXSTRING))) return sz;
		szAcc = szRsrc + MAXSTRING - MAXACCELSTR;
	}
	AddMenuAccelStr(uID, &sz, szRsrc, szAcc, FALSE);
	return sz;
}



void LocalizeMenuItems(HMENU m, HMENU pm, WORD pos, WORD depth, LPTSTR tpbuf, LPTSTR tabuf){
	MENUITEMINFO mio;
	LPCTSTR ts = NULL, pts = NULL;
	TCHAR tbuf[2];
	LPVOID *psub = NULL;
	WORD cmd=0, gpos, *pgpos = NULL;
	INT i, j, ct, pct=0;
	BOOL popup = FALSE;
	mio.cbSize = sizeof(MENUITEMINFO);
	if (pm && IsMenu(pm) && (pct = GetMenuItemCount(pm)) > 0) {
		psub = (LPVOID*)kallocz(pct * sizeof(LPVOID));
		pgpos = (WORD*)kallocz(pct * sizeof(WORD));
		for (j=0, gpos=0; j<pct; j++) {
			mio.fMask = MIIM_TYPE | MIIM_ID | MIIM_SUBMENU;
			mio.fType = MFT_STRING;
			mio.cch = 2;
			mio.dwTypeData = tbuf;
			GetMenuItemInfo(pm, j, TRUE, &mio);
			if (mio.hSubMenu && IsMenu(mio.hSubMenu)) {
				psub[j] = mio.hSubMenu;
				pgpos[j] = gpos;
				gpos++;
			} else if (mio.wID <= 0xffff && (LPVOID)mio.wID != (LPVOID)mio.hSubMenu)
				pgpos[j] = mio.wID;
			else gpos = (gpos & ~0xf) + 0x10;
		}
	} else pm=NULL;
	for (i=0, ct=GetMenuItemCount(m), gpos=0; i<ct; i++, popup=FALSE, cmd=0, ts=pts=NULL) {
		mio.fMask = MIIM_TYPE | MIIM_ID | MIIM_SUBMENU;
		mio.fType = MFT_STRING;
		mio.cch = 2;
		mio.dwTypeData = tbuf;
		GetMenuItemInfo(m, i, TRUE, &mio);
		if (mio.hSubMenu && IsMenu(mio.hSubMenu)) {
			popup = TRUE;
			cmd = pos;
		} else if (mio.wID <= 0xffff && (LPVOID)mio.wID != (LPVOID)mio.hSubMenu)
			cmd = (WORD)mio.wID;
		else gpos = (gpos & ~0xf) + 0x10;
		if (pm && cmd) {
			for (j=0; j<pct; j++)
				if (pgpos[j] == (popup ? gpos : cmd))
					break;
		} else j = pct;
		if (popup) {
			LocalizeMenuItems(mio.hSubMenu, j<pct ? psub[j] : NULL, pos+depth/10, depth/10, tpbuf, tabuf);
			pos += depth;
			gpos++;
		}
		if (cmd < IDC_BASE || cmd >= 0xffff) continue;
		if (!mio.dwTypeData || *mio.dwTypeData < _T(' ')) {
			if (j < pct) {
				mio.fMask = MIIM_TYPE;
				mio.fType = MFT_STRING;
				mio.cch = MAXSTRING;
				mio.dwTypeData = tpbuf;
				GetMenuItemInfo(pm, j, TRUE, &mio);
				if (mio.dwTypeData && *mio.dwTypeData) pts = ts = mio.dwTypeData;
			}
			if (ts && *ts) AddMenuAccelStr(cmd, &ts, tpbuf, tabuf, TRUE);
			else ts = GetString(cmd);
			if (ts && *ts) {
				mio.fMask = MIIM_TYPE | MIIM_STATE;
				mio.fType = MFT_STRING;
				mio.fState = (mio.dwTypeData && *mio.dwTypeData < _T(' ') ? *mio.dwTypeData : MFS_ENABLED);
				mio.dwTypeData = (LPTSTR)ts;
				SetMenuItemInfo(m, i, TRUE, &mio);
			}
		}
	}
	kfree(&(LPVOID)psub);
	kfree(&pgpos);
}

HMENU LocalizeMenu(WORD mID) {
	HMENU menu, pmenu = NULL;
	LPTSTR pbuf = NULL, abuf = NULL;
	if (!(menu = LoadMenu(hinstThis, MAKEINTRESOURCE(mID))))
		return menu;
	if (hinstLang && hinstThis != hinstLang) {
		pmenu = LoadMenu(hinstLang, MAKEINTRESOURCE(mID));
		pbuf = kallocs(MAXSTRING);
		abuf = pbuf + MAXSTRING - MAXACCELSTR;
	}
	LocalizeMenuItems(menu, pmenu, IDM_BASE+(mID-IDR_BASE)*100+10, 10, pbuf, abuf);
	if (pmenu) {
		kfree(&pbuf);
		DestroyMenu(pmenu);
	}
	return menu;
}


#define MAXDLGCONTROLS 48
typedef struct {
	WORD cct, gpos, cgpos[MAXDLGCONTROLS];
	HWND parent, ctl[MAXDLGCONTROLS];
	TCHAR tbuf[MAXSTRING];
} LDCList;
typedef struct {
	WORD dID, cnum;
	HWND parent;
	LDCList *plist;
} LDCState;

BOOL CALLBACK LDSetFont(HWND hwnd, LPARAM font){
	SendMessage(hwnd, WM_SETFONT, font, TRUE);
	return TRUE;
}
BOOL CALLBACK LocalizeDialogGather(HWND hwnd, LPARAM lParam){
	INT i;
	TCHAR tbuf[16];
	LDCList *list = (LDCList*)lParam;
	if (!list || GetParent(hwnd) != list->parent || list->cct >= MAXDLGCONTROLS) return TRUE;
	GetClassName(hwnd, tbuf, 16);
	if (!lstrcmpi(tbuf, WC_COMBOBOX) || !lstrcmpi(tbuf, WC_EDIT)) return TRUE;
	i = GetDlgCtrlID(hwnd);
	if (i < 0 || i == (WORD)IDC_STATIC) i = 0;
	else if (i < IDC_BASE) i+= IDC_BASE;
	GetWindowText(hwnd, tbuf, 2);
	if (*tbuf >= _T(' ')) {
		list->cgpos[list->cct] = i ? i : list->gpos;
		list->ctl[list->cct++] = hwnd;
	}
	if (!i) list->gpos++;
	return TRUE;
}
BOOL CALLBACK LocalizeDialogItems(HWND hwnd, LPARAM lParam){
	/* Escape string definitions (in .rc file):
		\1: Don't use IDDC_ string for this control (handles some conflicting IDs grandfathered in from 3.6-)
		\2: External lang. DLL handling - localize by-position if by-command localization failed - for controls which didn't have specific ID assigned in 3.6-
		\3: External lang. DLL handling - force localize by-position - for controls whose ID has changed since 3.6-
	*/
	INT i, j;
	LPCTSTR ts=NULL;
	TCHAR tbuf[16];
	LDCState *state = (LDCState*)lParam;
	if (!state || GetParent(hwnd) != state->parent) return TRUE;
	state->cnum++;
	GetClassName(hwnd, tbuf, 16);
	if (!lstrcmpi(tbuf, WC_COMBOBOX) || !lstrcmpi(tbuf, WC_EDIT)) return TRUE;
	i = GetDlgCtrlID(hwnd);
	if (i < 0 || i == (WORD)IDC_STATIC) i = 0;
	else if (i < IDC_BASE) i+= IDC_BASE;
	GetWindowText(hwnd, tbuf, 2);
	if (state->plist) {
		for (j = 0; i && j < state->plist->cct; j++) {
			if (state->plist->cgpos[j] == i)
				break;
		}
		if ((!i || (BYTE)*tbuf == 2 || (BYTE)*tbuf == 3) && (!i || j >= state->plist->cct)) {
			for (j = 0; j < state->plist->cct; j++) {
				if (((BYTE)*tbuf == 3 && state->plist->cgpos[j] != 0xffff) || state->plist->cgpos[j] == state->plist->gpos)
					break;
			}
			if ((BYTE)*tbuf != 3)
				state->plist->gpos++;
		} else if (*tbuf)
			state->plist->gpos++;
		if (j < state->plist->cct && state->plist->ctl[j]) {
			ts = state->plist->tbuf;
			GetWindowText(state->plist->ctl[j], (LPTSTR)ts, MAXSTRING);
			state->plist->ctl[j] = NULL;
			state->plist->cgpos[j] = 0xffff;
		}
	}
	if (*tbuf < _T(' ')) {
		if (ts && *ts >= _T(' ')) ;
		else if ((BYTE)*tbuf != 1 && (ts = GetString(IDDC_BASE + (state->dID%100)*100 + i%100)) && *ts) ;
		else if ((ts = GetString(IDDP_BASE + (state->dID%100)*100 + state->cnum-1)) && *ts) ;
		else if ((ts = GetString(i)) && *ts) ;
		if (ts && *ts) {
#ifdef UNICODE
			if (*ts == _T('\x200f'))
				SetWindowLongPtr(hwnd, GWL_EXSTYLE, GetWindowLongPtr(hwnd, GWL_EXSTYLE) | WS_EX_LAYOUTRTL);
#endif
			SetWindowText(hwnd, ts);
		}
	}
	return TRUE;
}

void LocalizeDialog(WORD dID, HWND dlg) {
	HWND pdlg = NULL;
	LPCTSTR ts = NULL;
	TCHAR tbuf[2];
	LDCState state = {0};
	state.dID = dID;
	state.parent = dlg;
#ifndef USE_RICH_EDIT
	if (dID == IDD_PROPPAGE_A1) dID = IDD_PROPPAGE_A1_LE;
#endif
	if (hinstLang && hinstLang != hinstThis && (pdlg = CreateDialog(hinstLang, MAKEINTRESOURCE(dID), dlg, NULL))) {
		state.plist = (LDCList*)kallocz(sizeof(LDCList));
		state.plist->parent = pdlg;
		EnumChildWindows(pdlg, LocalizeDialogGather, (LPARAM)state.plist);
		state.plist->gpos = 0;
	}
	GetWindowText(dlg, tbuf, 2);
	if (*tbuf < _T(' ')) {
		if (pdlg && GetWindowText(pdlg, state.plist->tbuf, MAXSTRING) && *state.plist->tbuf >= _T(' ')) ts = state.plist->tbuf;
		else if ((ts = GetString(dID)) && *ts) ;
		else ts = GetString(STR_METAPAD);
		if (ts) SetWindowText(dlg, ts);
	}
	EnumChildWindows(dlg, LocalizeDialogItems, (LPARAM)&state);
	EnumChildWindows(dlg, LDSetFont, (LPARAM)GetStockObject(DEFAULT_GUI_FONT));
	kfree(&state.plist);
	if (pdlg) DestroyWindow(pdlg);
}