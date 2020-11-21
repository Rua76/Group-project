#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>
#include "game.h"
using namespace std;

Game game;

Player player[12];

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
              case 4:{ player[i].role = "Villager" ;break;}
                    case 5:
                    case 6:
                    case 7:
                    case 8: { player[i].role = "Werewolf" ;break;}
                    case 9:{ player[i].role = "Seer";break;}
                    case 10:{ player[i].role = "Guard";break; }
                    case 11:{ player[i].role = "Witch" ;break;}
              case 12: { player[i].role = "Hunter" ;break; }
            }//switch   
        }
        cout << "\n";
        cout << "You are the " << player[11].role << endl;
        cout << "Now, enjoy your game and try to win." << "\n" << endl;
    }

int wolfhuman (){
    cout << "Shh.....You are a werewolf." << endl << "Your teammates are: " << endl;
    for (int i = 0; i < 11; i++){
        if (game.wolf_list[i] != 0)
        cout << game.wolf_list[i] << endl;
    }
    std::this_thread::sleep_for (std::chrono::seconds(3));
    //killing
    int themantokill;
    cout << "Choose the one to kill tonight: " << endl;
    for (int i = 0; i < 12; i++){
        if (game.goodman_list[i] != 0)
        cout << "[" << game.goodman_list[i] <<"] ";        
    }
    cout << "\n";
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
    int kill = 0;
    if (game.revealed == 0){
    kill = rand() % 12;
    while (game.goodman_list[kill] == 0 || player[kill].good == false)
    kill = rand() % 12;
    if (game.goodman_list[kill] != 0){
        if (player[kill].good && player[kill].role != "Villager")
            player[kill].life -= 1;
        else if (player[kill].good && player[kill].role == "Villager")
            player[kill].life -= 1;
        }
    }
    
    else if (game.revealed != 0 && player[11].life != 0){
        int random = rand() % 10;
        if (random < 5){
            kill = 11;
            player[11].life -= 1;
        }
        else{
            kill = rand() % 12;
            while (game.goodman_list[kill] == 0 || player[kill].good == false)
            kill = rand() % 12;
            if (game.goodman_list[kill] != 0){
                if (player[kill].good && player[kill].role != "Villager")
                    player[kill].life -= 1;
                else if (player[kill].good && player[kill].role == "Villager")
                    player[kill].life -= 1;
            }
        }
    }
    
    else{
        kill = rand() % 12;
        while (game.goodman_list[kill] == 0 || player[kill].good == false)
        kill = rand() % 12;
        if (game.goodman_list[kill] != 0){
            if (player[kill].good && player[kill].role != "Villager")
                player[kill].life -= 1;
            else if (player[kill].good && player[kill].role == "Villager")
                player[kill].life -= 1;
            }
    }
    return kill;
}

void hunter_player(Player player[12]){
    int command;
    cout << "Actually I am the hunter, so let's die together !" << endl;
    cout << "\n";
    cout << "Choose one to kill: " << endl;
    for (int i=0; i<12; ++i){
        if (player[i].life > 0) cout <<"[" << i+1 <<"]" << " ";
    }
    cin >> command;
    int i = command - 1;
    player[i].life = 0;
    if (player[i].life == 0){
        if (game.goodman_list[i] != 0){
            if (player[i].good && player[i].role != "Villager"){
                game.goodman_list[i] = 0;
                game.player_list[i] = 0;
                game.god_num -= 1;
                }
            else if (player[i].good && player[i].role == "Villager"){
                game.goodman_list[i] = 0;
                game.player_list[i] = 0;
                game.villager_num -= 1;
                }
        }
        // if wolf died
        if (game.wolf_list[i] != 0){
            game.wolf_list[i] = 0;
            game.player_list[i] = 0;
            game.wolf_num -= 1;
        }
    }
    
    cout << "Player " << command << " has been killed by the hunter." << endl;
    cout << "\n";
    game.hunter_kill = 1;
}
    
