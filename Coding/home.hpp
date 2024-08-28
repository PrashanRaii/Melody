#ifndef HOME_HPP
#define HOME_HPP

#include <iostream>
#include <string>
#include "popup.hpp"
#include "error.hpp"
#include "musician.hpp"
#include "User.hpp"
#include "tinyfiledialogs.h"
#include "player.hpp"

using namespace sf;
using namespace std;

int login();
int loadFavorites(string);
int loadUpload(string);

int player(string username, const string& songFilePath, const string& songImagePath, const string& songName, const string& musicianName);


Color color(0x071952FF);
Color color2(0xFD3A69FF);
Color color3(0x6F6F6FFF);

std::string openFileDialog()
{
    const char *filterPatterns[] = {"*.wav", "*.ogg"};
    const char *filePath = tinyfd_openFileDialog(
        "Select an Music File",
        "",
        4,
        filterPatterns,
        NULL,
        0);

    if (filePath)
    {
        return std::string(filePath);
    }
    else
    {
        return "";
    }
}

std::string openFileDialogImage()
{
    const char *filterPatterns[] = {"*.png", "*.jpg", "*.jpeg", "*.bmp"};
    const char *imagePath = tinyfd_openFileDialog(
        "Select an Image File",
        "",
        4,
        filterPatterns,
        NULL,
        0);

    if (imagePath)
    {
        return std::string(imagePath);
    }
    else
    {
        return "";
    }
}



int home(string username = "Listener")
{
    RenderWindow window(sf::VideoMode(700, 600), "Melody Tunes - Home");

    Texture background, homeButton, favouritesButton, logoutButton, uploadButton;
    if (!background.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/homePage.png") ||
        !homeButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/home.png") ||
        !favouritesButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/favourites.png") ||
        !logoutButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/logout.png"))
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
        return 1;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Sprite backgroundSprite(background);
    Sprite homeSprite(homeButton);
    Sprite favouritesSprite(favouritesButton);
    Sprite logoutSprite(logoutButton);

    string welcomeText = "Hey, " + username;

    Text homeText("Home", font, 25);
    homeText.setStyle(Text::Bold);
    homeText.setFillColor(color);
    homeText.setPosition(150, 100);

    Text welcomeTextObj(welcomeText, font, 19);
    welcomeTextObj.setStyle(Text::Bold);
    welcomeTextObj.setFillColor(color);
    welcomeTextObj.setPosition(90, 30);

    homeSprite.setPosition(10, 150);
    favouritesSprite.setPosition(10, 200);
    logoutSprite.setPosition(10, 570);

    listener userListener(username);
    userListener.loadFromFile();
    vector<Song> songs = userListener.getCollection();
    vector<Sprite> songSprites;

    for (const auto& song : songs) {
        Texture songTexture;
        if (!songTexture.loadFromFile(song.getImagePath())) {
            showPopup(window, "Failed to load image: " + song.getImagePath(), Vector2f(400, 60), "Error");
            continue;
        }
        Sprite songSprite(songTexture);
        songSprites.push_back(songSprite);
    }

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2f mouseCoords = window.mapPixelToCoords(Mouse::getPosition(window));

                if (homeSprite.getGlobalBounds().contains(mouseCoords))
                {
                    window.close();
                    return home(username); 
                }
                if (favouritesSprite.getGlobalBounds().contains(mouseCoords))
                {
                    window.close();
                    return loadFavorites(username); 
                }
                if (logoutSprite.getGlobalBounds().contains(mouseCoords))
                {
                    showPopup(window, "Logging Out...", Vector2f(400, 60), "Error");
                    window.close();
                    return login();
                }

                for (size_t i = 0; i < songSprites.size(); ++i) {
                    if (songSprites[i].getGlobalBounds().contains(mouseCoords)) {
                        window.close();
                        return player(username, songs[i].getFilePath(), songs[i].getImagePath(), songs[i].getSongName(), songs[i].getMusicianName());
                    }
                }
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        window.draw(welcomeTextObj);
        window.draw(homeText);
        window.draw(homeSprite);
        window.draw(favouritesSprite);
        window.draw(logoutSprite);

        if (songs.empty()) {
            Texture emptyTexture;
            if (!emptyTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/empty.png")) {
                error("Error Loading Image File.");
                return 1;
            }
            emptyTexture.setSmooth(true);
            Sprite emptySprite(emptyTexture);
            emptySprite.setPosition(280, 230);
            emptySprite.setScale(0.5, 0.5);
            window.draw(emptySprite);
        }

        // Draw the songs
        for (size_t i = 0; i < songSprites.size(); ++i) {
            float scaleX = 80.0f / songSprites[i].getLocalBounds().width;
            float scaleY = 80.0f / songSprites[i].getLocalBounds().height;
            songSprites[i].setScale(scaleX, scaleY);
            songSprites[i].setPosition(150, 150 + i * 200);

            Texture song2Texture;
            if (!song2Texture.loadFromFile(songs[i].getImagePath()))
            {
                cout << "Failed to load image: "  << songs[i].getImagePath() << endl;
            }
            song2Texture.setSmooth(true);
            Sprite song2Sprite(song2Texture);
            float scaleX2 = 80.0f / song2Sprite.getLocalBounds().width;
            float scaleY2 = 80.0f / song2Sprite.getLocalBounds().height;
            song2Sprite.setScale(scaleX2, scaleY2);
            song2Sprite.setPosition(150, 150 + i * 100);

            Text songNameText(songs[i].getSongName(), font, 20);
            songNameText.setFillColor(color);
            songNameText.setPosition(250, 170 + i * 100);

            Text musicianNameText("by " + songs[i].getMusicianName(), font, 12);
            musicianNameText.setFillColor(color3);
            musicianNameText.setPosition(250, 195 + i * 100);

            window.draw(songSprites[i]);
            window.draw(song2Sprite);
            window.draw(songNameText);
            window.draw(musicianNameText);
        }

        window.display();
    }
    return 0;
}


