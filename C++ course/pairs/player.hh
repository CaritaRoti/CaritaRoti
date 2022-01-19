/* Class: Player
 * -------------
 * Represents a single player in pairs (memory) game.
 *
 * COMP.CS.110 K2021
 * */

#ifndef PLAYER_HH
#define PLAYER_HH

#include "card.hh"
#include <string>
#include <vector>

using namespace std;

class Player
{
public:
    /**
     * @brief Player Constructor: creates a player with the given name
     * @param name given name
     */
    Player(const string& name);


    /**
     * @brief get_name Returns the name of the player
     * @return the name of the player
     */
    string get_name() const;


    /**
     * @brief get_number_of_pairs Returns the number of pairs collected by the player so far
     * @return number of pairs collected by the player so far
     */
    unsigned int get_number_of_pairs() const;


    /**
     * @brief add_card Moves the given card from the game board for the player
     * @param card chosen card
     */
    void add_card(Card& card);


    /**
     * @brief print Prints the game status of the player: name and collected pairs so far
     */
    void print() const;

private:
    string name_;
    vector<Card> found_pairs_;
};

#endif // PLAYER_HH
