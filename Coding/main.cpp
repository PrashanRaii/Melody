#include "error.hpp"
#include "player.hpp"
#include "login.hpp"
#include "register.hpp"
#include "home.hpp"
#include "homeAdmin.hpp"
#include "User.hpp"
#include "listener.hpp"
#include "tinyfiledialogs.h"

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