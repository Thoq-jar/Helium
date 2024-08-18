#ifndef PURROOSERFRAME_H
#define PURROOSERFRAME_H

enum class Theme {
  LIGHT,
  DARK
};

constexpr int WIDTH = 1600;
constexpr int HEIGHT = 900;

class PurrooserFrame final : public wxFrame {
public:
  explicit PurrooserFrame(const wxString &title);
  void OnToggleTheme(wxCommandEvent &event);
  wxChoice *m_searchEngineChoice;

private:
  wxWebView *CreateNewTab(const wxString &url);
  wxWebView *GetCurrentWebView() const;

  void OnQuit(wxCommandEvent &event);
  void OnSearchEngineChange(wxCommandEvent &event);
  void OnSearch(wxCommandEvent &event);
  void OnNewTab(wxCommandEvent &event);
  void OnCloseTab(wxCommandEvent &event);
  void ApplyTheme();

  wxButton *m_closeTabButton;
  Theme m_currentTheme;
  wxNotebook *m_notebook;
  wxSearchCtrl *m_searchCtrl;
  wxButton *m_newTabButton;
  wxMenuItem *m_toggleThemeItem;
};

#endif // PURROOSERFRAME_H
