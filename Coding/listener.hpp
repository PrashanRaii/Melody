// #ifndef LISTENER_HPP
// #define LISTENER_HPP

// #include <iostream>
// #include <vector>
// #include <string>
// #include <algorithm>
// #include <fstream>
// #include "popup.hpp"
// #include "User.hpp"

// using namespace std;

// class Song {
// private:
//     string songName;
//     string musicianName;
//     string filePath;
//     string imagePath; // Added imagePath attribute

// public:
//     Song(const string& songName, const string& musicianName,
//          const string& filePath, const string& imagePath)
//         : songName(songName), musicianName(musicianName),
//           filePath(filePath), imagePath(imagePath) {}

//     string getSongName() const { return songName; }
//     string getMusicianName() const { return musicianName; }
//     string getFilePath() const { return filePath; }
//     string getImagePath() const { return imagePath; }

//     void printDetails() const {
//         cout << "Song Name: " << songName << endl;
//         cout << "Musician Name: " << musicianName << endl;
//         cout << "File Path: " << filePath << endl;
//         cout << "Image Path: " << imagePath << endl;
//     }

//     string serialize() const {
//         return songName + "|" + musicianName + "|" + filePath + "|" + imagePath;
//     }

//     // Deserialize Song from string
//     static Song deserialize(const string& data) {
//         size_t pos1 = data.find('|');
//         size_t pos2 = data.find('|', pos1 + 1);
//         size_t pos3 = data.find('|', pos2 + 1);

//         string songName = data.substr(0, pos1);
//         string musicianName = data.substr(pos1 + 1, pos2 - pos1 - 1);
//         string filePath = data.substr(pos2 + 1, pos3 - pos2 - 1);
//         string imagePath = data.substr(pos3 + 1);

//         return Song(songName, musicianName, filePath, imagePath);
//     }
// };

// class listener: public User {
// private:
//     string name;
//     vector<Song> collection; 
//     vector<Song> favorites;

// public:
//     listener(const string& name) : name(name) {}

//     void addSong(const Song& song) {
//         collection.push_back(song);
//     }

//     void viewCollection() const {
//         cout << "\n" << name << "'s Music Collection:\n";
//         for (size_t i = 0; i < collection.size(); ++i) {
//             cout << "\nSong " << (i + 1) << ":\n";
//             collection[i].printDetails();
//         }
//     }

//     void viewFilePath(const string& songName) const {
//         for (const auto& song : collection) {
//             if (song.getSongName() == songName) {
//                 cout << "File Path for '" << songName << "': " << song.getFilePath() << endl;
//                 return;
//             }
//         }
//         cout << "Song '" << songName << "' not found in the collection." << endl;
//     }

//     void deleteSong(const string& songName) {
//         auto it = remove_if(collection.begin(), collection.end(),
//             [&songName](const Song& song) { return song.getSongName() == songName; });
//         collection.erase(it, collection.end());
//     }

//     int addToFavorites(const string& songName) {
//         loadFromFile();
//         for (const auto& song : collection) {
//             if (song.getSongName() == songName){
//                 if (find_if(favorites.begin(), favorites.end(),
//                             [&songName](const Song& fav) { return fav.getSongName() == songName; }) == favorites.end()) {
//                     favorites.push_back(song);
//                     saveToFile();
//                     return 1;
//                 } else {
//                     cout << "Song '" << songName << "' is already in favorites." << endl;
//                     return 2;
//                 }
//             }
//             return 3;   
//         }
//         cout << "Song '" << songName << "' not found in the collection." << endl;
//         return 4;
//     }
//     int removeFromFavorites(const string& songName) {
//         loadFromFile(); // Ensure the favorites list is up-to-date
//         auto it = find_if(favorites.begin(), favorites.end(),
//                         [&songName](const Song& song) { return song.getSongName() == songName; });

//         if (it != favorites.end()) {
//             favorites.erase(it);
//             saveToFile();
//             return 1;
//         } else {
//             return 2;
//         }
//         return 3;
//     }

    

//     void saveToFile() const {
//         ofstream outFile("collection.txt");
//         if (!outFile) {
//             cerr << "Error opening file for writing." << endl;
//             return;
//         }

//         outFile << "Collection\n";
//         for (const auto& song : collection) {
//             outFile << song.serialize() << endl;
//         }

//         outFile << "Favorites\n";
//         for (const auto& song : favorites) {
//             outFile << song.serialize() << endl;
//         }

//         outFile.close();
//     }

//     void loadFromFile() {
//         ifstream inFile("collection.txt");
//         if (!inFile) {
//             cerr << "Error opening file for reading." << endl;
//             return;
//         }

//         string line;
//         string section;
//         while (getline(inFile, line)) {
//             if (line == "Collection") {
//                 section = "Collection";
//             } else if (line == "Favorites") {
//                 section = "Favorites";
//             } else {
//                 if (section == "Collection") {
//                     collection.push_back(Song::deserialize(line));
//                 } else if (section == "Favorites") {
//                     favorites.push_back(Song::deserialize(line));
//                 }
//             }
//         }

//         inFile.close();
//     }

//     bool isFavorites(const string &name) const {
//         for (const auto& song : favorites) {
//             if (song.getSongName() == name) {
//                 return true;
//             }
//         }
//         return false;
//     }

