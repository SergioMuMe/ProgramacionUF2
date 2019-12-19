#include <vector>
#include "List.h"

//1.d Utilización de constantes para parametrizar
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

#define PLAYER_HP 20
#define ENEMY_HP 15

#define PLAYER_CHAR '$'
#define ENEMY_CHAR '@'

//1.a Diseño correcto de las estructuras de datos
//1.b Código separado en al menos dos ficheros

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

// Struct de una sala
struct Room
{
	//Lista de enemigos de la sala.
	List<Character> liEnemies;
	

	// Punteros a las salas colindantes (navegaciñn de Personaje).
	// Room* aDoors[4] = {Norte, Sur, Este, Oeste}
	Room* aDoors[4] = { nullptr,nullptr,nullptr,nullptr };


	//Punteros a las salas colindantes (navegaciñn de Personaje).
	//Room* aDoors[4];

	//Mapa de la sala.

	// Mapa de la sala.

	std::vector<std::vector<char>> roomMap;
	
	// Tipo de sala.
	typeRoom eRoom;

	// Tamaño de la sala, al ser cuadrada guardamos un único valor.
	int sizeRoom;
	//TO DO: Añadir a la creacion de salas
	int id;
};



//Struct del nivel del juego
struct Level
{
	/*Lista de habitaciones*/
	List<Room> liRooms;
	
	// Cantidad de habitaciones que hay en el nivel (START, END, MASTER). No tiene en cuenta el nñ de habitaciones en ramificaciñn (PUPPETS)
	int nRooms;
	
	// Array dinamico de ramificaciones. La posiciñn indica el nñ de ramificaciñn. El valor INT indica la cantidad de salas en esa ramificaciñn. Ej: aPuppets[6] = El nivel tendrñ 6 ramificaciones.
	std::vector<int> aPuppets;
};

//Struct de parametros para generar el nivel. Estos parametros se ven modificados por constantes. La modificaciñn es dada por el nivel de dificultad.
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

// Pone todas las baldosas del suelo dada una sala y su tamaño.
void SetTilesRoom(Level &level, int size);

//Sobrecarga para repintar el suelo del mapa.
void SetTilesRoom(Room &room, int size);

// Pone todas las puertas dada una sala: Cuando la sala tiene mñs de 1 puerta.
void SetTilesDoor(Room &sala, int frontDoor, int backDoor, int size);

// Pone todas las puertas dada una sala: Cuando la sala tiene una ñnica puerta.
void SetTilesDoor(Room &sala, int frontDoor, int size);

//Sobrecarga para pintar todas las puertas si las tiene.
void SetTilesDoor(Room &sala, int size);

// Crea las posiciones de los enemigos de la sala: La distancia entre el player y el enemigo debe ser mayor o igual a 1/4 del size de la sala. Dado el azar, los enemigos pueden superponerse a si mismos o a puertas.
void CreateEnemies(Room &sala, GameVar var, int size);

// Pone a los enemigos sobre el mapa.
void SetTilesEnemies(Room &sala, int size);


int PathFinding(Character &enemy, Character player);

int PlayerMovement(int num, Room sala, int key, Character &player);

