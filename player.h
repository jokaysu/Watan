#ifndef player_h
#define player_h

#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include "board.h"

class Board;

class Player{
    static bool anyWin;
    int vp;
    int res[5]; //0Caff 1Lab 2Lec 3Stu 4Tut
    std::vector<int> crit;
    std::vector<int> goal;
    std::string num2name(int);
    int res2num(std::string);
    std::string num2res(int);
public:
    Player();
    ~Player();
    static bool anyoneWin() {
        return anyWin;
    }
    void addCrit(int);
    void addGoal(int);
    void addRes(int, int);
    void printStatus(int);
    void printCrit(Board *, int);
    bool canBuildGoal();
    void buildGoal();
    bool canBuildAss();
    void buildAss();
    bool canImpMid();
    void impMid();
    bool canImpExam();
    void impExam();
    void getAforB(std::string, std::string);
    void lost2geese(int);
    bool notZeroRes();
    void getRes(int);
    void loseRes(int);
    void stealBy(int, int, Player *);
    void savePlayer(std::ofstream &);
    int getVP();
    void loadData(std::ifstream &, Board *, int);
};

#endif /* player_h */
