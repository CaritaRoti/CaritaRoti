/* Class: Card
 * -----------
 * Represents a single card in pairs (memory) game.
 *
 * COMP.CS.110 K2021
 * */

#ifndef CARD_HH
#define CARD_HH

enum Visibility_type {OPEN, HIDDEN, EMPTY};
const char HIDDEN_CHAR = '#';
const char EMPTY_CHAR = '.';

class Card
{
public:
    /**
     * @brief Card Default constructor: creates an empty card
     */
    Card();


    /**
     * @brief Card Constructor: creates a hidden card with the given character
     * @param c given character
     */
    Card(const char c);


    /**
     * @brief set_letter Set the letter on the front side of the card
     * @param c letter
     */
    void set_letter(const char c);


    /**
     * @brief set_visibility Set card visibility
     * @param visibility OPEN/HIDDEN/EMPTY
     */
    void set_visibility(const Visibility_type visibility);


    /**
     * @brief get_letter Get the letter assigned to the card
     * @return assigned letter
     */
    char get_letter() const;


    /**
     * @brief get_visibility Get the visibility type of the card
     * @return OPEN/HIDDEN/EMPTY
     */
    Visibility_type get_visibility() const;


    /**
     * @brief turn Turns a card: changes the visibility from open to hidden and vice versa
     */
    void turn();


    /**
     * @brief print Prints a card based on its current visibility
     */
    void print() const;


    /**
     * @brief remove_from_game_board Removes a card from the game board: changes the visibility to empty
     */
    void remove_from_game_board();

private:
    char letter_;
    Visibility_type visibility_;
};

#endif // CARD_HH
