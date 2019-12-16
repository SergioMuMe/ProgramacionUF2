#include <vector>
#include "List.h"

#define MAX_ROOMS 7
#define MIN_ROOMS 5
#define MAX_SIZE 30
#define MIN_SIZE 20
#define MAX_ENEMY 5
#define MIN_ENEMY 3
#define MAX_PUPPETS 3
#define MIN_PUPPETS 2
#define MAX_PUPPET_LENGTH 3
#define MIN_PUPPET_LENGTH 1
#define CHAR_HP 5
#define ENEMY_HP 15


/*
Start = Sala inicial.
End = Sala final.
Master = Golden Path. Salas principales.
Puppet = Rama dungeon.
*/
enum typeRoom {	START, END, MASTER,	PUPPET };

enum cardinalDoor {	NORTH, SOUTH, EAST, WEST };

struct Character
{
	int x;
	int y;
	int hp;
};

struct Room
{
	List<Character> liEnemies;
	
	/*Room* ptrN = nullptr;
	Room* ptrS = nullptr;
	Room* ptrE = nullptr;
	Room* ptrO = nullptr;*/
	
	
	Room* aDoors[4];

	//bool aDoors[4];
	
		
	//char ** room;

	std::vector<std::vector<char>> roomMap;
	
	
	//Tipo de sala
	typeRoom eRoom;

	//Tamaño de la sala, al ser cuadrada guardamos un único valor.
	int sizeRoom;
};

//aDoors2[CardinalPoints::NORTH]


/*Nivel del juego.*/
struct Level
{
	/*Lista de habitaciones*/
	List<Room> liRooms;
	
	/*Cantidad de habitaciones que hay en el nivel*/
	int nRooms;
	
	std::vector<int> aPuppets;
};

struct GameVar
{
	int maxRooms;
	int minRooms;
	int maxSize;
	int minSize;
	int maxEnemy;
	int minEnemy;
	int	maxPuppets;
	int minPuppets;
	int maxPuppetLength;
	int minPuppetLength;
	
	int charHp;
	int enemyHp;
};

void SetTilesRoom(Room &sala, int size);

void SetTilesDoor(Room &sala, int frontDoor, int backDoor, int size);

void SetTilesDoor(Room &sala, int frontDoor, int size);

void CreateEnemies(Room &sala, GameVar var, int size);

void SetTilesEnemies(Room &sala, int size);

