#include "error.hpp"
#include "player.hpp"
#include "login.hpp"
#include "register.hpp"
#include "home.cpp"
#include "User.hpp"
#include "listener.hpp"

int main()
{
    bool isLoggedIn = true;
    if (isLoggedIn  == false)    
    {
        return registerUser();
        return 0;
    }
    else 
    {
        return home();
        return 0;
    }
    return 0;
}