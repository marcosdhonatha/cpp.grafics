/*


 POO??? Não sei oq é isso


Cores:
        verde: (58,163,148)
        amarelo: (211,172,105)
        preto: (49, 42, 44)
        cor de fundo: (110, 92, 98)
        cor dos botoes editaveis: (52, 44, 56)
        cor dos outros botoes: (100, 84, 92)
        cor dos botoes do teclado( 76,68,68)
*/
//#include "keyboard.h"
#include <wx/wx.h>
#include <map>
class EditableButton : public wxButton
{
public:
    EditableButton(wxWindow *parent, wxWindowID id, bool editable)
        : wxButton(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, editable ? 0 : wxTE_READONLY)
    {
        maxTextLength = 2;
        Bind(wxEVT_CHAR_HOOK, &EditableButton::OnChar, this);
        editable_ = editable;
    }

    void SetEditable(bool editable)
    {
        editable_ = editable;
        SetWindowStyleFlag(editable ? 0 : wxTE_READONLY);
    }

    void OnChar(wxKeyEvent &event)
    {
        if (!editable_)
        {
            event.Skip();
            return;
        }

        wxString character = event.GetUnicodeKey();

        SetValue(character);
    }

    void SetMaxTextLength(int length)
    {
        maxTextLength = length;
    }

    void SetValue(const wxString &value)
    {
        wxString truncatedValue = value;
        if (truncatedValue.length() > maxTextLength)
        {
            truncatedValue.Truncate(maxTextLength);
        }
        wxButton::SetLabel(truncatedValue);
        // wxMessageBox("A TECLA QUE DIGITOU FOI SETADA ");
    }

    bool editable_;
    int maxTextLength;
};

