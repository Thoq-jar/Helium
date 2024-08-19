#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <fstream>
#include <wx/msgdlg.h>
#include <wx/notebook.h>
#include <wx/srchctrl.h>
#include <wx/webview.h>
#include <wx/wx.h>
#include <wx/choice.h>
#include <wx/filename.h>

#include "./Purrooser/Purrooser.hpp"
#include "./Utils/Utils.hpp"
#include "./Utils/Actions/Actions.hpp"
#include "./Window/PurrooserFrame.hpp"

constexpr int ID_SAVE_SEARCH_ENGINE = wxID_HIGHEST + 1;
constexpr size_t SEARCH_ENGINES_SIZE = 5;

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
  "https://www.ecosia.org",
  "https://www.startpage.com",
  "https://searx.work",
};

#endif //MAIN_HPP