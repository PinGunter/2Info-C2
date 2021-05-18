//
// Created by salva on 18/5/21.
//

#ifndef BACKTRACK_PLAYER_H
#define BACKTRACK_PLAYER_H



#include <iostream>
#include <vector>

using namespace std;


struct Player {
    int id;     // we need some kind of identifier
    int score;

    Player();

    Player(int score);

    void autoID();

    bool operator==(const Player &other){ return this->id == other.id; }

    friend istream& operator>>(istream &is, Player &player);

    friend istream& operator>>(istream &is, vector <Player> &players);

private:
    static int uid;

};


#endif //BACKTRACK_PLAYER_H
