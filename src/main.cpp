#include <iostream>
#include "app.h"

int main(int, char **)
{
    App app;
    app.init("Desenvolvimento", 800, 600);
    app.loop();
    
    return 0;
}