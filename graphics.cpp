#include <iostream>
#include "graphics.h"

int main()
{
    graphics graphics;
    graphics.init(1000, 700, "Test");

    int obj = graphics.create(0, 5, 10, RED, 5, 5);
    int obj2 = graphics.create(0, 40, 10, YELLOW, 10, 10);

    graphics.renderAll();

    while (true) {
        if (graphics.collidesWith(obj, obj2)) { graphics.renderText("COLLIDES", 0, 0, 10); };

        //graphics.setPosition(obj, graphics.getPositionX(obj)+1, 10);
        graphics.move(obj, "right", 1);
        graphics.renderAll();
        if (graphics.keyDown('A')) { graphics.renderText("A PRESSED", 10, 10, 9); }
        Sleep(10);
    }
}
