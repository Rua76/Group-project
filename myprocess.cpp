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

void hunterhuman(){
    
}

void hunterPC(){
    
}
//int checking_command;
//cin >> checking_command;
void seer_player_checking(Player player[12], int command){
	if (player[command].role == "Werewolf") cout << "Shh... That guy is a werewolf !";
	else {cout << "Hey, that guy is a good one."};
	}
//int checking_num;
//checking_num = rand()%(sizeof(arr)/sizeof(arr[0]))
bool seer_PC_checking(Player player[12],int num ){ 
	if (player[num].good) return 1;
	else {return 0};
	}

//bool checking_result = seer_PC_checking(player, checking_num)
void seer_pc_debating(int checking_num, bool checking_result){
	if (checking_result){
		cout<<"I am the seer !"<<endl;
		cout<<"Last night I checked Player "<< checking_num << " and this person is a good guy." 
	}
	else{
		cout<<"I am the seer !"<<endl;
		cout<<"Last night I checked Player "<< checking_num << " and this person is a bad guy."
		}
	}
	
void seer_player_debating(int checking_command, Player player[12]){
	ifstream fin;
	fin.open("Seer_Player.txt");
	string text[2];
	int i = 0;
	while (!fin.eof()){
		string inbuf;
		getline(fin, inbuf);
		text[i] = inbuf;
		i+=1;
	}
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
		bool checking_result = seer_PC_checking(player, checking_command)
		seer_pc_debating(checking_num, checking_result)
	}//if
	else {
		cout << text[1] << endl;
	}//else
	}

int witch_player_night(Player player[12], int kill, int i){ //death 处引入kill作为被杀人的号码 
	cout << "Tonight Player " << death << " has been killed." <<endl;
	cout << "Do you want to save him/her ?" << endl;
	cout << "Please choose: 1 [Yes] 2 [No]" << endl;
	int saving_command;
	cin >> saving_command;
	if (saving_command == 1 && player[i].medicine = 1){
		player[kill].life += 1;
		player[i].medicine -= 1;
	}
	cout << "Also you have a poisson, meaning that you can use this to kill one people." <<endl;
	cout << "Do you want to use this ?" << endl;
	cout << "Please choose: 1 [Yes] 2 [No]" << endl;
	cin >> poisson_command;
	if (poisson_command == 1 && player.poisson = 1){
		cout << "Which man do you want to kill?" 
		for (int i=0; i<12; ++i){
			if (player[i].life > 0) cout <<"[" << i <<"]" << " ";
		}//for
		cin << poisson_num;
		player[poisson_num].life -= 1;
		player[i].poisson -= 1;
		}//if  
		return poisson_command;
	}


void witch_PC_medicine(Player player[12], int death, int i){ 
	int medicine_num;
	medicine_num = rand()%2;
	cout << "Tonight Player ? has been killed." <<endl;
	cout << "Do you want to save him/her ?" << endl;
	if (medicine_num == 1 && player[i].medicine = 1){
		player[kill].life += 1;
		player[i].medicine -= 1;
	}
	cout << "Also you have a poisson, meaning that you can use this to kill one people." <<endl;
	cout << "Do you want to use this ?" << endl;
}

void witch_player_debating(int kill, Player player[12]){
	ifstream fin;
	fin.open("witch_Player.txt");
	string text[2];
	int i = 0;
	while (!fin.eof()){
		string inbuf;
		getline(fin, inbuf);
		text[i] = inbuf;
		i+=1;
	}
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
	    cout << "Please choose the person you suspect: (input 0 if you are not suspecting anyone) "
		for (int i=0; i<12; ++i){
		    if (player[i].life > 0) cout <<"[" << i <<"]" << " ";
			}//for
		int suspect;
		cin >> suspect;
		cout<<"Last night I Noticed that Player "<< kill << " has been killed." << endl;
		if (suspect != 0) cout << " I saved him/her and I think player " << suspect << "can be the bad guy.";			
		}//if
		else {
			cout << text[1] << endl;
		}//else
	}

void villager_pc_debating(){
	ifstream fin;
	fin.open("villager_PC.txt");
	string text[4];
	int i = 0;
	while (!fin.eof()){
		string inbuf;
		getline(fin, inbuf);
		text[i] = inbuf;
		i+=1;
	} 
	srand((int)time(0));
		cout << text[rand()%4] << endl;
	}
void villager_player(){
	ifstream fin;
	fin.open("villager_Player.txt");
	string text[4];
	int i = 0;
	while (!fin.eof()){
		string inbuf;
		getline(fin, inbuf);
		text[i] = inbuf;
		i+=1;
	}
	cout <<  "Please choose your response to debate: "<< endl;
		
	for (int i=0; i<4; ++i){
		cout << "[" << i+1 << "]"<< " "<< text[i] << endl;
			
	}//for
	cout << "Please input: 1 2 3 4"<<endl;
	int command;
	cin >> command;
	cout << "-------------------------------------------------------"<< endl;
	cout << "Your response: " << text[command-1] << endl;
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
    cout << "Killed:" << killed << endl;
    cout << "Guarded:" << guarded << endl;
    //at the end of the night
    //guard
    if (guarded == killed){
        player[guarded].life = 1;
        player[guarded].guard = 0;
    }
    
    
    //if died
    for (int i = 0; i<12; i++){

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
        }
    }//for
    cout << "living list" << endl;
    for (int i = 0; i < 12; i++){
        if (game.goodman_list[i] != 0)
        cout << game.goodman_list[i] << endl;
    }
    cout << game.god_num << " " << game.villager_num << endl;
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
