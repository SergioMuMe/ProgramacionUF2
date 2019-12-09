#include <iostream>
#include <array>
#include <time.h>
#include <thread>
#include <stdlib.h>
#include <stdio.h>

#define WIDTH 5
#define HEIGHT 5
#define FIELD '_'
#define CHARACTER 'O'
#define ZOMB 'Z'
#define MOVIMIENTO_ENEMIGO 1


const int length = 2;
enum GoTo { EjeX, EjeY };
GoTo eje;

struct Character { int x; int y; };

int PathFinding(std::array<Character, length> &zombie, Character player, /*Testing ->*/ bool &gameLoop, int index)
{

	//Metodo sencillo de PathFinding
	//Si ningún eje coincide con el de player, coge un eje al azar.
	if (zombie[index].x != player.x && zombie[index].y != player.y)
	{
		rand() % 2 == 0 ? eje = EjeX : eje = EjeY;
	}
	//...Sino, mira si el eje X es distinto, coge el eje X.
	else if (zombie[index].x != player.x) { eje = EjeX; }
	//...Sino, coge el eje Y.
	else { eje = EjeY; }


	//Movimiento del enemigo en el Eje seleccionado
	switch (eje)
	{
	case EjeX:
		if (zombie[index].x > player.x) { zombie[index].x -= MOVIMIENTO_ENEMIGO; }
		if (zombie[index].x < player.x) { zombie[index].x += MOVIMIENTO_ENEMIGO; }
		break;
	case EjeY:
		if (zombie[index].y > player.y) { zombie[index].y -= MOVIMIENTO_ENEMIGO; }
		if (zombie[index].y < player.y) { zombie[index].y += MOVIMIENTO_ENEMIGO; }
		break;
	}

	if (zombie[index].x == player.x && zombie[index].y == player.y)
	{

		/*Testing ->*/ gameLoop = false;

		//TODO: Función attack + Remove Enemy.
	}

	return 0;
}

typedef std::array<std::array<char, WIDTH>, HEIGHT> mapArray;

void InitMap(mapArray(&map)/*, Character &pj, Character &zombie*/)
{
	//pj.x = rand() % HEIGHT;	pj.y = rand() % WIDTH;

	//do { zombie.x = rand() % HEIGHT; zombie.y = rand() % WIDTH; } while (zombie.x == pj.x && zombie.y == pj.y);

	for (int i = 0; i < HEIGHT; i++) { for (int j = 0; j < WIDTH; j++) { map[i][j] = FIELD; } }
}

void PrintMap(mapArray(&map), Character pj, std::array<Character, length> zombie, int index)
{
	
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (i == pj.y && j == pj.x) { std::cout << CHARACTER; }
			//else if (i == zombie[index].y && j == zombie[index].x) { std::cout << ZOMB; }
			else { std::cout << map[i][j]; }
		}
		std::cout << std::endl;
	}
}
void PrintZombies()

int main()
{
	mapArray map;

	srand(time(NULL));

	bool gameLoop = true;
	
	
	Character pj;
	/*pj.x = WIDTH / 2;
	pj.y = HEIGHT / 2;*/

	pj.x = 2;
	pj.y = 2;

	std::array<Character, length> zombie;

	zombie[0].x = 4;
	zombie[0].y = 1;
	zombie[1].x = 0;
	zombie[1].y = 0;
		

		
	/*for (size_t i = 0; i < length; i++)
	{
		do
		{
			zombie[i].x = rand() % HEIGHT;
			zombie[i].y = rand() % WIDTH;
		} while (zombie[i].x == pj.x && zombie[i].y == pj.y);
	}*/
	

	clock_t tInicial = clock();
	clock_t tPintaMapa = clock();
	clock_t tCorreHumano = clock();
	int contador = 1;

	InitMap(map/*, pj, zombie*/);

	while (gameLoop)
	{
		clock_t aux = clock();

		//OPCION 2 - Marc
		/*if ((aux - tInicial) / CLOCKS_PER_SEC == contador)
		{
			PrintMap(map, pj, zombie);
			contador++;
		}*/

		if ((aux - tPintaMapa) / 2000 == 1)
		{
			tPintaMapa = clock();
			
			for (size_t i = 0; i < length; i++)
			{
				PrintMap(map, pj, zombie, i);
				PathFinding(zombie, pj, gameLoop, i); //Zombie persigue
			}
			std::cout << ".....";
			
			
		}

		//if ((aux - tCorreHumano) / 2000 == 1)
		//{
		//	tCorreHumano = clock();
		//	for (size_t i = 0; i < length; i++)
		//	{
		//		PrintMap(map, pj, zombie, i);
		//		//humano huye persigue
		//	}
		//	system("cls");
		//}

		//if ((aux - tInicial) / CLOCKS_PER_SEC >= 10) { gameLoop = false; }

	}

	system("cls");
	std::cout << "GAME OVER";
	std::cin.ignore();
	std::cin.get();

	return 0;
}