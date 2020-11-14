#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

struct Game {
    int turn = 1;
    int wolf_num = 4;
    int god_num = 4;
    int villager_num = 4;
    int wolf_list[12];
    int goodman_list[12];
    int player_list[12];
};
Game game;

struct Player{
    int player_index;
    int player_role;
    string role;
    int life = 1;
    bool good = true;
    int vote = 0;
    int guard = 0;
};

Player player[13];

void game_ini (Game game, Player player[12]){

    srand((int)time(0));
    int idx[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
    random_shuffle(begin(idx), end(idx));
    for (int i=0; i <= 11; i++){
            player[i].player_index = i;
            player[i].player_role = idx[i];
                switch (idx[i]) {
              case 1:
              case 2:
              case 3:
            case 4:
                    case 5:{ player[i].role = "Villager" ;break;}
                    case 6:{ player[i].role = "Guard";break; }//player
              case 7:
            case 8: { player[i].role = "Werewolf" ;break;}
              case 9: { player[i].role = "Seer";break;}
              case 10:
              case 11: { player[i].role = "Witch" ;break;}
              case 12: { player[i].role = "Hunter" ;break; }
            }//switch
            cout << "Player " <<  player[i].player_index+1 << " is " << player[i].role << endl;
    
        }
    }

int wolfhuman (){
    cout << "Shh.....You are a werewolf." << endl << "Your teammates are: " << endl;
    for (int i = 0; i < 11; i++){
        if (game.wolf_list[i] != 0)
        cout << game.wolf_list[i] << endl;
    }
    //killing
    int themantokill;
    cout << "Choose the one to kill tonight: " << endl;
    for (int i = 0; i < 12; i++){
        if (game.goodman_list[i] != 0)
        cout << game.goodman_list[i] << endl;
    }
    cin >> themantokill;
    for (int i = 0; i < 12; i++){
        if (player[i].player_index + 1 == themantokill){
            if (player[i].good && player[i].role != "Villager"){
            player[i].life -= 1;
            }
            else if (player[i].good && player[i].role == "Villager"){
                player[i].life -= 1;
            }
            else
                break;
        }
    }
    return themantokill;
}

int wolfPC(){
    int kill = rand() % 12;
    while (game.goodman_list[kill] == 0 || player[kill].good == false)
    kill = rand() % 12;
    if (game.goodman_list[kill] != 0){
        if (player[kill].good && player[kill].role != "Villager"){
            cout << game.goodman_list[kill] << " " << player[kill].role << endl;
            player[kill].life -= 1;
            }
        else if (player[kill].good && player[kill].role == "Villager"){
            cout << game.goodman_list[kill] << " " << player[kill].role << endl;
            player[kill].life -= 1;
            }

        }
    cout << "------------------------------" << endl;
    cout << game.goodman_list[kill] << " " << player[kill].role << endl;
    cout << game.god_num << " " << game.villager_num << endl;
    cout << "Choose the one to kill tonight: " << endl;
    for (int i = 0; i < 12; i++){
        if (game.goodman_list[i] != 0)
        cout << game.goodman_list[i] << endl;
    }
    return kill;
}

void hunterhuman(){
    
}

void hunterPC(){
    
}

void seerhuman(){
    
}

void seerPC(){
    
}

void witchhuamn(){
    
}

void witchPC(){
    
}
int guardhuman(){
    int guard;
    cout << "Choose the one to protect tonight: " << endl;
    for (int i = 0; i < 12; i++){
        if (game.player_list[i] != 0)
        cout << game.player_list[i] << endl;
    }
    cin >> guard;
    for (int i = 0; i < 12; i++){
        if (player[i].player_index + 1 == guard)
            player[i].guard = 1;
    }
    return guard;
}


int guardPC(){
    int guard = rand() % 12;
    while (game.player_list[guard] == 0)
    guard = rand() % 12;
    player[guard].guard = 1;
    return guard;
}

void night (){
    cout << "Night " << game.turn << endl;
    //get list of wolf
    //tell the player if he is wolf
    int killed, healed, poisoned, guarded;
    if (player[11].role == "Werewolf")
       killed = wolfhuman();
    else
        killed = wolfPC();
    
    if (player[11].role == "Seer")
        seerhuman();
    else
        seerPC();
    
    if (player[11].role == "Witch")
        witchhuamn();
    else
        witchPC();
    
    if (player[11].role == "Guard")
        guarded = guardhuman();
    else
        guarded = guardPC();
    
    //at the end of the night
    
    
    game.turn++;
}

int main(int argc, const char * argv[]) {
    //Game start
    cout << "intro" << endl;
    //initate the game
    //get wolflist
    game_ini(game, player);
    for (int i = 0; i < 12; i++){
        if (player[i].role == "Werewolf"){
            game.wolf_list[i] = player[i].player_index + 1;
            player[i].good = false;
        }
    }
    //get list of goodman
    for (int i = 0; i < 12; i++){
        if (player[i].role != "Werewolf")
            game.goodman_list[i] = player[i].player_index + 1;
    }
    //get list of players
    for (int i = 0; i < 12; i++){
            game.player_list[i] = i + 1;
    }
   
    //game process
    while (game.god_num != 0 && game.wolf_num != 0 && game.villager_num != 0){
        night();
    }
    if (game.god_num == 0 || game.villager_num == 0)
        cout << "Werewolves win!" << endl;
    return 0;
}
    

