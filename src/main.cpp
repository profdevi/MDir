/*    
    MDir.exe : Converts text in Windows Clipboard to HTML text.
    Copyright (C) 2017  Comine.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

//v1.1 copyright Comine.com 20170330R0708
#include "MStdLib.h"
#include "MCommandArg.h"
#include "MDriveInfo.h"
#include "MDirOps.h"
#include "MLicenseGPL.h"

//******************************************************
//* Module Elements
//******************************************************
static const char *GApplicationName="MDir";	// Used in Help
static const char *GApplicationVersion="1.1";	// Used in Help

////////////////////////////////////////////////////
static void GDisplayHelp(void);

////////////////////////////////////////////////////
int main(int argn,const char *argv[])
	{
	MCommandArg args(argn,argv);
	if(args.CheckRemoveHelp()==true)
		{
		GDisplayHelp();
		return 0;
		}

	if(args.CheckRemoveArg("-gpl")==true)
		{
		MLicenseGPL license(true);
		license.Print();
		return 0;
		}

	MDriveInfo driveinfo(true);
	MDirOps dirops(true);
	for(int i=0;i<26;++i)
		{
		char driveletter='A'+i;
		if(driveinfo.IsDriveLetter(driveletter)==false)
			{  continue;  }

		// Get Drive Path
		MBuffer drivepath;
		if(dirops.GetCurrentDir(driveletter,drivepath)==false)
			{  continue; }

		MStdPrintf(" %-15s ",driveinfo.GetDriveTypeStr(driveletter) );
		MStdPrintf("%s\n",drivepath.GetBuffer() );
		}

	return 0;
	}


////////////////////////////////////////////////////
static void GDisplayHelp(void)
	{
	MStdPrintf(	"\n"
				"   usage:  %s [-?|-gpl]\n"
				"           v%s copyright Comine.com\n"
				"           use -gpl to display GPL copyright\n"
				"\n"
				"   Displays all active drive and working directories"
				"\n"
				,GApplicationName,GApplicationVersion);
	}


