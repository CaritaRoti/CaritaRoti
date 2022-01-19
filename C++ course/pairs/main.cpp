/* Pairs
 *
 * This program generates a pairs (memory) game. The game has a variant
 * number of cards and players. At the beginning, the program also asks for a
 * seed value, since the cards will be set randomly in the game board.
 * 
 * On each round, the player in turn gives the coordinates of two cards
 * (totally four numbers). After that the given cards will be turned as
 * visible and told if they are pairs or not. If they are pairs, they are
 * removed from the game board, the score of the player is increased, and
 * a new turn is given for the player. If the cards are not pairs, they
 * will be  turned hidden again, and the next player will be in turn.
 *  
 * The program checks if the user-given coordinates are legal. The cards
 * determined by the coordinates must be found in the game board.
 *  
 * After each change, the game board is printed again. The cards are
 * described as letters, starting from A and lasting so far as there are
 * cards. In printing the game board, a visible card is shown as its letter,
 * a hidden one as the number sign (#), and a removed one as a dot.
 *  
 * Game will end when all pairs have been found, and the game board is
 * empty. The program tells who has/have won, i.e. collected most pairs.
 */

#include "player.hh"
#include "card.hh"
#include <iostream>
#include <vector>
#include <random>

using namespace std;

const string INPUT_AMOUNT_OF_CARDS = "Enter the amount of cards (an even number): ";
const string INPUT_SEED = "Enter a seed value: ";
const string INPUT_AMOUNT_OF_PLAYERS = "Enter the amount of players (one or more): ";
const string INPUT_CARDS = "Enter two cards (x1, y1, x2, y2), or q to quit: ";
const string INVALID_CARD = "Invalid card.";
const string FOUND = "Pairs found.";
const string NOT_FOUND = "Pairs not found.";
const string GIVING_UP = "Why on earth you are giving up the game?";
const string GAME_OVER = "Game over!";

const unsigned int STARTING_ROW_COLUMN = 0;

using Game_row_type = vector<Card>;
using Game_board_type = vector<vector<Card>>;


/**
 * @brief stoi_with_check Casts the given string into the corresponding
 * positive integer
 * @param str given string
 * @return Corresponding integer or 0 if casting failed
 */
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}


/**
 * @brief init_with_empties Fills the game board with empty cards
 * @param g_board game board
 * @param rows number of rows on the game board
 * @param columns number of columns on the game board
 */
void init_with_empties(Game_board_type& g_board, unsigned int rows, unsigned int columns)
{
    g_board.clear();
    Game_row_type row;
    for(unsigned int i = STARTING_ROW_COLUMN; i < columns; ++i)
    {
        Card card;
        row.push_back(card);
    }
    for(unsigned int i = STARTING_ROW_COLUMN; i < rows; ++i)
    {
        g_board.push_back(row);
    }
}


/**
 * @brief next_free Finds the next free position in the game board (g_board), 
 * starting from the given position start and continuing from the beginning if needed.
 * (Called only by the function init_with_cards.)
 * @param g_board game board
 * @param lookup_start starting location for the free-position-search
 * @return the next free empty card location
 */
unsigned int next_free(Game_board_type& g_board, unsigned int lookup_start)
{
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    for(unsigned int i = lookup_start; i < rows * columns; ++i)
    {
        if(g_board.at(i / columns).at(i % columns).get_visibility() == EMPTY)
        {
            return i;
        }
    }
    
    // If no free positions are found after desired starting position, the program 
    // will look for them starting from the beginning of the board
    for(unsigned int i = STARTING_ROW_COLUMN; i < lookup_start; ++i)
    {
        if(g_board.at(i / columns).at(i % columns).get_visibility() == EMPTY)
        {
            return i;
        }
    }
    
    // You should never reach this
    std::cout << "No more empty spaces" << std::endl;
    return rows * columns - 1;
}


/**
 * @brief init_with_cards Initializes the given game board (g_board) with randomly 
 * generated cards, based on the given seed value.
 * @param g_board game board
 * @param seed randomEng seed
 */
void init_with_cards(Game_board_type& g_board, int seed)
{
    const unsigned int rows = g_board.size();
    const unsigned int columns = g_board.at(0).size();

    // Drawing a cell to be filled
    std::default_random_engine randomEng(seed);
    std::uniform_int_distribution<int> distr(0, rows * columns - 1);
    distr(randomEng);

    // If the drawn cell is already filled with a card, next empty cell will be used.
    // (The next empty cell is searched for circularly, see function next_free.)
    for(unsigned int i = 0, c = 'A'; i < rows * columns - 1; i += 2, ++c)
    {
        // Adding two identical cards (pairs) on the game board
        for(unsigned int j = 0; j < 2; ++j)
        {
            unsigned int cell = distr(randomEng);
            cell = next_free(g_board, cell);
            g_board.at(cell / columns).at(cell % columns).set_letter(c);
            g_board.at(cell / columns).at(cell % columns).set_visibility(HIDDEN);
        }
    }
}


