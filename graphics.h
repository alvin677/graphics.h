#pragma once
#include <vector>
#include <Windows.h>

// Color variables
#define BLACK 0
#define GRAY 119
#define DARK_GRAY 136
#define RED 68
#define GREEN 34
#define BLUE 51
#define DARK_BLUE 17
#define YELLOW 102
#define PURPLE 85
#define AQUA 187
#define LIME 170
#define LIGHT_BLUE 153
#define LIGHT_RED 204
#define LIGHT_PURPLE 221
#define LIGHT_YELLOW 238
#define WHITE 255

// Class
class graphics
{

public:
	int winX;
	int winY;
	void init(int windowX, int windowY, std::string title) {
		HWND console2 = GetConsoleWindow();
		RECT r;
		GetWindowRect(console2, &r);
		MoveWindow(console2, r.left, r.top, windowX, windowY, TRUE);
		std::string exec= "title " + title;
		system(exec.c_str());

		GetConsoleCursorInfo(console, &cursorInfo);
		cursorInfo.bVisible = false;
		SetConsoleCursorInfo(console, &cursorInfo);
		winX = windowX;
		winY = windowY;
	};

	// Type 0 = rectangle
	int create(int type, int x, int y, int color = WHITE, int width = 1, int height = 1) {
		std::vector<int> temp = { type, x, y, width, height, color };
		objects.push_back(temp);
		return objects.size()-1;
	};

	void setColor(int id, int color) {
		objects.at(id).at(5) = color;
	}

	void setPosition(int id, int x, int y, int prevColor = BLACK) {
		int oldX = getPositionX(id);
		int oldY = getPositionY(id);
		int diffX, diffY;
		diffX = x - oldX;
		if (diffX < 0)
			diffX = -diffX;
		diffY = y - oldY;
		if (diffY < 0)
			diffY = -diffY;
		draw(oldX, oldY, objects.at(id).at(3)-diffX, objects.at(id).at(4)-diffY, prevColor);
		objects.at(id).at(1) = x;
		objects.at(id).at(2) = y;
	}

	void move(int id, std::string direction, int amount, int prevColor = BLACK) {
		for (int i = 0; i < amount; i++) {
			if (direction == "up") {
				setPosition(id, objects.at(id).at(1), objects.at(id).at(2)-1, prevColor);
			}
			else if (direction == "right") {
				setPosition(id, objects.at(id).at(1)+1, objects.at(id).at(2), prevColor);
			}
			else if (direction == "down") {
				setPosition(id, objects.at(id).at(1), objects.at(id).at(2)+1, prevColor);
			}
			else if (direction == "left") {
				setPosition(id, objects.at(id).at(1)-1, objects.at(id).at(2), prevColor);
			}
		};
	};

	void setSize(int id, int width, int height) {
		objects.at(id).at(3) = width;
		objects.at(id).at(4) = height;
	}

	void setType(int id, int type) {
		objects.at(id).at(0) = type;
	}

	int getColor(int id) {
		return objects.at(id).at(5);
	}

	int getPositionX(int id) {
		return objects.at(id).at(1);
	}
	int getPositionY(int id) {
		return objects.at(id).at(2);
	}
	int getWidth(int id) {
		return objects.at(id).at(3);
	}
	int getHeight(int id) {
		return objects.at(id).at(4);
	}
	int getType(int id) {
		return objects.at(id).at(0);
	}

	void render(int id) {
		SetConsoleTextAttribute(console, objects.at(id).at(5));
		if (objects.at(id).at(0) == 0) {
			for (int i = 0; i < objects.at(id).at(3); i++) {
				for (int j = 0; j < objects.at(id).at(4); j++) {
					coord.X = objects.at(id).at(1)+i;
					coord.Y = objects.at(id).at(2)+j;
					SetConsoleCursorPosition(console, coord); std::cout << "X"; };
			};
		};
		SetConsoleTextAttribute(console, 15);
	};
	
	void renderAll() {
		for (int id = 0; id < objects.size(); id++) {
			render(id);
		};
	};

	void renderText(std::string text, int x, int y, int color) {
		SetConsoleTextAttribute(console, color);
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(console, coord); std::cout << text;
	}

