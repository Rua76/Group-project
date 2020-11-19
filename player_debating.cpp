#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>
#include "game.h"

void player_debating(){
    ifstream fin;
    fin.open("villager_Player.txt");
    string text[5];
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
    fin.close();
    }
