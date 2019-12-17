#include <iostream>
#include <array>
#include <string>
#include <thread>

const int animationSpeed = 250;

//ASCII_Art.h > Da mensaje de bienvenida con un pergamino. Se adapta al tamaño del nombre del jugador y su nombre siempre aparecerá centrado.
void WelcomeMessage(std::string userName)
{
	const int laneLength = 39; //39char ocupa una fila del pergamino contando margin, border y paddin. 32char es el espacio interior sin contar bordes.
	std::array <char, laneLength> nameLane;
	int nameLength = userName.length();

	if (nameLength <= 32) //Debe caber en el pergamino
	{
		
		int sobrante = (laneLength - nameLength);
		int padding = (sobrante / 2);
		bool enterName = true;

		for (int i = 0; i < laneLength; i++)
		{
			if (i <= 3) { nameLane[i] = ' '; }
			else if (i == 4) { nameLane[i] = '|'; }
			else if (i > 4 && i <= padding) { nameLane[i] = ' '; } // 32char | interior |: padding izq 
			else if (i > padding && i < padding + nameLength && enterName == true) // 32char | interior |: name
			{
				int j = 0;
				for (; j < nameLength; j++)
				{
					nameLane[i + j] = userName[j];
				}
				enterName = false;
				i += (j - 1); //Necesario para evitar las iteraciones de i que se han avanzado dentro del for de j
			}
			else if (i == laneLength - 1) { nameLane[i] = '.'; }
			else if (i == laneLength - 2) { nameLane[i] = '|'; }
			else if (i > padding + nameLength) { nameLane[i] = ' '; } // 32char | interior |: padding der
		}

		//Art from: https://www.asciiart.eu/art-and-design/borders

		std::cout << "   __________________________________" << std::endl;
		std::cout << " / \\                                 \\." << std::endl;
		std::cout << "|   |           .:·ENTI·:.           |." << std::endl;
		std::cout << " \\_ |                                |." << std::endl;
		std::cout << "    |           BIENVENID@           |." << std::endl;
		std::cout << "    |          A LA DUNGEON          |." << std::endl;
		std::cout << "    |                                |." << std::endl;
		for (int i = 0; i < 39; i++) { std::cout << nameLane[i]; } std::cout << "\n";
		std::cout << "    |                                |." << std::endl;
		std::cout << "    |           ·:. o .:·            |." << std::endl;
		std::cout << "    |    ____________________________|____ " << std::endl;
		std::cout << "    |   /                                /." << std::endl;
		std::cout << "    \\_ /________________________________/." << std::endl;

	}
	else //No cabe en el pergamino
	{
		std::cout << "   __________________________________" << std::endl;
		std::cout << " / \\                                 \\." << std::endl;
		std::cout << "|   |           .:·ENTI·:.           |." << std::endl;
		std::cout << " \\_ |                                |." << std::endl;
		std::cout << "    |           BIENVENID@           |." << std::endl;
		std::cout << "    |                                |." << std::endl;
		std::cout << "    |          A LA DUNGEON          |." << std::endl;
		std::cout << "    |                                |." << std::endl;
		std::cout << "    |           ·:. o .:·            |." << std::endl;
		std::cout << "    |    ____________________________|____ " << std::endl;
		std::cout << "    |   /                                /." << std::endl;
		std::cout << "    \\_ /________________________________/." << std::endl;

		std::cout << "\n    USUARIO: " << userName <<std::endl;
	}

	
}

