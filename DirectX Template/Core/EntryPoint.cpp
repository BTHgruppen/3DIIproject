// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Filename: EntryPoint.cpp															║
// ║																					║
// ║ Copyright: Jonas Axelsson															║
// ║ Created: 2013-02-05																║
// ║																					║
// ║ Desciription:																		║
// ║  Main entry point for the program, used to initiate and run the project.			║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

#include "../Misc/Inclusions.h"

#include "Main\Main.h"

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ WinMain entry point.																║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
int WINAPI WinMain(HINSTANCE p_instanceHandle, HINSTANCE p_previousInstanceHandle, PSTR p_commandLine, int p_show)
{
	Main* l_main;

	// Create the main object.
	l_main = new Main(p_instanceHandle, p_show);
	if(!l_main)
	{
		MessageBox(NULL, "DESCRIPTION:\nCreation of main system object failed.\n\nFILE:\nEntryPoint\n\nFUNCTION:\nWinMain", "FATAL ERROR", MB_ICONSTOP);
		return 0;
	}
	
	// Runs the main object function.
	l_main -> Run(); 

	// Release and delete the main object once its done running, if it exists.
	if(l_main)
	{
		delete l_main;
		l_main = 0;
	}

	return 0;
}