void hunter_PC(Player player[12]){
    int command = rand()%12;
    while (game.player_list[command] == 0 || command == game.hunter_index)
        command = rand()%12;
    player[command].life -= 1;
    int i = command;
    if (player[i].life == 0){
        if (game.goodman_list[i] != 0){
            if (player[i].good && player[i].role != "Villager"){
                game.goodman_list[i] = 0;
                game.player_list[i] = 0;
                game.god_num -= 1;
                }
            else if (player[i].good && player[i].role == "Villager"){
                game.goodman_list[i] = 0;
                game.player_list[i] = 0;
                game.villager_num -= 1;
                }
        }
        // if wolf died
        if (game.wolf_list[i] != 0){
            game.wolf_list[i] = 0;
            game.player_list[i] = 0;
            game.wolf_num -= 1;
        }
    }
    cout << "Actually I am the hunter, so let's die together !'" << endl;
    cout << "\n";
    cout << "Player " << command + 1 << " has been killed by the hunter." << endl;
    cout << "\n";
    game.hunter_kill = 1;
}


void witch_player_night(Player player[12], int killed){ //death ¥¶“˝»Îkill◊˜Œ™±ª…±»Àµƒ∫≈¬Î
    cout << "Tonight Player " << killed + 1<< " has been killed." <<endl;
    cout << "\n";
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
    std::this_thread::sleep_for (std::chrono::seconds(1));
    cout << "\n";
    cout << "Do you want to save him/her ?" << endl;
    std::this_thread::sleep_for (std::chrono::seconds(1));
    cout << "\n";
    if (medicine_num == 1 && player[i].medicine == 1){
        player[kill].life += 1;
        player[i].medicine -= 1;
    }
    cout << "Also you have a poison, meaning that you can use this to kill one people." <<endl;
    std::this_thread::sleep_for (std::chrono::seconds(1));
    cout << "\n";
    cout << "Do you want to use this ?" << endl;
    std::this_thread::sleep_for (std::chrono::seconds(1));
    cout << "\n";
}


int guardhuman(){
    int guard;
    cout << "\n";
    cout << "Choose the one to protect tonight: " << endl;
    for (int i = 0; i < 12; i++){
        if (game.player_list[i] != 0)
        cout << "[" << game.player_list[i] <<"] ";
    }
    cout << "\n";
    cin >> guard;
    for (int i = 0; i < 12; i++){
        if (player[i].player_index + 1 == guard)
            player[i].guard = 1;
    }
    return guard-1;
}


int guardPC(){
    int guard = 0;
    if (game.revealed == 0){
        guard = rand() % 12;
        while (game.player_list[guard] == 0)
            guard = rand() % 12;
        player[guard].guard = 1;
    }
    else if (game.revealed != 0 && player[11].life != 0){
        int random = rand() % 10;
        if (random < 5){
            guard = 11;
            player[11].guard = 1;
        }
        else{
            guard = rand() % 12;
            while (game.player_list[guard] == 0)
                guard = rand() % 12;
            player[guard].guard = 1;
        }
    }
    return guard;
}

void seer_player_checking(Player player[12], int command){
    if (player[command-1].role == "Werewolf") cout << "That guy is a werewolf !" << endl;
    else {cout << "Hey, that guy is a good one." << endl;};
    }
//int checking_num;
//checking_num = rand()%(sizeof(arr)/sizeof(arr[0]))
bool seer_PC_checking(Player player[12],int num){
    if (player[num].good) return 1;
    else {return 0;};
    }

//NIGHT



//debating
void seer_pc_debating(int checking_num, bool checking_result){
        if (checking_result){
            cout<<"I am the seer !";
            cout<<"Last night I checked Player "<< checking_num + 1<< " and this person is a good guy." <<endl;
            cout << "\n";
        }
        else{
            cout<<"I am the seer !"<<endl;
            cout<<"Last night I checked Player "<< checking_num + 1<< " and this person is a bad guy."<<endl;
            cout << "\n";
        }
    }

