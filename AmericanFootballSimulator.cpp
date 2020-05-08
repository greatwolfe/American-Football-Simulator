#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <Windows.h>
#include <direct.h>
#include <algorithm>

using namespace std;

struct player {
    string name;
    int throwing_power;
    int throwing_accuracy;
    int hand_eye;
    int catching;
    int speed;
    int dodging;
    int trucking;
    int tackling;
    int ball_tracking;
    int blocking;
    int leg_power;
    int punting;
    int kicking_power;
    int kicking_accuracy;
    int football_iq;
};

struct team {
    string name;
    //offensive positions
    player qb;
    player wr1;
    player wr2;
    player te;
    player rb1;
    player rb2;
    player center;
    player tackle1;
    player tackle2;
    player guard1;
    player guard2;
    //defensive positions
    player safety1;
    player safety2;
    player cb1;
    player cb2;
    player outlb1;
    player outlb2;
    player midlb;
    player end1;
    player end2;
    player tackle3;
    player tackle4;
    //special team
    player kicker;
    player punter;
};

struct game {
    team home;
    team away;
    int passsuccess;
    int passfail;
    int rushsuccess;
    int rushfail;
    int quarter;
    int time;
    int homescore;
    int awayscore;
    int curteam;
    int yard;
};

string curpath() {
    char buf[256];
    GetCurrentDirectoryA(256, buf);
    return string(buf) + '\\';
}

//compares strings a and b while ignoring case
bool iequals(const string& a, const string& b) {
    return equal(a.begin(), a.end(), b.begin(), b.end(), [](char a, char b) {
        return tolower(a) == tolower(b);
        });
}

//compares string to see if it only containts integers
bool is_num(const string& a) {
    return !a.empty() && find_if(a.begin(), a.end(), [](unsigned char c) {return !isdigit(c); }) == a.end();
}

