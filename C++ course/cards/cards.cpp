#include "cards.hh"
#include <iostream>

using namespace std;

// A dynamic structure must have a constructor
// that initializes the top item as nullptr.
Cards::Cards(): top_(nullptr)
{
}


// Adds a new card with the given id as the topmost element.
void Cards::add(int id)
{
    Card_data* new_card = new Card_data{id, nullptr};

    if ( top_ == nullptr ) {
       top_ = new_card;
    } else {
        new_card->next = top_;
        top_ = new_card;
    }
}

// Prints the content of the data structure with ordinal numbers to the
// output stream given as a parameter starting from the first element.
void Cards::print_from_top_to_bottom(std::ostream &s)
{
    Card_data* card_to_be_printed = top_;
    int running_number = 1;

    while ( card_to_be_printed != nullptr ) {
       s << running_number << ": " << card_to_be_printed->data << endl;
       ++running_number;
       card_to_be_printed = card_to_be_printed->next;
    }
}

bool Cards::remove(int &id)
{
    // empty deck
    if ( top_ == nullptr ) {
       return false;
    }

    Card_data* card_to_be_removed = top_;

    id = card_to_be_removed->data;

    // only 1 item
    if ( top_->next == nullptr ) {
       top_ = nullptr;
    // multiple items
    } else {
       top_ = top_->next;
    }

    delete card_to_be_removed;

    return true;
}

// Moves the last element of the data structure as the first one.
// Returns false, if the data structure is empty, otherwise returns true.
bool Cards::bottom_to_top()
{
    // empty deck
    if (top_ == nullptr)
        return false;

    // only one card
    if (top_->next == nullptr)
        return true;

    Card_data* index = top_;
    Card_data* card_to_be_moved = top_;

    while ( index != nullptr ) {
       if (index->next->next == nullptr) {
           // second last card reached
           card_to_be_moved->next->next = top_;
           top_ = card_to_be_moved->next;
           card_to_be_moved->next = nullptr;
       }
       index = index->next;
       card_to_be_moved = index;
    }
    return true;
}

// Moves the first element of the data structure as the last one.
// Returns false, if the data structure is empty, otherwise returns true.
bool Cards::top_to_bottom()
{
    // empty deck
    if (top_ == nullptr)
        return false;

    // only one card
    if (top_->next == nullptr)
        return true;

    Card_data* last = top_;
    Card_data* tmp = top_;

    // setting "last" as the last card
    while (last->next != nullptr) {
        last = last->next;
    }

    // second first to first
    top_ = top_->next;

    // original first to last
    last->next = tmp;

    // emptying the link from the last card
    last = last->next;
    last->next = nullptr;

    return true;
}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
    recursive_print(top_, s);
}

// destructor
Cards::~Cards()
{
    while ( top_ != nullptr ) {
       Card_data* item_to_be_released = top_;
       top_ = top_->next;

       delete item_to_be_released;
    }
}

int Cards::recursive_print(Cards::Card_data *top, ostream &s)
{
    int running_number = 1;
    if (top->next != nullptr) {
        running_number = recursive_print(top->next, s);
    }

    s << running_number << ": " << top->data << endl;
    return running_number + 1;
}
