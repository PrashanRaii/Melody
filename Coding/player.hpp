#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include "error.hpp"
#include "popup.hpp"
#include "slider.hpp"

using namespace std;
using namespace sf;

int player()
{

    Color color(0x071952FF);
    Color color2(0xFD3A69FF);

    Music music;
    if (!music.openFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/Bulleya.wav"))
    {
        error("Error Loading Music File.");
        return 1;
    }
    Image icon;
    if (!icon.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/icon.png"))
    {
        error("Error Loading Icon File.");
        return 1;
    }

    Texture background, musicSprite;
    if (!background.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/Melody.png") || !musicSprite.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/player.jpg"))
    {
        error("Error Loading Background File.");
        return 1;
    }
    musicSprite.setSmooth(true);
    Texture playTexture, pauseTexture, playBackTexture, playForwardTexture, playNextTexture, playPrevTexture, repeatTexture, nonRepeatTexture;
    if (!playTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/play.png") || !pauseTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/pause.png") || !playBackTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/arrow-left.png") || !playForwardTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/arrow-right.png") || !playPrevTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/previous.png") || !playNextTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/next.png") || !repeatTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/Repeat.png") || !nonRepeatTexture.loadFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/Non-Repeat.png"))
    {
        error("Error loading Icons");
        return 1;
    }
    RenderWindow window(VideoMode(700, 500), "Melody Tunes");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Sprite backgroundSprite(background);
    Vector2u textureSize = background.getSize();
    Vector2u windowSize = window.getSize();
    backgroundSprite.setScale(float(windowSize.x) / textureSize.x, float(windowSize.y) / textureSize.y);

    music.pause();

    Font font;
    if (!font.loadFromFile("Poppins-Medium.ttf"))
    {
        error("Error Loading Font File.");
        return 1;
    }
    const int numBars = 5;
    RectangleShape bars[numBars];

    float barWidth = 7.0f;
    float spacing = 5.0f;
    for (int i = 0; i < numBars; ++i)
    {
        bars[i].setSize(Vector2f(barWidth, 50));
        bars[i].setPosition(i * (barWidth + spacing) + 318, window.getSize().y / 2 - 25);
        bars[i].setFillColor(color2);
    }
    Clock clock;

    Sprite playSprite(playTexture);
    Sprite pauseSprite(pauseTexture);
    Sprite repeatSprite(repeatTexture);
    Sprite nonRepeatSprite(nonRepeatTexture);

    
    CircleShape musicImage(50);
    musicImage.setTexture(&musicSprite);
    musicImage.setTextureRect(sf::IntRect(0, 0, musicSprite.getSize().x, musicSprite.getSize().y));
    musicImage.setPosition(window.getSize().x / 2 - musicImage.getRadius(), 20);

    musicImage.setOutlineColor(color2);
    musicImage.setOutlineThickness(3);


    Vector2f iconSize(70.f, 70.f);
    playSprite.setScale(iconSize.x / playTexture.getSize().x, iconSize.y / playTexture.getSize().y);
    pauseSprite.setScale(iconSize.x / pauseTexture.getSize().x, iconSize.y / pauseTexture.getSize().y);

    playSprite.setPosition(windowSize.x / 2 - iconSize.x / 2, windowSize.y / 2 - iconSize.y / 2 + 190);
    pauseSprite.setPosition(windowSize.x / 2 - iconSize.x / 2, windowSize.y / 2 - iconSize.y / 2 + 190);

    Sprite playBack(playBackTexture);
    Sprite playForward(playForwardTexture);
    Vector2f iconSize2(40.f, 40.f);
    Vector2f iconSize3(30.f, 30.f);
    playBack.setPosition((windowSize.x / 2 - iconSize2.x / 2) - 70, windowSize.y/2 - iconSize2.y / 2 + 190);
    playForward.setPosition((windowSize.x / 2 - iconSize2.x / 2) + 70, windowSize.y/2 - iconSize2.y / 2 + 190);


    repeatSprite.setPosition((windowSize.x / 2 - iconSize2.x / 2) + 200, windowSize.y/2 - iconSize2.y / 2 + 194);
    nonRepeatSprite.setPosition((windowSize.x / 2 - iconSize2.x / 2) + 200, windowSize.y/2 - iconSize2.y / 2 + 194);

    Sprite playNext(playNextTexture);
    Sprite playPrev(playPrevTexture);


    playNext.setPosition((windowSize.x / 2 - iconSize3.x / 2) + 130, (windowSize.y/2 - iconSize3.y / 2) + 190);
    playPrev.setPosition((windowSize.x / 2 - iconSize3.x / 2) - 130, (windowSize.y/2 - iconSize3.y / 2) + 190);

    Slider playerSlider(Vector2f(100, 388), Vector2f(500, 10));
    playerSlider.setTotalDuration(music.getDuration().asSeconds());
    playerSlider.setThumbPosition(0);


    bool isPlaying = false;

    while (window.isOpen())
    {
        
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
            {
                if (music.getStatus() == Music::Playing)
                {
                    music.pause();
                    isPlaying = false;
                }
                else
                {
                    music.play();
                    isPlaying = true;
                }
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Right)
            {
                Time currentTime = music.getPlayingOffset();
                    Time newTime = currentTime + seconds(5);
                    if (newTime < music.getDuration())
                        music.setPlayingOffset(newTime);
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Left)
            {
                Time currentTime = music.getPlayingOffset();
                    Time newTime = currentTime - seconds(5);
                    if (newTime < music.getDuration())
                        music.setPlayingOffset(newTime);
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::R)
            {
                music.setLoop(true);
            }
            if (event.type == Event::MouseButtonPressed)
            {
                if (playSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) ||
                    pauseSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    if (music.getStatus() == Music::Playing)
                    {
                        music.pause();
                        isPlaying = false;
                    }
                    else
                    {
                        music.play();
                        isPlaying = true;
                    }
                }
                if (playForward.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    Time currentTime = music.getPlayingOffset();
                    Time newTime = currentTime + seconds(5);
                    if (newTime < music.getDuration())
                        music.setPlayingOffset(newTime);
                }
                if (playBack.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    Time currentTime = music.getPlayingOffset();
                    Time newTime = currentTime - seconds(5);
                    if (newTime < music.getDuration())
                        music.setPlayingOffset(newTime);
                }
                if (playerSlider.onTrackClick(Vector2f(event.mouseButton.x, event.mouseButton.y)) == 2)
                {
                    float ratio = (event.mouseButton.x - playerSlider.getTrackPosition()) / playerSlider.getTrackWidth();
                    float newTime = ratio * 100;
                    playerSlider.setThumbPosition(newTime);
                    music.setPlayingOffset(seconds(newTime * music.getDuration().asSeconds() / 100));
                }
                if (playNext.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    music.openFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/Bulleya.wav");
                    music.play();
                    isPlaying = true;
                }
                if (playPrev.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    music.openFromFile("C:/Users/Dell/Desktop/Learning/C++ Project/Coding/static/Bulleya.wav");
                    music.play();
                    isPlaying = true;
                }
                if (repeatSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    if (music.getLoop())
                    {
                        music.setLoop(false);
                        showPopup(window,"Repeat Off", Vector2f(400, 60), "Success");
                    }
                    else
                    {
                        music.setLoop(true);
                        showPopup(window, "Repeat On", Vector2f(400, 60), "Success");
                    }
                }
            }
        }


        float currentValue = playerSlider.getThumbPosition();
        Time currentTime = music.getPlayingOffset();
        Time duration = music.getDuration();
        playerSlider.setCurrentDuration(currentTime.asSeconds());
        currentValue = (currentTime.asSeconds() / duration.asSeconds()) * 100;
        playerSlider.setThumbPosition(currentValue);

        float time = clock.getElapsedTime().asSeconds();
        if (music.getStatus() == Music::Playing)
        {
            for (int i = 0; i < numBars; ++i)
            {
                float amplitude = 15.0f * std::sin(time * 4 + i);
                bars[i].setSize(Vector2f(barWidth, amplitude + 20));
                bars[i].setPosition(bars[i].getPosition().x, (window.getSize().y / 2 + 100) - amplitude / 2);
            }
        }
        else {
            for (int i = 0; i < numBars; ++i)
            {
                bars[i].setSize(Vector2f(barWidth, 10));
                bars[i].setPosition(bars[i].getPosition().x, window.getSize().y / 2 + 100);
            }
        }

        if (music.getStatus() == Music::Stopped && !music.getLoop())
        {
            isPlaying = false;
        }

        window.clear(Color::White);
        window.draw(backgroundSprite);
        window.draw(musicImage);
        for (int i = 0; i < numBars; i++)
        {
            window.draw(bars[i]);
        }
        window.draw(playBack);
        window.draw(playForward);
        window.draw(playPrev);
        window.draw(playNext);
        if (isPlaying)
            window.draw(pauseSprite);
        else
            window.draw(playSprite);
        if (music.getLoop())
            window.draw(repeatSprite);
        else
            window.draw(nonRepeatSprite);
        playerSlider.draw(window);
        window.display();
    }

    return 0;
}