/**
 * @brief print_line_with_charPrints a line consisting of the given character c.
 * The length of the line is given in the parameter line_length.
 * (Called only by the function print.)
 * @param c
 * @param line_length
 */
void print_line_with_char(char c, unsigned int line_length)
{
    for(unsigned int i = 0; i < line_length * 2 + 7; ++i)
    {
        cout << c;
    }
    cout << endl;
}


/**
 * @brief print Prints a variable-length game board with borders
 * @param g_board game board
 */
void print(const Game_board_type& g_board)
{
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    print_line_with_char('=', columns);
    cout << "|   | ";
    for(unsigned int i = STARTING_ROW_COLUMN; i < columns; ++i)
    {
        cout << i + 1 << " ";
    }
    cout << "|" << endl;
    print_line_with_char('-', columns);
    for(unsigned int i = STARTING_ROW_COLUMN; i < rows; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = STARTING_ROW_COLUMN; j < columns; ++j)
        {
            g_board.at(i).at(j).print();
            cout << " ";
        }
        cout << "|" << endl;
    }
    print_line_with_char('=', columns);
}


/**
 * @brief ask_product_and_calculate_factors Asks the desired product from the user,
 * and calculates the factors of the product such that the factor as near
 * to each other as possible
 * @param smaller_factor smaller factor
 * @param bigger_factor bigger factor
 * @return the amount of pairs on the game board
 */
uint ask_product_and_calculate_factors(unsigned int& smaller_factor, 
                                       unsigned int& bigger_factor)
{
    unsigned int product = 0;
    while(not (product > 0 and product % 2 == 0))
    {
        std::cout << INPUT_AMOUNT_OF_CARDS;
        string product_str = "";
        std::getline(std::cin, product_str);
        product = stoi_with_check(product_str);
    }

    for(unsigned int i = 1; i * i <= product; ++i)
    {
        if(product % i == 0)
        {
            smaller_factor = i;
        }
    }
    bigger_factor = product / smaller_factor;

    uint number_of_pairs = product/2;
    return number_of_pairs;
}


/**
 * @brief create_players Asks the user for the amount of players and their names.
 * Creates the players as Player objects.
 * @return vector containing the Player objects.
 */
vector<Player> create_players()
{
    string input;
    uint player_amount = 0;
    string name;
    vector<string> player_names;
    vector<Player> list_of_players;

    while(player_amount == 0)
    {
        cout << INPUT_AMOUNT_OF_PLAYERS;
        cin >> input;
        player_amount = stoi_with_check(input);
    }

    printf("List %u players: ", player_amount);
    for(uint i = 0; i < player_amount; ++i)
    {
        cin >> name;
        player_names.push_back(name);
    }

    for(string& name : player_names)
    {
        Player player(name);
        list_of_players.push_back(player);
    }
    return list_of_players;
}


/**
 * @brief quit_game Prints a give up message and quits the game
 */
void quit_game()
{
    cout << GIVING_UP << endl;
    return EXIT_SUCCESS;
}


/**
 * @brief check_if_valid_coords Checks if the given coordinates are
 * 1. positive numerics
 * 2. inside board bounds
 * 3. not the same card picked twice
 * 4. not an already turned card
 * @param user_input user given input
 * @param g_board game board
 * @return true = valid coordinates, false = invalid coordinates
 */
bool check_if_valid_coords(vector<string>& user_input, Game_board_type& g_board)
{
    uint coordinate;
    uint x_axis_length = g_board.size();
    uint y_axis_length = g_board.at(0).size();
    for(uint i = 0; i < user_input.size(); ++i)
    {
        coordinate = stoi_with_check(user_input.at(i));

        // checking if coordinate is a positive numeric
        if(coordinate == 0)
            return false;

        // and inside board bounds
        if((i == 0 or i == 2) and coordinate > y_axis_length)
            return false;
        if((i == 1 or i == 3) and coordinate > x_axis_length)
            return false;
    }
    uint y1 = stoi(user_input.at(0))-1;
    uint x1 = stoi(user_input.at(1))-1;
    uint y2 = stoi(user_input.at(2))-1;
    uint x2 = stoi(user_input.at(3))-1;

    // same card picked twice
    if(user_input.at(0) == user_input.at(2) and user_input.at(1) == user_input.at(3))
        return false;

    // card already turned
    if(g_board.at(x1).at(y1).get_visibility() == EMPTY
            or g_board.at(x2).at(y2).get_visibility() == EMPTY)
        return false;

    return true;
}


/**
 * @brief ask_for_coordinates Asks the user for card coordinates until 
 * valid coordinates are given
 * @param player the player in turn
 * @param g_board the game board
 * @return list of user given valid coordinates
 */
