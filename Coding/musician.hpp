#ifndef MUSICIAN_HPP
#define MUSICIAN_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;
void emptyFile(const std::string& filePath);

class Song {
protected:
    string title;
    string artist;
    string filePath;
    string imagePath;

public:
    Song() = default;

    Song(const string& title, const string& artist, const string& filePath, const string& imagePath)
        : title(title), artist(artist), filePath(filePath), imagePath(imagePath) {}

    string getSongName() const {
        return title;
    }
    string getMusicianName() const {
        return artist;
    }

    string getFilePath() const {
        return filePath;
    }

    string getImagePath() const {
        return imagePath;
    }

    void printDetails() const {
        cout << "Title: " << title << "\nArtist: " << artist
             << "\nFilepath: " << filePath << "\nImagePath: " << imagePath << endl;
    }

    string serialize() const {
        return "\nTitle:" + title + "\nArtist:" + artist + "\nFilePath:" + filePath + "\nImagePath:" + imagePath + "\n" + "-----\n"; 
    }

    static Song deserialize(const string& data) {
        string title, artist, album, filePath, imagePath;

        stringstream ss(data);
        getline(ss, title, '\n');
        title = title.substr(title.find(":") + 1);

        getline(ss, artist, '\n');
        artist = artist.substr(artist.find(":") + 1);

        getline(ss, filePath, '\n');
        filePath = filePath.substr(filePath.find(":") + 1);

        getline(ss, imagePath, '\n');
        imagePath = imagePath.substr(imagePath.find(":") + 1);

        return Song(title, artist, filePath, imagePath);
    }
};

class musician {
public:
    musician(const std::string& username);

    void addSong(const std::string& title, const std::string& artist, const std::string& filePath, const std::string& imagePath);
    void editSong(const std::string& title, const std::string& newTitle, const std::string& newArtist, const std::string& newAlbum, const std::string& newFilePath, const std::string& newImagePath);
    void deleteSong(const std::string& title);
    void loadFromFile(); // Add this line
    void saveToFile() const;
    std::vector<Song> getCollection() const;

private:
    std::string username;
    std::vector<Song> songs;
    std::string filename = "musician.txt";
};


musician::musician(const string& username) : username(username) {}

// Adds a new song
void musician::addSong(const string& title, const string& artist, const string& filePath, const string& imagePath) {
    Song newSong(title, artist, filePath, imagePath);

    ofstream file("musician.txt", ios::app);
    if (file.is_open()) {
        file << newSong.serialize();
        cout << "Successfully added song.";
        file.close();
    } else {
        cerr << "Error opening file for writing!" << endl;
    }
}

// Loads songs from file
void musician::loadFromFile() {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    string line, data;
    while (getline(file, line)) {
        if (line == "-----") {
            Song song = Song::deserialize(data);
            songs.push_back(song);
            data.clear();
        } else {
            data += line + '\n';
        }
    }
    file.close();
}

// Edits an existing song
void musician::editSong(const string& title, const string& newTitle, const string& newArtist, const string& newAlbum, const string& newFilePath, const string& newImagePath) {
    ifstream file(filename);
    string line, data;
    bool songFound = false;
    vector<Song> songs;

    while (getline(file, line)) {
        if (line == "-----") {
            Song song = Song::deserialize(data);
            if (song.getSongName() == title) {
                songFound = true;
                songs.push_back(Song(newTitle, newArtist, newFilePath, newImagePath));
            } else {
                songs.push_back(song);
            }
            data.clear();
        } else {
            data += line + '\n';
        }
    }
    file.close();

    if (songFound) {
        ofstream outFile("musician.txt");
        if (outFile.is_open()) {
            for (const auto& song : songs) {
                outFile << song.serialize() << "-----\n";
            }
            outFile.close();
            cout << "Song edited successfully." << endl;
        } else {
            cerr << "Error opening file for writing!" << endl;
        }
    } else {
        cout << "Song not found!" << endl;
    }
}

// Deletes a song
void musician::deleteSong(const string& title) {
    ifstream file("musician.txt");
    string line, data;
    vector<Song> songs;
    bool songFound = false;

    while (getline(file, line)) {
        if (line == "-----") {
            Song song = Song::deserialize(data);
            if (song.getSongName() != title) {
                songs.push_back(song);
            } else {
                songFound = true;
            }
            data.clear();
        } else {
            data += line + '\n';
        }
    }
    file.close();

    if (songFound) {
        ofstream outFile("musician.txt");
        if (outFile.is_open()) {
            emptyFile(filename);
            for (const auto& song : songs) {
                outFile << song.serialize() << "-----\n";
            }
            outFile.close();
            cout << "Song deleted successfully." << endl;
        } else {
            cerr << "Error opening file for writing!" << endl;
        }
    } else {
        cout << "Song not found!" << endl;
    }
}