// checks if the directory exists
int dirExists(const char* path) {
    struct stat info;
    if (stat(path, &info) != 0) return 0;
    else if (info.st_mode & S_IFDIR) return 1;
    else return 0;
}
// checks if the file exists
bool fileexists(const string name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

// createplayer, serializes a player into the players folder
void createplayer() {
    player addition;
    string messagestring;
    cout << "What is the player's name?\n";
    getline(cin, messagestring);
    addition.name = messagestring;
    for (int x = 0; x < 15; x++) {
        if (x == 0) cout << "What is the player's throwing power?\n";
        else if (x == 1) cout << "What is the player's throwing accuracy?\n";
        else if (x == 2) cout << "What is the player's hand-eye?\n";
        else if (x == 3) cout << "What is the player's catching?\n";
        else if (x == 4) cout << "What is the player's speed?\n";
        else if (x == 5) cout << "What is the player's dodging?\n";
        else if (x == 6) cout << "What is the player's trucking?\n";
        else if (x == 7) cout << "What is the player's tackling?\n";
        else if (x == 8) cout << "What is the player's ball tracking?\n";
        else if (x == 9) cout << "What is the player's blocking?\n";
        else if (x == 10) cout << "What is the player's leg power?\n";
        else if (x == 11) cout << "What is the player's punting?\n";
        else if (x == 12) cout << "What is the player's kicking power?\n";
        else if (x == 13) cout << "What is the player's kicking accuracy?\n";
        else if (x == 14) cout << "What is the player's football IQ?\n";

        getline(cin, messagestring);
        char* message = new char[messagestring.size() + 1];
        copy(messagestring.begin(), messagestring.end(), message);
        message[messagestring.size()] = '\0';
        if (is_num(message)) {
            if (x == 0) addition.throwing_power = stoi(message);
            else if (x == 1) addition.throwing_accuracy = stoi(message);
            else if (x == 2) addition.hand_eye = stoi(message);
            else if (x == 3) addition.catching = stoi(message);
            else if (x == 4) addition.speed = stoi(message);
            else if (x == 5) addition.dodging = stoi(message);
            else if (x == 6) addition.trucking = stoi(message);
            else if (x == 7) addition.tackling = stoi(message);
            else if (x == 8) addition.ball_tracking = stoi(message);
            else if (x == 9) addition.blocking = stoi(message);
            else if (x == 10) addition.leg_power = stoi(message);
            else if (x == 11) addition.punting = stoi(message);
            else if (x == 12) addition.kicking_power = stoi(message);
            else if (x == 13) addition.kicking_accuracy = stoi(message);
            else if (x == 14) addition.football_iq = stoi(message);
            continue;
        }
        x--;
    }
    const string path = curpath();
    const int x = curpath().size();
    char charpath[257];
    path.copy(charpath, x + 1);
    charpath[x] = '\0';
    strcat_s(charpath, "Players\\");
    if (!dirExists(charpath)) {
        _mkdir(charpath);
    }
    ofstream myfile;
    myfile.open(charpath + addition.name);
    myfile << addition.name << "\n";
    myfile << addition.throwing_power << "\n";
    myfile << addition.throwing_accuracy << "\n";
    myfile << addition.hand_eye << "\n";
    myfile << addition.catching << "\n";
    myfile << addition.speed << "\n";
    myfile << addition.dodging << "\n";
    myfile << addition.trucking << "\n";
    myfile << addition.tackling << "\n";
    myfile << addition.ball_tracking << "\n";
    myfile << addition.blocking << "\n";
    myfile << addition.leg_power << "\n";
    myfile << addition.punting << "\n";
    myfile << addition.kicking_power << "\n";
    myfile << addition.kicking_accuracy << "\n";
    myfile << addition.football_iq << "\n";
}

// convertfiletoteam converts a text file to a team
team convertfiletoteam(const string path, string teamname) {
    team addition;
    int x;
    string s;
    ifstream myfile;
    addition.name = teamname;

    myfile.open(path);
    if (!myfile) {
        cout << "File couldn't open\n";
    }
    int z = 0;
    while (getline(myfile, s)) {
        player person;
        person.name = s;
        for (int t = 0; t < 15; t++) {
            getline(myfile, s);
            x = stoi(s);
            if (t == 0) person.throwing_power = x;
            else if (t == 1) person.throwing_accuracy = x;
            else if (t == 2) person.hand_eye = x;
            else if (t == 3) person.catching = x;
            else if (t == 4) person.speed = x;
            else if (t == 5) person.dodging = x;
            else if (t == 6) person.trucking = x;
            else if (t == 7) person.tackling = x;
            else if (t == 8) person.ball_tracking = x;
            else if (t == 9) person.blocking = x;
            else if (t == 10) person.leg_power = x;
            else if (t == 11) person.punting = x;
            else if (t == 12) person.kicking_power = x;
            else if (t == 13) person.kicking_accuracy = x;
            else if (t == 14) person.football_iq = x;
        }
        if (z == 0) addition.qb = person;
        else if (z == 1) addition.wr1 = person;
        else if (z == 2) addition.wr2 = person;
        else if (z == 3) addition.te = person;
        else if (z == 4) addition.rb1 = person;
        else if (z == 5) addition.rb2 = person;
        else if (z == 6) addition.center = person;
        else if (z == 7) addition.tackle1 = person;
        else if (z == 8) addition.tackle2 = person;
        else if (z == 9) addition.guard1 = person;
        else if (z == 10) addition.guard2 = person;
        else if (z == 11) addition.safety1 = person;
        else if (z == 12) addition.safety2 = person;
        else if (z == 13) addition.cb1 = person;
        else if (z == 14) addition.cb2 = person;
        else if (z == 15) addition.outlb1 = person;
        else if (z == 16) addition.outlb2 = person;
        else if (z == 17) addition.midlb = person;
        else if (z == 18) addition.end1 = person;
        else if (z == 19) addition.end2 = person;
        else if (z == 20) addition.tackle3 = person;
        else if (z == 21) addition.tackle4 = person;
        else if (z == 22) addition.kicker = person;
        else if (z == 23) addition.punter = person;
        z++;
    }

    return addition;
}

// convertfiletoplayer converts a text file to a player
player convertfiletoplayer(const string path, string name) {
    player person;
    int x;
    string s;
    ifstream myfile;

    myfile.open(path);
    if (!myfile) {
        cout << "File couldn't open\n";
        return person;
    }
    person.name = name;
    int z = 0;
    while (myfile >> s) {
        if (!is_num(s)) continue;
        x = stoi(s);
        if (z == 0) person.throwing_power = x;
        else if (z == 1) person.throwing_accuracy = x;
        else if (z == 2) person.hand_eye = x;
        else if (z == 3) person.catching = x;
        else if (z == 4) person.speed = x;
        else if (z == 5) person.dodging = x;
        else if (z == 6) person.trucking = x;
        else if (z == 7) person.tackling = x;
        else if (z == 8) person.ball_tracking = x;
        else if (z == 9) person.blocking = x;
        else if (z == 10) person.leg_power = x;
        else if (z == 11) person.punting = x;
        else if (z == 12) person.kicking_power = x;
        else if (z == 13) person.kicking_accuracy = x;
        else if (z == 14) person.football_iq = x;
        z++;
    }
    myfile.close();
    return person;
}

void addcharactertofile(const player person, const string path) {
    ofstream myfile;
    myfile.open(path, ios_base::app);
    myfile << person.name << "\n";
    myfile << person.throwing_power << "\n";
    myfile << person.throwing_accuracy << "\n";
    myfile << person.hand_eye << "\n";
    myfile << person.catching << "\n";
    myfile << person.speed << "\n";
    myfile << person.dodging << "\n";
    myfile << person.trucking << "\n";
    myfile << person.tackling << "\n";
    myfile << person.ball_tracking << "\n";
    myfile << person.blocking << "\n";
    myfile << person.leg_power << "\n";
    myfile << person.punting << "\n";
    myfile << person.kicking_power << "\n";
    myfile << person.kicking_accuracy << "\n";
    myfile << person.football_iq << "\n";
}

// createteam, serializes a team into the teams folder
void createteam() {
    team addition;
    string messagestring;
    cout << "What is the team's name?\n";
    getline(cin, messagestring);
    addition.name = messagestring;
    const string path = curpath();
    const int x = curpath().size();
    char charpath2[257];
    path.copy(charpath2, x + 1);
    charpath2[x] = '\0';
    strcat_s(charpath2, "Players\\");

    char charpath[257];
    path.copy(charpath, x + 1);
    charpath[x] = '\0';
    strcat_s(charpath, "Teams\\");
    if (!dirExists(charpath)) {
        _mkdir(charpath);
    }
    string charpathstring = "";
    for (int n = 0; n < 257; n++) {
        charpathstring += charpath[n];
        if (charpath[n + 1] == '\0') break;
    }
    charpathstring.append(addition.name);
    ofstream myfile;
    myfile.open(charpathstring);
    for (int t = 0; t < 24; t++) {
        for (bool x = true; x;) {
            if (t == 0) cout << "Who is the Quarterback?\n";
            else if (t == 1) cout << "Who is the first Wide Receiver?\n";
            else if (t == 2) cout << "Who is the second Wide Receiver?\n";
            else if (t == 3) cout << "Who is the Tight End?\n";
            else if (t == 4) cout << "Who is the first Running Back?\n";
            else if (t == 5) cout << "Who is the second Running Back?\n";
            else if (t == 6) cout << "Who is the Center?\n";
            else if (t == 7) cout << "Who is the first Offensive Tackle?\n";
            else if (t == 8) cout << "Who is the second Offensive Tackle?\n";
            else if (t == 9) cout << "Who is the first Guard?\n";
            else if (t == 10) cout << "Who is the second Guard?\n";
            else if (t == 11) cout << "Who is the first Safety?\n";
            else if (t == 12) cout << "Who is the second Safety?\n";
            else if (t == 13) cout << "Who is the first Cornerback?\n";
            else if (t == 14) cout << "Who is the second Cornerback?\n";
            else if (t == 15) cout << "Who is the first Outside Linebacker?\n";
            else if (t == 16) cout << "Who is the second Outside Linebacker?\n";
            else if (t == 17) cout << "Who is the Middle Linebacker?\n";
            else if (t == 18) cout << "Who is the first End?\n";
            else if (t == 19) cout << "Who is the second End?\n";
            else if (t == 20) cout << "Who is the first Defensive Tackle?\n";
            else if (t == 21) cout << "Who is the second Defensive Tackle?\n";
            else if (t == 22) cout << "Who is the Kicker?\n";
            else if (t == 23) cout << "Who is the Punter?\n";
            getline(cin, messagestring);
            string charpath2string = "";
            for (int n = 0; n < 257; n++) {
                charpath2string += charpath2[n];
                if (charpath2[n + 1] == '\0') break;
            }
            charpath2string.append(messagestring);
            char newarray[257];
            strcpy_s(newarray, charpath2string.c_str());
            if (fileexists(newarray) && !empty(messagestring)) {
                player helper = convertfiletoplayer(charpath2string, messagestring);
                addcharactertofile(helper, charpathstring);
                if (t == 0) addition.qb = helper;
                else if (t == 1) addition.wr1 = helper;
                else if (t == 2) addition.wr2 = helper;
                else if (t == 3) addition.te = helper;
                else if (t == 4) addition.rb1 = helper;
                else if (t == 5) addition.rb2 = helper;
                else if (t == 6) addition.center = helper;
                else if (t == 7) addition.tackle1 = helper;
                else if (t == 8) addition.tackle2 = helper;
                else if (t == 9) addition.guard1 = helper;
                else if (t == 10) addition.guard2 = helper;
                else if (t == 11) addition.safety1 = helper;
                else if (t == 12) addition.safety2 = helper;
                else if (t == 13) addition.cb1 = helper;
                else if (t == 14) addition.cb2 = helper;
                else if (t == 15) addition.outlb1 = helper;
                else if (t == 16) addition.outlb2 = helper;
                else if (t == 17) addition.midlb = helper;
                else if (t == 18) addition.end1 = helper;
                else if (t == 19) addition.end2 = helper;
                else if (t == 20) addition.tackle3 = helper;
                else if (t == 21) addition.tackle4 = helper;
                else if (t == 22) addition.kicker = helper;
                else if (t == 23) addition.punter = helper;

                break;
            }
            else continue;
        }
    }
}

// traverse through the creation zone menu
void creationzone() {
    for (bool x = true; x;) {
        cout << "What would you like to do?\n";
        cout << "Create Player\n";
        cout << "Create Team\n";
        cout << "Exit\n";
        string messagestring;
        getline(cin, messagestring);
        char* message = new char[messagestring.size() + 1];
        copy(messagestring.begin(), messagestring.end(), message);
        message[messagestring.size()] = '\0';
        if (iequals(message, "Exit")) {
            return;
        }
        else if (iequals(message, "Create Player")) {
            createplayer();
        }
        else if (iequals(message, "Create Team")) {
            createteam();
        }
    }
}

// rush performs a rush with the current character
int rush(const team offence, const team defence, const player carrier, int yard) {
    player defender;
    for (int x = 0; x < 3; x++) {
        if (x == 0) {
            if (rand() % 2 == 1) defender = defence.cb1;
            else defender = defence.cb2;
        }
        else if (x == 1) {
            defender = defence.midlb;
        }
        else if (rand() % 2 == 1) defender = defence.safety1;
        else defender = defence.safety2;
        if (rand() % (carrier.speed + defender.speed) < defender.speed / 2) {
            cout << carrier.name << " ran by " << defender.name << "\n";
            yard += carrier.speed / 10;
        }
        else if (rand() % (carrier.trucking + defender.tackling) < defender.trucking / 2) {
            cout << carrier.name << " knocked over " << defender.name << "\n";
            yard += carrier.speed / 10;
        }
        else {
            cout << defender.name << " tackled " << carrier.name << "\n";
            return yard;
        }
    }
    return 100;
}

// pass performs a pass with the current character
int pass(const team offence, const team defence, const player catcher, int yard) {
    player defender;
    if (rand() % 2 == 0) defender = defence.cb1;
    else defender = defence.cb2;
    int z = offence.qb.throwing_accuracy + catcher.ball_tracking + catcher.hand_eye;
    int y = defender.ball_tracking + defender.hand_eye;
    if (rand() % (z + y) < z + 10) {
        cout << catcher.name << " caught a pass\n";
        rush(offence, defence, catcher, yard + 6);
    }
    cout << defender.name << " knocked the ball out of the air \n";
    return 0;
}

// start of game/after half-time kick-off
int kickoff(const team offence, const team defence, game curgame) {
    int kick = defence.kicker.kicking_power;
    player returner;
    kick = min(max(10, kick + rand() % 36), kick - rand() % 16, 100);
    if (kick > 50) {
        //check if the kick is out of bounds
        if (defence.kicker.kicking_accuracy < rand() % 50) {
            cout << "Ball was kicked out of bounds\n";
            curgame.time -= 7;
            return 35;
        }
    }
    if (kick >= 100) { 
        cout << "Ball was kicked into the the end-zone\n";
        curgame.time -= 10;
        return 20; 
    }
    if (rand() % 2 == 1) returner = offence.wr1;
    else returner = offence.rb1;
    cout << returner.name << " caught the ball at the " << kick << "-yard line\n";
    curgame.time -= kick / 10;
    return rush(offence, defence, returner, kick);
}

// determines what play the team will do and then performs that play.
void play(game *curgame) {
    team offence;
    team defence;
    // set which teams are on offence and defence based on curgame.curteam
    if (curgame->curteam == 0) {
        offence = curgame->home;
        defence = curgame->away;
    }
    else {
        offence = curgame->away;
        defence = curgame->home;
    }
    // start of game/after half-time kick-off
    if (curgame->time == 900 && (curgame->quarter == 0 || curgame->quarter == 2)) {
        curgame->yard = 0;
        curgame->yard = kickoff(offence, defence, *curgame);
        curgame->time -= rand() & 30 + 10;
    }
    else if (rand() % 2 == 0) {
        //pass
        int x = rand() % 3;
        if (x == 0) pass(offence, defence, offence.wr1, curgame->yard);
        else if (x == 1) pass(offence, defence, offence.wr2, curgame->yard);
        else pass(offence, defence, offence.te, curgame->yard);
        curgame->time -= rand() & 30 + 10;
    }
    else {
        //rush
        if (rand() % 3 == 0) curgame->yard = rush(offence, defence, offence.rb2, curgame->yard - 5);
        else curgame->yard = rush(offence, defence, offence.rb1, curgame->yard - 5);
        curgame->time -= rand() & 30 + 10;
    }
}

// plays the touchdown play
int touchdown(const team offence, const team defence) {
    int x = 5;
    if (rand() % (offence.kicker.kicking_accuracy + defence.tackle3.blocking) > offence.kicker.kicking_accuracy * 2) {
        x = 7;
        cout << defence.tackle3.name << " blocked the field goal\n";
        return x;
    }
    cout << "field goal good\n";
    return x;
}

// begins the game process
void startgame(game curgame) {
    curgame.curteam = rand() % 2;
    curgame.yard = 0;
    int down = 0;
    int preyard = 0;
    while (curgame.quarter < 4) {
        curgame.time = 900;
        while (curgame.time > 0) {
            preyard = curgame.yard;
            play(&curgame);
            down++;
            if (curgame.yard >= 100) {
                if (curgame.curteam == 1) {
                    curgame.curteam = 0;
                    //away team touchdown
                    curgame.yard = kickoff(curgame.home, curgame.away, curgame);
                    curgame.awayscore += touchdown(curgame.away, curgame.home);
                }
                else {
                    curgame.curteam = 1;
                    //home team touchdown
                    curgame.yard = kickoff(curgame.away, curgame.home, curgame);
                    curgame.homescore += touchdown(curgame.home, curgame.away);
                }
            }
            else if (curgame.yard - 10 >= preyard) {
                down = 0;
            }
            else if (down > 4) {
                down = 0;
                if (curgame.curteam == 1) curgame.curteam = 0;
                else curgame.curteam = 1;
            }
        }
        cout << "end of quarter " << curgame.quarter + 1 << "\n";
        curgame.quarter++;
    }
    cout << curgame.home.name << " Scored: " << curgame.homescore << " points\n";
    cout << curgame.away.name << " Scored: " << curgame.awayscore << " points\n";
}

// playgame, traverse through the playgame menu, setting home and away teams
void playgame() {
    game curgame;
    curgame.quarter = 0;
    curgame.time = 900;
    curgame.homescore = 0;
    curgame.awayscore = 0;
    curgame.passsuccess = 0;
    curgame.passfail = 0;
    curgame.rushsuccess = 0;
    curgame.rushfail = 0;
    const string path = curpath();
    const int x = curpath().size();
    char charpath[257];
    path.copy(charpath, x + 1);
    charpath[x] = '\0';
    strcat_s(charpath, "Teams\\");
    if (!dirExists(charpath)) {
        cout << "No Teams Exist\n";
    }
    int z = 0;
    for (bool x = true; x;) {
        if (z == 0) cout << "Who is the home team?\n";
        else if (z == 1) cout << "Who is the away team?\n";
        string messagestring;
        string charpathstring = "";
        team helperteam;
        getline(cin, messagestring);
        for (int n = 0; n < 257; n++) {
            charpathstring += charpath[n];
            if (charpath[n + 1] == '\0') break;
        }
        charpathstring.append(messagestring);
        char newarray[257];
        strcpy_s(newarray, charpathstring.c_str());
        if (fileexists(newarray) && !empty(messagestring)) {
            helperteam = convertfiletoteam(newarray, messagestring);
        }
        else continue;
        if (z == 0) curgame.home = helperteam;
        else { 
            curgame.away = helperteam; 
            break;
        }
        z++;
    }
    startgame(curgame);
}

// main, traverse through the main menu
int main()
{
    for (bool x = true; x;) {
        cout << "What would you like to do?\n";
        cout << "Creation Zone\n";
        cout << "Play Game\n";
        cout << "Exit\n";
        string messagestring;
        getline(cin, messagestring);
        char* message = new char[messagestring.size() + 1];
        copy(messagestring.begin(), messagestring.end(), message);
        message[messagestring.size()] = '\0';
        if (iequals(message, "Exit")) {
            return 0;
        }
        else if (iequals(message, "Play Game")) {
            playgame();
        }
        else if (iequals(message, "Creation Zone")) {
            creationzone();
        }
    }
}
