#include "board.h"

using namespace std;

string Board::num2name(int n) {
    if (n == 0) return "Blue";
    if (n == 1) return "Red";
    if (n == 2) return "Orange";
    if (n == 3) return "Yellow";
    cout << "Fail 02" << endl;
    return "FAIL";
}

string Board::num2res(int n) {
    if (n == 0) return "CAFFEINE";
    if (n == 1) return "LAB";
    if (n == 2) return "LECTURE";
    if (n == 3) return "STUDY";
    if (n == 4) return "TUTORIAL";
    if (n == 5) return "NETFLIX";
    cout << "Fail 03" << endl;
    return "FAIL";
}

void Board::printSpace(int n) {
    for (int i = 0; i < n; ++i)
        cout << " ";
}

Board::Board() {
    ifstream f;
    f.open("board.txt");
    int n = 0;
    for (int i = 1; i <= 21; ++i)
        for (int j = 1; j <= 11; ++j) {
            f >> n;
            s[i][j].setValue(n);
            if (n != -1) {
                if (i % 2 == 1 && j % 2 == 1) {
                    s[i][j].setCrit();
                } else if (i % 2 == 0 && j % 2 == 0) {
                    s[i][j].setTile();
                } else s[i][j].setGoal();
            }
        }
    f.close();
    geese = -1;
}

Board::~Board() { }

void Board::buildAss(int owner, int num) {
    for (int i = 1; i <= 21; ++i)
        for (int j = 1; j <= 11; ++j) {
            if(s[i][j].isCrit() &&
               s[i][j].getValue() == num) {
                s[i][j].buildCrit(owner);
            }
        }
}

bool Board::canBuildAss(int owner, int num, bool isBegin) {
    for (int i = 1; i <= 21; ++i)
        for (int j = 1; j <= 11; ++j)
            if (s[i][j].isCrit() && s[i][j].getValue() == num) {
                if (s[i][j].getCritOwner() != -1) return false;
                if (i - 2 >= 1)
                    if (s[i - 2][j].isCrit())
                        if (s[i - 2][j].getCritOwner() != -1)
                            return false;
                if (i + 2 <= 21)
                    if (s[i + 2][j].isCrit())
                        if (s[i + 2][j].getCritOwner() != -1)
                            return false;
                if ((i + j) % 4 == 2) {
                    if (j + 2 <= 11)
                        if (s[i][j + 2].isCrit())
                            if (s[i][j + 2].getCritOwner() != -1)
                                return false;
                } else {
                    if (j - 2 >= 1)
                        if (s[i][j - 2].isCrit())
                            if (s[i][j - 2].getCritOwner() != -1)
                                return false;
                }
                if (isBegin) return true;
                if (i - 1 >= 1)
                    if (s[i - 1][j].isGoal())
                        if (s[i - 1][j].getGoalOwner() == owner)
                            return true;
                if (i + 1 <= 21)
                    if (s[i + 1][j].isGoal())
                        if (s[i + 1][j].getGoalOwner() == owner)
                            return true;
                if ((i + j) % 4 == 2) {
                    if (j + 1 <= 11)
                        if (s[i][j + 1].isGoal())
                            if (s[i][j + 1].getGoalOwner() == owner)
                                return true;
                } else {
                    if (j - 1 >= 1)
                        if (s[i][j - 1].isCrit())
                            if (s[i][j - 1].getGoalOwner() == owner)
                                return true;
                }
                return false;
            }
    cout << "FAIL 07" << endl;
    return false;
}

void Board::print() {
    for (int i = 1; i <= 21; ++i) {
        for (int j = 1; j <= 11; ++j) {
            if (s[i][j].isCrit()) {
                if ((i + j) % 4 == 0) {
                    cout << "|" << s[i][j].formatCrit() << "|";
                    printSpace(5);
                } else {
                    printSpace(5);
                    cout << "|" << s[i][j].formatCrit() << "|";
                }
            } else if (s[i][j].isGoal()) {
                if (i % 2 == 1) {
                    cout << "--" << s[i][j].formatGoal() << "--";
                } else {
                    printSpace(3);
                    cout << s[i][j].formatGoal();
                    printSpace(4);
                }
            } else if (s[i][j].isTile()) {
                printSpace(2);
                cout << s[i][j].formatTileVal();
                printSpace(2);
            } else if (s[i - 1][j].isTile()) {
                printSpace(2);
                cout << s[i - 1][j].formatTileNum();
                printSpace(2);
            } else {
                if (j % 2 == 1) printSpace(9);
                else printSpace(6);
            }
        }//j loop
        cout << endl;
        if (i == 21) break;
        for (int j = 1; j <= 11; ++j) {
            if (s[i][j].isCrit()) {
                if (s[i + 1][j].getValue() != -1) {
                    if ((i + j) % 4 == 0) {
                        printSpace(3);
                        cout << "\\";
                        printSpace(5);
                    } else {
                        printSpace(5);
                        cout << "/";
                        printSpace(3);
                    }
                } else printSpace(9);
            } else if (s[i][j].isGoal()) {
                if (j % 2 == 1) {
                    if ((i + j) % 4 == 3) {
                        printSpace(3);
                        cout << "/";
                        printSpace(5);
                    } else {
                        if (s[i][j - 1].isTile()) printSpace(3);
                        else printSpace(5);
                        cout << "\\";
                        printSpace(3);
                    }
                } else printSpace(6);
            } else if (s[i][j].isTile()) {
                cout << s[i][j].formatTileName();
            } else if (s[i - 1][j].isTile() && s[i - 1][j].getValue() == geese) {
                cout << "GEESE ";
            } else {
                if (j % 2 == 1) printSpace(9);
                else printSpace(6);
            }
        }
        cout << endl;
    }//i loop
}