	void draw(int x, int y, int width, int height, int color) {
		SetConsoleTextAttribute(console, color);
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				coord.X = x + i;
				coord.Y = y + j;
				SetConsoleCursorPosition(console, coord); 
				std::cout << "X";
			};
		};
		SetConsoleTextAttribute(console, 15);
	};

	void clear() { system("cls"); };

	bool collidesWith(int id, int id2) {
		if (
			objects.at(id).at(1) <= objects.at(id2).at(1) + objects.at(id2).at(3) &&
			objects.at(id).at(1) + objects.at(id).at(3) >= objects.at(id2).at(1) &&
			objects.at(id).at(2) <= objects.at(id2).at(2) + objects.at(id2).at(4) &&
			objects.at(id).at(4) + objects.at(id).at(2) >= objects.at(id2).at(2)
			) {
			return true;
		}
		else { return false; };
	};

	int collidesWithAny(int id) {
		int result = -1;
		for (int i = 0; i < objects.size(); i++) {
			if (i != id) {
				if (
					objects.at(id).at(1) <= objects.at(i).at(1) + objects.at(i).at(3) &&
					objects.at(id).at(1) + objects.at(id).at(3) >= objects.at(i).at(1) &&
					objects.at(id).at(2) <= objects.at(i).at(2) + objects.at(i).at(4) &&
					objects.at(id).at(4) + objects.at(id).at(2) >= objects.at(i).at(2)
					) {
					result = i;
					break;
				}
			}
		};
		return result;
	};

	bool keyDown(char key) {
		if (GetKeyState(key) & 0x8000)
		{
			return true;
		}
		else { return false; }
	};

/*
VK_LBUTTON	0x01	Left mouse button
VK_RBUTTON	0x02	Right mouse button
VK_CANCEL	0x03	Control-break processing
VK_MBUTTON	0x04	Middle mouse button (three-button mouse)
VK_XBUTTON1	0x05	X1 mouse button
VK_XBUTTON2	0x06	X2 mouse button
-	0x07	Undefined
VK_BACK	0x08	BACKSPACE key
VK_TAB	0x09	TAB key
-	0x0A-0B	Reserved
VK_CLEAR	0x0C	CLEAR key
VK_RETURN	0x0D	ENTER key
-	0x0E-0F	Undefined
VK_SHIFT	0x10	SHIFT key
VK_CONTROL	0x11	CTRL key
VK_MENU	0x12	ALT key
VK_PAUSE	0x13	PAUSE key
VK_CAPITAL	0x14	CAPS LOCK key
VK_KANA	0x15	IME Kana mode
VK_HANGUEL	0x15	IME Hanguel mode (maintained for compatibility; use VK_HANGUL)
VK_HANGUL	0x15	IME Hangul mode
VK_IME_ON	0x16	IME On
VK_JUNJA	0x17	IME Junja mode
VK_FINAL	0x18	IME final mode
VK_HANJA	0x19	IME Hanja mode
VK_KANJI	0x19	IME Kanji mode
VK_IME_OFF	0x1A	IME Off
VK_ESCAPE	0x1B	ESC key
VK_CONVERT	0x1C	IME convert
VK_NONCONVERT	0x1D	IME nonconvert
VK_ACCEPT	0x1E	IME accept
VK_MODECHANGE	0x1F	IME mode change request
VK_SPACE	0x20	SPACEBAR
VK_PRIOR	0x21	PAGE UP key
VK_NEXT	0x22	PAGE DOWN key
VK_END	0x23	END key
VK_HOME	0x24	HOME key
VK_LEFT	0x25	LEFT ARROW key
VK_UP	0x26	UP ARROW key
VK_RIGHT	0x27	RIGHT ARROW key
VK_DOWN	0x28	DOWN ARROW key
VK_SELECT	0x29	SELECT key
VK_PRINT	0x2A	PRINT key
VK_EXECUTE	0x2B	EXECUTE key
VK_SNAPSHOT	0x2C	PRINT SCREEN key
VK_INSERT	0x2D	INS key
VK_DELETE	0x2E	DEL key
VK_HELP	0x2F	HELP key
*/
private:
	std::vector<std::vector<int>> objects;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	CONSOLE_CURSOR_INFO cursorInfo;
};

