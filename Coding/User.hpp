#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <limits> // for numeric_limits
#include <cctype> // for isalnum
#include <cstdlib> 
using namespace std;

int main();

class User
{
protected:
    string username, password, role;

public:
    User(string usrnm = "", string pass = "", string role = "") : username(usrnm), password(pass), role(role) {}

    // Check if the username is valid (alphanumeric)
    bool isValidUsername(const string &username)
    {
        for (size_t i = 0; i < username.length(); ++i)
        {
            if (!isalnum(username[i])) // Check if the character is not alphanumeric
            {
                return false;
            }
        }
        return true;
    }

    // Encrypt the password
    string encryptPassword(const string &password, int shift)
    {
        string encryptedPassword = password;
        for (size_t i = 0; i < password.length(); ++i)
        {
            if (isalpha(password[i]))
            {
                char base = islower(password[i]) ? 'a' : 'A';
                encryptedPassword[i] = (password[i] - base + shift) % 26 + base;
            }
            else if (isdigit(password[i]))
            {
                encryptedPassword[i] = (password[i] - '0' + shift) % 10 + '0';
            }
        }
        return encryptedPassword;
    }

    // Register a new user
    bool UserRegister(RenderWindow &window, string &username, string &password, string &role)
    {
        bool validUsername = false;
        do
        {
            if (isValidUsername(username))
            {
                ifstream in("users.txt");
                string fileUsername;
                bool usernameExists = false;

                while (in >> fileUsername)
                {
                    in.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (fileUsername == username)
                    {
                        usernameExists = true;
                        break;
                    }
                }
                in.close();

                if (usernameExists)
                {
                    showPopup(window, "Username already exists!", Vector2f(500, 60), "Error");
                    return false;
                }
                else
                {
                    validUsername = true;
                }
            }
            else
            {
                showPopup(window, "Invalid Username! Only alphabets and numbers are allowed.", Vector2f(500, 60), "Error");
            }
        } while (!validUsername);

        int roleChoice;
        bool validRole = false;


        while (!validRole)
        {
            if (role == "Listener" || role == "Musician")
            {
                validRole = true;
            }
            else
            {
                showPopup(window, "Invalid Role!", Vector2f(500, 60), "Error");
                return false;
            }
        }

        string encryptedPassword = encryptPassword(password, 7);

        ofstream out("users.txt", ios::app); // Only ios::app is needed for appending
        if (!out)
        {
            error("Error opening file for writing.");
            return false;
        }
        out << username << " " << encryptedPassword << " " << role << endl;
        out.close();

        cout << "Registration successful! You are a " << role << "." << endl;
        return true;
    }

    // Login an existing user
    bool UserLogin(RenderWindow &window, string &username, string &password)
    {
        ifstream in("users.txt");
        if (!in)
        {
            error("Error opening file for reading.");
            return false;
        }
        bool validUsername = false;
        do
        {
            if (isValidUsername(username))
            {
                validUsername = true;
            }
            else
            {
                showPopup(window, "Invalid Username!", Vector2f(500, 60), "Error");
                return false;
            }
        } while (!validUsername);

        string encryptedPassword = encryptPassword(password, 7);

        string fileUsername, filePassword, fileRole, role;
        bool loginSuccess = false;

        while (in >> fileUsername >> filePassword >> fileRole)
        {
            if (fileUsername == username && filePassword == encryptedPassword)
            {
                role = fileRole;
                loginSuccess = true;
                break;
            }
        }

        in.close();

        if (loginSuccess)
        {
            cout << "Login successful! Welcome " << username << "." << endl;
            return true;
        }
        else
        {
            showPopup(window, "Invalid username or password.", Vector2f(500, 60), "Error");
            return false;
        }
        return false;
    }

    // Getter methods
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getRole() const { return role; }
};


#endif