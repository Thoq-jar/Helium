#ifndef PURROOSERFRAME_HPP
#define PURROOSERFRAME_HPP

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

  void OnBack(wxCommandEvent &event);

  void OnHome(wxCommandEvent &event);

  void OnForward(wxCommandEvent &event);

  void OnSaveSearchEngine(wxCommandEvent &event);

  void LoadSearchEngine();

  void ApplyTheme();

  wxSearchCtrl *m_searchCtrl;
  wxButton *m_newTabButton;
  wxButton *m_closeTabButton;
  wxButton *m_backButton;
  wxButton *m_forwardButton;
  wxButton *m_homeButton;
  wxNotebook *m_notebook;
  wxMenuItem *m_toggleThemeItem;
  Theme m_currentTheme;
};

#endif // PURROOSERFRAME_HPP