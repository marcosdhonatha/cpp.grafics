#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/grid.h>

const int MAX_ATTEMPTS = 5;

const int BUTTONS_PER_ROW = 10;
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

        // Create the text field for user input
        textField = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(400, 50));

        // Create the "Enviar" button
        wxButton* sendButton = new wxButton(panel, wxID_ANY, "Enviar");

        // Create the attempts left label
        attemptsLabel = new wxStaticText(panel, wxID_ANY, wxString::Format("Tentativas restantes: %d", attemptsLeft));

        // Set up the layout
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        sizer->AddSpacer(30);
        sizer->Add(textField, 0, wxALIGN_CENTER_HORIZONTAL);
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

        // Create Enter and Backspace buttons
        wxButton* enterButton = new wxButton(panel, wxID_ANY, "Enter", wxDefaultPosition, wxSize(BUTTON_SIZE, BUTTON_SIZE));
        enterButton->Bind(wxEVT_BUTTON, &MyFrame::OnEnterButtonClick, this);
        buttons.push_back(enterButton);
        gridSizer->Add(enterButton, 0, wxALIGN_CENTER);

        wxButton* backButton = new wxButton(panel, wxID_ANY, "Backspace", wxDefaultPosition, wxSize(BUTTON_SIZE, BUTTON_SIZE));
        backButton->Bind(wxEVT_BUTTON, &MyFrame::OnBackspaceButtonClick, this);
        buttons.push_back(backButton);
        gridSizer->Add(backButton, 0, wxALIGN_CENTER);

        gridSizer->AddGrowableCol(0); // Make the first column growable
        sizer->AddSpacer(30);
        sizer->Add(gridSizer, 0, wxALIGN_CENTER_HORIZONTAL);

        // Create the word grid
        wordGrid = new wxGrid(panel, wxID_ANY);
        wordGrid->CreateGrid(1, targetWord.length());
        wordGrid->DisableDragRowSize();
        wordGrid->DisableDragColSize();
        wordGrid->EnableGridLines();
        wordGrid->SetDefaultColSize(BUTTON_SIZE);
        wordGrid->SetDefaultRowSize(BUTTON_SIZE);
        wordGrid->SetCellBackgroundColour(0, 0, wxColour(255, 255, 255)); // Set background color of the first cell to white
        sizer->AddSpacer(30);
        sizer->Add(wordGrid, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

        // Set the panel as the main window's content
        SetSizeHints(wxDefaultSize, wxDefaultSize);
        Centre();
        Show();
    }

private:
    wxTextCtrl* textField;
    std::vector<wxButton*> buttons;
    std::vector<wxString> buttonLabels = {
        "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
        "A", "S", "D", "F", "G", "H", "J", "K", "L",
        "Z", "X", "C", "V", "B", "N", "M"};

    wxStaticText* attemptsLabel;
    int attemptsLeft;

    wxGrid* wordGrid;

    wxString targetWord = "BRASIL";

    void OnLetterButtonClick(wxCommandEvent& event)
    {
        wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
        if (button)
        {
            wxString letter = button->GetLabel();
            textField->SetValue(textField->GetValue() + letter);
        }
    }

    void OnEnterButtonClick(wxCommandEvent& event)
    {
        wxString userInput = textField->GetValue();
        CheckAnswer(userInput);
    }

    void OnBackspaceButtonClick(wxCommandEvent& event)
    {
        wxString currentText = textField->GetValue();
        if (!currentText.IsEmpty())
        {
            currentText.RemoveLast();
            textField->SetValue(currentText);
        }
    }

    void OnSendButtonClick(wxCommandEvent& event)
    {
        wxString userInput = textField->GetValue();
        CheckAnswer(userInput);
    }

    void CheckAnswer(const wxString& userInput)
    {
        if (userInput.Lower() == targetWord.Lower())
        {
            wxMessageBox("Parabens! Voce acertou!", "Resultado", wxOK | wxICON_INFORMATION, this);
        }
        else
        {
            attemptsLeft--;
            wxString message;
            if (attemptsLeft > 0)
            {
                message = wxString::Format("Tente novamente. Tentativas restantes: %d", attemptsLeft);
            }
            else
            {
                message = "Suas tentativas acabaram. A palavra era 'BRASIL'.";
            }
            wxMessageBox(message, "Resultado", wxOK | wxICON_INFORMATION, this);
            attemptsLabel->SetLabel(wxString::Format("Tentativas restantes: %d", attemptsLeft));
        }

        textField->SetValue(wxEmptyString);
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