//ASCII_Art.h > Displaya en un libro las opciones del usuario. Libro: https://www.asciiart.eu/books/books
void PlayerMenuASCII()
{
	std::cout << "   .---------------------   --------------------- " << std::endl;
	std::cout << ".-/|                     \\ /                     |\\-. " << std::endl;
	std::cout << "||||   ELIGE UNA OPCIÓN   |                      |||| " << std::endl;
	std::cout << "||||       USUARIO        |                      |||| " << std::endl;
	std::cout << "||||                      |                      |||| " << std::endl;
	std::cout << "||||     --== 1 ==--      |                      |||| " << std::endl;
	std::cout << "||||   Crear personaje    |      _-·· 4 ··-_     |||| " << std::endl;
	std::cout << "||||                      |    Eliminar cuenta   |||| " << std::endl;
	std::cout << "||||                      |                      |||| " << std::endl;
	std::cout << "||||     ..~~ 2 ~~..      |                      |||| " << std::endl;
	std::cout << "||||   Listar personajes  |     ·:-=% 5 %=-:·    |||| " << std::endl;
	std::cout << "||||                      |      S A L I R       |||| " << std::endl;
	std::cout << "||||                      |                      |||| " << std::endl;
	std::cout << "||||     --<< 3 >>--      |                      |||| " << std::endl;
	std::cout << "||||  Eliminar personaje  |                      |||| " << std::endl;
	std::cout << "||||                      |                      |||| " << std::endl;
	std::cout << "||||_____________________ | _____________________|||| " << std::endl;
	std::cout << "||/======================\\|/=====================\\|| " << std::endl;
	std::cout << "`-----------------------~___~---------------------'' " << std::endl;
}

//ASCII_Art.h > Displaya en un libro las opciones del ADMIN. Libro: https://www.asciiart.eu/books/books
void AdminMenuASCII()
{
	std::cout << "   .---------------------   --------------------- " << std::endl;
	std::cout << ".-/|                     \\ /                     |\\-. " << std::endl;
	std::cout << "||||   ELIGE UNA OPCIÓN   |                      |||| " << std::endl;
	std::cout << "||||        ADMIN         |                      |||| " << std::endl;
	std::cout << "||||                      |                      |||| " << std::endl;
	std::cout << "||||     --== 1 ==--      |                      |||| " << std::endl;
	std::cout << "||||   Listar cuentas     |      _-·· 4 ··-_     |||| " << std::endl;
	std::cout << "||||     de jugador       |  Eliminar personaje  |||| " << std::endl;
	std::cout << "||||                      |     de un jugador    |||| " << std::endl;
	std::cout << "||||     ..~~ 2 ~~..      |                      |||| " << std::endl;
	std::cout << "||||   Eliminar cuenta    |     ·:-=% 5 %=-:·    |||| " << std::endl;
	std::cout << "||||     de jugador       |      S A L I R       |||| " << std::endl;
	std::cout << "||||                      |                      |||| " << std::endl;
	std::cout << "||||     --<< 3 >>--      |                      |||| " << std::endl;
	std::cout << "||||  Mostrar personajes  |                      |||| " << std::endl;
	std::cout << "||||    de un jugador     |                      |||| " << std::endl;
	std::cout << "||||_____________________ | _____________________|||| " << std::endl;
	std::cout << "||/======================\\|/=====================\\|| " << std::endl;
	std::cout << "`-----------------------~___~---------------------'' " << std::endl;
}


