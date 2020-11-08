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

struct Player{
    int player_index;
    int player_role
    string role;
};

void game_ini (Game game, Player player[13]);
