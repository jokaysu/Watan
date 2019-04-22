#include "player.h"

using namespace std;

bool Player::anyWin = false;

string Player::num2name(int n) {
    if (n == 0) return "Blue";
    if (n == 1) return "Red";
    if (n == 2) return "Orange";
    if (n == 3) return "Yellow";
    cout << "Fail 05" << endl;
    return "FAIL";
}

int Player::res2num(string s) {
    if (s == "CAFFEINE") return 0;
    if (s == "LAB") return 1;
    if (s == "LECTURE") return 2;
    if (s == "STUDY") return 3;
    if (s == "TUTORIAL") return 4;
    cout << "FAIL 10" << endl;
    return -1;
}

string Player::num2res(int n) {
    if (n == 0) return "CAFFEINE";
    if (n == 1) return "LAB";
    if (n == 2) return "LECTURE";
    if (n == 3) return "STUDY";
    if (n == 4) return "TUTORIAL";
    if (n == 5) return "NETFLIX";
    cout << "Fail 03" << endl;
    return "FAIL";
}

Player::Player() {
    anyWin = false;
    vp = 2;
    for (int i = 0; i < 5; ++i)
        res[i] = 0;
}

Player::~Player() { }

void Player::addCrit(int n) {
    crit.push_back(n);
}

void Player::addGoal(int n) {
    goal.push_back(n);
}

void Player::addRes(int num, int type) {
    res[type] += num;
}

void Player::printStatus(int p) {
    cout << num2name(p) << " has " << vp << " victory points, ";
    cout << res[0] << " caffeines, " << res[1] << " labs, ";
    cout << res[2] << " lectures, " << res[4] << " tutorials, and ";
    cout << res[3] << " studies." << endl;
}

void Player::printCrit(Board *b, int p) {
    cout << num2name(p) << " has completed:" << endl;
    for (int i = 0; i < crit.size(); ++i)
        cout << crit[i] << " " << b->findCritType(crit[i]) << endl;
}

bool Player::canBuildGoal() {
    if (res[3] >= 1 && res[4] >= 1)
        return true;
    else return false;
}

void Player::buildGoal() {
    res[3]--;
    res[4]--;
}

bool Player::canBuildAss() {
    if (res[0] >= 1 && res[1] >= 1 && res[2] >= 1 && res[4] >= 1)
        return true;
    else return false;
}

void Player::buildAss() {
    res[0]--;
    res[1]--;
    res[2]--;
    res[4]--;
    vp++;
    if (vp >= 10) anyWin = true;
}

bool Player::canImpMid() {
    if (res[2] >= 2 && res[3] >= 3)
        return true;
    else return false;
}

void Player::impMid() {
    res[2] -= 2;
    res[3] -= 3;
    vp++;
    if (vp >= 10) anyWin = true;
}

bool Player::canImpExam() {
    if (res[0] >= 3 && res[1] >= 2 && res[2] >= 2 &&
        res[4] >= 1 && res[3] >= 2) {
        return true;
    } else return false;
}

void Player::impExam() {
    res[0] -= 3;
    res[1] -= 2;
    res[2] -= 2;
    res[4] -= 1;
    res[3] -= 2;
    vp++;
    if (vp >= 10) anyWin = true;
}

void Player::getAforB(string res1, string res2) {
    res[res2num(res1)]++;
    res[res2num(res2)]--;
}

void Player::lost2geese(int p) {
    int sum = 0;
    for (int i = 0; i < 5; ++i) {
        sum += res[i];
    }
    if (sum >= 10) {
        int lost = sum / 2;
        cout << "Student " << num2name(p) << " loses " << lost << " resources ";
        cout << "to the geese. They lose:" << endl;
        int resLost[5] = {0, 0, 0, 0, 0};
        while (lost > 0) {
            int rd = rand() % sum + 1;
            int i = 0;
            while (rd > res[i]) {
                rd -= res[i];
                i++;
            }
            resLost[i]++;
            res[i]--;
            lost--;
            sum--;
        }
        for (int j = 0; j < 5; ++j) {
            if (resLost[j] != 0) {
                cout << resLost[j] << " " << num2res(j) << endl;
            }
        }
    }
}

bool Player::notZeroRes() {
    for (int i = 0; i < 5; ++i)
        if (res[i] > 0)
            return true;
    return false;
}

void Player::getRes(int n) {
    res[n]++;
}

void Player::loseRes(int n) {
    res[n]--;
}

void Player::stealBy(int stealer, int me, Player *sp) {
    int sum = 0;
    for (int i = 0; i < 5; ++i)
        sum += res[i];
    int rd = rand() % sum + 1;
    int i = 0;
    while (rd > res[i]) {
        rd -= res[i];
        i++;
    }
    res[i]--;
    sp->getRes(i);
    cout << "Student " << num2name(stealer) << " steals ";
    cout << num2res(i) << " from student " << num2name(me) << "." << endl;
}

void Player::savePlayer(std::ofstream &f) {
    for (int i = 0; i < 5; ++i)
        f << res[i] << " ";
    f << "g ";
    for (int i = 0; i < goal.size(); ++i)
        f << goal[i] << " ";
    f << "c ";
    for (int i = 0; i < crit.size(); ++i)
        f << crit[i] << " ";
    f << endl;
}

int Player::getVP() {
    return vp;
}

void Player::loadData(std::ifstream &f, Board *b, int cp) {
    int n;
    string line;
    getline(f, line);
    istringstream iss(line);
    for (int i = 0; i < 5; ++i) {
        iss >> n;
        res[i] = n;
    }
    char c;
    iss >> c;
    while (true) {
        //cout << c << " A " << endl;
            iss >> n;
            //cout << n << " A+ ";
            while (true) {
                goal.push_back(n);
                b->buildGoal(cp, n);
                if (!(iss >> n)) break;
            }
        // if (c == 'c') {
        iss >> c;
        iss >> c;
        iss >> c;
            iss >> n;
            //cout << c << " B ";
            while (true) {
                //cout << n << " C" << endl;
                crit.push_back(n);
                b->buildAss(cp, n);
                if (!(iss >> n)) break;
            }
        //}
        if (!(iss >> c)) {
            cout << "D" << endl;
            break;
        }
    }
}
