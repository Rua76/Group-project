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
void pc_debating(){
    ifstream fin;
    fin.open("villager_PC.txt");
    string text[11];
    int i = 0;
    while (!fin.eof()){
        string inbuf;
        getline(fin, inbuf);
        text[i] = inbuf;
        i+=1;
        }
    srand((int)time(0));
    cout << text[rand()%10] << endl;
    cout << "\n";
    fin.close();
    }