void seer_human_debating(int checking_num, bool checking_result){
        if (checking_result){
            cout<<"I am the seer !";
            cout<<"Last night I checked Player "<< checking_num << " and this person is a good guy." <<endl;
            cout << "\n";
        }
        else{
            cout<<"I am the seer !"<<endl;
            cout<<"Last night I checked Player "<< checking_num << " and this person is a bad guy."<<endl;
            cout << "\n";
        }
    }

void seer_player_debating(int checking_command){
    ifstream fin;
    fin.open("Seer_Player.txt");
    string text[4];
    int i = 0;
    while (!fin.eof()){
        string inbuf;
        getline(fin, inbuf);
        text[i] = inbuf;
        i+=1;
    }
        fin.close();
        cout <<  "Please choose your response to debate: "<< endl;
        
        for (int i=0; i<2; ++i){
            cout << "[" << i+1 << "]"<< " "<< text[i] << endl;
            
        }//for
        cout << "Please input: 1 2"<<endl;
        int command;
        cin >> command;
        cout << "-------------------------------------------------------"<< endl;
        cout << "Your response: " << text[command-1] << endl;
        if (command == 1 ){
            bool checking_result = seer_PC_checking(player, checking_command-1);
            seer_human_debating(checking_command, checking_result);
            game.revealed = 1;
        }//if
        else {
            cout << text[1] << endl;
        }//else
    }

void witch_player_debating(int kill, Player player[12]){
    ifstream fin;
            fin.open("witch_Player.txt");
            string text[4];
            int i = 0;
            while (!fin.eof()){
                string inbuf;
                getline(fin, inbuf);
                text[i] = inbuf;
                i+=1;
            }
        fin.close();
        cout <<  "Please choose your response to debate: "<< endl;
        
        for (int i=0; i<2; ++i){
            cout << "[" << i+1 << "]"<< " "<< text[i] << endl;
            
        }//for
        cout << "Please input: 1 2"<<endl;
        int command;
        cin >> command;
        cout << "-------------------------------------------------------"<< endl;
        cout << "Your response: " << text[command-1] << endl;
        if (command == 1 ){
            cout << "Please choose the person you suspect: (input 0 if you are not suspecting anyone) ";
            for (int i=0; i<11; ++i){
                if (game.player_list[i] != 0) cout <<"[" << i + 1 <<"]" << " ";
            }//for
		cout << "\n";
            int suspect;
            cin >> suspect;
            game.suspect = suspect;
            cout<<"Last night I Noticed that Player "<< kill + 1<< " has been killed." << endl;
            if (suspect != 0) cout << " I saved him/her and I think player " << suspect << " can be the bad guy.";
            game.revealed = 1;
        }//if
        else {
            cout << text[1] << endl;
        }//else
    fin.close();
    }

    

