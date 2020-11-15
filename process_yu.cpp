//
//  main.cpp
//  mainbody
//
//  Created by 于 on 11/8/20.
//

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

struct Game {
    int turn = 1;
    int wolf_num = 2;
    int god_num = 4;
    int villager_num = 4;
    int player_num = wolf_num + god_num + villager_num;
    int wolf_list[12];
    int goodman_list[12];
    int player_list[12];
    int seer_index;
    int witch_index;
    int guard_index;
    int hunter_index;
    int killed_tonight[2];
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
    int medicine = 1;
    int poison = 1;
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
                    case 6:{ player[i].role = "Witch" ;break;}//player
              case 7:
            case 8: { player[i].role = "Werewolf" ;break;}
              case 9: { player[i].role = "Seer";break;}
                    case 10:{ player[i].role = "Guard";break; }
              case 11:
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
            if (player[i].good)
                player[i].life -= 1;
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
        if (player[kill].good && player[kill].role != "Villager")
            player[kill].life -= 1;
        else if (player[kill].good && player[kill].role == "Villager")
            player[kill].life -= 1;
        }
    return kill;
}

void hunter_player(Player player[12]){
    int command;
    cin >> command;
    player[command].life -= 1;
    cout << "Actually I am the hunter, fuck you off bitch!" << endl;
}
    
void hunter_PC(Player player[12]){
    int command;
    int j=0;
    for (int i=0; i<12; ++i){
        if (player[i].life > 0) j+=1;
    }
    command = rand()%j;
    player[command].life -= 1;
    cout << "Actually I am the hunter, fuck you off bitch!" << endl;
}

void seerhuman(){
    
}

void seerPC(){
    
}

void witch_player_night(Player player[12], int killed){ //death 处引入kill作为被杀人的号码
    cout << "Tonight Player " << killed + 1 << " has been killed." <<endl;
    cout << "Do you want to save him/her ?" << endl;
    cout << "Please choose: 1 [Yes] 2 [No]" << endl;
    int saving_command;
    cin >> saving_command;
    if (saving_command == 1 && player[11].medicine == 1){
        player[killed].life += 1;
        player[11].medicine -= 1;
    }
    cout << "Also you have a poison, meaning that you can use this to kill one people." <<endl;
    cout << "Do you want to use this ?" << endl;
    cout << "Please choose: 1 [Yes] 2 [No]" << endl;
    int poison_command, posion_num;
    cin >> poison_command;
    if (poison_command == 1 && player[11].poison == 1){
        cout << "Which man do you want to kill?" << endl;
        for (int i=0; i<12; ++i){
            if (player[i].life > 0) cout <<"[" << i+1 <<"]" << " ";
        }//for
        cin >> posion_num;
        player[posion_num - 1].life -= 1;
        player[11].poison -= 1;
        }//if
    }


void witch_PC_medicine(Player player[12], int kill, int i){
    int medicine_num;
    medicine_num = rand()%2;
    cout << "Tonight Player ? has been killed." <<endl;
    cout << "Do you want to save him/her ?" << endl;
    if (medicine_num == 1 && player[i].medicine == 1){
        player[kill].life += 1;
        player[i].medicine -= 1;
    }
    cout << "Also you have a poisson, meaning that you can use this to kill one people." <<endl;
    cout << "Do you want to use this ?" << endl;
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
    return guard-1;
}


int guardPC(){
    int guard = rand() % 12;
    while (game.player_list[guard] == 0)
    guard = rand() % 12;
    player[guard].guard = 1;
    return guard;
}

//NIGHT

void night (){
    cout << "Night " << game.turn << endl;
    //get list of wolf
    //tell the player if he is wolf
    int killed = 0, guarded = 0;
    if (player[11].role == "Werewolf")
       killed = wolfhuman();
    else if (player[11].role == "Werewolf" && player[11].life == 0){
        cout << "YOU GOT KILLED!!!" << endl;
        killed = wolfPC();
    }
    else
        killed = wolfPC();
    
    if (player[11].role == "Seer" && player[11].life != 0){
        cout << "Hi seer, you have the right to check a person~: "<< endl; 
		cout << "Which person do you want to check Ah ?: " << endl;
		//print put current alive people in the game 
		for (int i=0; i<12; ++i){
			if (player[i].life > 0) cout <<"[" << i+1 <<"]" << " ";
		}
		cout << "\n";
		//checking
		int checking_command;  
		cin >> checking_command;
        seer_player_checking(player, checking_command);
    }
    else{
        cout << "Hi seer, you have the right to check a person~: "<< endl;
		cout << "Which person do you want to check Ah ?: " << endl;
		int checking_num;
		int j=0;
		//get the # of current alive people
		for (int i=0; i<12; ++i){
		if (player[i].life > 0) j+=1;
		}
		checking_num = rand()%j
        bool checking_result = seer_PC_checking(player, checking_num);
    }
    
    if (player[11].role == "Witch" && player[11].life != 0)
        witch_player_night(player, killed);
    else if (player[11].role == "Witch" && player[11].life == 0)
        cout << "YOU GOT KILLED!!!" << endl;
    else
        witch_PC_medicine(player, killed, game.witch_index);
    
    if (player[11].role == "Guard" && player[11].life != 0)
        guarded = guardhuman();
    else if (player[11].role == "Guard" && player[11].life == 0){
        cout << "YOU GOT KILLED!!!" << endl;
        player[11].good = true;
    }
    else
        guarded = guardPC();
    //at the end of the night
    //guard
    if (guarded == killed){
        player[guarded].life = 1;
        player[guarded].guard = 0;
    }
    
    
    //if good man died
    for (int i = 0; i<12; i++){

        if (player[i].life == 0){
            if (game.goodman_list[i] != 0){
                if (player[i].good && player[i].role != "Villager"){
                    game.goodman_list[i] = 0;
                    game.player_list[i] = 0;
                    game.god_num -= 1;
                    if (game.killed_tonight[0] == 0)
                        game.killed_tonight[0] = i + 1;
                    else
                        game.killed_tonight[1] = i + 1;
                    }
                else if (player[i].good && player[i].role == "Villager"){
                    game.goodman_list[i] = 0;
                    game.player_list[i] = 0;
                    game.villager_num -= 1;
                    if (game.killed_tonight[0] == 0)
                        game.killed_tonight[0] = i + 1;
                    else
                        game.killed_tonight[1] = i + 1;
                    }
            }
            // if wolf died
            if (game.wolf_list[i] != 0){
                game.wolf_list[i] = 0;
                game.player_list[i] = 0;
                game.wolf_num -= 1;
                if (game.killed_tonight[0] == 0)
                    game.killed_tonight[0] = i + 1;
                else
                    game.killed_tonight[1] = i + 1;
            }
        }
    } //for
    game.turn++;
    cout << "Night is over......" << endl;
}//night





