#include "subject.h"

Subject::Subject(){
    val = 0;
    isC = false;
    isG = false;
    isT = false;
    critOwner = -1;
    critType = 0;
    goalOwner = -1;
    tileNum = 0;
}

Subject::~Subject() { }

bool Subject::isCrit() {
    return isC;
}

bool Subject::isGoal() {
    return isG;
}

bool Subject::isTile() {
    return isT;
}

void Subject::setValue(int n) {
    val = n;
}

int Subject::getValue() {
    return val;
}

void Subject::setCrit() {
    isC = true;
}

void Subject::buildCrit(int n) {
    critOwner = n;
    critType = 1;
}

int Subject::getCritOwner() {
    return critOwner;
}

int Subject::getCritType() {
    return critType;
}

void Subject::impCritType(int n) {
    critType++;
}

std::string Subject::formatCrit() {
    std::string ans;
    std::stringstream ss;
    if (critOwner == -1) {
        ss << val;
        ans = ss.str();
        if (val < 10) ans = " " + ans;
    } else {
        if (critOwner == 0) ans = "B";
        if (critOwner == 1) ans = "R";
        if (critOwner == 2) ans = "O";
        if (critOwner == 3) ans = "Y";
        if (critType == 1) ans = ans + "A";
        if (critType == 2) ans = ans + "M";
        if (critType == 3) ans = ans + "E";
    }
    return ans;
}

void Subject::setGoal() {
    isG = true;
}

void Subject::setGoalOwner(int n){
    goalOwner = n;
}

int Subject::getGoalOwner() {
    return goalOwner;
}

std::string Subject::formatGoal() {
    std::string ans;
    std::stringstream ss;
    if (goalOwner == -1) {
        ss << val;
        ans = ss.str();
        if (val < 10) ans = " " + ans;
    } else {
        if (goalOwner == 0) ans = "B";
        if (goalOwner == 1) ans = "R";
        if (goalOwner == 2) ans = "O";
        if (goalOwner == 3) ans = "Y";
        ans = ans + "A";
    }
    return ans;
}

void Subject::setTile() {
    isT = true;
}

void Subject::setTileType(int n) {
    tileType = n;
}

void Subject::setTileNum(int n) {
    tileNum = n;
}

int Subject::getTileType() {
    return tileType;
}

int Subject::getTileNum() {
    return tileNum;
}

std::string Subject::formatTileVal() {
    std::string ans;
    std::stringstream ss;
    ss << val;
    ans = ss.str();
    if (val < 10) ans = " " + ans;
    return ans;
}

std::string Subject::formatTileNum() {
    std::string ans;
    std::stringstream ss;
    if (tileNum == 0) return "  ";
    ss << tileNum;
    ans = ss.str();
    if (tileNum < 10) ans = " " + ans;
    return ans;
}

std::string Subject::formatTileName() {
    if (tileType == 0) return "CAFFEINE";
    if (tileType == 1) return "LAB     ";
    if (tileType == 2) return "LECTURE ";
    if (tileType == 3) return "STUDY   ";
    if (tileType == 4) return "TUTORIAL";
    if (tileType == 5) return "NETFLIX ";
    return "FAIL 04";
}
