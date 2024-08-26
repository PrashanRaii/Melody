#include <windows.h>
#include <commdlg.h>
#include <string>
#include <iostream>

using namespace std;

string OpenFileDialog() 
{    
    char filename[MAX_PATH] = "";        
    OPENFILENAME ofn;    
    ZeroMemory(&ofn, sizeof(ofn));    
    ofn.lStructSize = sizeof(ofn);    
    ofn.hwndOwner = nullptr;    
    ofn.lpstrFilter = "All Files\0*.*\0Text Files\0*.TXT\0";    
    ofn.lpstrFile = filename;    
    ofn.nMaxFile = MAX_PATH;    
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;    
    ofn.lpstrDefExt = "wav";    
    if (GetOpenFileName(&ofn)) 
    {        
        return string(filename);    
    }    
    return "";
}

int main() {
    string title, artist, album, duration;
    int choice;

    cout << "Enter the title of the song: ";
    getline(cin, title);
    cout << "Enter the artist of the song: ";
    getline(cin, artist);
    cout << "Enter the album name: ";
    getline(cin, album);
    cout << "Enter the duration of the song: ";
    getline(cin, duration);

    // Open file dialog to get the file path
    string filepath = OpenFileDialog();
    if (filepath.empty()) {
        cout << "No file selected. Exiting..." << endl;
        return 1;
    }

    cout << title  << endl << artist << endl << album << endl << duration << endl << filepath << endl;
    return 0;

    // do {
    //     cout << "\nEnter a choice (1: Play, 2: Pause, 3: Display, 4: Exit): ";
    //     cin >> choice;

    //     switch (choice) {
    //         case 1:
    //             s.play();
    //             break;
    //         case 2:
    //             s.pause();
    //             break;
    //         case 3:
    //             s.display();
    //             break;
    //         case 4:
    //             cout << "Exiting..." << endl;
    //             break;
    //         default:
    //             cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
    //             break;
    //     }
    // } while (choice != 4);

    // return 0;
}
