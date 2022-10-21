# graphics.h
A graphics library that can be used in C/C++

To use, simply put the graphics.h file in your repos/PROJECTNAME/PROJECTNAME/ folder.

```cpp
// Color variables
BLACK
GRAY
DARK_GRAY
RED
GREEN
BLUE
DARK_BLUE
YELLOW
PURPLE
AQUA
LIME
LIGHT_BLUE
LIGHT_RED 
LIGHT_PURPLE
LIGHT_YELLOW
WHITE
```


When using in your main() function, start by referencing the class and initializing:

```cpp
int main() {
  graphics graphics;
  graphics.init(1920, 1080, "Title");
}
```
After that you're ready to work on your project.

Existing functions in the library:

```cpp
init(int windowX, int windowY, std::string title);
int create(int type, int x, int y, int color = WHITE, int width = 1, int height = 1) // As of right now, the only type existing is 0, and it's a rectangle.
void setColor(int id, int color)
void setPosition(int id, int x, int y, int prevColor = BLACK)
void setSize(int id, int width, int height)
void setType(int id, int type)
int getColor(int id)
int getPositionX(int id)
int getPositionY(int id)
int getWidth(int id)
int getHeight(int id)
int getType(int id)
void render(int id)
void renderAll()
void renderText(std::string text, int x, int y, int color)
void draw(int x, int y, int width, int height, int color)
void clear()
bool collidesWith(int id, int id2)
int collidesWithAny(int id)
bool keyDown(char key)
```

More Virtual-Key Codes can be found at: https://learn.microsoft.com/sv-se/windows/win32/inputdev/virtual-key-codes?redirectedfrom=MSDN

The example project:

```cpp
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

        graphics.setPosition(obj, graphics.getPositionX(obj)+1, 10);
        graphics.renderAll();
        if (graphics.keyDown('A')) { graphics.renderText("A PRESSED", 10, 10, 9); }
        Sleep(10);
    }
}
```

