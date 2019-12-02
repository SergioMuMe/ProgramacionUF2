#include "List.h"
#define INIT_ENEMIES 3
#define MAX_PUPPETS 3


enum typeRoom
{
	START,
	END,
	MASTER,
	PUPPET
};

struct Character
{
	int x;
	int y;
	int hp;
};

struct Room
{
	List<Character> liEnemies;
	Room* ptrN = nullptr;
	Room* ptrS = nullptr;
	Room* ptrE = nullptr;
	Room* ptrO = nullptr;
	Room* next = nullptr;
	typeRoom eRoom;
	bool aDoors[4];
	int sizeRoom;
};

struct Level
{
	List<Room> liRooms;
	int nRooms;
	int aPuppets[MAX_PUPPETS];
};


