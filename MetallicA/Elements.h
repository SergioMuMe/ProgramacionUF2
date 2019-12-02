#include "List.h"
#include <vector>
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
	//char ** room;
	//std::vector<std::vector<char>> room;
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

struct GameVar
{
	int maxRooms;
	int minRooms;
	int maxEnemy;
	int minEnemy;
	int	maxPuppets;
	int minPuppets;
	int maxPuppetLenght;
	int minPuppetLenght;
	int maxSize;
	int minSize;
	int charHp;
	int enemyHp;
};

