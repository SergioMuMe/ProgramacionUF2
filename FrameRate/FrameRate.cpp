#include <time.h>
#include <iostream>
#include <thread>
#include <array>

#include <conio.h>

#include "List.h"
#include "Elements.h"


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


const int width = 25, height = 25;

// TODO: Medidas sala

enum tipoSala
{
	ENTRADA,
	SALIDA

};

struct sala
{
	
	int casa;
	//= tipoSala::ENTRADA;

	casa = 1;





};

double clockToMilliseconds(clock_t ticks) {
	// units/(units/time) => time (seconds) * 1000 = milliseconds
	return (ticks / (double)CLOCKS_PER_SEC)*1000.0;
}
//...

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

	unsigned int score; 

	srand(time(NULL));


	// INIT GAME
	
	Player sPlayer;

	sPlayer.hp = 10;
	sPlayer.x = height / 2;
	sPlayer.y = width / 2;

	List <Balls> lBalls;
	Balls sBalls;

	//Bucle
	
	bool comparePlayer = sBalls.x == sPlayer.x && sBalls.y == sPlayer.y;
	bool compareBalls = sBalls.x == sPlayer.x && sBalls.y == sPlayer.y;

	while (lBalls.GetLength() != maxBalls)
	{

		
		do
		{
			sBalls.x = rand() % height;
			sBalls.y = rand() % width;




		}while(comparePlayer)


		

		if (lBalls.GetLength() == 0)
		{

		}
		else
		{
			
		}

		/*TODO:
		1-Crear 1 bola
		1.1.- if GetLength==0{x=rand != player.x && y=rand != player.y}
		1.2.- else {(x=rand != player.x && y=rand != player.y) && pos != resto de bolas}
		*/

	}

	sBalls.id;
	sBalls.x=;
	sBalls.y=;



	lBalls.Add(sBalls)

	// end


	
	List <Enemies> enemies;

	
	/*TODO:
	Crear Struct Enemies
	Crear Struct Balls
	
	*/

	
	char map[width][height];
	initMap(map, width, height);
	int characterX = height / 2;
	int characterY = width / 2;

	

	// GAME LOOP

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
		
		//antes de drawMap()
		/* TODO
		Todos los enemigos -1hp.
		Si posición enemigo == player {destruye enemigo, player -1hp}
		Si hp enemigo == 0 {destruye enemigo}
		Si posición jugador == bola (destruye bola, score ++}
		*/


		//
		
		drawMap(map, width, height); //TODO: Imprimir puntuación actual de jugador

		std::chrono::high_resolution_clock::time_point endFrame = std::chrono::high_resolution_clock::now();

		deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(endFrame - beginFrame).count();
		timer += deltaTime;
		time += deltaTime;
		frames++;
		//TODO: Si frame es PAR {mover enemigo}
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