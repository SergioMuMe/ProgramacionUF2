#include <time.h>
#include <iostream>
#include <thread>
#include <array>
#include <conio.h>
#include "Elements.h"
#include "List.h"


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

int nextDoor;

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

GameVar SetGameVar(int choice)
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


void InitRoom(Level &level, GameVar var, typeRoom type)
{

	Room sala;
	sala.eRoom = type;
	sala.sizeRoom = var.minSize + (rand() % (var.maxSize - var.minSize + 1));
	int backDoor;

	level.liRooms.Add(sala);

	switch (type)
	{
	case START:
		int resta;

		nextDoor = rand() % 4;

		SetTilesRoom(level.liRooms.GetItem(level.liRooms.GetLength()), sala.sizeRoom);

		SetTilesDoor(level.liRooms.GetItem(level.liRooms.GetLength()), nextDoor, sala.sizeRoom);

		CreateEnemies(level.liRooms.GetItem(level.liRooms.GetLength()), var, sala.sizeRoom);

		SetTilesEnemies(level.liRooms.GetItem(level.liRooms.GetLength()), sala.sizeRoom);

		break;

	case END:

		if (nextDoor % 2 == 0)
		{
			backDoor = nextDoor + 1;
		}
		else
		{
			backDoor = nextDoor - 1;
		}

		level.liRooms.GetItem(level.liRooms.GetLength()).aDoors[backDoor] = &level.liRooms.GetBack()->data;

		level.liRooms.GetBack()->data.aDoors[nextDoor] = &level.liRooms.GetItem(level.liRooms.GetLength());

		SetTilesRoom(level.liRooms.GetItem(level.liRooms.GetLength()), sala.sizeRoom);

		SetTilesDoor(level.liRooms.GetItem(level.liRooms.GetLength()), backDoor, sala.sizeRoom);

		break;

	case MASTER:

		if (nextDoor % 2 == 0)
		{
			backDoor = nextDoor + 1;
		}
		else
		{
			backDoor = nextDoor - 1;
		}

		level.liRooms.GetItem(level.liRooms.GetLength()).aDoors[backDoor] = &level.liRooms.GetBack()->data;

		level.liRooms.GetBack()->data.aDoors[nextDoor] = &level.liRooms.GetItem(level.liRooms.GetLength());

		do
		{
			nextDoor = rand() % 4;
		} while (nextDoor == backDoor);

		SetTilesRoom(level.liRooms.GetItem(level.liRooms.GetLength()), sala.sizeRoom);

		SetTilesDoor(level.liRooms.GetItem(level.liRooms.GetLength()), nextDoor, backDoor, sala.sizeRoom);

		CreateEnemies(level.liRooms.GetItem(level.liRooms.GetLength()), var, sala.sizeRoom);

		SetTilesEnemies(level.liRooms.GetItem(level.liRooms.GetLength()), sala.sizeRoom);

		break;

	case PUPPET:

		if (nextDoor % 2 == 0)
		{
			backDoor = nextDoor + 1;
		}
		else
		{
			backDoor = nextDoor - 1;
		}

		level.liRooms.GetItem(level.liRooms.GetLength()).aDoors[backDoor] = &level.liRooms.GetBack()->data;

		level.liRooms.GetBack()->data.aDoors[nextDoor] = &level.liRooms.GetItem(level.liRooms.GetLength());

		SetTilesRoom(level.liRooms.GetItem(level.liRooms.GetLength()), sala.sizeRoom);

		SetTilesDoor(level.liRooms.GetItem(level.liRooms.GetLength()), nextDoor, backDoor, sala.sizeRoom);

		CreateEnemies(level.liRooms.GetItem(level.liRooms.GetLength()), var, sala.sizeRoom);

		SetTilesEnemies(level.liRooms.GetItem(level.liRooms.GetLength()), sala.sizeRoom);

		break;
	}
	/*
	RANDS:
	-- Size
	-- Enemy
	--
	*/
	
}


