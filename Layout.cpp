#include "Layout.h"

#include <iostream>
#include <random>
#include <ctime>
#include <cstdio>
#include <conio.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Layout
{
public:

    //ctor 
    Layout()    
    {

    }
    
    // Initialize Level file
    void initLayout(string filename)          
    {
        ifstream Level_file;
        Level_file.open(filename);
        if (Level_file.fail())
            perror("");
        LevelReshape();
        string Line;
        while (getline(Level_file, Line))
            _levelData.push_back(Line);

        Level_file.close();
    }

    //Print LevelFile on the Console
    void PrintLayout()                        
    {
        system("CLS");
        cout << "\n";
        for (int i = 0; i < _levelData.size(); i++)
        {
            printf("\t%s\n", _levelData[i].c_str());
        }
        GetPlayer();
    }

    //Return Tile At the XY
    char GetTile(int y, int x)          
    {
        if (y < _levelData.size() || x < _levelData[y].size())
            return _levelData[y][x];
        else
            throw "Vector out_of_range:";

    }

    // Set a NewTile At XY
    void SetTile(int y, int x, char NewTile) 
    {
        if (y < _levelData.size() || x < _levelData[y].size())
            _levelData[y][x] = NewTile;
        else
            throw "Vector out_of_range";
    }
                        
    // I dont care to desctibe it to U, ****
    bool Done = false;

    // inti Important tiles
    void GetPlayer()  
    {
        for (int i = 0; i < _levelData.size(); i++)
        {
            for (int j = 0; j < _levelData[i].size(); j++)
            {
                switch (GetTile(i, j))
                {
                case '@': //Player Tile
                    Playerinit(i, j);
                    break;
                case '?': // Win tile 
                    _Winy = i;
                    _Winx = j;
                    break;
                case 'D': // Enimies
                case 'Z':
                case 'H':
                case 'L':
                    if (!Done)
                        Enemyinit(i, j, 80, 25, 20);

                    break;

                }
            }
        }
        Done = true;
    }

    // Make Player Move //
    void PlayerMove()
    {
        switch (_getch())
        {
        case'W':  // Up!
        case'w':
        case 72:
            MovePlayerTo(_Ply - 1, _Plx);
            break;

        case 'S': // Down!
        case 's':
        case 80:
            MovePlayerTo(_Ply + 1, _Plx);
            break;

        case 'A': // Left!
        case 'a':
        case 75:
            MovePlayerTo(_Ply, _Plx - 1);
            break;

        case 'D': // Right!
        case 'd':
        case 77:
            MovePlayerTo(_Ply, _Plx + 1);
            break;
        case 27:  // Esc_Key
            exit(1);
        }
        PrintLayout();
    }

    // Move Player Tile To The Given XY //
    void MovePlayerTo(int New_y, int New_x)
    {
        char NewTile = GetTile(New_y, New_x);
        if (NewTile == '.' || NewTile == '?')
        {
            SetTile(_Ply, _Plx, '.');
            SetTile(New_y, New_x, '@');
        }
        else
            ReadyBattle(New_y, New_x);
    }

    // Check Winner OR Game-is-Done-OR-Not //
    bool CheckWin()
    {
        if (_Ply == _Winy && _Plx == _Winx)
        {
            printf("You Won!");
            Asurs.clear();
            return true;
        }
        else
            return false;
    }

    //  PLayer Initializer  //
    void Playerinit(int y, int x)
    {
        P_Health = 120;
        P_Attack = 30;
        _Ply = y;
        _Plx = x;
    }

    //  Asur iniitializer  //
    void Enemyinit(int y, int x, int Health, int Attack, int xp)
    {
        Asurs.push_back({ y ,x ,Health, Attack });
    }

    // Setup the Whole Level by Given FileName //
    void Level_Setup(string FileName)
    {

        initLayout(FileName);
        PrintLayout();
        while (!CheckWin())    // While -No Winner- or 
        {
            PlayerMove();
        }

    }

    // Clear _levelData vector
    void LevelReshape()
    {
        _levelData.clear();
        Asurs.clear();
        Done = false();
    }

    // Player Attack
    int PlayerAtt()
    {
        // Random attack
        default_random_engine AttAccuracy(12048);
        uniform_int_distribution < int  > atttck(-50, 30);
        P_Attack += atttck(AttAccuracy);
        cout << P_Attack;
        return P_Attack;
    }

    // Enemy identifier
    int GetEnmy(int asurx, int asury)
    {
        cout << "1";
        for (int i = 0; i < 18; i++)
        {
            cout << "2";
            if (asury == Asurs[i].Y && asurx == Asurs[i].X)
            {
                cout << "3";
                return i;
            }
            else
            {
                cout << " $*-*$ ";
                return 0;
            }
        }
        return 0;

    }

    // Pre Battle formalties
    void ReadyBattle(int TargetY, int TargetX)
    {
        char NewTile = GetTile(TargetY, TargetX);
        int ourEnmy = GetEnmy(TargetY, TargetX);
        switch (NewTile)
        {
        case 'Z':
            cout << "Cse";

            Fight(ourEnmy);
            break;

        case 'D':
            cout << "D";
            int ourEenmy = GetEnmy(TargetY, TargetX);
            Fight(ourEenmy);
            break;


        }
    }

    int Fight(int EnmyRoll_no)
    {
        Asur CurrentAsur = Asurs[EnmyRoll_no];
        while (true)
        {
            CurrentAsur.health -= PlayerAtt();
            cout << " A Player Atacked at= " << P_Health << endl;
            P_Health -= CurrentAsur.attack;
            cout << CurrentAsur.attack << " A Asur Attacked at=  " << CurrentAsur.health << endl;
            if (P_Health < 0)
            {
                cout << "You Died";
                exit(0);
            }
            if (CurrentAsur.health < 0)
            {

                cout << "Asur Died :";

                //SetTile(CurrentAsur.X, CurrentAsur.Y, '.');
                PrintLayout();
                system("PAuse");
                break;
            }
            PlayerMove();
        }
        return 0;
    }



private:
    // Stores Data from the Given File 
    vector<string>_levelData;

    // Player Properties
    int _Plx;
    int _Ply;
    int P_Health;
    int P_Attack;

    int _Winx;
    int _Winy;

    // Enmies properties
    struct Asur
    {
        int X;
        int Y;
        int health;
        int attack;
        int Exp;
    };

    vector<Asur>Asurs;


};
