#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "Elements.h"

#define MOVIMIENTO_ENEMIGO 1

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

enum GoTo { EjeX, EjeY };
GoTo eje;

//Pathfinding Enemigo + realiza movimiento
int PathFinding(Character &enemy, Character player, /*Testing ->*/ bool gameLoop)
{	

	//Si ningún eje coincide con el de player, coge un eje al azar.
	if (enemy.x != player.x && enemy.y != player.y)
	{	
		rand() % 2 == 0 ? eje = EjeX : eje = EjeY;
	}
	//...Sino, mira si el eje X es distinto, coge el eje X.
	else if (enemy.x != player.x){eje = EjeX;}
	//...Sino, coge el eje Y.
	else {eje = EjeY;}


	//Movimiento del enemigo en el Eje seleccionado
	switch (eje)
	{
	case EjeX:
		if (enemy.x > player.x) { enemy.x -= MOVIMIENTO_ENEMIGO; }
		if (enemy.x < player.x) { enemy.x += MOVIMIENTO_ENEMIGO; }
		break;
	case EjeY:
		if (enemy.y > player.y) { enemy.y -= MOVIMIENTO_ENEMIGO; }
		if (enemy.y < player.y) { enemy.y += MOVIMIENTO_ENEMIGO; }
		break;
	}

	return 0;
}

// Función de movimiento del jugador. Dependiendo de donde se encuentre, lo mantiene en el limite o le permite moverse.
int PlayerMovement(int num, Room sala, int key, Character &player)
{
	int max = sala.sizeRoom-1;
	int min = 0;

	//El jugador ya se encuentra en el limite max, return su misma posición.
	if (num >= max)
	{
		return num;
	}

	//El jugador ya se encuentra en el limite min, return su misma posición.
	if (num <= 0)
	{
		return num;
	}

	//El jugador no se encuentra en un limite, return nueva posición.
	if (num > 0 && num < max)
	{
		switch (key)
		{
		case KEY_UP:
			return player.x--;

		case KEY_DOWN:
			return player.x++;

		case KEY_LEFT:
			return player.y--;

		case KEY_RIGHT:
			return player.y++;
		}
	}

}