#include <iostream>
using namespace std;

class Singleton
{
private:
    static Singleton *instance;
    Singleton()
    {
        cout << "This the Singleton object created." << endl;
    }

public:
    static Singleton *getInstance()
    {
        return instance;
    }
};

// INITIALISE STATIC MEMBERS
Singleton *Singleton::instance = new Singleton();

int main()
{

    Singleton *s1 = Singleton::getInstance();
    Singleton *s2 = Singleton::getInstance();

    cout << (s1 == s2) << endl;
    cout << s1 << endl;
    cout << s2 << endl;

    /*
    OUTPUT:
    This the Singleton object created.
    1
    0x1031c17b0
    0x1031c17b0
    */
}

/* REAL WORLD APLICATIONS
1- LOGGING SYSTEM
2 - DATABASE CONNECTION
3 - CONFIGURATION MANAGERS
*/