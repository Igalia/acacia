#include <iostream>
#include <ostream>
#include <string>

// We will need these for windows related things, see the formatter_win.cc in chromium
//#include <oleacc.h>
//#include <wrl/client.h>

// to do: we will probably need to get these from the IAccessible2 git repo, like in Chromium
//#include "third_party/iaccessible2/ia2_api_all.h"

// imports to try to get the hwnd
#include <windows.h>
#include <tlhelp32.h>
#include <vector>

#include "axaccess/ia2/win_utils.h"

void GetAllWindowsFromProcessID(DWORD dwProcessID, std::vector<HWND> &hwnds)
{
    HWND hCurWnd = nullptr;
    do
    {
        hCurWnd = FindWindowEx(nullptr, hCurWnd, nullptr, nullptr);
        DWORD checkProcessID = 0;
        GetWindowThreadProcessId(hCurWnd, &checkProcessID);
        if (checkProcessID == dwProcessID)
        {
            hwnds.push_back(hCurWnd);
            std::cout << "Found hWnd: " << hCurWnd  << "\n";
        }
    }
    while (hCurWnd != nullptr);
}

Ia2NodePtr find_root_accessible_from_pid(const int pid) {
    std::vector<HWND> hwnds;
    GetAllWindowsFromProcessID(pid, hwnds);
    return std::make_unique<Ia2Node>(Ia2Node());
}
