#include "Level_Transition.h"
#include <iostream>
#include <stdlib.h>
#include "game.h"
#include "Framework\console.h"

using namespace std;


void Level_Transition::Transition(int roundNumber)
{
	if (roundNumber == 1)
	{
		system("CLS");
		cout << "Level 1" << endl;
	}
}