#include <time.h>
#include <iostream>
#include <thread>
#include <array>
#include <conio.h>
#include "Elements.h"
#include "List.h"

void PrintRoom(Room sala, int size ) {
	sala.roomMap.resize(size);

	for (int i = 0; i < size; i++)
	{
		sala.roomMap[i].resize(size, '.');
	}

}

void PrintDoor(Room sala, int frontDoor, int backDoor, int size) {
	
	switch (frontDoor)
	{
	case cardinalDoor::NORTH:
		sala.roomMap[size / 2][0] = '-';
		break;
	case cardinalDoor::SOUTH:
		sala.roomMap[size / 2][size] = '-';
		break;
	case cardinalDoor::EAST:
		sala.roomMap[size][size / 2] = '|';
		break;
	case cardinalDoor::WEST:
		sala.roomMap[0][size / 2] = '|';
		break;
	}
}

void CreateEnemies(Room sala, GameVar var, int size) {
	int enemiesNum;
	enemiesNum = var.minEnemy + (rand() % (var.maxEnemy - var.minEnemy + 1));

	for (int i = 0; i < enemiesNum; i++)
	{
		Character enemy;

		do
		{
			enemy.x = rand() % (size + 1);
			enemy.y = rand() % (size + 1);
		} while (sqrt(pow(enemy.x-(size/2),2) + pow(enemy.y-(size/2),2)) < size/4 );

		sala.liEnemies.Add(enemy);
	}

}

void PrintEnemies(Room sala, int size) {

	std::vector<Character>  charArray = sala.liEnemies.GiveAllData();

	
	for (int i = 0; i<sala.liEnemies.GetLength(); i++)
	{
		sala.roomMap[charArray[i].x][charArray[i].y] = 'o';
	}	
};

GameVar SetGame(int choice)
{
	// Creamos struct GameVar para retornar como parametro en la funcion InitMap.
	GameVar sValues;

	/*
	Switch pensado en escalabilidad.
	- Cada dificultad define un número de variables de dificultad.
	- Estas variables multiplican el valor base de la dificultad del juego, obteniendo nuevos valores.
	- Con esta estructura de código podemos hacer un modelo escalable de dificultad,
	permitiendo añadir nuevos cases, a�adir nuevos multiplicadores, cambiar las multiplicaciones por funciones logaritmicas, etc.
	*/

	float modEnemy = 0;
	float modRooms = 0;


	switch (choice)
	{
	case 1:
		modEnemy = 1;
		modRooms = 1;
		break;
	case 2:
		modEnemy = 1.67;
		modRooms = 1.5;
		break;
	}

	sValues.maxRooms = (int)ceil(MAX_ROOMS * modRooms);
	sValues.minRooms = (int)floor(MIN_ROOMS * modRooms);
	sValues.maxSize = MAX_SIZE;
	sValues.minSize = MIN_SIZE;
	sValues.maxEnemy = (int)ceil(MAX_ENEMY * modEnemy);
	sValues.minEnemy = (int)floor(MIN_ENEMY * modEnemy);
	sValues.maxPuppets = (int)ceil(MAX_PUPPETS * modRooms);
	sValues.minPuppets = (int)floor(MIN_PUPPETS * modRooms);
	sValues.maxPuppetLength = MAX_PUPPET_LENGTH;
	sValues.minPuppetLength = MIN_PUPPET_LENGTH;
	sValues.charHp = CHAR_HP;
	sValues.enemyHp = ENEMY_HP;

	return sValues;
}

void main() {
	Room salita;
	GameVar bar = SetGame(1);

	PrintRoom(salita,10);
	CreateEnemies(salita, bar, 10);
	PrintDoor(salita,0,1,10);
	PrintEnemies(salita,10);

	system("pause");
}