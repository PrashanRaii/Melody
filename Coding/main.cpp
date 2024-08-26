#include "error.hpp"
#include "player.hpp"
#include "login.hpp"
#include "register.hpp"
#include "home.cpp"
int main()
{
    bool isLoggedIn = true;
    
    if (isLoggedIn  == true)    
    {
        return home();
        return 0;
    }
    else 
    {
        return registerUser();
        return 0;
    }
    return 0;
}