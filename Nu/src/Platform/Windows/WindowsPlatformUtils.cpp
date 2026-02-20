#include "nupch.h"
#include "Nu/Utils/PlatformUtils.h"

#include <sstream> // TODO: Maybe remove?
#include <commdlg.h> //win32 opendialog
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32 // Window handle that Windows uses, to use <GLFW/glfw3native.h>
#include <GLFW/glfw3native.h>

#include "Nu/Core/Application.h"

namespace Nu {

	std::optional<std::string> FileDialogs::OpenFile(const char* filter)
	{
		OPENFILENAMEA ofn; // Common dialog box structure ASCII version
		CHAR szFile[260] = { 0 }; // if using TCHAR macros
		//CHAR currentDir[256] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME)); // Initialize OPENFILENAME
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		//if (GetCurrentDirectoryA(256, currentDir))
			//ofn.lpstrInitialDir = currentDir;
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetOpenFileNameA(&ofn) == TRUE)
			return ofn.lpstrFile;
		return std::nullopt;
	}

	std::optional<std::string> FileDialogs::SaveFile(const char* filter)
	{
		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		//CHAR currentDir[256] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		//if (GetCurrentDirectoryA(256, currentDir))
			//ofn.lpstrInitialDir = currentDir;
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		// Sets the default extension by extracting it from the filter
		ofn.lpstrDefExt = strchr(filter, '\0') + 1;

		if (GetSaveFileNameA(&ofn) == TRUE)
			return ofn.lpstrFile;
		return std::nullopt;
	}

}