void Board::randomMap() {
    int arr[6] = {3, 3, 4, 4, 4, 1};
    int rd = 0;
    for (int i = 1; i <= 21; ++i)
        for (int j = 1;j <= 11; ++j)
            if (s[i][j].isTile()) {
                rd = rand() % 6;
                while (arr[rd] == 0) {//be careful #1
                    rd = rand() % 6;
                }
                s[i][j].setTileType(rd);
                arr[rd]--;
            }
    int brr[11] = {1, 2, 2, 2, 2, 0, 2, 2, 2, 2, 1};
    for (int i = 1; i <= 21; ++i)
        for (int j = 1; j <= 11; ++j)
            if (s[i][j].isTile() && s[i][j].getTileType() != 5) {
                rd = rand() % 11;
                while (brr[rd] == 0) {//be careful #2
                    rd = rand() % 11;
                }
                s[i][j].setTileNum(rd + 2);
                brr[rd]--;
            }
}

bool Board::giveRes(int n, Player *pp, int p) {
    bool gained = false;
    int res[6] = {0, 0, 0, 0, 0, 0};
    for (int i = 1; i <= 21; ++i)
        for (int j = 1; j <= 11; ++j)
            if (s[i][j].isTile()) {
                if (s[i][j].getTileNum() == n &&
                    s[i][j].getValue() != geese && s[i][j].getTileType() != 5) {
                    if (s[i - 1][j - 1].getCritOwner() == p) {
                        pp->addRes(s[i - 1][j - 1].getCritType(), s[i][j].getTileType());
                        gained = true;
                        res[s[i][j].getTileType()] += s[i - 1][j - 1].getCritType();
                    }
                    if (s[i - 1][j + 1].getCritOwner() == p) {
                        pp->addRes(s[i - 1][j + 1].getCritType(), s[i][j].getTileType());
                        gained = true;
                        res[s[i][j].getTileType()] += s[i - 1][j + 1].getCritType();
                    }
                    if (s[i + 1][j - 1].getCritOwner() == p) {
                        pp->addRes(s[i + 1][j - 1].getCritType(), s[i][j].getTileType());
                        gained = true;
                        res[s[i][j].getTileType()] += s[i + 1][j - 1].getCritType();
                    }
                    if (s[i + 1][j + 1].getCritOwner() == p) {
                        pp->addRes(s[i + 1][j + 1].getCritType(), s[i][j].getTileType());
                        gained = true;
                        res[s[i][j].getTileType()] += s[i + 1][j + 1].getCritType();
                    }
                    if (s[i + 3][j - 1].getCritOwner() == p) {
                        pp->addRes(s[i + 3][j - 1].getCritType(), s[i][j].getTileType());
                        gained = true;
                        res[s[i][j].getTileType()] += s[i + 3][j - 1].getCritType();
                    }
                    if (s[i + 3][j + 1].getCritOwner() == p) {
                        pp->addRes(s[i + 3][j + 1].getCritType(), s[i][j].getTileType());
                        gained = true;
                        res[s[i][j].getTileType()] += s[i + 3][j + 1].getCritType();
                    }
                }
            }
    if (gained) {
        cout << "Student " << num2name(p) << " gained:" << endl;
        for (int i = 0; i < 6; ++i)
            if (res[i] != 0)
                cout << res[i] << " " << num2res(i) << endl;
        return true;
    } else {
        return false;
    }
}

int Board::findCritType(int n) {
    for (int i = 1; i <= 21; ++i)
        for (int j = 1; j <= 11; ++j)
            if (s[i][j].isCrit() && s[i][j].getValue() == n)
                return s[i][j].getCritType();
    cout << "FAIL 05" << endl;
    return -1;
}

