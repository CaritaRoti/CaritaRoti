/* Player class
*
* Player contains the amount of points the player has scored.
*/

#include "player.hh"

Player::Player(string name):
    name_(name)
{
    pts_ = 0;
}


/**
 * @brief add_points adds points to the player's current score
 * @param pts points to be added
 */
void Player::add_points(int pts)
{
    if(pts_ + pts > 50)
        pts_ = 25;
    else
        pts_ += pts;
}


/**
 * @brief get_name returns the player name
 * @return player name
 */
string Player::get_name()
{
    return name_;
}

/**
 * @brief get_points returns the current amount of points the player has scored
 * @return amount of points
 */
int Player::get_points()
{
    return pts_;
}


/**
 * @brief has_won checks if player has exactly 50 points
 * @return true = 50 points, false = other than 50 points
 */
bool Player::has_won()
{
    if(pts_ == 50)
        return true;
    else
        return false;
}
