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

///// Consts /////
#ifndef CONSTS_H
#define CONSTS_H

#ifdef USE_RICH_EDIT
#define VI_KIND		""
#else
#define VI_KIND		" LE"
#endif
#ifdef UNICODE
#define VI_BUILD	""
#else
#define VI_BUILD	"-ANSI"
#endif
#define VI_NAME		"metapad"
#define VI_FULLNAME	VI_NAME VI_KIND
#define VI_VER		"3.71" VI_BUILD
#define VI_VERSYNC	"3.7"
#define VI_VERVI	3,7,1,0
#define VI_COPY		"\xa9 2021-2024 SoBiT Corp\n\xa9 2013 Mario Rugiero\n\xa9 1999-2011 Alexander Davidson"
#define VI_BUILDER	"SoBiT Corp"



#define MAXFN 4096
#define MAXFONT 32
#define MAXARGS 4096
#define MAXQUOTE 1024
#define MAXFIND 32761	//more than this causes corruption in the windows control holding the find/replace/insert string
#define MAXSTRING 500
#define MAXACCELSTR 32
#define MAXACCELKEYS 0x30
//#define MAXFAVES 16
#define MAXMACRO 32761
#define MAXDATEFORMAT 255
#define LARGEFILESIZEWARN 0x1000000
#define LARGEPASTEWARN 0x400000
#define MAXGBUF MAX(MAX(MAXFN*2+MAXSTRING*2,MAXMACRO),MAXFIND)+7

#define NUMCUSTOMBITMAPS 6
#ifdef USE_RICH_EDIT
#define NUMBUTTONS 26
#else
#define NUMBUTTONS 25
#endif
#define NUMSTATPANES 6
#define THROTTLEMAX 768

#define CUSTOMBMPBASE 15
#define NUMFINDS 25
#define NUMINSERTS 25
#define EGGNUM 15
#define SBPANE_TYPE 0
#define SBPANE_INS 1
#define SBPANE_SIZE 2
#define SBPANE_LINE 3
#define SBPANE_COL 4
#define SBPANE_MESSAGE 5
#define STATUS_FONT_CONST 1.4
#define IDT_UPDATE 1

#define MPOS_FILE_READONLY 4
#define MPOS_FILE_FORMAT_STATIC 8
#define MPOS_FILE_FORMAT (options.bReadOnlyMenu ? 8 : 7)
#define MPOS_FILE_RECENT (options.bReadOnlyMenu ? 14 : 13)
#define MPOS_EDIT (options.bRecentOnOwn ? 2 : 1)
#define MPOS_FAVE (options.bRecentOnOwn ? 3 : 2)

#define ID_CLIENT 100
#define ID_STATUSBAR 101
#define ID_TOOLBAR 102

#define LWA_COLORKEY 0x00000001
#define LWA_ALPHA 0x00000002

#ifndef WS_EX_LAYERED
#define WS_EX_LAYERED 0x00080000
#endif

#endif