void vote(){
    int vote, v_index = 0, to_be_voted = 0;
    if (player[11].life != 0){
        cin >> vote;
        cout << "You voted " << vote << endl;
        v_index = vote -1;
        player[v_index].vote += 1;
        for (int i = 0; i < 11; i++){
            if (game.player_list[i] != 0){
                int random = rand() % 10;
            //following players
                if (random < 4){
                    player[v_index].vote += 1;
                    cout << "Player " << player[i].player_index + 1 << " " << "voted " << vote << " " << endl;
                }
                else{
                    //random voting
                    int PC_vote = rand() % 12;
                    while (game.player_list[PC_vote] == 0)
                        PC_vote = rand() % 12;
                    player[PC_vote].vote += 1;
                    cout << "Player " << player[i].player_index + 1 << " " << "voted " << PC_vote + 1 << " " << endl;
                }//else
            }
        }//for
    }
    
    
    //if player died
    else if (player[11].life == 0){
        for (int i = 0; i < game.player_num; i++){
                int PC_vote = rand() % 12;
                while (game.player_list[PC_vote] == 0)
                    PC_vote = rand() % 12;
                player[PC_vote].vote += 1;
            if (game.player_list[i] != 0)
                cout << "Player " << i + 1 << " " << "voted " << PC_vote + 1 << endl;
        }//for
    }
    int Max_vote = 0;
    for (int i = 0; i < 12; i++){
        int current = player[i].vote;
        if (current >= Max_vote){
            Max_vote = current;
            to_be_voted = i;
        }
    }
    
    cout << "The player been voted out is " << to_be_voted + 1 << endl;
    player[to_be_voted].life = 0;
    for (int i = 0; i < 12; i++){
        player[i].vote = 0;
    }
        //if wolf
        if (player[to_be_voted].role == "Werewolf"){
            game.player_list[to_be_voted] = 0;
            game.wolf_num -= 1;
            game.wolf_list[to_be_voted] = 0;
        }
        //if good
        else if (player[to_be_voted].good && player[to_be_voted].role != "Villager"){
            game.goodman_list[to_be_voted] = 0;
            game.player_list[to_be_voted] = 0;
            game.god_num -= 1;
            }
        else if (player[to_be_voted].good && player[to_be_voted].role == "Villager"){
            game.goodman_list[to_be_voted] = 0;
            game.player_list[to_be_voted] = 0;
            game.villager_num -= 1;
            }
}


void daytime(){
    cout << "Day " << game.turn << endl;
    cout << "It's morning, all the survivors come together......" << endl;
    for (int i = 0; i < 2; i++){
        if (game.killed_tonight[i] != 0){
            cout << "Player " << game.killed_tonight[i] << " was killed last night!" << endl;
            game.killed_tonight[i] = 0;
        }
    }
    if (game.killed_tonight[1] == 0 && game.killed_tonight[0] == 0)
        cout << "Last night is a peaceful night! No one died!" << endl;
    cout << "Debate time" << endl;
    //debate function
    cout << "Voting time" << endl;
    cout << "Please choose one to vote out" << endl;
    for (int i = 0; i < 12; i++){
        if (game.player_list[i] != 0)
        cout << game.player_list[i] << endl;
    }
    cout << game.god_num << " " << game.villager_num << endl;//god/villager pointer
    
    //voting
    vote();
        
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
    //get god index
    for (int i = 0; i < 12; i++){
        if (player[i].role == "Seer")
            game.seer_index = i;
    }
    
    for (int i = 0; i < 12; i++){
        if (player[i].role == "Witch")
            game.witch_index = i;
    }
    
    for (int i = 0; i < 12; i++){
        if (player[i].role == "Guard")
            game.guard_index = i;
    }
    
    for (int i = 0; i < 12; i++){
        if (player[i].role == "Hunter")
            game.hunter_index = i;
    }
    //get list of players
    for (int i = 0; i < 12; i++){
            game.player_list[i] = i + 1;
    }
   
    //game process
    while (game.god_num != 0 && game.wolf_num != 0 && game.villager_num != 0){
        night();
        daytime();
    }
    if (game.god_num == 0 || game.villager_num == 0)
        cout << "Werewolves win!" << endl;
    if (game.wolf_num == 0)
        cout << "Good people win!" << endl;
    return 0;
}