// Returns the song collection
vector<Song> musician::getCollection() const {
    return songs;
}


class listener {
private:
    string name;
    vector<Song> collection;
    vector<Song> favorites;


public:
    listener(const string& name);
    void saveToFile() const;
    void loadFromFile();

    void addSong(const string& title, const string& artist, const string& filePath, const string& imagePath);
    void viewCollection() const;
    void viewFilePath(const string& songName) const;
    void deleteSong(const string& songName);
    int addToFavorites(const string& songName);
    int removeFromFavorites(const string& songName);
    bool isFavorites(const string &name) const;

    const vector<Song>& getCollection() const;
    const vector<Song>& getFavorites() const;
};


// Constructor
listener::listener(const string& name) : name(name) {
    loadFromFile();
}

// Adds a song to the listener's collection
void listener::addSong(const string& title, const string& artist, const string& filePath, const string& imagePath) {
    Song newsong(title, artist, filePath, imagePath);
    collection.push_back(newsong);
    saveToFile();
}

// View the entire song collection
void listener::viewCollection() const {
    for (const auto& song : collection) {
        song.printDetails();
        cout << "----------------------" << endl;
    }
}

// View file path of a specific song
void listener::viewFilePath(const string& songName) const {
    for (const auto& song : collection) {
        if (song.getSongName() == songName) {
            cout << "Filepath: " << song.getFilePath() << endl;
            return;
        }
    }
    cout << "Song not found!" << endl;
}

// Delete a song from the collection
void listener::deleteSong(const string& songName) {
    auto it = remove_if(collection.begin(), collection.end(), [&](const Song& song) {
        return song.getSongName() == songName;
    });

    if (it != collection.end()) {
        collection.erase(it, collection.end());
        saveToFile();
        cout << "Song deleted." << endl;
    } else {
        cout << "Song not found!" << endl;
    }
}

// Add a song to the favorites
int listener::addToFavorites(const string& songName) {
    auto it = find_if(collection.begin(), collection.end(), [&](const Song& song) {
        return song.getSongName() == songName;
    });

    if (it != collection.end()) {
        favorites.push_back(*it);
        saveToFile();
        cout << "Song added to favorites." << endl;
        return 0;
    } else {
        cout << "Song not found in collection!" << endl;
        return 1;
    }
}

// Remove a song from the favorites
int listener::removeFromFavorites(const string& songName) {
    auto it = remove_if(favorites.begin(), favorites.end(), [&](const Song& song) {
        return song.getSongName() == songName;
    });

    if (it != favorites.end()) {
        favorites.erase(it, favorites.end());
        saveToFile();
        cout << "Song removed from favorites." << endl;
        return 0;
    } else {
        cout << "Song not found in favorites!" << endl;
        return 1;
    }
}

// Check if a song is in the favorites list
bool listener::isFavorites(const string &name) const {
    return any_of(favorites.begin(), favorites.end(), [&](const Song& song) {
        return song.getSongName() == name;
    });
}

// Save the collection and favorites to a file
void listener::saveToFile() const {
    ofstream file(name + "_collection.txt");
    for (const auto& song : collection) {
        file << song.serialize() << "-----\n";
    }
    file.close();

    ofstream favFile(name + "_favorites.txt");
    for (const auto& song : favorites) {
        favFile << song.serialize() << "-----\n";
    }
    favFile.close();
}

// Load the collection and favorites from a file
void listener::loadFromFile() {
    collection.clear();
    favorites.clear();

    ifstream file(name + "_collection.txt");
    string line, data;
    while (getline(file, line)) {
        if (line == "-----") {
            collection.push_back(Song::deserialize(data));
            data.clear();
        } else {
            data += line + '\n';
        }
    }
    file.close();

    ifstream favFile(name + "_favorites.txt");
    while (getline(favFile, line)) {
        if (line == "-----") {
            favorites.push_back(Song::deserialize(data));
            data.clear();
        } else {
            data += line + '\n';
        }
    }
    favFile.close();
}

// Get the collection of songs
const vector<Song>& listener::getCollection() const {
    return collection;
}

// Get the list of favorite songs
const vector<Song>& listener::getFavorites() const {
    return favorites;
}

void emptyFile(const std::string& filePath) {
    std::ofstream file(filePath, std::ios::trunc);
    if (!file) {
        std::cerr << "Error opening file for truncation: " << filePath << std::endl;
    }
    // File is automatically closed when going out of scope
}
#endif