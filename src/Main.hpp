#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <wx/msgdlg.h>
#include <wx/notebook.h>
#include <wx/srchctrl.h>
#include <wx/webview.h>
#include <wx/wx.h>
#include <wx/choice.h>

#include "./Purrooser/Purrooser.hpp"
#include "./Utils/Utils.hpp"
#include "./Utils/Actions/Actions.hpp"
#include "./Window/PurrooserFrame.hpp"

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
  "https://www.ecosia.org",
  "https://www.qwant.com",
  "https://www.startpage.com",
  "https://searx.work",
};

#endif //MAIN_H
