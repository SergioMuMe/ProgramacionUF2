#include <time.h>
#include <iostream>
#include <thread>
#include <array>

#include <conio.h>


#define KEY_UP 77
#define KEY_DOWN 75
#define KEY_LEFT 80
#define KEY_RIGHT 72
#define KEY_w 119
#define KEY_W 87
#define KEY_a 97
#define KEY_A 65
#define KEY_D 68
#define KEY_d 100
#define KEY_S 83
#define KEY_s 115


double clockToMilliseconds(clock_t ticks) {
	// units/(units/time) => time (seconds) * 1000 = milliseconds
	return (ticks / (double)CLOCKS_PER_SEC)*1000.0;
}


//...


const int width = 25, height = 25;
int maxSpawn = 1;
bool needNewList = false;


void initMap(char  (&map)[width][height], const int w, const int h)
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
		std::cout<<std::endl;
	}
}

struct Data {
	int x;
	int y;
};

struct Node {
	Node* next;
	Node* prev;
	Data data;
};

struct Lista {

	private:
	
		Node* front = nullptr;
		Node* tail = nullptr;
		

	public:
		
		int length = 0;

		void addNode() //Push
		{
			Node* node = new Node;
			length++;

			int xRand, yRand;

			//TODO: Evitar que se genere unas coordenadas ya usadas por: character or otro nodo.
			xRand = rand() % width;
			yRand = rand() % height;

			node->data.x = xRand;
			node->data.y = yRand;

			node->next = front;
			front = node;
		}

		void setNodeInMap(int characterX, int characterY, char(&map)[width][height])
		{
			Node* node = front;

			while (node->next != nullptr)
			{
				map[node->data.x][node->data.y] = '8';
				node = node->next;
			}
		}

		void removeNode(int maxSpawn, int characterX, int characterY, bool &needNewList)
		{
			
			Node* node = front;
			Node* aux;

						
			while (node->data.x != characterX && node->data.y != characterY)
			{
				node = node->next;
			}

			if (node == front) //Head
			{
				node = front; //node = oldfront
				front = front->next; //new front = id 1
				delete node; // delete oldfront
				length--;
				return;
			}
			else if (node == tail) //Last
			{
				aux = front;
				while (aux->next != tail)
				{
					aux = aux->next;
				}
				delete tail;
				tail = aux;
				aux->next = nullptr;
				length--;
				return;
			}
			else //Cualquier otro dentro de rango
			{
				aux = node->next; // aux = nodo a eliminar
				node->next = node->next->next; // Nodo [id-1] apunta a Nodo [id+1]
				delete aux; // delete nodo ID
				length--;
				return;
			}

			if (length == 0) { front = nullptr; }

			if (front == nullptr)
			{
				//TODO: Cuando se ha eliminan todos los nodos, marcar BOOL
				needNewList=true;
			}
			return;
			
		}
};



//Generar Lista de Bolas
void generarListaBolas(int &maxSpawn, int characterX, int characterY, char(&map)[width][height])
{
	maxSpawn = 2 * maxSpawn;
	Lista listaBolas;
		
	int count = 0;

	while (count <= maxSpawn)
	{
		listaBolas.addNode();
		listaBolas.setNodeInMap(characterX,characterY,map);
		count++;
	}

}


int 2()
{
	clock_t timer = 0;
	double deltaTime;0
	unsigned int frames = 0;
	double  frameRate = 120;
	
	Lista listaBolas;

	srand(time(NULL));

	char map[width][height];
	initMap(map,width,height);
	int characterX = height / 2;
	int characterY = width / 2;

	generarListaBolas(maxSpawn, characterX, characterY, map);
	

	clock_t time = 0;
	while (true) {

		
		std::chrono::high_resolution_clock::time_point beginFrame = std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		int c = 0;
		
			map[characterX][characterY] = '_';
			switch ((c = _getch())) {

			case KEY_UP:
				
				std::cout << std::endl << "Up" << std::endl;//key up
				characterY++;
				break;

			case KEY_DOWN:
				
				characterY--;
				std::cout << std::endl << "Down" << std::endl; // key down

				break;

			case KEY_LEFT:
				
				characterX++;
				std::cout << std::endl << "Left" << std::endl; // key left

				break;

			case KEY_RIGHT:
				
				characterX--;
				std::cout << std::endl << "Right" << std::endl; // key right

				break;

			default:

				std::cout << std::endl << c << "null" << std::endl; // not arrow

				break;

			}
			
			if (map[characterX][characterY] == '8')
			{
				listaBolas.removeNode(maxSpawn, characterX, characterY, needNewList);
			}

			map[characterX][characterY] = 'O';
			system("cls");			
			if (needNewList == true)
			{
				generarListaBolas(maxSpawn, characterX, characterY, map); 
				needNewList = false;
			}
			drawMap(map,width,height);
			
			
		std::chrono::high_resolution_clock::time_point endFrame = std::chrono::high_resolution_clock::now();

		deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(endFrame - beginFrame).count();
		timer += deltaTime;
		time += deltaTime;
		frames++;
		std::cout <<"Delta Time: " << deltaTime / 1000.0f << std::endl;
		std::cout << time/1000.0f << std::endl;
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