void debate (){
    if (player[11].role == "Villager" && player[11].life != 0){
        player_debating();
    }
    
    if (player[11].role == "Werewolf" && player[11].life != 0){
       cout << "Dear Werewolf, although you are strong, do remember to protect yourself"<<endl;
        player_debating();
    }
    
    if (player[11].role == "Seer" && player[11].life != 0){
        seer_player_debating(game.player_checking);
       }
    if (player[11].role == "Witch" && player[11].life != 0){
        witch_player_debating(game.wolf_killed, player);
       }
    if (player[11].role == "Hunter" && player[11].life != 0){
        player_debating();
    }
    if (player[11].role == "Guard" && player[11].life != 0){
        player_debating();
    }
    cout << "\n";
    //PC
    for (int i=0; i<11; i++){
        
        if (player[i].role == "Villager" && player[i].life != 0){
            cout << "Player " << i+1 << ": ";
            pc_debating();
            std::this_thread::sleep_for (std::chrono::seconds(1));
    }
    
        if (player[i].role == "Werewolf" && player[i].life != 0){
            cout << "Player " << i+1 << ": ";
            pc_debating();
            std::this_thread::sleep_for (std::chrono::seconds(1));
    }
    
        if (player[i].role == "Seer" && player[i].life != 0){
           cout << "Player " << i+1 << ": ";
           //get the # of current alive people
            int see = rand() % 12;
        while (game.player_list[see] == 0 || player[see].role == "Seer")
            see = rand() % 12;
           bool checking_result = seer_PC_checking(player, see);
            game.see = see;
            game.gb = checking_result;
           seer_pc_debating(see, checking_result);
           std::this_thread::sleep_for (std::chrono::seconds(1));
       }
        if (player[i].role == "Witch" && player[i].life != 0){
           cout << "Player " << i+1 << ": ";
           pc_debating();
           std::this_thread::sleep_for (std::chrono::seconds(1));
       }
        if (player[i].role == "Hunter" && player[i].life != 0){
           cout << "Player " << i+1 << ": ";
           pc_debating();
           std::this_thread::sleep_for (std::chrono::seconds(1));
       }
        if (player[i].role == "Guard" && player[i].life != 0){
           cout << "Player " << i+1 << ": ";
           pc_debating();
           std::this_thread::sleep_for (std::chrono::seconds(1));
       }
    }
}




