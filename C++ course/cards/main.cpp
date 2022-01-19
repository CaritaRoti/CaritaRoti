/* Cards
*
* Exercise for trying out the different basic aspects of dynamic memory and pointers.
*
* Asks the user to input the amount of cards the program will start with.
* Prints the cards in the empty deck. Then adds the cards.
*
* Then the program moves the bottommost card to top two times.
*
* After that, topmost card is moved to bottom.
*
* Then the deck order is printed from top to bottom and then from bottom to top.
*
* Lastly, all cards are removed from the deck.
*/

#include "cards.hh"
#include <iostream>

using namespace std;

int main() {
    cout << "constructor" << endl;
    Cards deck;

    int n = 0;
    cout << "Enter amount of test cards: ";
    cin >> n;

    cout << endl << "print_from_top_to_bottom (deck is empty)" << endl;
    deck.print_from_top_to_bottom(cout);

    cout << endl << "adding cards" << endl;
    for(int i = 0; i < n; i++) {
        deck.add(i);
    }

    cout << endl << "print_from_top_to_bottom" << endl;
    deck.print_from_top_to_bottom(cout);

    cout << endl << "bottom_to_top * 2" << endl;
    deck.bottom_to_top();
    deck.bottom_to_top();

    cout << endl << "print_from_top_to_bottom" << endl;
    deck.print_from_top_to_bottom(cout);

    cout << endl << "top_to_bottom * 1" << endl;
    deck.top_to_bottom();

    cout << endl << "print_from_top_to_bottom" << endl;
    deck.print_from_top_to_bottom(cout);

    cout << endl << "print_from_bottom_to_top" << endl;
    deck.print_from_bottom_to_top(cout);

    cout << endl;
    int value = 0;
    while(deck.remove(value)) {
        cout << "remove " << value << endl;
    }

    cout << endl << "destructor" << endl;
    return EXIT_SUCCESS;
}
