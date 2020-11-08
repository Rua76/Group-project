#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <bits/stdc++.h>
#include <string> 
#include <fstream>

using namespace std;
struct Villager{
	int life = 1;
	int vote = 0;
	int guard = 0; 
	bool good = 1;
	
	void pc_debating(){
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
	
	void player_debating(){
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
};

int main(){
	Villager player;
	player.player_debating();
}