//     // Getter for the collection
//     const vector<Song>& getCollection() const {
//         return collection;
//     }

//     const vector<Song>& getFavorites() const {
//         return favorites;
//     }
// };

// void addSong(vector<Song>& songList) {
//     string songName, musicianName, filePath, imagePath;

//     cout << "Enter song name: ";
//     getline(cin, songName);

//     cout << "Enter musician name: ";
//     getline(cin, musicianName);

//     cout << "Enter file path: ";
//     getline(cin, filePath);

//     cout << "Enter image path: ";
//     getline(cin, imagePath);

//     Song newSong(songName, musicianName, filePath, imagePath);
//     songList.push_back(newSong);
// }

// #endif




// #ifndef LISTENER_HPP
// #define LISTENER_HPP

// #include <vector>
// #include <algorithm>
// #include "song.hpp"

// class listener {
// private:
//     string name;
//     vector<Song> collection;
//     vector<Song> favorites;


// public:
//     listener(const string& name);
//     void saveToFile() const;
//     void loadFromFile();

//     void addSong(const string& title, const string& artist, const string& filePath, const string& imagePath);
//     void viewCollection() const;
//     void viewFilePath(const string& songName) const;
//     void deleteSong(const string& songName);
//     int addToFavorites(const string& songName);
//     int removeFromFavorites(const string& songName);
//     bool isFavorites(const string &name) const;

//     const vector<Song>& getCollection() const;
//     const vector<Song>& getFavorites() const;
// };


// // Constructor
// listener::listener(const string& name) : name(name) {
//     loadFromFile();
// }

// // Adds a song to the listener's collection
// void listener::addSong(const string& title, const string& artist, const string& filePath, const string& imagePath) {
//     Song newsong(title, artist, filePath, imagePath);
//     collection.push_back(newsong);
//     saveToFile();
// }

// // View the entire song collection
// void listener::viewCollection() const {
//     for (const auto& song : collection) {
//         song.printDetails();
//         cout << "----------------------" << endl;
//     }
// }

// // View file path of a specific song
// void listener::viewFilePath(const string& songName) const {
//     for (const auto& song : collection) {
//         if (song.getSongName() == songName) {
//             cout << "Filepath: " << song.getFilePath() << endl;
//             return;
//         }
//     }
//     cout << "Song not found!" << endl;
// }

// // Delete a song from the collection
// void listener::deleteSong(const string& songName) {
//     auto it = remove_if(collection.begin(), collection.end(), [&](const Song& song) {
//         return song.getSongName() == songName;
//     });

//     if (it != collection.end()) {
//         collection.erase(it, collection.end());
//         saveToFile();
//         cout << "Song deleted." << endl;
//     } else {
//         cout << "Song not found!" << endl;
//     }
// }

// // Add a song to the favorites
// int listener::addToFavorites(const string& songName) {
//     auto it = find_if(collection.begin(), collection.end(), [&](const Song& song) {
//         return song.getSongName() == songName;
//     });

//     if (it != collection.end()) {
//         favorites.push_back(*it);
//         saveToFile();
//         cout << "Song added to favorites." << endl;
//         return 0;
//     } else {
//         cout << "Song not found in collection!" << endl;
//         return 1;
//     }
// }

// // Remove a song from the favorites
// int listener::removeFromFavorites(const string& songName) {
//     auto it = remove_if(favorites.begin(), favorites.end(), [&](const Song& song) {
//         return song.getSongName() == songName;
//     });

//     if (it != favorites.end()) {
//         favorites.erase(it, favorites.end());
//         saveToFile();
//         cout << "Song removed from favorites." << endl;
//         return 0;
//     } else {
//         cout << "Song not found in favorites!" << endl;
//         return 1;
//     }
// }

// // Check if a song is in the favorites list
// bool listener::isFavorites(const string &name) const {
//     return any_of(favorites.begin(), favorites.end(), [&](const Song& song) {
//         return song.getSongName() == name;
//     });
// }

// // Save the collection and favorites to a file
// void listener::saveToFile() const {
//     ofstream file(name + "_collection.txt");
//     for (const auto& song : collection) {
//         file << song.serialize() << "-----\n";
//     }
//     file.close();

//     ofstream favFile(name + "_favorites.txt");
//     for (const auto& song : favorites) {
//         favFile << song.serialize() << "-----\n";
//     }
//     favFile.close();
// }

// // Load the collection and favorites from a file
// void listener::loadFromFile() {
//     collection.clear();
//     favorites.clear();

//     ifstream file(name + "_collection.txt");
//     string line, data;
//     while (getline(file, line)) {
//         if (line == "-----") {
//             collection.push_back(Song::deserialize(data));
//             data.clear();
//         } else {
//             data += line + '\n';
//         }
//     }
//     file.close();

//     ifstream favFile(name + "_favorites.txt");
//     while (getline(favFile, line)) {
//         if (line == "-----") {
//             favorites.push_back(Song::deserialize(data));
//             data.clear();
//         } else {
//             data += line + '\n';
//         }
//     }
//     favFile.close();
// }

// // Get the collection of songs
// const vector<Song>& listener::getCollection() const {
//     return collection;
// }

// // Get the list of favorite songs
// const vector<Song>& listener::getFavorites() const {
//     return favorites;
// }

// #endif