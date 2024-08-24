#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include "popup.hpp"
#include "error.hpp"

using namespace std;
using namespace sf;


int player();

int login()
{
    RenderWindow window(sf::VideoMode(700, 500), "Login Form");

    Font font;
    if (!font.loadFromFile("Poppins-Medium.ttf"))
    {
        error("Error Loading Font File.");
        return 1;
    }
    Texture background;
    if (!background.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/Melody.png"))
    {
        error("Error Loading Image File.");
        return 1;
    }

    Sprite s(background);

    Image icon;
    if (!icon.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/icon.png"))
    {
        error("Error Loading Icon File.");
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Color color(0x071952FF);

    Text text("Login", font, 30);
    text.setPosition(310, 140);
    text.setFillColor(color);

    Text usernameText("Username:", font, 20);
    usernameText.setPosition(175, 220);
    usernameText.setFillColor(color);

    Text passwordText("Password:", font, 20);
    passwordText.setPosition(175, 290);
    passwordText.setFillColor(color);

    RectangleShape inputBox1(Vector2f(250, 50));
    inputBox1.setPosition(300, 210);
    inputBox1.setOutlineThickness(2);
    inputBox1.setOutlineColor(color);
    inputBox1.setFillColor(Color::White);

    RectangleShape inputBox2(Vector2f(250, 50));
    inputBox2.setPosition(300, 280);
    inputBox2.setOutlineColor(color);
    inputBox2.setOutlineThickness(2);
    inputBox2.setFillColor(Color::White);

    Text usernameInput("", font, 20);
    usernameInput.setPosition(310, 220);
    usernameInput.setFillColor(color);

    Text passwordInput("", font, 20);
    passwordInput.setPosition(310, 295);
    passwordInput.setFillColor(color);

    Texture submitTexture;
    if (!submitTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/Submit.png"))
    {
        error("Error Loading Submit Button.");
        return 1;
    }

    Sprite submitButton(submitTexture);
    submitButton.setPosition(300, 360);
    string username = "";
    string password = "";
    bool typingUsername = true;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::TextEntered)
            {
                if (event.text.unicode == '\b')
                {
                    if (typingUsername)
                    {
                        if (!username.empty())
                            username.pop_back();
                    }
                    else
                    {
                        if (!password.empty())
                            password.pop_back();
                    }
                }
                else if (event.text.unicode == '\r')
                {
                    typingUsername = !typingUsername;
                }
                else if (event.text.unicode < 128)
                {
                    if (typingUsername)
                    {
                        inputBox1.setOutlineThickness(5);
                        inputBox2.setOutlineThickness(2);
                        username += static_cast<char>(event.text.unicode);
                    }
                    else
                    {
                        inputBox2.setOutlineThickness(5);
                        inputBox1.setOutlineThickness(2);
                        password += static_cast<char>(event.text.unicode);                       
                    }
                }
                else if (event.text.unicode >= 128)
                {
                    showPopup(window, "Invalid character input.");
                    return 1;
                }
                
            }


            if (event.type == Event::MouseButtonPressed && password != "" && username != "")
            {
                if (submitButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    cout << "Username: " << username << endl;
                    cout << "Password: " << password << endl;
                    cout << "Logged in." << endl;                  
                    string message = "Welcome Back, " + username;
                    showPopup(window, message);
                    player();
                    window.close();
                }
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter && password != "" && username != "")
            {
                cout << "Username: " << username << endl;
                cout << "Password: " << password << endl;
                cout << "Logged in." << endl;
                string message = "Welcome Back, " + username;
                window.close();
                showPopup(window, message, Vector2f(400, 60), "Success");
                player();
            }
        }



        usernameInput.setString(username);
        passwordInput.setString(string(password.length(), '*'));

        window.clear(Color::White);

        window.draw(s);
        window.draw(text);
        window.draw(inputBox1);
        window.draw(inputBox2);
        window.draw(usernameText);
        window.draw(passwordText);
        window.draw(usernameInput);
        window.draw(passwordInput);
        window.draw(submitButton);

        window.display();
    }
    return 0;
}
