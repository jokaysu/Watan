#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "game.h"

using namespace std;

int main(int argc, const char * argv[]) {
label:
    Game g;
    srand((int)time(NULL));
    bool flag = true;
    for (int i = 1; i <= argc / 2; ++i) {
        if (argv[i][1] == 's') {
            stringstream str(argv[i + 1]);
            int x;
            str >> x;
            srand(x);
        } else if (argv[i][1] == 'l') {
            flag = false;
            g.start(2, argv[i + 1]);
        } else if (argv[i][1] == 'b') {
            flag = false;
            g.start(1, argv[i + 1]);
        }
    }
    if (flag) g.start(0, argv[0]);
    cout << "Would you like to play again?" << endl;
    string ans;
    cin >> ans;
    if (ans == "yes") goto label;
}
