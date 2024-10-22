#ifndef MAIN_H
#define MAIN_H

// ReSharper disable CppUnusedIncludeDirective
#include <iostream>
#include <wx/choice.h>
#include <wx/filename.h>
#include <wx/msgdlg.h>
#include <wx/notebook.h>
#include <wx/srchctrl.h>
#include <wx/webview.h>
#include <wx/wx.h>
#include <fstream>
#include <memory>

#include "Helium/Helium.h"
#include "Utils/Actions/Actions.h"
#include "Utils/Utils.h"
#include "Window/HeliumFrame.h"
// ReSharper restore CppUnusedIncludeDirective

#ifdef defined__WXGTK__
#define RELOAD_STOP_KEYBIND "Reload/Stop\tF5"
#define FULLSCREEN_KEYBIND "Fullscreen\tF11"
#define QUIT_KEYBIND "Quit\tAlt+F4"
#define RELOAD_ICON "R"
#define STOP_ICON "S"
#elif defined(__WXOSX__)
#define RELOAD_STOP_KEYBIND "Reload/Stop\tCtrl+R"
#define FULLSCREEN_KEYBIND "Fullscreen\tCtrl+F"
#define QUIT_KEYBIND "Quit\tCtrl+Q"
#define RELOAD_ICON "↻"
#define STOP_ICON "⏹"
#elif __WXMSW__
#define RELOAD_STOP_KEYBIND "Reload/Stop\tF5"
#define FULLSCREEN_KEYBIND "Fullscreen\tF11"
#define QUIT_KEYBIND "Quit\tAlt+F4"
#define RELOAD_ICON "R"
#define STOP_ICON "S"
#else
#define RELOAD_STOP_KEYBIND "Reload/Stop\tF5"
#define FULLSCREEN_KEYBIND "Fullscreen\tF11"
#define QUIT_KEYBIND "Quit\tAlt+F4"
#define RELOAD_ICON "R"
#define STOP_ICON "S"
#endif

const string name = "Helium";
constexpr float version = 2.2;
const string type = "Nightly";
const string space = " ";

constexpr int ID_FULLSCREEN_TOGGLE = wxID_HIGHEST + 2;
constexpr int ID_THEME_TOGGLE = wxID_HIGHEST + 3;
constexpr int ID_BACK_BUTTON = wxID_HIGHEST + 6;
constexpr int ID_FORWARD_BUTTON = wxID_HIGHEST + 7;
constexpr int ID_HOME_BUTTON = wxID_HIGHEST + 8;
constexpr int ID_RELOAD_BUTTON = wxID_HIGHEST + 9;
constexpr int ID_SEARCH_BUTTON = wxID_HIGHEST + 10;
constexpr int ID_NEW_TAB_BUTTON = wxID_HIGHEST + 11;
constexpr int ID_CLOSE_TAB_BUTTON = wxID_HIGHEST + 12;

#endif //MAIN_H
