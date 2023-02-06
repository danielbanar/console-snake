#include "snake.h"

bool isFree(const std::vector<Coord>& snake, const Coord& apple)
{
	for (const Coord& snakeBlock : snake)
	{
		if (snakeBlock == apple)
			return false;
	}
	return true;
}

int main()
{
	srand(time(0));
	//Initialize console
	char screenBuffer[mapSize*mapSize];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, 0, CONSOLE_TEXTMODE_BUFFER, 0);
	SetConsoleActiveScreenBuffer(hConsole);
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 32;
	cfi.dwFontSize.Y = 32;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	SetCurrentConsoleFontEx(hConsole, false, &cfi);
	DWORD dwBytesWritten = 0;
	//Init end
	std::vector<Coord> snake;
	Direction direction = None;
	Coord head = { 1 + rand() % (mapSize - 2), 1 + rand() % (mapSize - 2) }, apple = { 1 + rand() % (mapSize - 2), 1 + rand() % (mapSize - 2) };
	snake.push_back(head);
	bool alive = true;
	while (alive)
	{
		//Handle input
		if (GetAsyncKeyState('W') && direction != Down)
			direction = Up;
		else if (GetAsyncKeyState('A') && direction != Right)
			direction = Left;
		else if (GetAsyncKeyState('S') && direction != Up)
			direction = Down;
		else if (GetAsyncKeyState('D') && direction != Left)
			direction = Right;
		switch (direction)
		{
		case Right:
			head = RightCoord(head);
			break;
		case Up:
			head = UpCoord(head);
			break;
		case Left:
			head = LeftCoord(head);
			break;
		case Down:
			head = DownCoord(head);
			break;
		}
		//Eating apfel
		if (head == apple)
		{
			snake.insert(snake.begin(), head);
			do
			apple = { 1+rand() % (mapSize-2), 1+rand() % (mapSize-2) };
			while (!isFree(snake, apple));
		}

		//Eating himself
		for (int i = 1; i < snake.size(); i++)
		{
			if (head == snake[i])
				alive = false;
		}
		//Out of screen
		if (head.x<1 || head.y<1 || head.x>mapSize - 2 || head.y>mapSize - 2)
			alive = false;
		snake.erase(snake.begin());
		snake.push_back(head);
		//Draw Frame
		for (size_t i = 0; i < strlen(screenBuffer); i++)
			screenBuffer[i] = ' ';
		for (size_t i = 0; i < snake.size(); i++)
			screenBuffer[GetIndex(snake[i])] = 219;
		screenBuffer[GetIndex(apple)] = '#';
		WriteConsoleOutputCharacterA(hConsole, screenBuffer, mapSize * mapSize, { 0, 0 }, &dwBytesWritten);
		std::this_thread::sleep_for(200ms);
	}
	WriteConsoleOutputCharacterA(hConsole, "GG", 3, { 0, 0 }, &dwBytesWritten);
	std::this_thread::sleep_for(60s);
}