
#define maxBalls 6
#define initEnemies 3

enum tipoSala
{
	ENTRADA,
	SALIDA,
	PRINCIPAL,
	RAMIFICACION
};


struct Balls
{
	int id;
	int x;
	int y;

};

struct Player
{
	int x;
	int y;
	int hp;
};

struct Enemies
{
	int id;
	int x;
	int y;
	int hp;

	void MoveEnemy()
	{
		//Mira la distancia del jugador X e Y. La distancia más lejana, la intentas igualar a la del jugador (+/-)
	}

	void DestroyEnemy()
	{
		
	}
	
};


