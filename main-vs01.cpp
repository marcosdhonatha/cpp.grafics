#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

const int BUTTONS_PER_ROW = 8;
const float BUTTON_SIZE = 50.f;
const float BUTTON_SPACING = 10.f;
const float BUTTON_START_X = 50.f;
const float BUTTON_START_Y = 100.f;
const sf::Color BUTTON_IDLE_COLOR = sf::Color(200, 200, 200);
const sf::Color BUTTON_HOVER_COLOR = sf::Color(150, 150, 150);
const sf::Color BUTTON_ACTIVE_COLOR = sf::Color(100, 100, 100);
const float LETTER_BOX_SIZE = 20.f;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Keyboard Input");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Failed to load font!" << std::endl;
        return -1;
    }

    sf::RectangleShape textFieldBackground;
    textFieldBackground.setSize(sf::Vector2f(400.f, 50.f));
    textFieldBackground.setFillColor(sf::Color::White);
    textFieldBackground.setOutlineColor(sf::Color::Black);
    textFieldBackground.setOutlineThickness(1.f);
    textFieldBackground.setPosition(200.f, 300.f);

    sf::Text textField;
    textField.setFont(font);
    textField.setCharacterSize(24);
    textField.setFillColor(sf::Color::Black);
    textField.setPosition(220.f, 315.f);

    std::string userInput;
    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonTexts;
    std::vector<sf::RectangleShape> letterBoxes;
    std::vector<std::string> buttonLabels = {
        "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
        "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

    std::vector<bool> buttonPressed(buttonLabels.size(), false); // Variável para verificar se o botão foi pressionado

    for (size_t i = 0; i < buttonLabels.size(); i++)
    {
        sf::RectangleShape button(sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE));
        button.setPosition(BUTTON_START_X + (i % BUTTONS_PER_ROW) * (BUTTON_SIZE + BUTTON_SPACING),
                           BUTTON_START_Y + (i / BUTTONS_PER_ROW) * (BUTTON_SIZE + BUTTON_SPACING));
        button.setFillColor(BUTTON_IDLE_COLOR);

        sf::Text buttonText(buttonLabels[i], font, 24);
        buttonText.setFillColor(sf::Color::Black);
        buttonText.setPosition(button.getPosition().x + (BUTTON_SIZE - buttonText.getGlobalBounds().width) / 2.f,
                               button.getPosition().y + (BUTTON_SIZE - buttonText.getGlobalBounds().height) / 2.f);

        buttons.push_back(button);
        buttonTexts.push_back(buttonText);
    }

    sf::RectangleShape wordBox;
    wordBox.setFillColor(sf::Color::White);
    wordBox.setOutlineColor(sf::Color::Black);
    wordBox.setOutlineThickness(1.f);
    wordBox.setPosition(200.f, 400.f);

    std::cout << "Enter the maximum word length: ";
    int maxWordLength;
    std::cin >> maxWordLength;
    std::cin.ignore();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);

                for (size_t i = 0; i < buttons.size(); i++)
                {
                    if (buttons[i].getGlobalBounds().contains(mousePos))
                    {
                        if (!buttonPressed[i]) // Verifica se o botão já foi pressionado
                        {
                            buttonPressed[i] = true;
                            userInput += buttonLabels[i];

                            sf::RectangleShape letterBox(sf::Vector2f(LETTER_BOX_SIZE, LETTER_BOX_SIZE));
                            letterBox.setPosition(textFieldBackground.getPosition().x + textField.getGlobalBounds().width + 5.f,
                                                   textFieldBackground.getPosition().y + 10.f);
                            letterBox.setFillColor(sf::Color::White);
                            letterBox.setOutlineColor(sf::Color::Black);
                            letterBox.setOutlineThickness(1.f);
                            letterBoxes.push_back(letterBox);

                            textField.setString(userInput);
                            buttons[i].setFillColor(BUTTON_ACTIVE_COLOR);
                        }
                        break;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                for (size_t i = 0; i < buttonPressed.size(); i++)
                {
                    buttonPressed[i] = false; // Reinicia o estado do botão quando o botão do mouse é solto
                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                sf::Keyboard::Key keyPressed = event.key.code;

                if (keyPressed >= sf::Keyboard::A && keyPressed <= sf::Keyboard::Z)
                {
                    char letter = static_cast<char>(keyPressed + 65); // A = 65 in ASCII

                    if (userInput.size() < static_cast<size_t>(maxWordLength) && !buttonPressed[keyPressed - sf::Keyboard::A])
                    {
                        buttonPressed[keyPressed - sf::Keyboard::A] = true;
                        userInput += letter;

                        sf::RectangleShape letterBox(sf::Vector2f(LETTER_BOX_SIZE, LETTER_BOX_SIZE));
                        letterBox.setPosition(textFieldBackground.getPosition().x + textField.getGlobalBounds().width + 5.f,
                                               textFieldBackground.getPosition().y + 10.f);
                        letterBox.setFillColor(sf::Color::White);
                        letterBox.setOutlineColor(sf::Color::Black);
                        letterBox.setOutlineThickness(1.f);
                        letterBoxes.push_back(letterBox);

                        textField.setString(userInput);

                        size_t buttonIndex = static_cast<size_t>(keyPressed - sf::Keyboard::A);
                        buttons[buttonIndex].setFillColor(BUTTON_ACTIVE_COLOR);
                    }
                }
                else if (keyPressed == sf::Keyboard::Backspace && !userInput.empty())
                {
                    userInput.pop_back();

                    if (!letterBoxes.empty())
                    {
                        letterBoxes.pop_back();
                    }

                    textField.setString(userInput);
                }
                else if (keyPressed == sf::Keyboard::Enter) // Enviar a palavra digitada ao pressionar Enter
                {
                    std::cout << "User input: " << userInput << std::endl;
                    userInput.clear();
                    textField.setString(userInput);
                    letterBoxes.clear();
                }
            }

            if (event.type == sf::Event::KeyReleased)
            {
                sf::Keyboard::Key keyReleased = event.key.code;

                if (keyReleased >= sf::Keyboard::A && keyReleased <= sf::Keyboard::Z)
                {
                    buttonPressed[keyReleased - sf::Keyboard::A] = false; // Reinicia o estado do botão quando a tecla é solta

                    size_t buttonIndex = static_cast<size_t>(keyReleased - sf::Keyboard::A);
                    buttons[buttonIndex].setFillColor(BUTTON_IDLE_COLOR);
                }
            }
        }

        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

        for (size_t i = 0; i < buttons.size(); i++)
        {
            if (buttons[i].getGlobalBounds().contains(mousePos))
            {
                buttons[i].setFillColor(BUTTON_HOVER_COLOR);

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !buttonPressed[i])
                {
                    if (userInput.size() < static_cast<size_t>(maxWordLength))
                    {
                        buttonPressed[i] = true;
                        userInput += buttonLabels[i];

                        sf::RectangleShape letterBox(sf::Vector2f(LETTER_BOX_SIZE, LETTER_BOX_SIZE));
                        letterBox.setPosition(textFieldBackground.getPosition().x + textField.getGlobalBounds().width + 5.f,
                                               textFieldBackground.getPosition().y + 10.f);
                        letterBox.setFillColor(sf::Color::White);
                        letterBox.setOutlineColor(sf::Color::Black);
                        letterBox.setOutlineThickness(1.f);
                        letterBoxes.push_back(letterBox);

                        textField.setString(userInput);
                        buttons[i].setFillColor(BUTTON_ACTIVE_COLOR);
                    }
                }
            }
            else
            {
                buttons[i].setFillColor(BUTTON_IDLE_COLOR);
            }
        }

        window.clear(sf::Color::Cyan);

        for (const auto& button : buttons)
        {
            window.draw(button);
        }

        for (const auto& buttonText : buttonTexts)
        {
            window.draw(buttonText);
        }

        window.draw(textFieldBackground);
        window.draw(textField);

        for (const auto& letterBox : letterBoxes)
        {
            window.draw(letterBox);
        }

        window.display();
    }

    return 0;
}
