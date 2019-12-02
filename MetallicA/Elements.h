#include "List.h"
#include <vector>
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

