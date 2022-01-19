#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>

using namespace std;


class Player
{
public:
    Player(string name);

    void add_points(int pts);
    string get_name();
    int get_points();
    bool has_won();

private:
    string name_;
    int pts_;
};

#endif // PLAYER_HH
