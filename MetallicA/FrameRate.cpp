#include <time.h>
#include <iostream>
#include <thread>
#include <array>
#include <conio.h>
#include <string>

#include "ASCII_Art.h"
#include "Elements.h"
#include "List.h"
#include "FrameRate.h"

/*
:::GRUPO:::

- MARC CAYMEL
- ROGER BUJAN
- SERGIO MURILLO
*/

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

void IntroContinue() 
{
	std::cout << "\nIntro para continuar." << std::endl;
	std::cin.ignore();
	std::cin.get();
}

double clockToMilliseconds(clock_t ticks) {
	// units/(units/time) => time (seconds) * 1000 = milliseconds
	return (ticks / (double)CLOCKS_PER_SEC)*1000.0;
}
//...

void drawMap(Room &actualRoom, Character player)
{
	for (size_t i = 0; i < actualRoom.sizeRoom; i++)
	{
		for (size_t j = 0; j < actualRoom.sizeRoom; j++)
		{
			if (i == player.x && j == player.y)
			{
				std::cout << PLAYER_CHAR;
			}
			else 
			{ 
				std::cout << actualRoom.roomMap[i][j];
			}
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
	permitiendo añadir nuevos cases, añadir nuevos multiplicadores, cambiar las multiplicaciones por funciones logaritmicas, etc.
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
	sValues.charHp = PLAYER_HP;
	sValues.enemyHp = ENEMY_HP;

	return sValues;
}


void InitRoom(Level &level, GameVar var, typeRoom type)
{

	// Declaramos e iniciamos la asignación de valores a la sala
	Room sala;
	sala.eRoom = type;
	sala.sizeRoom = var.minSize + (rand() % (var.maxSize - var.minSize + 1));

	// La puerta para volver a la sala anterior. La usaremos para definir una de las posiciones en aDoors.
	int backDoor;
	
	// Definimos el ID de la sala. Los IDs corresponden al tamaño de la lista (actualmente 0 ya que aun no se ha añadido) + 1
	sala.id = level.liRooms.GetLength() + 1;
	
	// Añadimos la sala
	level.liRooms.Add(sala);
	

	switch (type)
	{
	case START:

		// Seleccionamos la puerta de salida para la sala.
		nextDoor = rand() % 4;


		// Set de funciones para crear una sala con enemigos
		SetTilesRoom(level, sala.sizeRoom);

		SetTilesDoor(level.liRooms.GetItem(level.liRooms.GetLength()), nextDoor, sala.sizeRoom);

		CreateEnemies(level.liRooms.GetItem(level.liRooms.GetLength()), var, sala.sizeRoom);

		SetTilesEnemies(level.liRooms.GetItem(level.liRooms.GetLength()), sala.sizeRoom);

		break;

	case END:

		/*
		aDoor[4]: Las puertas cardinales estan consecutivas según su oposición:
		[0] Norte
		[1] Sur

		[2] Este
		[3] Oeste

		Por lo tanto. Si la puerta nextDoor es PAR. Su contrario (backDoor) será la siguiente posición en la array aDoors.
		*/
		if (nextDoor % 2 == 0)
		{
			backDoor = nextDoor + 1;
		}
		else
		{
			backDoor = nextDoor - 1;
		}

		// Vinculamos la sala actual con la anterior por la backDoor
		level.liRooms.GetItem(level.liRooms.GetLength()).aDoors[backDoor] = &level.liRooms.GetBack()->data;

		// Vinculamos la sala anterior con la creada por la nextDoor.... 
		level.liRooms.GetBack()->data.aDoors[nextDoor] = &level.liRooms.GetItem(level.liRooms.GetLength());

		// Set de funciones para crear una sala SIN enemigos
		SetTilesRoom(level, sala.sizeRoom);

		SetTilesDoor(level.liRooms.GetItem(level.liRooms.GetLength()), backDoor, sala.sizeRoom);

		break;

	case MASTER:

		// Seleccionamos random la puerta que vamos a usar para avanzar a la siguiente sala.
		if (nextDoor % 2 == 0)
		{
			backDoor = nextDoor + 1;
		}
		else
		{
			backDoor = nextDoor - 1;
		}

		// Vinculamos la sala actual con la anterior por la backDoor
		level.liRooms.GetItem(level.liRooms.GetLength()).aDoors[backDoor] = &level.liRooms.GetBack()->data;

		// Vinculamos la sala anterior con la creada por la nextDoor.... 
		level.liRooms.GetBack()->data.aDoors[nextDoor] = &level.liRooms.GetItem(level.liRooms.GetLength());
		
		// ...Si la sala anterior es la START, ya viene desde allí inicializada. Sino, la generamos a continuación para la siguiente iteración de sala MASTER/END.
		do
		{
			nextDoor = rand() % 4;
		} while (nextDoor == backDoor);


		// Set de funciones para crear una sala con enemigos
		SetTilesRoom(level, sala.sizeRoom);

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

		do
		{
			nextDoor = rand() % 4;
		} while (nextDoor == backDoor);

		SetTilesRoom(level, sala.sizeRoom);

		SetTilesDoor(level.liRooms.GetItem(level.liRooms.GetLength()), nextDoor, backDoor, sala.sizeRoom);

		CreateEnemies(level.liRooms.GetItem(level.liRooms.GetLength()), var, sala.sizeRoom);

		SetTilesEnemies(level.liRooms.GetItem(level.liRooms.GetLength()), sala.sizeRoom);

		break;
	}
}


//TODO: Buscar y sustituir en todos lados, var=>sValues;
Level InitMap(GameVar var)
{

	/* ---------------  */
	/*   GOLDEN PATH    */
	/* ---------------  */

	Level level;
	
	// Cantidad de ramificaciones que habrá.
	int	puppets = rand() % var.maxPuppets + var.minPuppets;

	// Reserva los PUPPETS que vamos a tener.
	level.aPuppets.reserve (puppets);
	
	level.nRooms = rand() % var.maxRooms + var.minRooms;

	// Definimos la cantidad de salas por cada una de las ramificaciones.
	for (size_t i = 0; i < puppets; i++)
	{
		level.aPuppets.emplace_back(rand() % var.maxPuppetLength + var.minPuppetLength);
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

	/* ---------  */
	/*   PUPPETS  */
	/* ---------  */

	// Generamos la primera sala de cada una de las ramificaciones. typeRoom::PUPPET
	// Al tener el size, iteramos.
	for (size_t i = 0; i < level.aPuppets.size(); i++)
	{
		// closedDoors: Puertas ocupadas. Son aquellas que existen y llevan a algún sitio.
		int closedDoors = 0;
		
		int masterIndex;
		
		// Puerta por la que desde el MASTER pasamos al PUPPET
		int linkDoor;

		/* --------------------- */
		/* PUPPET: PRIMERA SALA */
		/* --------------------- */

		Room firstRoom;

		int backDoor;

		// Creamos la sala
		firstRoom.eRoom = typeRoom::PUPPET;

		firstRoom.sizeRoom = var.minSize + (rand() % (var.maxSize - var.minSize + 1));

		level.liRooms.Add(firstRoom);


		do
		{
			// Inicializamos a 0 las puertas ocupadas.
			closedDoors = 0;
			
			// Obtenemos una sala MASTER random. Excluimos la END al restar -1 a nRooms. Excluimos la START al sumar +1 al resultado. 
			masterIndex = (rand() % (level.nRooms - 1)) + 1;

			// Iteramos por cada posible puerta: Norte, Sur, Este, Oeste
			for (size_t i = 0; i < 4; i++)
			{
				// Revisamos: Si la puerta es igual a NULL, sabemos que hay una puerta libre.
				if (level.liRooms.GetItem(masterIndex).aDoors[i] == nullptr)
				{
					// Como sabemos que hay un hueco, lanzamos una tirada aleatoria para que busque en todos los posibles huecos
					// No tiene porque ser la que se ha comprovado en el if anterior...
					do
					{
						linkDoor = rand() % 4;
					} while (level.liRooms.GetItem(masterIndex).aDoors[linkDoor] != nullptr);

					//...Una vez escogida la puerta...

					// Pintamos la puerta
					SetTilesDoor(level.liRooms.GetItem(masterIndex), linkDoor, level.liRooms.GetItem(masterIndex).sizeRoom);

					// Y la vinculamos a la posicion de memoria de la sala que corresponda
					level.liRooms.GetItem(masterIndex).aDoors[linkDoor] = &level.liRooms.GetItem(level.liRooms.GetLength());

					//Guardamos la posicion linkDoor para usar en siguientes iteraciones de otros PUPPETS.
					nextDoor = linkDoor;
					i = 4;//break
				}
				else
				{
					// Si todas las puertas estan ocupadas, volvemos a buscar un master random
					closedDoors++;
				}


			}
		} while (closedDoors >= 4);


		// Una vez modificado el master, pasamos a trabajar sobre el PUPPET....

		// 
		if (nextDoor % 2 == 0)
		{
			backDoor = nextDoor + 1;
		}
		else
		{
			backDoor = nextDoor - 1;
		}

		do
		{
			nextDoor = rand() % 4;
		} while (nextDoor == backDoor);

		SetTilesRoom(level, firstRoom.sizeRoom);

		SetTilesDoor(level.liRooms.GetItem(level.liRooms.GetLength()), backDoor, firstRoom.sizeRoom);

		CreateEnemies(level.liRooms.GetItem(level.liRooms.GetLength()), var, firstRoom.sizeRoom);

		SetTilesEnemies(level.liRooms.GetItem(level.liRooms.GetLength()), firstRoom.sizeRoom);

		level.liRooms.GetItem(level.liRooms.GetLength()).aDoors[backDoor] = &level.liRooms.GetItem(masterIndex);

		/* ------------------------- */
		/* PUPPET: SALAS INTERMEDIAS */
		/* ------------------------- */


		// Inicializamos j=1 ya que j=0 es la sala PUPPET INICIAL ya creada. 
		for (size_t j = 1; j < level.aPuppets[i]; j++)
		{
			InitRoom(level, var, typeRoom::PUPPET);
		}

		/* ----------------------------------- */
		/* PUPPET: SALA FINAL DE RAMIFICACION  */
		/* ----------------------------------- */

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

		level.liRooms.GetItem(level.liRooms.GetLength()).aDoors[backDoor] = &level.liRooms.GetBack()->data;

		level.liRooms.GetBack()->data.aDoors[nextDoor] = &level.liRooms.GetItem(level.liRooms.GetLength());

		SetTilesRoom(level, endRoom.sizeRoom);

		SetTilesDoor(level.liRooms.GetItem(level.liRooms.GetLength()), backDoor, endRoom.sizeRoom);

		CreateEnemies(level.liRooms.GetItem(level.liRooms.GetLength()), var, endRoom.sizeRoom);

		SetTilesEnemies(level.liRooms.GetItem(level.liRooms.GetLength()), endRoom.sizeRoom);

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
	system("cls");
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
	//2.C De la rúbrica
	system("cls");
	std::cout << "MENU" << std::endl;
	std::cout << "0:---------------:0" << std::endl;
	std::cout << "1. Mostrar datos" << std::endl;
	std::cout << "2. Jugar nivel" << std::endl;
	std::cout << "0:---------------:0" << std::endl;
	std::cout << "\n\n" << std::endl;
	std::cout << "0. Salir" << std::endl;
}

bool choose2(Level sLevel)
{
	menu2();
	int choice2;
	std::cin >> choice2;

	switch (choice2)
	{
	case 1:
		//Mostrar los datos del nivel
		system("cls");
		for (size_t i = 0; i <= sLevel.liRooms.GetLength() ; i++)
		{
			std::string doorData[4];
			
			//Guardamos los datos de la habitación en una variable temporal para no iterar por cada dato
			Room tempRoom = sLevel.liRooms.GetItem(i);
			
			std::string sTypeRoom;
			switch (tempRoom.eRoom)
			{
				case typeRoom::START:
					sTypeRoom = "Start";
					break;
				case typeRoom::END:
					sTypeRoom = "End";
					break;
				case typeRoom::MASTER:
					sTypeRoom = "Master";
					break;
				case typeRoom::PUPPET:
					sTypeRoom = "Puppet";
					break;
			}
			
			std::cout << "\n::::--------------------------------:::: " << std::endl;
			std::cout << " *** DATOS SALA [id." << tempRoom.id << "] *** " << std::endl;
			std::cout << "Tipo de sala: " << sTypeRoom << std::endl;
			std::cout << "Costado: " << tempRoom.sizeRoom << " casillas." << std::endl;
			for (size_t j = 0; j < 4; j++)
			{
				if (tempRoom.aDoors[j] == nullptr) 
				{
					doorData[j] = "No existe";
				}
				else 
				{
					doorData[j] = std::to_string(tempRoom.aDoors[j]->id);
				}
			}
			std::cout << "Puerta norte: " << doorData[0] << std::endl;
			std::cout << "Puerta sur: " << doorData[1] << std::endl;
			std::cout << "Puerta este: " << doorData[2] << std::endl;
			std::cout << "Puerta oeste: " << doorData[3] << std::endl;
			std::cout << "Cantidad enemigos: " << tempRoom.liEnemies.GetLength() << std::endl;

		}
		std::cout << "\n\n\n";
		IntroContinue();
		return false;
	case 2:
		//Jugar el nivel(seguir)
		return false;
	case 0:
		//salir scope
		return true;
	}
}

bool Init(Level &level)
{
	int choice;
	
	do
	{
		menu();
		
		std::cin >> choice;
		if (choice == 0)
		{
			//cerrar programa
			return false;
		}

		level = InitMap(SetGameVar(choice));
		
	} while (choose2(level));

	// LLAMAR FUNCION PARA EL JUEGO argumento: level
		
}

void InitPlayerPos(Character &player, Room* &actualRoom) 
{
	player.x = actualRoom->sizeRoom / 2;
	player.y = actualRoom->sizeRoom / 2;
}

void gameLoop(Level &level) 
{
	/* VARIABLES FRAMERATE */
	clock_t timer = 0;
	double deltaTime;
	unsigned int frames = 0;
	double  frameRate = 240;

	clock_t time = 0;

	/* INIT PLAYER */
	Character player;
	player.hp = PLAYER_HP;

	Room* actualRoom;

	actualRoom = &level.liRooms.GetStart()->data;

	InitPlayerPos(player, actualRoom);

	while (true) {


		std::chrono::high_resolution_clock::time_point beginFrame = std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		int key = 0;
		
		if (_kbhit()) {
			switch ((key = _getch())) {

			case KEY_UP:
				PlayerMovement(player.y, *actualRoom, key, player);
				break;

			case KEY_DOWN:
				PlayerMovement(player.y, *actualRoom, key, player);
				break;

			case KEY_LEFT:
				PlayerMovement(player.x, *actualRoom, key, player);
				break;

			case KEY_RIGHT:
				PlayerMovement(player.x, *actualRoom, key, player);
				break;

			default:
				std::cout << std::endl << key << "null" << std::endl; // not arrow
				break;
			}

		}

		if (actualRoom->roomMap[player.x][player.y] == '#')
		{
			if (player.x < actualRoom->sizeRoom/4)
			{
				actualRoom = actualRoom->aDoors[0];
				InitPlayerPos(player, actualRoom);
			}
			else if (player.x > actualRoom->sizeRoom*3/4)
			{
				actualRoom = actualRoom->aDoors[1];
				InitPlayerPos(player, actualRoom);
			}
			else if (player.y > actualRoom->sizeRoom*3/4)
			{
				actualRoom = actualRoom->aDoors[2];
				InitPlayerPos(player, actualRoom);
			}
			else if (player.y < actualRoom->sizeRoom / 4)
			{
				actualRoom = actualRoom->aDoors[3];
				InitPlayerPos(player, actualRoom);
			}
		}
		std::cout << "\n\n\n\n";
		drawMap(*actualRoom, player);

		// PASO 1 - VERIFICAR SI HA TOCADO UNA PUERTA



		// PASO 2 - VIAJAR A LA SALA DE ESA PUERTA


		

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
		system("cls");
	}
}

void seekAndDestroy(Level &level)
{
	for (size_t i = 0; i < level.liRooms.GetLength(); i++)
	{
		level.liRooms.GetItem(i).liEnemies.Clear();
	}
	level.liRooms.Clear();
}

int main()
{
	Level level;

	srand(time(NULL));

	//Animation();

	if (!Init(level)) {
		/*gameLoop(level);

		return 0;*/
	}

	
	seekAndDestroy(level);
	return 0;
}