bool Board::canBuildGoal(int owner, int num) {
    for (int i = 1; i <= 21; ++i)
        for (int j = 1; j <= 11; ++j)
            if (s[i][j].isGoal() && s[i][j].getValue() == num) {
                if (s[i][j].getGoalOwner() != -1) return false;
                if (i - 1 >= 1)
                    if (s[i - 1][j].isCrit())
                        if (s[i - 1][j].getCritOwner() == owner)
                            return true;
                if (i + 1 <= 21)
                    if (s[i + 1][j].isCrit())
                        if (s[i + 1][j].getCritOwner() == owner)
                            return true;
                if (j - 1 >= 1)
                    if (s[i][j - 1].isCrit())
                        if (s[i][j - 1].getCritOwner() == owner)
                            return true;
                if (j + 1 <= 11)
                    if (s[i][j + 1].isCrit())
                        if (s[i][j + 1].getCritOwner() == owner)
                            return true;
                if (i - 2 >= 1)
                    if (s[i - 2][j].isGoal())
                        if (s[i - 2][j].getGoalOwner() == owner)
                            return true;
                if (i + 2 <= 21)
                    if (s[i + 2][j].isGoal())
                        if (s[i + 2][j].getGoalOwner() == owner)
                            return true;
                if (i - 1 >= 1 && j - 1 >= 1)
                    if (s[i - 1][j - 1].isGoal())
                        if (s[i - 1][j - 1].getGoalOwner() == owner)
                            return true;
                if (i - 1 >= 1 && j + 1 <= 11)
                    if (s[i - 1][j + 1].isGoal())
                        if (s[i - 1][j + 1].getGoalOwner() == owner)
                            return true;
                if (i + 1 <= 21 && j - 1 >= 1)
                    if (s[i + 1][j - 1].isGoal())
                        if (s[i + 1][j - 1].getGoalOwner() == owner)
                            return true;
                if (i + 1 <= 21 && j + 1 <= 11)
                    if (s[i + 1][j + 1].isGoal())
                        if (s[i + 1][j + 1].getGoalOwner() == owner)
                            return true;
                return false;
            }
    cout << "FAIL 06" << endl;
    return false;
}

void Board::buildGoal(int owner, int num) {
    for (int i = 1; i <= 21; ++i)
        for (int j = 1; j <= 11; ++j)
            if (s[i][j].isGoal() && s[i][j].getValue() == num) {
                s[i][j].setGoalOwner(owner);
            }
}

bool Board::canImp (int owner, int num) {
    for (int i = 1; i <= 21; ++i)
        for (int j = 1; j <= 11; ++j)
            if (s[i][j].isCrit() && s[i][j].getValue() == num) {
                if (s[i][j].getCritOwner() == owner) return true;
                else return false;
            }
    cout << "FAIL 08" << endl;
    return false;
}

void Board::improve(int n) {
    for (int i = 1; i <= 21; ++i)
        for (int j = 1; j <= 11; ++j)
            if (s[i][j].isCrit() && s[i][j].getValue() == n) {
                s[i][j].impCritType(n);
                return;
            }
}

int Board::getGeese() {
    return geese;
}

void Board::moveGeese(int cp, int val, bool *b) {
    geese = val;
    for (int i = 1; i <= 21; ++i)
        for (int j = 1; j <= 11; ++j)
            if (s[i][j].isTile() && s[i][j].getValue() == val) {
                b[s[i - 1][j - 1].getCritOwner()] = true;
                b[s[i - 1][j + 1].getCritOwner()] = true;
                b[s[i + 1][j - 1].getCritOwner()] = true;
                b[s[i + 1][j + 1].getCritOwner()] = true;
                b[s[i + 3][j - 1].getCritOwner()] = true;
                b[s[i + 3][j + 1].getCritOwner()] = true;
            }
    b[cp] = false;
}

void Board::saveBoard(std::ofstream &f) {
    int k = 0;
    for (int i = 1; i <= 21; ++i)
        for (int j = 1; j <= 11; ++j)
            if (s[i][j].isTile() && s[i][j].getValue() == k) {
                f << s[i][j].getTileType() << " ";
                if (s[i][j].getTileType() == 5) {//Netflix
                    f << "7 ";
                } else f << s[i][j].getTileNum() << " ";
                k++;
            }
    f << endl;
}

void Board::loadBoard(std::ifstream &f) {
    int k = 0;
    for (int i = 1; i <= 21; ++i)
        for (int j = 1; j <= 11; ++j)
            if (s[i][j].isTile() && s[i][j].getValue() == k) {
                int n;
                f >> n;
                s[i][j].setTileType(n);
                if (n != 5) { //not netflix
                    f >> n;
                    s[i][j].setTileNum(n);
                    k++;
                } else {
                    f >> n;
                    k++;
                }
            }
}
