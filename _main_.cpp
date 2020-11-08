#include <iostream>
using namespace std;

void Role_distribute (){
    
}

struct Game {
    int player_num;
    int turn;
};
Game game;

struct Player{
    int player_index[20];
    string role;
};
Player player;

int main(int argc, const char * argv[]) {
    // choose player number
    cout << "select the number of players: ";
    cin >> game.player_num;
    //initialize players
    for (int i = 0; i < game.player_num; i++){
        player.player_index[i] = i;
    }
    return 0;
}