//ASCII_Art.h > Dragon sobrevuela campo hasta llegar a la DUNGEON ENTI. Dragon: https://www.asciiart.eu/mythology/dragons
void Animation()
{
	
	std::cout << "x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x" << std::endl;
	std::cout << "x                        \\`----._                  ____                      _                    x" << std::endl;
	std::cout << "x                         |       `--.___       <=#  , *--,                 (`  ).                x" << std::endl;
	std::cout << "x   _.-¨-_                /_             `-.    ,/  / `````               ((     ).               x" << std::endl;
	std::cout << "x  ((     )_                \\__             (_.'  ,'                   (_-(      '.               x" << std::endl;
	std::cout << "x (        _)                    \\__ ......'       \___----^_            (. (  ._ )                x" << std::endl;
	std::cout << "x  (   )  )                  _./                ,'           `._                                  x" << std::endl;
	std::cout << "x    (  )          |\\     _.'   ___/ )\\...._\"   ___             \\                                 x" << std::endl;
	std::cout << "x                  | \\__.'   _.'            `\"\"'   `\"\"`.'\"\"\"`- - \\                                x" << std::endl;
	std::cout << "x                  \\______.--'                                                                    x" << std::endl;
	std::cout << "x                                                                                                 x" << std::endl;
	std::cout << "x                                                                                                 x" << std::endl;
	std::cout << "x..._.--..-._.-_-.:-._--..,___.--,--'`,---..-.--+--.,,-,,..._.--..-._._-__--..,___.--,--'`-,-.._.:x" << std::endl;
	std::cout << "x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(animationSpeed));
	system("cls");

	std::cout << "x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x" << std::endl;
	std::cout << "x                              \\`----._                  ____             _                       x" << std::endl;
	std::cout << "x                               |       `--.___       <=#  , *--,        (`  ).                   x" << std::endl;
	std::cout << "x_.-¨-_                         /_             `-.    ,/  / `````      ((     ).                  x" << std::endl;
	std::cout << "x(     )_                         \\__             (_.'  ,'          (_-(      '.                  x" << std::endl;
	std::cout << "x       _)                             \\__ ......'       \___----^_   (. (  ._ )                   x" << std::endl;
	std::cout << "x   )  )                           _./                ,'           `._                            x" << std::endl;
	std::cout << "x (  )                   |\\     _.'   ___/ )\\...._\"   ___             \\                           x" << std::endl;
	std::cout << "x                        | \\__.'   _.'            `\"\"'   `\"\"`.'\"\"\"`- - \\                          x" << std::endl;
	std::cout << "x                        \\______.--'                                                              x" << std::endl;
	std::cout << "x                                                                                                 x" << std::endl;
	std::cout << "x                                                                                                 x" << std::endl;
	std::cout << "x-..-._.-_-.:-._--..,___.--,--'`,---..-.--+--.,,-,,..._.--..-._._-__--..,___.--,--'`-,-.._.:._.+-.x" << std::endl;
	std::cout << "x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(animationSpeed));
	system("cls");

	std::cout << "x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x" << std::endl;
	std::cout << "x                              \\`----._                  ____       _                             x" << std::endl;
	std::cout << "x                               |       `--.___       <=#  , *--,  (`  ).     D                   x" << std::endl;
	std::cout << "x                               /_             `-.    ,/  / `````((     ).                        x" << std::endl;
	std::cout << "x)_                               \\__             (_.'  ,'    (_-(      '.                        x" << std::endl;
	std::cout << "x _)                                   \\__ ......'       \___----^_(  ._ )                         x" << std::endl;
	std::cout << "x)                                 _./                ,'           `._                            x" << std::endl;
	std::cout << "x                        |\\     _.'   ___/ )\\...._\"   ___             \\                           x" << std::endl;
	std::cout << "x                        | \\__.'   _.'            `\"\"'   `\"\"`.'\"\"\"`- - \\                          x" << std::endl;
	std::cout << "x                        \\______.--'                                                              x" << std::endl;
	std::cout << "x                                                                                              [c]x" << std::endl;
	std::cout << "x                                                                                              [ ]x" << std::endl;
	std::cout << "x.-_-.:-._--..,___.--,--'`,---..-.--+--.,,-,,..._.--..-._._-__--..,___.--,--'`-,-.._.:._.+-.___[ ]x" << std::endl;
	std::cout << "x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(animationSpeed));
	system("cls");

	std::cout << "x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x" << std::endl;
	std::cout << "x                        \\`----._                  ____ _                                         x" << std::endl;
	std::cout << "x                         |       `--.___       <=#  , *--,).                 D U                 x" << std::endl;
	std::cout << "x                         /_             `-.    ,/  / ````` ).                                    x" << std::endl;
	std::cout << "x                           \\__             (_.'  ,'-(      '.                                    x" << std::endl;
	std::cout << "x                                \\__ ......'       \___----^_)                                     x" << std::endl;
	std::cout << "x                            _./                ,'           `._                                  x" << std::endl;
	std::cout << "x                  |\\     _.'   ___/ )\\...._\"   ___             \\                                 x" << std::endl;
	std::cout << "x                  | \\__.'   _.'            `\"\"'   `\"\"`.'\"\"\"`- - \\                                x" << std::endl;
	std::cout << "x                  \\______.--'                                                                    x" << std::endl;
	std::cout << "x                                                                                        [c]      x" << std::endl;
	std::cout << "x                                                                                        [ ] ___  x" << std::endl;
	std::cout << "x-._--..,___.--,--'`,---..-.--+--.,,-,,..._.--..-._._-__--..,___.--,--'`-,-.._.:._.+-.___[ ]| U | x" << std::endl;
	std::cout << "x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(animationSpeed));
	system("cls");

	std::cout << "x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x" << std::endl;
	std::cout << "x                  \\`----._                  ____       _                                         x" << std::endl;
	std::cout << "x                   |       `--.___       <=#  , *--,).                       D U N               x" << std::endl;
	std::cout << "x                   /_             `-.    ,/  / ````` ).                                          x" << std::endl;
	std::cout << "x                     \\__             (_.'  ,'-(      '.                                          x" << std::endl;
	std::cout << "x                          \\__ ......'       \___----^_)                                           x" << std::endl;
	std::cout << "x                      _./                ,'           `._                                        x" << std::endl;
	std::cout << "x            |\\     _.'   ___/ )\\...._\"   ___             \\                                       x" << std::endl;
	std::cout << "x            | \\__.'   _.'            `\"\"'   `\"\"`.'\"\"\"`- - \\                                      x" << std::endl;
	std::cout << "x            \\______.--'                                                                          x" << std::endl;
	std::cout << "x                                                                                  [c]         +  x" << std::endl;
	std::cout << "x                                                                                  [ ] ___   _:|:_x" << std::endl;
	std::cout << "x.,___.--,--'`,---..-.--+--.,,-,,..._.--..-._._-__--..,___.--,--'`-,-.._.:._.+-.___[ ]| U | |u U ux" << std::endl;
	std::cout << "x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(animationSpeed ));
	system("cls");

	std::cout << "x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x" << std::endl;
	std::cout << "x         \\`----._                  ____       _                                                  x" << std::endl;
	std::cout << "x          |       `--.___       <=#  , *--,).                                D U N G             x" << std::endl;
	std::cout << "x          /_             `-.    ,/  / ````` ).                                                   x" << std::endl;
	std::cout << "x            \\__             (_.'  ,'-(      '.                                                   x" << std::endl;
	std::cout << "x                 \\__ ......'       \___----^_)                                                    x" << std::endl;
	std::cout << "x             _./                ,'           `._                                                 x" << std::endl;
	std::cout << "x   |\\     _.'   ___/ )\\...._\"   ___             \\                                                x" << std::endl;
	std::cout << "x   | \\__.'   _.'            `\"\"'   `\"\"`.'\"\"\"`- - \\                                               x" << std::endl;
	std::cout << "x   \\______.--'                                                                                   x" << std::endl;
	std::cout << "x                                                                         [c]         +           x" << std::endl;
	std::cout << "x                                                                         [ ] ___   _:|:_   _[]   x" << std::endl;
	std::cout << "x--'`,---..-.--+--.,,-,,..._.--..-._._-__--..,___.--,--'`-,-.._.:._.+-.___[ ]| U | |u U u| [U ]  /x" << std::endl;
	std::cout << "x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(animationSpeed));
	system("cls");

	std::cout << "x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x" << std::endl;
	std::cout << "x`----._                  ____                                                                     x" << std::endl;
	std::cout << "x       `--.___       <=#  , *--,                                             D U N G E           x" << std::endl;
	std::cout << "x_             `-.    ,/  / `````                                                                 x" << std::endl;
	std::cout << "x \\__             (_.'  ,'                                                                      + x" << std::endl;
	std::cout << "x      \\__ ......'       \___----^_                                                             [c]x" << std::endl;
	std::cout << "x  _./                ,'           `._                                                         [ ]x" << std::endl;
	std::cout << "x_.'   ___/ )\\...._\"   ___             \\                                                       [c]x" << std::endl;
	std::cout << "x   _.'            `\"\"'   `\"\"`.'\"\"\"`- - \\                                                      [ ]x" << std::endl;
	std::cout << "x.--'                                                                                          [U]x" << std::endl;
	std::cout << "x                                                                   [c]         +            /    x" << std::endl;
	std::cout << "x                                                                   [ ] ___   _:|:_   _[]   /   _ x" << std::endl;
	std::cout << "x--..-.--+--.,,-,,..._.--..-._._-__--..,___.--,--'`-,-.._.:._.+-.___[ ]| U | |u U u| [U ]  /   { }x" << std::endl;
	std::cout << "x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(animationSpeed));
	system("cls");
		
	std::cout << "x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x" << std::endl;
	std::cout << "x-._                  ____                                                                        x" << std::endl;
	std::cout << "x   `--.___       <=#  , *--,                                                 D U N G E O         x" << std::endl;
	std::cout << "x          `-.    ,/  / `````                                                                     x" << std::endl;
	std::cout << "x_             (_.'  ,'                                                                     +     x" << std::endl;
	std::cout << "x  \\__ ......'       \___----^_                                                             [c]    x" << std::endl;
	std::cout << "x/                ,'           `._                                                         [ ]    x" << std::endl;
	std::cout << "x  ___/ )\\...._\"   ___             \\                                                       [c]    x" << std::endl;
	std::cout << "x.'            `\"\"'   `\"\"`.'\"\"\"`- - \\                                                      [ ]    x" << std::endl;
	std::cout << "x                                                                                          [U]    x" << std::endl;
	std::cout << "x                                                               [c]         +            /     \\  x" << std::endl;
	std::cout << "x                                                               [ ] ___   _:|:_   _[]   /   _   \\ x" << std::endl;
	std::cout << "x-.--+--.,,-,,..._.--..-._._-__--..,___.--,--'`-,-.._.:._.+-.___[ ]| U | |u U u| [U ]  /   { }   \\x" << std::endl;
	std::cout << "x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(animationSpeed));
	system("cls");

	std::cout << "x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x" << std::endl;
	std::cout << "x                 ____                                                                             x" << std::endl;
	std::cout << "x--.___       <=#  , *--,                                                     D U N G E O N       x" << std::endl;
	std::cout << "x      `-.    ,/  / `````                                                                         x" << std::endl;
	std::cout << "x          (_.'  ,'                                                                         +     x" << std::endl;
	std::cout << "x__ ......'       \___----^_                                                                [c]    x" << std::endl;
	std::cout << "x             ,'           `._                                                             [ ]    x" << std::endl;
	std::cout << "x_/ )\\...._\"   ___             \\                                                           [c]    x" << std::endl;
	std::cout << "x          `\"\"'   `\"\"`.'\"\"\"`- - \\                                                          [ ]    x" << std::endl;
	std::cout << "x                                                                                          [U]    x" << std::endl;
	std::cout << "x                                                               [c]         +            /     \\  x" << std::endl;
	std::cout << "x                                                               [ ] ___   _:|:_   _[]   /   _   \\ x" << std::endl;
	std::cout << "x-.--+--.,,-,,..._.--..-._._-__--..,___.--,--'`-,-.._.:._.+-.___[ ]| U | |u U u| [U ]  /   { }   \\x" << std::endl;
	std::cout << "x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(animationSpeed));
	system("cls");


	std::cout << "x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x" << std::endl;
	std::cout << "x             ____                                                                                x" << std::endl;
	std::cout << "x__       <=#  , *--,                                                         D U N G E O N       x" << std::endl;
	std::cout << "x  `-.    ,/  / `````                                                            E N T I          x" << std::endl;
	std::cout << "x      (_.'  ,'                                                                             +     x" << std::endl;
	std::cout << "x.....'       \___----^_                                                                    [c]    x" << std::endl;
	std::cout << "x         ,'           `._                                                                 [ ]    x" << std::endl;
	std::cout << "x\\...._\"   ___             \\                                                               [c]    x" << std::endl;
	std::cout << "x      `\"\"'   `\"\"`.'\"\"\"`- - \\                                                              [ ]    x" << std::endl;
	std::cout << "x                                                                                          [U]    x" << std::endl;
	std::cout << "x                                                               [c]         +            /     \\  x" << std::endl;
	std::cout << "x                                                               [ ] ___   _:|:_   _[]   /   _   \\ x" << std::endl;
	std::cout << "x-.--+--.,,-,,..._.--..-._._-__--..,___.--,--'`-,-.._.:._.+-.___[ ]| U | |u U u| [U ]  /   { }   \\x" << std::endl;
	std::cout << "x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x" << std::endl;
	
	std::this_thread::sleep_for(std::chrono::milliseconds(animationSpeed*6));

}
