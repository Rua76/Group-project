#ifndef GAME_H // include guard
#define GAME_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>
using namespace std;
struct Game {
    int turn = 1;
    int wolf_num = 4;
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
    int wolf_killed;
    int player_checking;
    int pc_checking;
    int see;
    bool gb = true;
    int suspect = 0;
    bool revealed = 0;
    bool hunter_kill = 0;
};



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



void game_ini (Game game, Player player[12]);

int wolfhuman ();

int wolfPC();

void hunter_player(Player player[12]);

void hunter_PC(Player player[12]);

void witch_player_night(Player player[12], int killed);

void witch_PC_medicine(Player player[12], int kill, int i);

int guardhuman();

int guardPC();

void seer_player_checking(Player player[12], int command);

bool seer_PC_checking(Player player[12],int num);

void seer_pc_debating(int checking_num, bool checking_result);

void seer_human_debating(int checking_num, bool checking_result);

void seer_player_debating(int checking_command);

void witch_player_debating(int kill, Player player[12]);

void pc_debating();

void player_debating();

void debate ();

void vote();

void night ();

void daytime();

#endif
