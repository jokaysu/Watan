#ifndef game_h
#define game_h

#include "board.h"
#include "player.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>

class Game {
    Board b;
    Player p[4];
    int curTurn;
    bool loadDice;
    void setBoard(const char *);
    void loadGame(const char *);
    void genRes();
    std::string num2name(int);
    int name2num(std::string);
    void invalidCommand();
    int gameBeginPrompt(int);
    int rollDice(int);
    void moveGeese(int);
    void getRes(int);
    void helpPrinting();
    void attemptAchieve();
    void attemptComplete();
    void attemptImprove();
    void attemptTrade();
    void saveGame(std::string);
public:
    Game();
    ~Game();
    void start(int, const char *);
};

#endif /* game_h */
