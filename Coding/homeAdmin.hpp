#ifndef HOMEADMIN_HPP
#define HOMEADMIN_HPP

#include <iostream>
#include <string>
#include "popup.hpp"
#include "error.hpp"
#include "listener.hpp"
#include "User.hpp"
#include "musician.hpp"
#include "tinyfiledialogs.h"

using namespace sf;
using namespace std;

int login();
int homeAdmin(string);
int loadUploadMusician(string);


Color primary(0x071952FF);
Color secondary(0xFD3A69FF);
Color tertiary(0x6F6F6FFF);



std::string openFileDialogAdmin()
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

std::string openFileDialogImageAdmin()
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


int homeAdmin(string username = "Musician")
{
    RenderWindow window(sf::VideoMode(700, 600), "Melody Tunes - Home - Admin");

    Texture background, homeButton, logoutButton, uploadButton;
    if (!background.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/homePage.png") ||
        !homeButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/home.png") ||
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
        return 1;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Sprite backgroundSprite(background);
    Sprite homeSprite(homeButton);
    Sprite logoutSprite(logoutButton);
    Sprite uploadSprite(uploadButton);

    string welcomeText = "Hey, " + username;

    Text homeText("Home", font, 25);
    homeText.setStyle(Text::Bold);
    homeText.setFillColor(primary);
    homeText.setPosition(150, 100);

    Text welcomeTextObj(welcomeText, font, 19);
    welcomeTextObj.setStyle(Text::Bold);
    welcomeTextObj.setFillColor(primary);
    welcomeTextObj.setPosition(90, 30);

    homeSprite.setPosition(10, 150);
    uploadSprite.setPosition(10, 200);
    logoutSprite.setPosition(10, 570);

    musician userMusician(username);
    userMusician.loadFromFile();
    vector<Song> songs = userMusician.getCollection();
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
                    return homeAdmin(username); 
                }
                if (uploadSprite.getGlobalBounds().contains(mouseCoords))
                {
                    window.close();
                    return loadUploadMusician(username); 
                }
                if (logoutSprite.getGlobalBounds().contains(mouseCoords))
                {
                    showPopup(window, "Logging Out...", Vector2f(400, 60), "Error");
                    window.close();
                    return login();
                }

                for (size_t i = 0; i < songSprites.size(); ++i) {
                    if (songSprites[i].getGlobalBounds().contains(mouseCoords)) {
                        // Add functionality for deleting the song
                            userMusician.deleteSong(songs[i].getSongName());
                            songs.erase(songs.begin() + i);
                            songSprites.erase(songSprites.begin() + i);
                            showPopup(window, "Song Deleted Successfully", Vector2f(400, 60), "Success");
                            break;
                    }
                }
            }
        }

        window.draw(backgroundSprite);
        window.draw(welcomeTextObj);
        window.draw(homeText);
        window.draw(homeSprite);
        window.draw(uploadSprite);
        window.draw(logoutSprite);

        if (songs.empty()) {
            Text emptyText("No music uploaded yet.", font, 20);
            emptyText.setFillColor(primary);
            emptyText.setPosition(250, 250);
            window.draw(emptyText);
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
            songNameText.setFillColor(primary);
            songNameText.setPosition(250, 170 + i * 100);

            Text musicianNameText("by " + songs[i].getMusicianName(), font, 12);
            musicianNameText.setFillColor(tertiary);
            musicianNameText.setPosition(250, 195 + i * 100);

            window.draw(songSprites[i]);
            window.draw(song2Sprite);
            window.draw(songNameText);
            window.draw(musicianNameText);

            // Draw delete button
            Text deleteText("Delete", font, 15);
            deleteText.setFillColor(Color::Red);
            deleteText.setPosition(500, 195 + i * 100);
            window.draw(deleteText);
        }

        window.display();
    }
    return 0;
}



