#include <iostream>
#include <string>
#include "popup.hpp"
#include "error.hpp"

using namespace std;
using namespace sf;

int login();
void loadHomepage(RenderWindow &, string, Font &);
void loadFavorites(RenderWindow &, string, Font &);


Color color(0x071952FF);
Color color2(0xFD3A69FF);

int home(string username = "Listener")
{
    RenderWindow window(sf::VideoMode(700, 600), "Melody Tunes - Home");

    Texture background, homeButton, favouritesButton, logoutButton, uploadButton;
    if (!background.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/homePage.png") ||
        !homeButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/home.png") ||
        !favouritesButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/favourites.png") ||
        !logoutButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/logout.png") ||
        !uploadButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/upload.png"))
    {
        error("Error Loading Image File.");
        return 1;
    }

    Font font;
    if (!font.loadFromFile("Poppins-Medium.ttf"))
    {
        error("Error Loading Font File.");
        return 1;
    }


    Image icon;
    if (!icon.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/icon.png"))
    {
        error("Error Loading Icon File.");
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Sprite s(background);
    Sprite home(homeButton);
    Sprite favourites(favouritesButton);
    Sprite logout(logoutButton);
    Sprite upload(uploadButton);

    string welcomeText = "Hey, " + username;
    Text text(welcomeText, font, 19);
    text.setStyle(Text::Bold);
    text.setFillColor(color);
    text.setPosition(90, 30);

    home.setPosition(10, 150);
    favourites.setPosition(10, 200);
    upload.setPosition(10, 250);
    logout.setPosition(10, 570);

    bool isHomePage = true;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed && (event.mouseButton.button == Mouse::Left))
            {
                if (home.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {
                    isHomePage = true;
                }
                if (favourites.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {
                    isHomePage = false;
                }
                if (upload.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {
                    showPopup(window, "Upload Button Clicked");
                }
                if (logout.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {
                    showPopup(window, "Logging Out...", Vector2f(400, 60), "Error");
                    window.close();
                    return login();
                }
            }
        }

        window.clear(Color::White);

        window.draw(s);
        window.draw(home);
        window.draw(text);
        window.draw(favourites);
        window.draw(upload);
        window.draw(logout);

        if (isHomePage)
        {
            loadHomepage(window, username, font);
        }
        else
        {
            loadFavorites(window, username, font);
        }

        window.display();
    }
    return 0;
}

void loadHomepage(RenderWindow &window, string username, Font &font)
{
    Text text2("Home", font, 25);
    text2.setStyle(Text::Bold);
    text2.setFillColor(color);
    text2.setPosition(150, 100);

    window.draw(text2);
}

void loadFavorites(RenderWindow &window, string username, Font &font)
{
    Text text2("Favourites", font, 25);
    text2.setStyle(Text::Bold);
    text2.setFillColor(color);
    text2.setPosition(150, 100);

    window.draw(text2);
}
