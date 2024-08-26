#include <iostream>
#include <string>
#include "popup.hpp"
#include "error.hpp"

using namespace std;
using namespace sf;

int login();

int home(string username = "Listener")
{
    RenderWindow window(sf::VideoMode(700, 600), "Melody Tunes - Home");

    Font font;
    if (!font.loadFromFile("Poppins-Medium.ttf"))
    {
        error("Error Loading Font File.");
        return 1;
    }
    Texture background;
    if (!background.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/homePage.png"))
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
    Color color2(0xFD3A69FF);

    string welcomeText = "Hey, " + username;

    Text text(welcomeText, font, 19);
    text.setStyle(Text::Bold);
    text.setFillColor(color);
    text.setPosition(90, 30);


    
    Text text4("Register", font, 20);
    text4.setStyle(Text::Bold);
    text4.setPosition(text.getPosition().x + 280, text.getPosition().y);
    text4.setFillColor(color2);

    Text usernameText("Username:", font, 20);
    usernameText.setPosition(175, 280);
    usernameText.setFillColor(color);

    Text passwordText("Password:", font, 20);
    passwordText.setPosition(175, 370);
    passwordText.setFillColor(color);

    RectangleShape inputBox1(Vector2f(250, 50));
    inputBox1.setPosition(300, 270);
    inputBox1.setOutlineThickness(2);
    inputBox1.setOutlineColor(color);
    inputBox1.setFillColor(Color::White);

    RectangleShape inputBox2(Vector2f(250, 50));
    inputBox2.setPosition(300, 358);
    inputBox2.setOutlineColor(color);
    inputBox2.setOutlineThickness(2);
    inputBox2.setFillColor(Color::White);

    Text usernameInput("", font, 20);
    usernameInput.setPosition(310, 280);
    usernameInput.setFillColor(color);

    Text passwordInput("", font, 20);
    passwordInput.setPosition(310, 373);
    passwordInput.setFillColor(color);

    Texture submitTexture;
    if (!submitTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/Submit.png"))
    {
        error("Error Loading Submit Button.");
        return 1;
    }

    Sprite submitButton(submitTexture);
    submitButton.setPosition(300, 450);
    string password = "";
    bool typingUsername = true;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::White);

        window.draw(s);
        window.draw(text);

        window.display();
    }
    return 0;
}