int loadUploadMusician(string username = "Musician")
{
    RenderWindow window(sf::VideoMode(700, 600), "Melody Tunes - Musician");

    Texture background, homeButton, logoutButton, uploadButton, uploadMusic, uploadImage;
    if (!background.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/homePage.png") ||
        !homeButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/home.png") ||
        !logoutButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/logout.png") ||
        !uploadButton.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/upload.png") ||
        !uploadMusic.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/uploadMusic.png") ||
        !uploadImage.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/uploadImage.png"))
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
    Sprite logout(logoutButton);
    Sprite upload(uploadButton);
    Sprite uploadMusicSprite(uploadMusic);
    Sprite uploadImageSprite(uploadImage);

    musician musician(username);
    musician.loadFromFile();

    string welcomeText = "Hey, " + username + ": Musician";
    Text text(welcomeText, font, 19);
    text.setStyle(Text::Bold);
    text.setFillColor(primary);
    text.setPosition(90, 30);

    homeSprite.setPosition(10, 150);
    upload.setPosition(10, 200);
    logout.setPosition(10, 570);

    bool isHomePage = true;
    bool isFavourites = false;
    bool isUpload = false;

    Text text2("Upload Your Music", font, 25);
    text2.setStyle(Text::Bold);
    text2.setFillColor(primary);
    text2.setPosition(150, 100);

    Texture submitTexture;
    if (!submitTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/Submit.png")) {
        error("Error Loading Submit Button.");
        return 1;
    }

    Sprite submitButton(submitTexture);
    submitButton.setPosition(300, 450);

    Text songNameText("Song Name:", font, 20);
    songNameText.setPosition(175, 155);
    songNameText.setFillColor(primary);

    Text filePathText("File Path:", font, 20);
    filePathText.setPosition(175, 225);
    filePathText.setFillColor(primary);

    Text imagePathText("Image Path: ", font, 20);
    imagePathText.setPosition(175, 295);
    imagePathText.setFillColor(primary);

    RectangleShape inputBox1(Vector2f(250, 40));
    inputBox1.setPosition(340, 150);
    inputBox1.setOutlineThickness(2);
    inputBox1.setOutlineColor(primary);
    inputBox1.setFillColor(Color::White);

    uploadMusicSprite.setPosition(340, 220);

    uploadImageSprite.setPosition(340, 290);

    string songName = "";
    string filePath = "";
    string imagePath = "";

    bool inputActive[3] = {false};
    bool pushedInput = false;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                inputActive[0] = inputBox1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y);

                inputBox1.setOutlineColor(inputActive[0] ? secondary : primary);

                if (homeSprite.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {
                    window.close();
                    homeAdmin(username);
                    return 1;
                }
                if (upload.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {
                    window.close();
                    loadUploadMusician(username);
                    return 1;
                }
                if (uploadMusicSprite.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {

                    filePath = openFileDialogAdmin();
                    if (filePath.empty()) {
                        showPopup(window, "No valid file selected.", Vector2f(400, 60), "Error");
                        loadUploadMusician(username);
                    }
                }
                if (uploadImageSprite.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {

                    imagePath = openFileDialogImageAdmin();
                    if (imagePath.empty()) {
                        showPopup(window, "No valid file selected.", Vector2f(400, 60), "Error");
                        loadUploadMusician(username);
                    }
                }
                if (logout.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {
                    showPopup(window, "Logging Out...", Vector2f(400, 60), "Error");
                    window.close();
                    return login();
                }

                if (submitButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && !songName.empty() && !filePath.empty() && !imagePath.empty())
                {
                    musician.addSong(songName, username, filePath, imagePath);
                    showPopup(window, "Song Uploaded Successfully!", Vector2f(400, 60), "Success");
                    window.close();
                    homeAdmin(username);
                    return 1; 
                }
            }

            if (event.type == Event::TextEntered)
            {
                if (event.text.unicode == '\b')
                {
                    if (inputActive[0] && !songName.empty()) songName.pop_back();
                }
                else if (event.text.unicode < 128)
                {
                    if (inputActive[0]) songName += static_cast<char>(event.text.unicode);
                }
            }
        }

        Text songNameInput(songName, font, 20);
        songNameInput.setPosition(350, 155);
        songNameInput.setFillColor(primary);

        Text filePathInput(filePath, font, 10);
        filePathInput.setPosition(350, 235);
        filePathInput.setFillColor(primary);

        Text imagePathInput(imagePath, font, 10);
        imagePathInput.setPosition(350, 305);
        imagePathInput.setFillColor(primary);

        window.draw(s);
        window.draw(homeSprite);
        window.draw(upload);
        window.draw(logout);
        window.draw(text);

        window.draw(text2);
        window.draw(songNameText);
        window.draw(inputBox1);
        window.draw(uploadMusicSprite);
        window.draw(uploadImageSprite);
        window.draw(imagePathText);
        window.draw(filePathText);
        window.draw(songNameInput);
        window.draw(filePathInput);
        window.draw(imagePathInput);
        window.draw(submitButton);
        window.display();
    }
    return 0;
}
#endif