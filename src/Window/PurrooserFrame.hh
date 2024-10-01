#ifndef PURROOSERFRAME_HH
#define PURROOSERFRAME_HH

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
  bool m_isLoading{};
  bool m_errorPageOpened{};

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

  void OnReload(wxCommandEvent &event);

  void OnStop(wxCommandEvent &event);

  void OnSiteLoading(wxWebViewEvent &event);

  void OnSiteLoaded(wxWebViewEvent &event);

  void OnSaveSearchEngine(wxCommandEvent &event);

  void OnSiteError(wxWebViewEvent &event);

  void LoadSearchEngine();

  void OnSiteNavigated(wxWebViewEvent &event);

  void FullScreenToggle(wxCommandEvent &event);

  void ToggleUIElements(bool show);

  void ApplyTheme();

  wxSearchCtrl *m_searchCtrl;
  wxButton *m_newTabButton;
  wxButton *m_closeTabButton;
  wxButton *m_backButton;
  wxButton *m_forwardButton;
  wxButton *m_homeButton;
  wxButton *m_searchButton;
  wxButton *m_reloadButton;
  wxNotebook *m_notebook;
  wxMenuItem *m_toggleThemeItem;
  Theme m_currentTheme;
};

#endif // PURROOSERFRAME_HH
