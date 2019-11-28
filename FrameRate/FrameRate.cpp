#include <time.h>
#include <iostream>
#include <thread>
#include <array>

#include <conio.h>


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_w 119
#define KEY_W 87
#define KEY_a 97
#define KEY_A 65
#define KEY_D 68
#define KEY_d 100
#define KEY_S 83
#define KEY_s 115



double clockToMilliseconds(clock_t ticks) {
	// units/(units/time) => time (seconds) * 1000 = milliseconds
	return (ticks / (double)CLOCKS_PER_SEC)*1000.0;
}
//...
const int width = 25, height = 25;
void initMap(char(&map)[width][height], const int w, const int h)
{
	for (size_t i = 0; i < w; i++)
	{
		for (size_t j = 0; j < h; j++)
		{
			map[i][j] = '_';
		}
	}
}
void drawMap(char(&map)[width][height], const int w, const int h)
{
	for (size_t i = 0; i < w; i++)
	{
		for (size_t j = 0; j < h; j++)
		{
			std::cout << map[i][j];
		}
		std::cout << std::endl;
	}
}
int main()
{
	clock_t timer = 0;
	double deltaTime;
	unsigned int frames = 0;
	double  frameRate = 120;

	char map[width][height];
	initMap(map, width, height);
	int characterX = height / 2;
	int characterY = width / 2;

	clock_t time = 0;
	while (true) {


		std::chrono::high_resolution_clock::time_point beginFrame = std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		int c = 0;

		map[characterX][characterY] = '_';
		if (_kbhit()) {
			switch ((c = _getch())) {

			case KEY_UP:

				std::cout << std::endl << "Up" << std::endl;//key up
				characterX--;
				break;

			case KEY_DOWN:
				characterX++;
				std::cout << std::endl << "Down" << std::endl; // key down

				break;

			case KEY_LEFT:
				characterY--;
				std::cout << std::endl << "Left" << std::endl; // key left

				break;

			case KEY_RIGHT:
				characterY++;
				std::cout << std::endl << "Right" << std::endl; // key right

				break;

			default:

				std::cout << std::endl << c << "null" << std::endl; // not arrow

				break;

			}

		}
		map[characterX][characterY] = 'O';
		system("cls");
		drawMap(map, width, height);

		std::chrono::high_resolution_clock::time_point endFrame = std::chrono::high_resolution_clock::now();

		deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(endFrame - beginFrame).count();
		timer += deltaTime;
		time += deltaTime;
		frames++;
		std::cout << "Delta Time: " << deltaTime / 1000.0f << std::endl;
		std::cout << time / 1000.0f << std::endl;
		//if you really want FPS
		if (timer >= 1000.0) { //every second
			std::cout << "Frames:" << frames << std::endl;
			timer = 0.0f;
			frames = 0;


		}
		/*FrameRate Limit*/
		else if (frames >= frameRate)
		{
			std::cout << "Wait" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds((long)(1000.0f - timer)));
			frames = 0;
			timer = 0.0f;
		}
	}
}