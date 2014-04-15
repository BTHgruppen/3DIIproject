// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Filename: Win32.h																	║
// ║																					║
// ║ Copyright: Jonas Axelsson															║
// ║ Created: 2013-02-07																║
// ║																					║
// ║ Desciription:																		║
// ║  Main window of the program, written in the Win32 API.								║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

#pragma once
#include "../../Misc/Inclusions.h"

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Class definition.																	║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
class Win32
{
	public:
		// Functions:
		Win32(LPCSTR p_className, LPCSTR p_title, Window p_window, HINSTANCE p_instanceHandle, int p_show);
		~Win32();

		HWND GetWindowHandle();
	
	private:
		// Variables:
		HWND m_windowHandle;

		// Functions:
		void RegisterWindow(LPCSTR p_className, HINSTANCE p_instanceHandle);
		void GenerateWindow(LPCSTR p_className, LPCSTR p_title, Window p_window, HINSTANCE p_instanceHandle, int p_show);

		static LRESULT CALLBACK WndProc(HWND p_windowHandle, UINT p_message, WPARAM p_wParam, LPARAM p_lParam);
};