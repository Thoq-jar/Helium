#ifndef MAIN_HH
#define MAIN_HH

#include <iostream>
#include <fstream>
#include <wx/msgdlg.h>
#include <wx/notebook.h>
#include <wx/srchctrl.h>
#include <wx/webview.h>
#include <wx/wx.h>
#include <wx/choice.h>
#include <wx/filename.h>

#include "./Purrooser/Purrooser.hh"
#include "./Utils/Utils.hh"
#include "./Utils/Actions/Actions.hh"
#include "./Window/PurrooserFrame.hh"

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

constexpr int ID_SAVE_SEARCH_ENGINE = wxID_HIGHEST + 1;
constexpr int ID_FULLSCREEN_TOGGLE = wxID_HIGHEST + 2;
constexpr int ID_THEME_TOGGLE = wxID_HIGHEST + 3;
constexpr size_t SEARCH_ENGINES_SIZE = 5;
constexpr int ID_BACK_BUTTON = wxID_HIGHEST + 6;
constexpr int ID_FORWARD_BUTTON = wxID_HIGHEST + 7;
constexpr int ID_HOME_BUTTON = wxID_HIGHEST + 8;
constexpr int ID_RELOAD_BUTTON = wxID_HIGHEST + 9;
constexpr int ID_SEARCH_BUTTON = wxID_HIGHEST + 10;
constexpr int ID_NEW_TAB_BUTTON = wxID_HIGHEST + 11;
constexpr int ID_CLOSE_TAB_BUTTON = wxID_HIGHEST + 12;

enum class SearchEngines {
  duckduckgo,
  ecosia,
  qwant,
  startpage,
  searx,
};

const std::string DEFAULT_SEARCH = "duckduckgo";
const std::string SEARCH_TLD = "com";
const std::string SEARCH_QUERY_TAG = "?q=";

const std::string SEARCH_ENGINES[] = {
  "https://www.duckduckgo.com",
  "https://www.qwant.com",
  "https://searx.work",
  "https://www.ecosia.org",
  "https://www.startpage.com",
};

#endif //MAIN_HH