int loadFavorites(string username = "Listener")
{
    RenderWindow window(sf::VideoMode(700, 600), "Melody Tunes - Home");

    Texture background, homeButton, favouritesButton, logoutButton, uploadButton;
    if (!background.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/homePage.png") ||
        !homeButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/home.png") ||
        !favouritesButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/favourites.png") ||
        !logoutButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/logout.png"))
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
        return 1;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Sprite s(background);
    Sprite homeSprite(homeButton);
    Sprite favourites(favouritesButton);
    Sprite logout(logoutButton);

    Text text2("Favourites", font, 25);
    text2.setStyle(Text::Bold);
    text2.setFillColor(color);
    text2.setPosition(150, 100);

    string welcomeText = "Hey, " + username;
    Text text(welcomeText, font, 19);
    text.setStyle(Text::Bold);
    text.setFillColor(color);
    text.setPosition(90, 30);

    homeSprite.setPosition(10, 150);
    favourites.setPosition(10, 200);
    logout.setPosition(10, 570);

    
    listener userListener(username);
    userListener.loadFromFile();
    vector<Song> favouriteSongs = userListener.getFavorites();
    vector<Sprite> songSprites;

    for (const auto& song : favouriteSongs) {
        Texture songTexture;
        if (!songTexture.loadFromFile(song.getImagePath())) {
            showPopup(window, "Failed to load image: " + song.getImagePath(), Vector2f(400, 60), "Error");
            continue;
        }
        Sprite songSprite(songTexture);
        songSprites.push_back(songSprite);
    }

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2f mouseCoords = window.mapPixelToCoords(Mouse::getPosition(window));

                if (homeSprite.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {
                    window.close();
                    home(username);
                    return 1;
                }
                if (favourites.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {
                    window.close();
                    loadFavorites(username);
                    return 1;
                }
                if (logout.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {
                    showPopup(window, "Logging Out...", Vector2f(400, 60), "Error");
                    window.close();
                    return login();
                }

                for (size_t i = 0; i < songSprites.size(); ++i) {
                    if (songSprites[i].getGlobalBounds().contains(mouseCoords)) {
                        window.close();
                        return player(username, favouriteSongs[i].getFilePath(), favouriteSongs[i].getImagePath(), favouriteSongs[i].getSongName(), favouriteSongs[i].getMusicianName());
                    }
                }
            }
        }
        window.draw(s);
        window.draw(homeSprite);
        window.draw(favourites);
        window.draw(logout);
        window.draw(text);
        window.draw(text2);
        
        if (favouriteSongs.empty()) {
            Texture emptyTexture;
            if (!emptyTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/empty.png")) {
                error("Error Loading Image File.");
                return 1;
            }
            emptyTexture.setSmooth(true);
            Sprite emptySprite(emptyTexture);
            emptySprite.setPosition(280, 230);
            emptySprite.setScale(0.5, 0.5);
            window.draw(emptySprite);
        }

        for (size_t i = 0; i < songSprites.size(); ++i) {
            float scaleX = 80.0f / songSprites[i].getLocalBounds().width;
            float scaleY = 80.0f / songSprites[i].getLocalBounds().height;
            songSprites[i].setScale(scaleX, scaleY);
            songSprites[i].setPosition(150, 150 + i * 200);

            Texture song2Texture;
            if (!song2Texture.loadFromFile(favouriteSongs[i].getImagePath()))
            {
                cout << "Failed to load image: "  << favouriteSongs[i].getImagePath() << endl;
            }
            song2Texture.setSmooth(true);
            Sprite song2Sprite(song2Texture);
            float scaleX2 = 80.0f / song2Sprite.getLocalBounds().width;
            float scaleY2 = 80.0f / song2Sprite.getLocalBounds().height;
            song2Sprite.setScale(scaleX2, scaleY2);
            song2Sprite.setPosition(150, 150 + i * 200);

            Text songNameText(favouriteSongs[i].getSongName(), font, 20);
            songNameText.setFillColor(color);
            songNameText.setPosition(250, 170 + i * 100);

            Text musicianNameText("by " + favouriteSongs[i].getMusicianName(), font, 12);
            musicianNameText.setFillColor(color3);
            musicianNameText.setPosition(250, 195 + i * 100);

            window.draw(songSprites[i]);
            window.draw(song2Sprite);
            window.draw(songNameText);
            window.draw(musicianNameText);
        }
        window.display();
    }
    return 0;
}

#endif