//voting
void vote(){
    int vote, v_index = 0, to_be_voted = 0;
    if (player[11].life != 0){
        cin >> vote;
        cout << "You voted " << vote << endl;
        v_index = vote -1;
        player[v_index].vote += 1;
        //other players vote
        for (int i = 0; i < 11; i++){
            if (game.player_list[i] != 0){
                int random = rand() % 10;
                //didn't find wolf
                if (game.gb == 1){
            //following players
                    if (game.suspect == 0){
                        // do not reveal, normal condition
                        if (game.revealed == 0){
                        if (random < 2 && vote != player[i].player_index + 1){
                            player[v_index].vote += 1;
                            cout << "Player " << player[i].player_index + 1 << " " << "voted " << vote << " " << endl;
                        }
                        else{
                            //random voting
                            int PC_vote = rand() % 12;
                            while (game.player_list[PC_vote] == 0 || PC_vote == i)
                                PC_vote = rand() % 12;
                            player[PC_vote].vote += 1;
                            cout << "Player " << player[i].player_index + 1 << " " << "voted " << PC_vote + 1 << " " << endl;
                        } //else
                        }
                        //reveal yourself
                        else{
                            if (random < 5 && vote != player[i].player_index + 1){
                                player[v_index].vote += 1;
                                cout << "Player " << player[i].player_index + 1 << " " << "voted " << vote << " " << endl;
                            }
                            else{
                                //random voting
                                int PC_vote = rand() % 12;
                                while (game.player_list[PC_vote] == 0 || PC_vote == i)
                                    PC_vote = rand() % 12;
                                player[PC_vote].vote += 1;
                                cout << "Player " << player[i].player_index + 1 << " " << "voted " << PC_vote + 1 << " " << endl;
                            } //else
                        }
                    } //sus = 0
                    //sus != 0
                    else{
                        if (random < 3 && vote != player[i].player_index + 1){
                            player[v_index].vote += 1;
                            cout << "Player " << player[i].player_index + 1 << " " << "voted " << vote << " " << endl;
                        }
                        else{
                            //random voting
                            int PC_vote = rand() % 12;
                            while (game.player_list[PC_vote] == 0 || PC_vote == i)
                                PC_vote = rand() % 12;
                            player[PC_vote].vote += 1;
                            cout << "Player " << player[i].player_index + 1 << " " << "voted " << PC_vote + 1 << " " << endl;
                        }
                    }
                }//didn't find wolf
                
                //find wolf
                else{
                    if (i == game.seer_index){
                        player[game.see].vote += 1;
                        cout << "Player " << player[i].player_index + 1 << " " << "voted " << game.see + 1 << " " << endl;
                    }
                    else{
                        if (random < 2 && vote != player[i].player_index + 1){
                            player[v_index].vote += 1;
                            cout << "Player " << player[i].player_index + 1 << " " << "voted " << vote << " " << endl;
                        }
                        else if (random > 7){
                            player[game.see].vote += 1;
                            cout << "Player " << player[i].player_index + 1 << " " << "voted " << game.see + 1 << " " << endl;
                        }
                        else{
                            int PC_vote = rand() % 12;
                            while (game.player_list[PC_vote] == 0 || PC_vote == i)
                                PC_vote = rand() % 12;
                            player[PC_vote].vote += 1;
                            cout << "Player " << player[i].player_index + 1 << " " << "voted " << PC_vote + 1 << " " << endl;
                        }
                }
                }
            std::this_thread::sleep_for (std::chrono::seconds(1));
        }
    } //for
    }
    
    //if player died
    else if (player[11].life == 0){
        for (int i = 0; i < game.player_num; i++){
                int PC_vote = rand() % 12;
                while (game.player_list[PC_vote] == 0 || PC_vote == i)
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
    if (player[to_be_voted].role == "Hunter")
        game.hunter_kill = 1;
    
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


void night (){
    cout << "Night " << game.turn << endl;
    cout << "\n";
    cout << "Be careful, werewolves are coming." << endl;
    std::this_thread::sleep_for (std::chrono::seconds(1));
    //get list of wolf
    //tell the player if he is wolf
    int killed = 0, guarded = 0;
    if (player[11].role == "Werewolf" && player[11].life != 0)
       killed = wolfhuman() - 1;
    else if (player[11].role == "Werewolf" && player[11].life == 0){
        cout << "YOU GOT KILLED!!!" << endl;
        killed = wolfPC();
    }
    else
        killed = wolfPC();
    cout << "--------------------" << "\n";
    
    game.wolf_killed = killed;
    
    cout << "Now things go on..." << "\n";
    cout << "--------------------" << "\n";
    
	if (player[11].role == "Seer"){
           cout << "Hi seer, you have the right to check a person: "<< endl;
        cout << "\n";
        std::this_thread::sleep_for (std::chrono::seconds(1));
           cout << "Which person do you want to check?: " << endl;
           //print put current alive people in the game
           for (int i=0; i<12; ++i){
               if (game.player_list[i] != 0) cout <<"[" << i+1 <<"]" << " ";
           }
           cout << "\n";
           //checking
           //int checking_command;

        cin >> game.player_checking;
           seer_player_checking(player, game.player_checking);
       }
       else{
           cout << "Hi seer, you have the right to check a person: "<< endl;
           cout << "\n";
           std::this_thread::sleep_for (std::chrono::seconds(1));
           cout << "Which person do you want to check?: " << endl;
       }
	std::this_thread::sleep_for (std::chrono::seconds(1));
	cout << "\n";
	cout << "--------------------" << "\n";
	cout << "Hi witch, gald to have you here." << endl;
    cout << "\n";
    if (player[11].role == "Witch" && player[11].life != 0)
        witch_player_night(player, killed);
    else if (player[11].role == "Witch" && player[11].life == 0){
        cout << "YOU GOT KILLED!!!" << endl;
        cout << "\n";
    }
    else
        witch_PC_medicine(player, killed, game.witch_index);
    
	cout << "--------------------" << "\n";
    cout << "Hi guard, welcome !" << endl;
    if (player[11].role == "Guard" && player[11].life != 0)
        guarded = guardhuman();
    else if (player[11].role == "Guard" && player[11].life == 0){
        cout << "YOU GOT KILLED!!!" << endl;
        cout << "\n";
        player[11].good = true;
    }
    else
        guarded = guardPC();
    //at the end of the night
    cout << "--------------------" << "\n";
    //guard
    if (guarded == killed){
        player[guarded].life = 1;
    }
    player[guarded].guard = 0;
    
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
    cout << "--------------------" << "\n";
}//night

void daytime(){
    cout << "\n";
    cout << "Day Time" << " "<< game.turn << endl;
    cout << "--------------------" << "\n";
    std::this_thread::sleep_for (std::chrono::seconds(1));
    cout << "\n";
    cout << "It's morning, all the survivors come together......" << endl;
    cout << "--------------------" << "\n";
    std::this_thread::sleep_for (std::chrono::seconds(2));
    for (int i = 0; i < 2; i++){
        if (game.killed_tonight[i] != 0){
            cout << "Player " << game.killed_tonight[i] << " was killed last night!" << endl;
            cout << "\n";
            std::this_thread::sleep_for (std::chrono::seconds(1));
        }
    }
    if (player[11].role == "Hunter" && player[11].life == 0 && game.hunter_kill == 0)
        hunter_player(player);
    
    for (int i = 0; i < 11; i++){
        if (player[i].role == "Hunter" && player[i].life == 0 && game.hunter_kill == 0){
            hunter_PC(player);
            break;
        }
    }
    
    if (game.killed_tonight[1] == 0 && game.killed_tonight[0] == 0)
        cout << "Last night is a peaceful night! No one died!" << endl;
    std::this_thread::sleep_for (std::chrono::seconds(1));
    game.killed_tonight[0] = 0;
    game.killed_tonight[1] = 0;
    cout << "--------------------" << "\n";
    cout << "Debate time" << endl;
    std::this_thread::sleep_for (std::chrono::seconds(1));
    debate();
    std::this_thread::sleep_for (std::chrono::seconds(1));
    cout << "Voting time" << endl;
    cout << "Please choose one to vote out" << endl;
    for (int i = 0; i < 12; i++){
        if (game.player_list[i] != 0)
        cout << "[" << game.player_list[i] <<"] ";       
    }
    cout << "\n";
    cout << "Current number of Gods that still alive : " << game.god_num << endl;
	cout << "Current number of Villagers that still alive : " << game.villager_num << endl;//god/villager pointer
    cout << "--------------------" << "\n";
    //voting
    vote();
	cout << "--------------------" << "\n";
	cout << "\n"; 
    }


int main(int argc, const char * argv[]) {
    //Game start
    ifstream fin;
    fin.open("intro.txt");
    string text[10];
    int i = 0;
    while (!fin.eof()){
        string inbuf;
        getline(fin, inbuf);
        text[i] = inbuf;
        i+=1;
    }
    fin.close();
    for (int i = 0; i < 10; i++){
        cout << text[i] <<endl;
        std::this_thread::sleep_for (std::chrono::seconds(1));
    }

    //initate the game
    int command = 9;
    ifstream manual;
    manual.open("manual.txt");
    string manu[20];
    i = 0;
    while (!manual.eof()){
        string inbuf;
        getline(manual, inbuf);
        manu[i] = inbuf;
        i+=1;
    }
        fin.close();
    
    cout << "Do you want to start the game now?" << endl;
    cout << "1 Yes " << "2 No " << "0 Manual" << endl;
    cin >> command;
    
    while (command != 1){
        
        if (command == 2){
            return 0;
            break;
        }
        else if (command == 0){
            for (int i = 0; i < 20; i++){
                cout << manu[i] <<endl;
                std::this_thread::sleep_for (std::chrono::seconds(1));
            }
            cout << "Do you want to start the game now?" << endl;
            cout << "1 Yes " << "2 No " << "0 Manual" << endl;
            cin >> command;
        }
        else
            cin >> command;
    }
    
    
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
        if (game.god_num == 0 || game.wolf_num == 0 || game.villager_num == 0)
            break;
        else
            daytime();
    }
    if (game.god_num == 0 || game.villager_num == 0)
        cout << "Werewolves win!" << endl;
    if (game.wolf_num == 0)
        cout << "Good people win!" << endl;
    
    return 0;
}


