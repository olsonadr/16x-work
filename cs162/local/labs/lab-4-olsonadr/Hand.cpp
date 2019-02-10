#include "Hand.hpp"

Hand::Hand()
{
    // std::cout << "Hand constructed" << std::endl;
    hand_cards = new Card[52];
    this->n_cards = 0;
}

Hand::Hand(const Hand &old_hand)
{
    this->n_cards = old_hand.n_cards;
    for (int i = 0; i < this->n_cards; i++)
    {
        this->hand_cards[i] = old_hand.hand_cards[i];
    }
}

Hand::~Hand()
{
    // std::cout << "Hand destructed" << std::endl;
    delete[] this->hand_cards;
}

void Hand::display(bool is_hidden)
{
    std::cout << "Hand:  ";
    if (this->n_cards > 0)
    {
        if (is_hidden)
        {
            for (int i = 0; i < this->n_cards; i++)
            {
                std::cout << "[     ] ";
            }
        }
        else
        {
            for (int i = 0; i < this->n_cards; i++)
            {
                if (this->hand_cards[i].get_rank() == 9)
                {
                    std::cout << "[ "
                              << this->hand_cards[i].get_name()
                              << " ] ";
                }
                else
                {
                    std::cout << "[ "
                              << this->hand_cards[i].get_name()
                              << " ] ";
                }
            }

            std::cout << std::endl
                      << "         ";

            for (int i = 0; i < this->n_cards; i++)
            {
                if (i < 10)
                {
                    std::cout << " ";
                }
                std::cout << " ("
                          << i
                          << ")   ";
            }
        }
    }
    else
    {
        std::cout << "<empty>";
    }
    std::cout << std::endl;
}

void Hand::add(Card new_card)
{
    // std::cout << "Adding " << new_card.get_full_name() << std::endl;
    // this->hand_cards[0] = Card(0, 2);
    // for (int i = 0; i < n_cards; i++)
    // {
    //     std::cout << "Hand's hand_cards[" << i << "] = " << hand_cards[i].get_name() << std::endl;
    // }
    this->hand_cards[this->n_cards] = new_card;
    this->n_cards++;
}

// Returns invalid card if not found (use is_valid() on card)
Card Hand::steal(int rank)
{
    //Debugging
    // std::cout << "HAND::STEAL GET_RAK OF HAND_CARDS:" << std::endl;
    // for (int i = 0; i < this->n_cards; i++)
    // {
    //     std::cout << this->hand_cards[i].get_rank() << " ";
    // }
    // std::cout << std::endl;
    //End Debugging
    for (int i = 0; i < this->n_cards; i++)
    {
        if (this->hand_cards[i].get_rank() == rank)
        {
            this->n_cards--;
            swap(i, this->n_cards);
            return this->hand_cards[this->n_cards];
        }
    }
    std::cout << "NO CARD FOUND IN STEAL" << std::endl;
    return Card();
}

bool Hand::is_held(int rank)
{
    for (int i = 0; i < this->n_cards; i++)
    {
        if (this->hand_cards[i].get_rank() == rank)
        {
            return true;
        }
    }

    return false;
}

int Hand::random()
{
    std::mt19937 rng(time(NULL));
    std::uniform_int_distribution<int> gen(0, this->n_cards - 1);
    int rand_i = gen(rng);
    return this->hand_cards[rand_i].get_rank();
}

int Hand::check_books()
{
    int card_counts[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int book_rank = -1;

    for (int i = 0; i < this->n_cards; i++)
    {
        card_counts[this->hand_cards[i].get_rank()]++;
        if (card_counts[this->hand_cards[i].get_rank()] == 4)
        {
            book_rank = this->hand_cards[i].get_rank();
            for (int j = 0; j < this->n_cards; j++)
            {
                if (this->hand_cards[j].get_rank() == book_rank)
                {
                    this->n_cards--;
                    swap(j, this->n_cards);
                }
            }
        }
    }

    return book_rank;
}

void Hand::swap(int first, int second)
{
    Card temp = this->hand_cards[first];
    this->hand_cards[first] = this->hand_cards[second];
    this->hand_cards[second] = temp;
}

void Hand::reset()
{
    this->n_cards = 0;
}