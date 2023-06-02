#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>

const int MAX_ATTEMPTS = 5;

const int BUTTONS_PER_ROW = 8;
const int BUTTON_SIZE = 50;
const int BUTTON_SPACING = 10;
const int BUTTON_START_X = 50;
const int BUTTON_START_Y = 100;
const wxString BUTTON_IDLE_COLOR = "#C8C8C8";
const wxString BUTTON_HOVER_COLOR = "#969696";
const wxString BUTTON_ACTIVE_COLOR = "#646464";

class MyFrame : public wxFrame
{
public:
    MyFrame() : wxFrame(NULL, wxID_ANY, "Keyboard Input", wxDefaultPosition, wxSize(800, 600)), attemptsLeft(MAX_ATTEMPTS)
    {
        // Create a panel to hold the controls
        wxPanel* panel = new wxPanel(this, wxID_ANY);

        // Create the "Enviar" button
        wxButton* sendButton = new wxButton(panel, wxID_ANY, "Enviar");

        // Create the attempts left label
        attemptsLabel = new wxStaticText(panel, wxID_ANY, wxString::Format("Tentativas restantes: %d", attemptsLeft));

        // Set up the layout
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        sizer->AddSpacer(30);
        sizer->Add(sendButton, 0, wxALIGN_CENTER_HORIZONTAL);
        sizer->AddSpacer(15);
        sizer->Add(attemptsLabel, 0, wxALIGN_CENTER_HORIZONTAL);
        panel->SetSizer(sizer);

        // Connect the event handler for the button click
        sendButton->Bind(wxEVT_BUTTON, &MyFrame::OnSendButtonClick, this);

        // Create the buttons for letter input
        wxFlexGridSizer* gridSizer = new wxFlexGridSizer(BUTTONS_PER_ROW, BUTTON_SPACING, BUTTON_SPACING);
        for (int i = 0; i < buttonLabels.size(); i++)
        {
            wxButton* button = new wxButton(panel, wxID_ANY, buttonLabels[i], wxDefaultPosition, wxSize(BUTTON_SIZE, BUTTON_SIZE));
            button->Bind(wxEVT_BUTTON, &MyFrame::OnLetterButtonClick, this);
            gridSizer->Add(button, 0, wxALIGN_CENTER);
            buttons.push_back(button);
        }
        gridSizer->AddGrowableCol(0); // Make the first column growable
        sizer->AddSpacer(30);
        sizer->Add(gridSizer, 0, wxALIGN_CENTER_HORIZONTAL);

        // Set the panel as the main window's content
        SetSizeHints(wxDefaultSize, wxDefaultSize);
        Centre();
        Show();
    }

private:
    std::vector<wxButton*> buttons;
    std::vector<wxString> buttonLabels = {
        "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
        "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

    wxStaticText* attemptsLabel;
    int attemptsLeft;

    void OnLetterButtonClick(wxCommandEvent& event)
    {
        wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
        if (button)
        {
            wxString letter = button->GetLabel();
            button->Disable();
            if (letter.IsEmpty())
                return;
            wxMessageBox("Letra: " + letter, "Letra clicada", wxOK | wxICON_INFORMATION, this);
            // Faça o que for necessário com a letra clicada
        }
    }

    void OnSendButtonClick(wxCommandEvent& event)
    {
        // Lógica para verificar a palavra digitada e as tentativas restantes
        wxMessageBox("Enviar clicado", "Botão Enviar", wxOK | wxICON_INFORMATION, this);
    }

    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
wxEND_EVENT_TABLE()

class MyApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        MyFrame* frame = new MyFrame();
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
