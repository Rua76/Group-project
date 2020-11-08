class Game{
    int player_num;
    int turn = 1;
    int wolf_num;
    int villager_num;
    int good_num;
    int seer_num;
    int witch_num;
    int guard_num;
    int hunter_num;
  public:
    void game_ini ();
};

class Player{
    int player_index[20];
    string role[20];
};
