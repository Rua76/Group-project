#include <iostream>
#include "init_game.h"
using namespace std;
void game_ini (Game game, Player player[13]){
    // choose player number
    cout << "select the number of players between 9-12: ";
    cin >> game.player_num;
    //initialize players
    switch (game.player_num) {
        case 9:
            game.wolf_num = 3;
            game.good_num = 6;
            game.villager_num = 3;
            game.seer_num = 1;
            game.guard_num = 1;
            game.witch_num = 1;
            break;
        case 10:
            game.wolf_num = 3;
            game.good_num = 7;
            game.villager_num = 4;
            game.seer_num = 1;
            game.guard_num = 1;
            game.witch_num = 1;
            break;
        case 11:
            game.wolf_num = 3;
            game.good_num = 8;
            game.villager_num = 4;
            game.seer_num = 1;
            game.guard_num = 1;
            game.witch_num = 1;
            game.hunter_num = 1;
            break;
        case 12:
            game.wolf_num = 4;
            game.good_num = 8;
            game.villager_num = 4;
            game.seer_num = 1;
            game.guard_num = 1;
            game.witch_num = 1;
            game.hunter_num = 1;
            break;
        default:
            cout << "Invalid number!" << endl;
    }
    //player initialize
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

