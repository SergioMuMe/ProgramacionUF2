#include <iostream>
#include <array>
#include <time.h>
#include <thread>

#include <stdlib.h>
#include <stdio.h>

#define WIDTH 10
#define HEIGHT 10
#define FIELD '#'
#define CHARACTER 'O'
#define ZOMB 'Z'

typedef std::array<std::array<char, WIDTH>, HEIGHT> mapArray;

struct POSICION
{
	int x;
	int y;
};

void InitMap(mapArray (&map), POSICION &pj, POSICION &zombie)
{
	pj.x = rand() % HEIGHT + 1;
	pj.y = rand() % WIDTH + 1;

	do
	{
		zombie.x = rand() % HEIGHT;
		zombie.y = rand() % WIDTH;
	} while (zombie.x == pj.x && zombie.y == pj.y);

		
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			map[i][j] = FIELD;
		}

	}
}

void PrintMap(mapArray (&map), POSICION pj, POSICION zombie)
{
	system("cls");
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (i == pj.y && j == pj.x)
			{
				std::cout << CHARACTER;
			}
			else if (i == zombie.y && j == zombie.x)
			{
				std::cout << ZOMB;
			}
			else
			{
				std::cout << map[i][j];
			}
		}
		std::cout << std::endl;
	}
	
}

int PathFindingCazador(POSICION &mueve, POSICION referencia, bool &gameLoop)
{
	int aux;

	if (mueve.x != referencia.x && mueve.y != referencia.y)
	{
		aux = rand() % 2;
	}
	else if (mueve.x != referencia.x)
	{
		aux = 0;
	}
	else if (mueve.y != referencia.y)
	{
		aux = 1;
	}

	switch (aux)
	{
		case 0:
			if (mueve.x > referencia.x)	{mueve.x -= 1;}
			if (mueve.x < referencia.x)	{mueve.x += 1;}
			break;
		case 1:
			if (mueve.y > referencia.y)	{mueve.y -= 1;}
			if (mueve.y < referencia.y)	{mueve.y += 1;}
			break;
	}	
	
	if (mueve.x == referencia.x && mueve.y == referencia.y)
	{
		gameLoop = false;
		return 0;
	}

	return 0;
}

int PathFindingPresa(POSICION &mueve, POSICION referencia)
{
	int aux;

	if (mueve.x != referencia.x && mueve.y != referencia.y)
	{
		aux = rand() % 2;
	}
	else if (mueve.x != referencia.x)
	{
		aux = 0;
	}
	else if (mueve.y != referencia.y)
	{
		aux = 1;
	}
	

	switch (aux)
	{
	case 0:
		if (mueve.x > referencia.x) 
		{ 
			if (mueve.x + 1 == WIDTH)
			{
				mueve.x = 0;
			}
			else
			{
				mueve.x += 1;
			}
		}
		if (mueve.x < referencia.x) 
		{ 
			if (mueve.x - 1 < 0)
			{
				mueve.x = WIDTH - 1;
			}
			else
			{
				mueve.x -= 1;
			} 
		}
		break;
	case 1:
		if (mueve.y > referencia.y)
		{
			if (mueve.y + 1 == WIDTH)
			{
				mueve.y = 0;
			}
			else
			{
				mueve.y += 1;
			}
		}
		if (mueve.y < referencia.y)
		{
			if (mueve.y - 1 < 0)
			{
				mueve.y = WIDTH - 1;
			}
			else
			{
				mueve.y -= 1;
			}
		}
		break;
	}

	return 0;
}

int main() 
{
	mapArray map;
	

	srand(time(NULL));

	bool gameLoop = true;
	
	POSICION pj;
	POSICION zombie;

	clock_t tInicial = clock();
	clock_t tPintaMapa = clock();
	clock_t tCorreHumano = clock();
	int contador = 1;

	InitMap(map, pj, zombie);

	while (gameLoop)
	{
		clock_t aux = clock();
		
		//OPCION 2 - Marc
		/*if ((aux - tInicial) / CLOCKS_PER_SEC == contador)
		{
			PrintMap(map, pj, zombie);
			contador++;
		}*/

		if ((aux - tPintaMapa) / CLOCKS_PER_SEC == 1)
		{
			PrintMap(map, pj, zombie);
			tPintaMapa = clock();
			PathFindingCazador(zombie, pj, gameLoop); //Zombie persigue
		}

		if ((aux - tCorreHumano) / CLOCKS_PER_SEC == 1)
		{
			PrintMap(map, pj, zombie);
			tCorreHumano = clock();
			PathFindingPresa(pj, zombie); //Humano persigue
		}

		//if ((aux - tInicial) / CLOCKS_PER_SEC >= 10) { gameLoop = false; }

	}

	system("cls");
	std::cout << "GAME OVER";
	std::cin.ignore();
	std::cin.get();

	return 0;
}