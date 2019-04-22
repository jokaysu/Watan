#include "game.h"

using namespace std;

void Game::setBoard(const char *c) {
    ifstream f;
    f.open(c);
    b.loadBoard(f);
    f.close();
}

void Game::loadGame(const char *c) {
    ifstream f;
    f.open(c);
    string str;
    getline(f, str);
    stringstream ss(str);
    ss >> curTurn;
    for (int i = 0; i < 4; ++i)
        p[i].loadData(f, &b, i);
    b.loadBoard(f);
    f.close();
}

void Game::genRes() {
    b.randomMap();
}

string Game::num2name(int n) {
    if (n == 0) return "Blue";
    if (n == 1) return "Red";
    if (n == 2) return "Orange";
    if (n == 3) return "Yellow";
    cout << "Fail 01" << endl;
    return "FAIL";
}

int Game::name2num(string s) {
    if (s == "Blue") return 0;
    if (s == "Red") return 1;
    if (s == "Orange") return 2;
    if (s == "Yellow") return 3;
    cout << "FAIL 09" << endl;
    return -1;
}

void Game::invalidCommand() {
    cout << "Invalid command." << endl;
}

int Game::gameBeginPrompt(int stu) {
    int ans = 0;
    cout << "Student " << num2name(stu);
    cout << ", where do you want to complete an Assignment?" << endl;
    cin >> ans;
    if (cin.eof()) {
        saveGame("backup.sv");
        exit(0);
    }
    while((ans > 53 || ans < 0) || (!b.canBuildAss(stu, ans, true))) {//add adj connot
        cout << "You cannot build here." << endl;
        cin >> ans;
        if (cin.eof()) {
            saveGame("backup.sv");
            exit(0);
        }
    }
    return ans;
}

int Game::rollDice(int pl) {
    cout << "Student " << num2name(pl);
    cout << "'s turn." << endl;
    p[pl].printStatus(pl);
    string s;
    while (true) {
        cin >> s;
        if (cin.eof()) {
            saveGame("backup.sv");
            exit(0);
        }
        if (s == "load") {
            loadDice = true;
        } else if (s == "fair") {
            loadDice = false;
        } else if (s == "roll") {
            break;
        } else invalidCommand();
    }
    int ans = 0;
    if (loadDice) {
        cout << "Input a roll between 2 and 12:" << endl;
        cin >> ans;
        if (cin.eof()) {
            saveGame("backup.sv");
            exit(0);
        }
        while (ans < 2 || ans > 12) {
            cout << "Invalid roll." << endl;
            cout << "Input a roll between 2 and 12:" << endl;
            cin >> ans;
            if (cin.eof()) {
                saveGame("backup.sv");
                exit(0);
            }
        }
    } else {
        ans = rand() % 6 + rand() % 6 + 2;
    }
    return ans;
}

void Game::moveGeese(int cp) {
    for (int i = 0; i < 4; ++i)
        p[i].lost2geese(i);
    cout << "Choose where to place the GEESE." << endl;
    int g;
    cin >> g;
    if (cin.eof()) {
        saveGame("backup.sv");
        exit(0);
    }
    while (g == b.getGeese()) {
        cout << "Should place in different tile." << endl;
        cout << "Choose where to place the GEESE." << endl;
        cin >> g;
        if (cin.eof()) {
            saveGame("backup.sv");
            exit(0);
        }
    }
    bool bo[4] = {false, false, false, false};
    b.moveGeese(cp, g, bo);
    if (!bo[0] && !bo[1] && !bo[2] && !bo[3]) {
        cout << "Student " << num2name(cp) << " has no students to steal from." << endl;
    } else {
        cout << "Student " << num2name(cp) << " can choose to steal from ";
        vector<int> stealList;
        for (int i = 0; i < 4; ++i) {
            if (bo[i] && p[i].notZeroRes())
                stealList.push_back(i);
        }
        for (int i = 0; i < stealList.size(); ++i) {
            if (i > 0) cout << ", ";
            cout << num2name(stealList[i]);
        }
        cout << "." << endl;
        cout << "Choose a student to steal from." << endl;
        string str;
        cin >> str;
        if (cin.eof()) {
            saveGame("backup.sv");
            exit(0);
        }
        p[name2num(str)].stealBy(cp, name2num(str), &(p[cp]));
    }
}

void Game::getRes(int n) {
    bool flag = true;
    for (int i = 0; i < 4; ++i)
        if (b.giveRes(n, &(p[i]), i))
            flag = false;
    if (flag) cout << "No students gained resources." << endl;
}

void Game::helpPrinting() {
    cout << "Valid commands:" << endl;
    cout << "board" << endl;
    cout << "status" << endl;
    cout << "criteria" << endl;
    cout << "achieve <goal>" << endl;
    cout << "complete <criterion>" << endl;
    cout << "improve <criterion>" << endl;
    cout << "trade <colour> <give> <take>" << endl;
    cout << "next" << endl;
    cout << "save <file>" << endl;
    cout << "help" << endl;
}