vector<uint> ask_for_coordinates(Player& player, Game_board_type& g_board)
{
    vector<string> card_coordinates;
    string user_input;

    bool invalid_coords = true;
    while(invalid_coords)
    {
        cout << player.get_name() << ": " << INPUT_CARDS;
        for(uint i = 0; i < 4; ++i)
        {
            cin >> user_input;
            if(user_input != "q")
                card_coordinates.push_back(user_input);
            else
                quit_game();
        }

        invalid_coords = !check_if_valid_coords(card_coordinates, g_board);
        if(invalid_coords)
        {
            cout << INVALID_CARD << endl;
            card_coordinates.clear();
        }
    }

    vector<uint> valid_card_coordinates;
    for(string& item : card_coordinates)
    {
        valid_card_coordinates.push_back(stoi(item)-1);
    }
    return valid_card_coordinates;
}


/**
 * @brief turn_cards_and_check_pairs Turns the chosen cards, prints the board and
 * checks if the cards were pairs. Prints the appliciable message.
 * @param card_coords card coordinates (y1, x1, y2, x2)
 * @param g_board game board
 * @return true = pairs found-> continue turn,
 *         false = no pairs found -> end turn
 */
bool turn_cards_and_check_pairs(vector<uint>& card_coords, Player& player, 
                                Game_board_type& g_board, uint& number_of_pairs)
{
    uint y1 = card_coords.at(0);
    uint x1 = card_coords.at(1);
    uint y2 = card_coords.at(2);
    uint x2 = card_coords.at(3);

    g_board.at(x1).at(y1).turn();
    g_board.at(x2).at(y2).turn();

    print(g_board);

    // pairs
    if(g_board.at(x1).at(y1).get_letter() == g_board.at(x2).at(y2).get_letter())
    {
        cout << FOUND << endl;
        g_board.at(x1).at(y1).set_visibility(EMPTY);
        g_board.at(x2).at(y2).set_visibility(EMPTY);
        player.add_card(g_board.at(x1).at(y1));
        number_of_pairs -= 1;
        return true;
    }

    // not pairs
    else
    {
        cout << NOT_FOUND << endl;
        g_board.at(x1).at(y1).turn();
        g_board.at(x2).at(y2).turn();
        return false;
    }
}


/**
 * @brief game_over Ends the game and announces the winner
 * @param list_of_winners list of winners
 * @param multiple_winners true if there are multiple winners, default is false
 */
void game_over(vector<Player>& list_of_players)
{
    cout << GAME_OVER << endl;

    vector<uint> winners;
    uint highest_pts = 1;

    // checking the winners
    for(uint i = 0; i < list_of_players.size(); ++i)
    {
        // new highest
        if(list_of_players.at(i).get_number_of_pairs() > highest_pts)
        {
            winners.clear();
            winners.push_back(i);
            highest_pts = list_of_players.at(i).get_number_of_pairs();
        }
        // tie
        else if(list_of_players.at(i).get_number_of_pairs() == highest_pts)
        {
            winners.push_back(i);
        }
    }

    // announcing the winners
    if(winners.size() == 1)
    {

        cout << list_of_players.at(winners.at(0)).get_name() << " has won with "
             << list_of_players.at(winners.at(0)).get_number_of_pairs() 
             << " pairs." << endl;
    }
    else
    {
        cout << "Tie of " << winners.size() << " players with "
             << list_of_players.at(winners.at(0)).get_number_of_pairs() 
             << " pairs." << endl;
    }
    return EXIT_SUCCESS;
}


/**
 * @brief player_turn Asks the player for card coordinates and turns the cards.
 * Continues the turn if pairs were found
 * @param player the player in turn
 * @param g_board the game board
 */
void player_turn(Player& player, Game_board_type& g_board, uint& number_of_pairs,
                 vector<Player>& list_of_players)
{
    bool continue_turn = true;
    while(continue_turn)
    {
      vector<uint> card_coordinates = ask_for_coordinates(player, g_board);
      continue_turn = turn_cards_and_check_pairs(card_coordinates, player, 
                                                 g_board, number_of_pairs);

      for(Player& player : list_of_players)
      {
        player.print();
      }

      print(g_board);

      if(number_of_pairs == 0)
      {
        continue_turn = false;
        game_over(list_of_players);
      }
    }
}


int main()
{
    Game_board_type game_board;

    unsigned int factor1 = 1;
    unsigned int factor2 = 1;
    uint number_of_pairs = ask_product_and_calculate_factors(factor1, factor2);
    init_with_empties(game_board, factor1, factor2);

    string seed_str = "";
    std::cout << INPUT_SEED;
    std::getline(std::cin, seed_str);
    int seed = stoi_with_check(seed_str);
    init_with_cards(game_board, seed);

    vector<Player> list_of_players;
    list_of_players = create_players();

    print(game_board);

    bool continue_game = true;
    while(continue_game)
    {
      for(Player& player : list_of_players)
      {
        player_turn(player, game_board, number_of_pairs, list_of_players);

        if(number_of_pairs == 0)
        {
          print(game_board);
          game_over(list_of_players);
          break;
        }
      }
    }

    return EXIT_SUCCESS;
}

