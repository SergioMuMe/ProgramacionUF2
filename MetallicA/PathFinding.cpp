#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "Elements.h"

#define MOVIMIENTO_ENEMIGO 1

enum GoTo { EjeX, EjeY };
GoTo eje;


int PathFinding(Character &enemy, Character player, /*Testing ->*/ bool gameLoop)
{	

	//Metodo sencillo de PathFinding
	//Si ningún eje coincide con el de player, coge un eje al azar.
	if (enemy.x != player.x && enemy.y != player.y)
	{	
		rand() % 2 == 0 ? eje = EjeX : eje = EjeY;
	}
	//...Sino, mira si el eje X es distinto, coge el eje X.
	else if (enemy.x != player.x){eje = EjeX;}
	//...Sino, coge el eje Y.
	else {eje = EjeY;}


	//Movimiento del enemigo en el Eje seleccionado
	switch (eje)
	{
	case EjeX:
		if (enemy.x > player.x) { enemy.x -= MOVIMIENTO_ENEMIGO; }
		if (enemy.x < player.x) { enemy.x += MOVIMIENTO_ENEMIGO; }
		break;
	case EjeY:
		if (enemy.y > player.y) { enemy.y -= MOVIMIENTO_ENEMIGO; }
		if (enemy.y < player.y) { enemy.y += MOVIMIENTO_ENEMIGO; }
		break;
	}

	if (enemy.x == player.x && enemy.y == player.y)
	{
		
		/*Testing ->*/ gameLoop = false; 

		//TODO: Función attack + Remove Enemy.
	}

	return 0;
}

// TESTING ALGORITMO

#include <array>
#include <time.h>
#include <thread>

#define WIDTH 10
#define HEIGHT 10
#define FIELD '#'
#define CHARACTER 'O'
#define ZOMB 'Z'

typedef std::array<std::array<char, WIDTH>, HEIGHT> mapArray;

void InitMap(mapArray(&map), Character &pj, Character &zombie)
{
	pj.x = rand() % HEIGHT + 1;	pj.y = rand() % WIDTH + 1;

	do 	{ zombie.x = rand() % HEIGHT; zombie.y = rand() % WIDTH; } while (zombie.x == pj.x && zombie.y == pj.y);

	for (int i = 0; i < HEIGHT; i++) {for (int j = 0; j < WIDTH; j++) {map[i][j] = FIELD;}}
}

void PrintMap(mapArray(&map), Character pj, Character zombie)
{
	system("cls");
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (i == pj.y && j == pj.x) { std::cout << CHARACTER; } 
			else if (i == zombie.y && j == zombie.x) { std::cout << ZOMB; }
			else { std::cout << map[i][j]; }
		}
		std::cout << std::endl;
	}
}

int TestPathFinding()
{
	mapArray map;

	srand(time(NULL));

	bool gameLoop = true;

	Character pj;
	Character zombie;

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

		if ((aux - tPintaMapa) / 10000 == 1)
		{
			PrintMap(map, pj, zombie);
			tPintaMapa = clock();
			PathFinding(zombie, pj, gameLoop); //Zombie persigue
		}

		if ((aux - tCorreHumano) / 10000 == 1)
		{
			PrintMap(map, pj, zombie);
			tCorreHumano = clock();
		}

		//if ((aux - tInicial) / CLOCKS_PER_SEC >= 10) { gameLoop = false; }

	}

	system("cls");
	std::cout << "GAME OVER";
	std::cin.ignore();
	std::cin.get();

	return 0;
}