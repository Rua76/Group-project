#include <iostream>
#include "init_game.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

void game_ini (Game game, Player player[13]){

	srand((int)time(0));
	int idx[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
	random_shuffle(begin(idx), end(idx));
	for (int i=1; i <= 12; i++){
    		player[i].player_index = i;
    		player[i].player_role = idx[i];
    	        switch (idx[i]) {
      		case 1:
      		case 2:
      		case 3:
			case 4: { player[i].role = "Villager" ;break;}
      		case 5:
      		case 6:
      		case 7: 
			case 8: { player[i].role = "Werewolf" ;break;}
      		case 9: { player[i].role = "Seer";break;}
      		case 10: { player[i].role = "Guard";break; }
      		case 11: { player[i].role = "Witch" ;break;}
      		case 12: { player[i].role = "Hunter" ;break; }
    		}//switch
    		cout << "Player " <<  player[i].player_index << " is " << player[i].role << endl;//运行可删
    
	}
}

