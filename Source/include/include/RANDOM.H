/*
*
*  RANDOM.H
*
*  Author:SAK-007
*
*  Contains:All function for Playstation Games random numbers
*
*
*/

#include<STDLIB.H>


int GetRandomInteger(int range)
{
	int Temp;
	Temp = rand()%range;
	return Temp;
}
