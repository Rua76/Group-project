#include <iostream>
using namespace std;

struct Game {
    int player_num;
    int turn = 1;
    int wolf_num;
    int villager_num;
    int good_num;
    int seer_num;
    int witch_num;
    int guard_num;
    int hunter_num;
};
Game game;

struct Player{
    int player_index[20];
    string role[20];
};
Player player;

void game_ini (){
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
    //player index
    for (int i = 0; i < game.player_num; i++){
        player.player_index[i] = i;
    }
    //roles
}

