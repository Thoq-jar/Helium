#ifndef PURROOSERFRAME_H
#define PURROOSERFRAME_H

#include <wx/wx.h>
#include <wx/webview.h>
#include <wx/notebook.h>
#include <wx/srchctrl.h>

enum class Theme {
    LIGHT,
    DARK
};

constexpr int width = 1600;
constexpr int height = 900;

class PurrooserFrame final : public wxFrame {
public:
    explicit PurrooserFrame(const wxString& title);
    void OnToggleTheme(wxCommandEvent& event);

private:
    void OnQuit(wxCommandEvent& event);
    wxWebView* GetCurrentWebView() const;
    void OnSearch(wxCommandEvent& event);
    void OnNewTab(wxCommandEvent& event);
    void OnCloseTab(wxCommandEvent& event);
    wxWebView* CreateNewTab(const wxString& url);
    void ApplyTheme();

    wxButton* m_closeTabButton;
    Theme m_currentTheme;
    wxNotebook* m_notebook;
    wxSearchCtrl* m_searchCtrl;
    wxButton* m_newTabButton;
    wxMenuItem* m_toggleThemeItem;
};

#endif // PURROOSERFRAME_H