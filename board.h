#ifndef board_h
#define board_h

#include "subject.h"
#include "player.h"
#include <fstream>
#include <iostream>

class Player;

class Board {
    Subject s[22][11];
    int geese;
    std::string num2name(int);
    std::string num2res(int);
    void printSpace(int);
public:
    Board();
    ~Board();
    void buildAss(int, int);
    bool canBuildAss(int, int, bool);
    void print();
    void randomMap();
    bool giveRes(int, Player *, int);
    int findCritType(int);
    bool canBuildGoal(int, int);
    void buildGoal(int, int);
    bool canImp(int, int);
    void improve(int);
    int getGeese();
    void moveGeese(int, int, bool *);
    void saveBoard(std::ofstream &);
    void loadBoard(std::ifstream &);
};

#endif /* board_h */
