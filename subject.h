#ifndef subject_h
#define subject_h

#include <string>
#include <sstream>

class Subject{
    //sub
    int val;
    bool isC;
    bool isG;
    bool isT;
    //Crit
    int critOwner;//0B 1R 2O 3Y
    int critType;//1 for Ass 2 for Mid 3 for Exam
    //Goal
    int goalOwner;//0B 1R 2O 3Y
    //Tile
    int tileType;//0Caff 1Lab 2Lec 3Stu 4Tut 5Net
    int tileNum;
public:
    //sub
    Subject();
    ~Subject();
    bool isCrit();
    bool isGoal();
    bool isTile();
    void setValue(int);
    int getValue();
    //Crit
    void setCrit();
    void buildCrit(int);
    int getCritOwner();
    int getCritType();
    void impCritType(int);
    std::string formatCrit();
    //Goal
    void setGoal();
    void setGoalOwner(int);
    int getGoalOwner();
    std::string formatGoal();
    //Tile
    void setTile();
    void setTileType(int);
    void setTileNum(int);
    int getTileType();
    int getTileNum();
    std::string formatTileVal();
    std::string formatTileNum();
    std::string formatTileName();
};

#endif /* subject_h */