//TODO: Buscar y sustituir en todos lados, var=>sValues;
Level InitMap(GameVar var)
{
	Level level;
	level.aPuppets.reserve (var.maxPuppets);
	int	puppets = rand() % var.maxPuppets + var.minPuppets;
	level.nRooms = rand() % var.maxRooms + var.minRooms;

	for (size_t i = 0; i < puppets; i++)
	{
		level.aPuppets.emplace_back(rand() % var.maxPuppetLength + var.minPuppetLength);
		//TODO PREGUNTAR: Preguntar Jose PQ NO FUNKAAAA!!!!
		//level.aPuppets[i] = rand() % var.maxPuppetLength + var.minPuppetLength;
	}
 
	
	
	// Generamos el Golden Path: START -> N salas MASTER -> END
	for (size_t i = 0; i < level.nRooms; i++)
	{
		if (i <= 0)
		{
			InitRoom(level, var, typeRoom::START);
		}else if (i > 0 && i != level.nRooms-1)
		{
			InitRoom(level, var, typeRoom::MASTER);	
		}
		else {
			InitRoom(level, var, typeRoom::END);
		}
		
	}	


	// Generamos la primera sala de cada una de las ramificaciones. typeRoom::PUPPET
	for (size_t i = 0; i < level.aPuppets.size(); i++)
	{
		// closedDoors: Puertas ocupadas. Son aquellas que existen y llevan a algún sitio.
		int closedDoors = 0;
		
		int masterIndex;
		int linkDoor;

		Room firstRoom;

		int backDoor;

		firstRoom.eRoom = typeRoom::PUPPET;

		firstRoom.sizeRoom = var.minSize + (rand() % (var.maxSize - var.minSize + 1));

		level.liRooms.Add(firstRoom);

		do
		{

			closedDoors = 0;
			// Obtenemos una sala MASTER random. Excluimos la END al restar -1 a nRooms. Excluimos la START al sumar +1 al resultado. 

			masterIndex = (rand() % (level.nRooms - 1)) + 1;

			// Iteramos por cada posible puerta: Norte, Sur, Este, Oeste
			for (size_t i = 0; i < 4; i++)
			{
				// Revisamos: Si la puerta es igual a NULL, podemos colocar una puerta.
				if (level.liRooms.GetItem(masterIndex).aDoors[i] == nullptr)
				{
					// ALERTA: Generamos la puerta aleatoria? Ya sabemos que la [i] está disponible.
					do
					{
						linkDoor = rand() % 4;
					} while (level.liRooms.GetItem(masterIndex).aDoors[linkDoor] != nullptr);

					SetTilesDoor(level.liRooms.GetItem(masterIndex), linkDoor, level.liRooms.GetItem(masterIndex).sizeRoom);

					level.liRooms.GetItem(masterIndex).aDoors[linkDoor] = &level.liRooms.GetItem(level.liRooms.GetLength());

					nextDoor = linkDoor;
					i = 4;//break
				}
				else
				{
					closedDoors++;
				}


				/*
				
				*/


			}
		} while (closedDoors >= 4);

		Room masterRoom = level.liRooms.GetItem(masterIndex);

		//Crear una primera sala a pelo
		//Vincularlo a master



		if (nextDoor % 2 == 0)
		{
			backDoor = nextDoor + 1;
		}
		else
		{
			backDoor = nextDoor - 1;
		}

		SetTilesRoom(firstRoom, firstRoom.sizeRoom);

		SetTilesDoor(firstRoom, backDoor, firstRoom.sizeRoom);

		firstRoom.aDoors[backDoor] = &level.liRooms.GetItem(masterIndex);

		

		for (size_t j = 1; j < level.aPuppets[i]; j++)
		{
			InitRoom(level, var, typeRoom::PUPPET);
		}

		Room endRoom;

		if (nextDoor % 2 == 0)
		{
			backDoor = nextDoor + 1;
		}
		else
		{
			backDoor = nextDoor - 1;
		}

		endRoom.eRoom = typeRoom::PUPPET;

		endRoom.sizeRoom = var.minSize + (rand() % (var.maxSize - var.minSize + 1));

		level.liRooms.Add(endRoom);

		endRoom.aDoors[backDoor] = &level.liRooms.GetBack()->data;

		level.liRooms.GetBack()->data.aDoors[nextDoor] = &level.liRooms.GetItem(level.liRooms.GetLength());

		SetTilesRoom(endRoom, endRoom.sizeRoom);

		SetTilesDoor(endRoom, backDoor, endRoom.sizeRoom);

		

	}

	return level;
}





void PrintDataMap()
{
	//Rúbrica 2.c
}

void menu() 
{
	/*
	Modificamos la opción propuesta en el enunciado (3 - Salir) por (0 - Salir).
	Motivos:
	- En el teclado, alejamos la opcion de salida (0) de las opciones de nivel (1-2). 
	Evitamos favorecer input no deseada por parte del user.
	- En caso de querer, podemos aprovechar la opción 3 para otro nivel de dificultad. 
	*/

	std::cout << "MENU" << std::endl;
	std::cout << "0:---------------:0" << std::endl;
	std::cout << "1. Nivel basico" << std::endl;
	std::cout << "2. Nivel inferno" << std::endl; 
	std::cout << "0:---------------:0" << std::endl;
	std::cout << "\n\n" << std::endl;
	std::cout << "0. Salir" << std::endl;
}

void menu2()
{
	//2.C De la rúbrica HACER QUE FUNCIONE
	std::cout << "MENU" << std::endl;
	std::cout << "0:---------------:0" << std::endl;
	std::cout << "1. Mostrar datos" << std::endl;
	std::cout << "2. Jugar nivel" << std::endl;
	std::cout << "0:---------------:0" << std::endl;
	std::cout << "\n\n" << std::endl;
	std::cout << "0. Salir" << std::endl;
}


bool Init()
{
	menu();
	int choice;
	std::cin >> choice;
	if(choice == 0)
	{
		//cerrar programa
		return false;
	}
	InitMap(SetGameVar(choice));
}

void gameLoop() 
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
		int key = 0;

		map[characterX][characterY] = '_';
		if (_kbhit()) {
			switch ((key = _getch())) {

			case KEY_UP:

				std::cout << std::endl << "Up" << std::endl;//key up
				characterX--; //player.x=PlayerMovement(player.x, sala, key, player);
				break;

			case KEY_DOWN:
				characterX++; //player.x=PlayerMovement(player.x, sala, key, player);
				std::cout << std::endl << "Down" << std::endl; // key down

				break;

			case KEY_LEFT:
				characterY--; //player.y=PlayerMovement(player.y, sala, key, player);
				std::cout << std::endl << "Left" << std::endl; // key left

				break;

			case KEY_RIGHT:
				characterY++; //player.y=PlayerMovement(player.y, sala, key, player);
				std::cout << std::endl << "Right" << std::endl; // key right

				break;

			default:

				std::cout << std::endl << key << "null" << std::endl; // not arrow

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

void destroy()
{

}

int main()
{
	srand(time(NULL));
	if (!Init()) {
		return 0;
	}
	gameLoop();
	destroy();
	return 0;
}