class EditableButtonFrame : public wxFrame 
{
public:
    EditableButtonFrame(const wxString &title)
        : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1200, 800)), linhaCont(0)
    {
        wxPanel *panel = new wxPanel(this, wxID_ANY);
        wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL); // Usamos um wxBoxSizer em vez de wxFlexGridSizer
        wxBoxSizer *centerSizer = new wxBoxSizer(wxHORIZONTAL);
        wxFlexGridSizer *buttonSizer = new wxFlexGridSizer(6, 5, 10, 10);
        SetBackgroundColour(wxColour(108, 92, 100)); // msm cor do  jogo original

        for (int i = 0; i < 30; i++)
        {
            int buttonId = i + 1;
            bool isEditable = i < 5;

            EditableButton *button = new EditableButton(panel, buttonId, isEditable);
            button->SetMaxTextLength(1);
            button->SetMinSize(wxSize(60, 60));
            buttonSizer->Add(button, 1, wxALL | wxEXPAND, 5);
            wxFont font(wxFontInfo(20).Family(wxFONTFAMILY_DEFAULT).FaceName("Arial"));
            button->SetFont(font);
            //////////////////
            button->SetWindowStyleFlag(GetWindowStyleFlag() | wxBORDER_SIMPLE);

            ///////////////////////////////////////
            if (isEditable)
            {
                button->SetBackgroundColour(wxColour(52, 44, 56));

                wxColour greenColor(108, 92, 100); // Cor verde

                firstRowButtons.push_back(button);
            }
            else
            {
                button->SetBackgroundColour(wxColour(100, 84, 92));
                wxColour redColor(0, 0, 0); // Cor preta

                firstRowButtons.push_back(button);
            }
            //////////////////////////////////////
        }
        centerSizer->AddSpacer(270);
        centerSizer->Add(buttonSizer, 0, wxALIGN_CENTER); // Adicione o buttonSizer ao centerSizer
                                                          // mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxTOP, 10);
        centerSizer->AddSpacer(100);                      // espaço entre a grade de botoes editaveis e o painel de informações
        mainSizer->AddSpacer(20);
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // isso é pra testes
        int variable = 0;
        wxBoxSizer *infoSizer = new wxBoxSizer(wxVERTICAL);

        wxStaticText *attemptsLabel = new wxStaticText(panel, wxID_ANY, "Tentativas restantes:");
        infoSizer->Add(attemptsLabel, 0, wxTOP | wxLEFT, 10);
        ////
        wxTextCtrl *tentativas = new wxTextCtrl(panel, wxID_ANY, wxString::Format(wxT("%d"), variable), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
        infoSizer->Add(tentativas, 0, wxTOP | wxLEFT, 10);
        ////////
        wxStaticText *helpsLabel = new wxStaticText(panel, wxID_ANY, "Ajudas restantes:");
        infoSizer->Add(helpsLabel, 0, wxTOP | wxLEFT, 10);
        //////
        wxTextCtrl *ajudas = new wxTextCtrl(panel, wxID_ANY, wxString::Format(wxT("%d"), variable), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
        infoSizer->Add(ajudas, 0, wxTOP | wxLEFT, 10);
        //////
        wxStaticText *skipsLabel = new wxStaticText(panel, wxID_ANY, "Pulamentos restantes:");
        infoSizer->Add(skipsLabel, 0, wxTOP | wxLEFT, 10);
        ////
        wxTextCtrl *pulos = new wxTextCtrl(panel, wxID_ANY, wxString::Format(wxT("%d"), variable), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
        infoSizer->Add(pulos, 0, wxTOP | wxLEFT, 10);
        //////

        wxStaticText *scoreLabel = new wxStaticText(panel, wxID_ANY, "Pontuacao atual:");
        infoSizer->Add(scoreLabel, 0, wxTOP | wxLEFT, 10);

        wxTextCtrl *variableTextBox = new wxTextCtrl(panel, wxID_ANY, wxString::Format(wxT("%d"), variable), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
        infoSizer->Add(variableTextBox, 0, wxTOP | wxLEFT, 10);

        centerSizer->Add(infoSizer, 0, wxALIGN_CENTER); // Adicione o infoSizer ao centerSizer

        // mainSizer->AddStretchSpacer(); // Adicione um espaçador expansível acima
        mainSizer->Add(centerSizer, 0, wxALIGN_CENTER); // Adicione o centerSizer ao mainSizer
                                                        // mainSizer->AddStretchSpacer(); // Adicione um espaçador expansível abaixo
        mainSizer->Add(0, 50);
        panel->SetSizer(mainSizer);
        ///////////////////////////////////////////////////////////////////////////////////////////////////
       
       //////////
        wxGridSizer *keyboardSizer = new wxGridSizer(4, 10, 10, 10); // Alterado para 4 linhas
//tira isso (acima)
        // Primeira linha - Teclas QWERTY
        std::vector<wxString> row1Labels = {"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P"};
        for (const wxString &label : row1Labels)
        {
            wxButton *button = new wxButton(panel, wxID_ANY, label, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
            button->SetMinSize(wxSize(30, 30)); // Tamanho ajustado para botões quadrados
            button->Bind(wxEVT_BUTTON, &EditableButtonFrame::OnLetterButtonClick, this);
            button->SetBackgroundColour(wxColour(76, 67, 71)); // cor padrao dos botoes
            buttons.push_back(button);
            keyboardSizer->Add(button, 0, wxALL | wxEXPAND, 5);
        }

        // Segunda linha - Teclas ASDFG
        std::vector<wxString> row2Labels = {"A", "S", "D", "F", "G", "H", "J", "K", "L"};
        // keyboardSizer->Add(0, 10); // Adiciona um espaço vertical de 10 pixels

        for (const wxString &label : row2Labels)
        {

            wxButton *button = new wxButton(panel, wxID_ANY, label, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
            button->SetMinSize(wxSize(30, 30));
            button->Bind(wxEVT_BUTTON, &EditableButtonFrame::OnLetterButtonClick, this);
            button->SetBackgroundColour(wxColour(76, 67, 71)); // cor padrao dos botoes
            buttons.push_back(button);
            keyboardSizer->Add(button, 0, wxALL | wxEXPAND, 5);
        }

        // Terceira linha - Teclas HJKL
        std::vector<wxString> row3Labels = {"Z", "X", "C", "V", "B", "N", "M"};
        for (const wxString &label : row3Labels)
        {
            wxButton *button = new wxButton(panel, wxID_ANY, label, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
            button->SetMinSize(wxSize(30, 30));
            button->Bind(wxEVT_BUTTON, &EditableButtonFrame::OnLetterButtonClick, this);
            button->SetBackgroundColour(wxColour(76, 67, 71)); // cor padrao dos botoes
            buttons.push_back(button);
            keyboardSizer->Add(button, 0, wxALL | wxEXPAND, 5);
        }

        // Quarta linha - Botões de apagar e enviar
        wxButton *backspaceButton = new wxButton(panel, wxID_ANY, "Backspace", wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
        backspaceButton->SetMinSize(wxSize(120, 60));
        backspaceButton->Bind(wxEVT_BUTTON, &EditableButtonFrame::OnBackspaceButtonClick, this);
        keyboardSizer->Add(backspaceButton, 0, wxALL | wxEXPAND, 5);

        wxButton *enterButton = new wxButton(panel, wxID_ANY, "Enter", wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
        enterButton->SetMinSize(wxSize(120, 60));
        enterButton->Bind(wxEVT_BUTTON, &EditableButtonFrame::OnEnterButtonClick, this);
        keyboardSizer->Add(enterButton, 0, wxALL | wxEXPAND, 5);

        // botao da ajuda:
        wxButton *ajuda = new wxButton(panel, wxID_ANY, "Ajuda", wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
        ajuda->SetMinSize(wxSize(120, 60));
        ajuda->Bind(wxEVT_BUTTON, &EditableButtonFrame::OnAjudaButtonClick, this);
        keyboardSizer->Add(ajuda, 0, wxALL | wxEXPAND, 5);

        // botao de pular desafio
        wxButton *pular = new wxButton(panel, wxID_ANY, "Pular", wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
        pular->SetMinSize(wxSize(120, 60));
        pular->Bind(wxEVT_BUTTON, &EditableButtonFrame::OnPularButtonClick, this);
        keyboardSizer->Add(pular, 0, wxALL | wxEXPAND, 5);
        // Adicionar mais linhas e botões conforme necessário para criar um layout completo do teclado

        mainSizer->Add(keyboardSizer, 0, wxALIGN_CENTER);

        // Bind do evento wxEVT_CHAR_HOOK para capturar o pressionamento de teclas
        Bind(wxEVT_CHAR_HOOK, &EditableButtonFrame::OnCharHook, this);

        ///////////////////////////////////////////////////////////////

        panel->SetSizer(mainSizer); // Usamos SetSizer em vez de SetSizerAndFit   antigo

        // Definimos um tamanho mínimo para a janela
        SetMinSize(wxSize(800, 600));

        // Centralizamos a janela na tela
        Centre();

        Show();
    }

    ///////////////////////////////////////////
    void ChangeButtonColor(wxButton *button, const wxColour &color)
    {
        button->SetBackgroundColour(color);
        button->Refresh();
    }

    // Se a palavra não exitir, isso  reseta a linha
    void cleanRow()
    {

        for (EditableButton *button : firstRowButtons)
        {
            if (button->GetId() <= (linhaCont + 1) * 5 && button->GetId() > linhaCont * 5)
            {
                button->SetValue("");
            }
        }
    }
    // Não ta pronto
    void OnPularButtonClick(wxCommandEvent &event)
    {

        wxMessageBox("IMPLEMENTE A FUNCAO DE PULAR");
    }
    void OnAjudaButtonClick(wxCommandEvent &event)
    {
        wxMessageBox("IMPLEMENTE A FUNCAO DE AJUDA");
    }
    void OnBackspaceButtonClick(wxCommandEvent &event)
    {

        wxMessageBox("IMPLEMENTE A FUNCAO DE APAGAR");
    }

    void OnEnterButtonClick(wxCommandEvent &event)
    {
        // SetRowEditable(2);
        if (IsAllButtonsFilledInFirstRow())
        {

            wxString word = GetFirstRowWord();

            if (Wordexists())
            {
                wxMessageBox("Palavra: " + word);

                linhaCont++;
                SetRowEditable(linhaCont, true);
                SetRowEditable(linhaCont - 1, false);
                std::map<wxString, bool> resultado;
                resultado = MapStringToBool(word);
                ChangeButtonColors(resultado);
            }
            else
            {
                wxMessageBox("Digite uma palavra que exista na lingua portuguesa!");
                cleanRow();
            }
        }

        else
        {
            wxMessageBox("Preencha todos os campos!");
        }
    }
    void ChangeButtonColors(std::map<wxString, bool> letterMap)
    {
        for (const auto &pair : letterMap)
        {
            wxString letter = pair.first;
            bool value = pair.second;

            // Encontrar o botão correspondente à letra
            wxButton *button = nullptr;
            for (wxButton *btn : buttons)
            {
                if (btn->GetLabel() == letter)
                {
                    button = btn;
                    break;
                }
            }

            // Verificar o valor booleano e trocar a cor do botão
            if (button)
            {
                if (value)
                {
                    button->SetBackgroundColour(wxColour(58, 163, 148)); // verde
                }
                else
                {
                    button->SetBackgroundColour(wxColour(255, 0, 0)); // Vermelho
                }

                button->Refresh();
            }
        }
    }

    // funçao que verifica as letras e retorna aquelas um valor booleano se ela estiver na palavra
    std::map<wxString, bool> MapStringToBool(const wxString &str)
    {
        std::map<wxString, bool> resultMap;

        for (size_t i = 0; i < str.length(); ++i)
        {
            wxString letter = str[i];
            resultMap[letter] = true;
        }

        return resultMap;
    }
    //////////////////////////////////////////
    EditableButton *GetEditableButton()
    {
        for (EditableButton *button : firstRowButtons)
        {
            if (button->editable_ && button->GetLabel().IsEmpty())
            {
                return button;
            }
        }
        return nullptr;
    }

private:
    wxFlexGridSizer *sizer;
    std::vector<EditableButton *> firstRowButtons;
    int linhaCont;

    std::vector<wxButton *> buttons; //retirar isso

    void OnLetterButtonClick(wxCommandEvent &event)
    {
        wxButton *button = dynamic_cast<wxButton *>(event.GetEventObject());

        if (button)
        {
            wxString letter = button->GetLabel();
            EditableButton *editableButton = GetEditableButton();

            editableButton->SetValue(letter);
        }
        else
        {
            wxMessageBox("Letra invalida.");
        }
    }
    ///////////////////////////////////////////////////////////1
    void OnCharHook(wxKeyEvent &event)
    {

        int keyCode = event.GetKeyCode();
        if (keyCode == WXK_RETURN || keyCode == WXK_NUMPAD_ENTER)
        {
            wxMessageBox("enter pressionado");
            wxWindow *focusWindow = wxWindow::FindFocus();
            if (focusWindow && focusWindow->IsKindOf(CLASSINFO(EditableButton)))
            {
                wxCommandEvent enterEvent(wxEVT_BUTTON, focusWindow->GetId());
                OnEnterButtonClick(enterEvent);
            }
        }
        else
        {
            // wxMessageBox("EVENTO IGNORADO");
            event.Skip();
        }
    }

    ////////////////////////////////////////////////////////////2

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    bool IsAllButtonsFilledInFirstRow() const
    {
        for (EditableButton *button : firstRowButtons)
        {
            if (button->GetLabel() == " " || button->GetLabel().IsEmpty() && button->GetId() < (linhaCont + 1) * 5)
            {
                return false;
            }
        }
        return true;
    }

    bool Wordexists()
    {
        // se a palavra existe ele retorna um true
        // caso contrario ele retorna um false e as letras sao apagadas.

        return true;
    }

    wxString GetFirstRowWord() const
    {
        wxString word;
        for (EditableButton *button : firstRowButtons)
        {
            if (button->GetId() <= (linhaCont + 1) * 5 && button->GetId() > linhaCont * 5)
            {
                word += button->GetLabel();
            }
        }
        return word;
    }

    void SetRowEditable(int row, bool editavel)
    {

        bool foundEditableButton = false;
        for (EditableButton *button : firstRowButtons)
        {
            int buttonId = button->GetId();
            if (buttonId >= (row * 5) && buttonId <= (row * 5) + 5)
            {
                if (editavel)
                {
                    button->SetBackgroundColour(wxColour(52, 44, 56));

                    button->SetEditable(editavel);
                    foundEditableButton = true;
                }
                else
                {

                    button->SetBackgroundColour(wxColour(70, 149, 138));

                    button->SetEditable(editavel);
                    foundEditableButton = true;
                }
            }
        }

        if (!foundEditableButton)
        {
            wxMessageBox("Nao ha botoes editaveis na linha especificada!");
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(EditableButtonFrame, wxFrame)
    wxEND_EVENT_TABLE()

        class EditableButtonApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        EditableButtonFrame *frame = new EditableButtonFrame("TERMO");
        frame->Show(true);

        return true;
    }
};

wxIMPLEMENT_APP(EditableButtonApp);
