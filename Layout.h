#pragma once
#include<string>
using namespace std;

class Layout
{
	public:
		Layout();
		void initLayout(string filename);
		void PrintLayout();
		char GetTile(int, int);
		void SetTile(int, int, char);
		void GetPlayer();
		void PlayerMove();
		void MovePlayerTo(int, int);
		void CheckWin();
		void Playerinit(int, int);
		void Enemyinit(int, int, int, int, int);
		void Level_Setup(string Filename);
		void LevelReshape();
		int PlayerAtt();
		int GetEnmy(int, int);
		void ReadyBattle(int, int);
		int Fight(int);
};

