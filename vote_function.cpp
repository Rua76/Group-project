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
                if (random < 5){
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
