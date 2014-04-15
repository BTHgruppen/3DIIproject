// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Filename: Win32.cpp																║
// ║																					║
// ║ Copyright: Jonas Axelsson															║
// ║ Created: 2013-02-07																║
// ║																					║
// ║ Desciription:																		║
// ║  Main window of the program, written in the Win32 API.								║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

#include "Win32.h"

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Constructor and Destructor.														║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
Win32::Win32(LPCSTR p_className, LPCSTR p_title, Window p_window, HINSTANCE p_instanceHandle, int p_show)
{
	// Initiates the window handler to zero.
	m_windowHandle = 0;

	// Describes and registers the window.
	RegisterWindow(p_className, p_instanceHandle);

	// Create and show the window.
	GenerateWindow(p_className, p_title, p_window, p_instanceHandle, p_show);
}

Win32::~Win32()
{

}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Window registration function.														║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Win32::RegisterWindow(LPCSTR p_className, HINSTANCE p_instanceHandle)
{
	// Describes the window, so that it can be registered.
	WNDCLASS l_windowDescription;

	l_windowDescription.style			= CS_HREDRAW | CS_VREDRAW;
	l_windowDescription.lpfnWndProc		= WndProc;
	l_windowDescription.cbClsExtra		= 0;
	l_windowDescription.cbWndExtra		= 0;
	l_windowDescription.hInstance		= p_instanceHandle;
	l_windowDescription.hIcon			= LoadIcon(0, IDI_APPLICATION);
	l_windowDescription.hCursor			= LoadCursor(0, IDC_ARROW);
	l_windowDescription.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	l_windowDescription.lpszMenuName	= 0;
	l_windowDescription.lpszClassName	= p_className;

	// Register window. If this fails, display an error message.
	if(!RegisterClass(&l_windowDescription))
	{
		MessageBox(NULL, "DESCRIPTION:\nRegistration of Win32 window failed.\n\nFILE:\nWin32\n\nFUNCTION:\nRegisterWindow", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Window creater function.															║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
void Win32::GenerateWindow(LPCSTR p_className, LPCSTR p_title, Window p_window, HINSTANCE p_instanceHandle, int p_show)
{
	// Create the window.
	m_windowHandle = CreateWindow
	(
		p_className,			// Registered WNDCLASS.
		p_title,				// Title to use.
		WS_OVERLAPPEDWINDOW,	// Style flags.
		p_window.x,				// X position.
		p_window.y,				// Y position.
		p_window.width,			// Window width.
		p_window.height,		// Window height.
		0,						// Parent window.
		0,						// Menu handle.
		p_instanceHandle,		// Instance handle.
		0						// Extra parameters.
	);

	// If creation failes, display an error message.
	if(m_windowHandle == 0)
	{
		MessageBox(NULL, "DESCRIPTION:\nCreation of Win32 window failed.\n\nFILE:\nWin32\n\nFUNCTION:\nGenerateWindow", "FATAL ERROR", MB_ICONSTOP);
		PostQuitMessage(0);
		return;
	}

	// Finally, show and update the newly created window.
	ShowWindow(m_windowHandle, p_show);
	UpdateWindow(m_windowHandle);
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Window processing function.														║
// ╚════════════════════════════════════════════════════════════════════════════════════╝
LRESULT CALLBACK Win32::WndProc(HWND p_windowHandle, UINT p_message, WPARAM p_wParam, LPARAM p_lParam)
{
	// Handle specific messages.
	switch(p_message)
	{
		// Quit message:
		case(WM_DESTROY):
		{
			// Post quit message.
			PostQuitMessage(0);

			return 0;
		}
	}

	// Default message procedure.
	return DefWindowProc(p_windowHandle, p_message, p_wParam, p_lParam);
}

// ╔════════════════════════════════════════════════════════════════════════════════════╗
// ║ Get functions.																		║
// ╚════════════════════════════════════════════════════════════════════════════════════╝

// Return main handle.
HWND Win32::GetWindowHandle()
{
	return m_windowHandle;
}