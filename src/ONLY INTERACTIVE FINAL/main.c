#include "functions.h"

int main()
{
    generate();
    readf();
    npenguins();
    while(1)
    {
        print();
        commands(getch());
        gameOver();
    }
}
