/* Player
 *
 * Contains the player name and a vector of found pairs
 */

#include "player.hh"
#include <vector>
#include <iostream>

using namespace std;

Player::Player(const string &name):
    name_(name)
{
    vector<Card> found_pairs_;
}


/**
 * @brief get_name returns the player name
 * @return player name
 */
string Player::get_name() const
{
    return name_;
}

/**
 * @brief get_number_of_pairs return the number of pairs the player has found
 * @return number of pairs
 */
unsigned int Player::get_number_of_pairs() const
{
    return found_pairs_.size();
}


/**
 * @brief add_card adds a card to the vector of pairs the player has found
 */
void Player::add_card(Card &card)
{
    found_pairs_.push_back(card);
}


/**
 * @brief print prints the amount of pairs the player has found
 */
void Player::print() const
{
    cout << "*** " << name_ << " has " << found_pairs_.size() <<" pair(s)." << endl;
}