void Game::attemptAchieve() {
    int n;
    cin >> n;
    if (cin.eof()) {
        saveGame("backup.sv");
        exit(0);
    }
    if (b.canBuildGoal(curTurn % 4, n)) {
        if (p[curTurn % 4].canBuildGoal()) {
            b.buildGoal(curTurn % 4, n);
            p[curTurn % 4].buildGoal();
            p[curTurn % 4].addGoal(n);
        } else {//no resource
            cout << "You do not have enough resources." << endl;
        }
    } else {//cant build here
        cout << "You cannot build here." << endl;
    }
}

void Game::attemptComplete() {
    int n;
    cin >> n;
    if (cin.eof()) {
        saveGame("backup.sv");
        exit(0);
    }
    int cp = curTurn % 4;
    if (b.canBuildAss(cp, n, false)) {
        if (p[cp].canBuildAss()) {
            b.buildAss(cp, n);
            p[cp].buildAss();
            p[cp].addCrit(n);
        } else {//p
            cout << "You do not have enough resources." << endl;
        }
    } else {//b
        cout << "You cannot build here." << endl;
    }
}

void Game::attemptImprove() {
    int n;
    cin >> n;
    if (cin.eof()) {
        saveGame("backup.sv");
        exit(0);
    }
    int cp = curTurn % 4;
    int ct = b.findCritType(n);
    if (ct == 3 || (!(b.canImp(cp, n)))) {
        cout << "You cannot build here." << endl;
    } else if (ct == 1) {
        if (p[cp].canImpMid()) {
            b.improve(n);
            p[cp].impMid();
        } else {
            cout << "You do not have enough resources." << endl;
        }
    } else if (ct == 2) {
        if (p[cp].canImpExam()) {
            b.improve(n);
            p[cp].impExam();
        } else {
            cout << "You do not have enough resources." << endl;
        }
    }
    
}

void Game::attemptTrade() {
    string col, resGive, resTake;
    cin >> col >> resGive >> resTake;
    if (cin.eof()) {
        saveGame("backup.sv");
        exit(0);
    }
    int cp = curTurn % 4;
    cout << num2name(cp) << " offers " << col << " one ";
    cout << resGive << " for one " << resTake << "." << endl;
    cout << "Does " << col << " accept this offer?" << endl;
    string ans;
    cin >> ans;
    if (cin.eof()) {
        saveGame("backup.sv");
        exit(0);
    }
    while (ans != "yes" && ans != "no") {
        invalidCommand();
        cin >> ans;
        if (cin.eof()) {
            saveGame("backup.sv");
            exit(0);
        }
    }
    if (ans == "yes") {
        p[cp].getAforB(resTake, resGive);
        p[name2num(col)].getAforB(resGive,resTake);
    }
}

void Game::saveGame(std::string str) {
    ofstream f;
    f.open(str);
    f << curTurn << endl;
    for (int i = 0; i < 4; ++i)
        p[i].savePlayer(f);
    b.saveBoard(f);
    f.close();
}

Game::Game() {
    curTurn = -1;
    loadDice = false;
}

Game::~Game() { }

void Game::start(int n, const char *c) {
    if (n == 1) {//board
        setBoard(c);
    } else if (n == 2) {//load
        loadGame(c);
        b.print();
        goto label2;
    } else genRes();
    b.print();
    for(int i = 0; i < 4; ++i) {
        int r = gameBeginPrompt(i);
        b.buildAss(i, r);
        p[i].addCrit(r);
    }
    for(int i = 3; i >= 0; --i) {
        int r = gameBeginPrompt(i);
        b.buildAss(i, r);
        p[i].addCrit(r);
    }
    b.print();
    while(!Player::anyoneWin()) {//turn
        curTurn++;
    label2:
        int curPlayer = curTurn % 4;
        int d = rollDice(curPlayer);
        if (d == 7) moveGeese(curPlayer);
            else getRes(d);
        while (true) {//end of turn
            string str;
            cin >> str;
            if (cin.eof()) {
                saveGame("backup.sv");
                exit(0);
            }
            if (str == "next") {
                break;
            } else if (str == "board") {
                b.print();
            } else if (str == "status") {
                for (int i = 0; i < 4; ++i)
                    p[i].printStatus(i);
            } else if (str == "help") {
                helpPrinting();
            } else if (str == "criteria") {
                p[curPlayer].printCrit(&b, curPlayer);
            } else if (str == "achieve") {
                attemptAchieve();
            } else if (str == "complete") {
                attemptComplete();
            } else if (str == "improve") {
                attemptImprove();
            } else if (str == "trade") {
                attemptTrade();
            } else if (str == "save") {
                string ss;
                cin >> ss;
                if (cin.eof()) {
                    saveGame("backup.sv");
                    exit(0);
                }
                saveGame(ss);
            } else {
                invalidCommand();
                continue;
            }
        }//end of turn
    }//turn
    if (p[0].getVP() >= 10) cout << "Blue won!!!" << endl;
    if (p[1].getVP() >= 10) cout << "Red won!!!" << endl;
    if (p[2].getVP() >= 10) cout << "Orange won!!!" << endl;
    if (p[3].getVP() >= 10) cout << "Yellow won!!!" << endl;
}
