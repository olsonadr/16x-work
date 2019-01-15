#include <iostream>
#include <random>
#include <stdlib.h>

int choice(std::string prompt, std::string option1, std::string option2)
{
    int input;

    std::cout << prompt << std::endl;
    std::cout << option1 << std::endl;
    std::cout << option2 << std::endl
              << "  >> ";
    std::cin >> input;

    return input;
}

int choice(std::string prompt, std::string option1, std::string option2, std::string option3)
{
    int input;

    std::cout << prompt << std::endl;
    std::cout << option1 << std::endl;
    std::cout << option2 << std::endl;
    std::cout << option3 << std::endl
              << "  >> ";
    std::cin >> input;

    return input;
}

int main()
{
    std::string red = "\033[1;31m";
    std::string yellow = "\033[1;33m";
    std::string green = "\033[1;32m";
    std::string blue = "\033[1;34m";
    std::string magenta = "\033[1;35m";
    std::string white = "\033[1;37m";

    try
    {
        system("cls");
        system("clear");
    }
    catch (const std::exception &e)
    {
    }

    std::cout << std::endl
              << "Welcome to the Adventure for the " << yellow << "Crown of Kings" << white << "!" << std::endl
              << std::endl;

    if (choice(
            "Would you like to...",
            "  1. Enjoy the scenery for 5 more minutes.",
            "  2. Get up and set off on the adventure!") == 1)
    {
        std::cout << std::endl
                  << "You wait 5 minutes in the shade. It's so nice out here..." << std::endl;
        if (choice(
                "Would you like to...",
                "  1. Enjoy the scenery for 5 more minutes.",
                "  2. Get up and set off!") == 1)
        {
            std::cout << std::endl
                      << "Oh, what could 5 more minutes hurt? This is just so relaxing!" << std::endl;

            switch (choice(
                "Would you like to...",
                "  1. Relax for 5 just 5 more minutes.",
                "  2. Not move at all for 300 more seconds."))
            {
            case 1:
                std::cout << std::endl
                          << "Yeah that hits the spot! Why should you move anyway?" << std::endl;
                break;
            case 2:
                std::cout << std::endl
                          << "God, why do you have to go out on this adventure? You aren't getting paid or anything..." << std::endl;
                break;
            }

            choice(
                "Would you like to...",
                "  1. Let out a sigh of relief.",
                "  2. Sigh with bountiful relaxation and relief.");
            std::cout << std::endl
                      << "You let out a well-deserved sigh. You really deserve this." << std::endl;

            switch (choice(
                "Would you like to...",
                "  1. Take a quick nap. It's not like anyone will bother you!",
                "  2. Stay awake for just a few more minutes first."))
            {
            case 1:
                std::cout << std::endl
                          << "You lay down for your nap, and the spirit of the park consumes your soul while you slumber!" << std::endl
                          << red << "GAME OVER!" << white << " You have found ending 1/7: 'Sleepy Knight'" << std::endl;
                return 0;
                break;
            case 2:
                std::cout << std::endl
                          << "You try your hardest to stay awake but your eye-lids are starting to droop anyway." << std::endl;
                if (choice(
                        "Do you...",
                        "  1. Just let it happen... you can take a quick nap before you go.",
                        "  2. Get up and set off on your amazing adventure!") == 1)
                {
                    std::cout << std::endl
                              << red << "GAME OVER!" << white << " You have found ending 1/7: 'Sleepy Knight'" << std::endl;
                    return 0;
                }
                break;
            }
        }
    }

    std::cout << std::endl
              << "And so the adventure begins! You arise and set down the well-worn path through central park. You suddenly come to a small creek running through the park. There is a rickety bridge spanning the tumultous waters." << std::endl;
    switch (choice(
        "To cross the creek you...",
        "  1. Dive in and swim across!",
        "  2. Walk across the bridge like a normal person..?",
        "  3. Walk on the surface of the water!"))
    {
    case 1:
        std::cout << std::endl
                  << "You dive in like a magnifiscent eagle, but the creek is significantly shallower than you thought... You smash your head against the rocks and die." << std::endl
                  << red + "GAME OVER!" + white + " You have found ending 2/7: 'Magnifiscent Knight'" << std::endl;
        return 0;
        break;
    case 2:
        std::cout << std::endl
                  << "You get your booty onto that bridge and run face-first into a terrifying " << red << "Bridge Troll" << white << "! Quick! What do you do?!" << std::endl;
        switch (choice(
            "Do you...",
            "  1. Try to seduce the surprisingly attractive" + red + " Bridge Troll" + white + " (charisma check).",
            "  2. Draw your sword and kill the terrifying" + red + " Bridge Troll" + white + " (strength check)!"))
        {
        case 1:
            std::cout << std::endl
                      << "You put on your most dashing face and try a couple of pick-up lines, and..." << std::endl;
            if (((double)rand() / (RAND_MAX)) < .5)
            {
                std::cout << std::endl
                          << "It doesn't work in the slightest... you quickly realize that 'yo thicc baby, what that " + red + "Bridge Troll" + white + " do?' isn't the best line... The " + red + "Bridge Troll" + white + " takes pity on you, though, so you're allowed to continue on the path! Score!" << std::endl;
            }
            else
            {
                std::cout << std::endl
                          << "It totally works! You pull out the best you've got, and the " + red + "Bridge Troll" + white + " is woo'd by your advances and is so impressed that it offers to teleport you further along. Score!" << std::endl;
                if (choice(
                        "Do you...",
                        "  1. Take the offer of teleportation!",
                        "  2. Politely refuse and go on foot.") == 1)
                {
                    std::cout << std::endl
                              << "You steal one last stolen kiss with the " + red + "Bridge Troll" + white + ", brace yourself for the ride, and suddenly appear in the bed chamber of the great and terrible wizard! Quick! What do you do?" << std::endl;

                    switch (choice(
                        "Do you...",
                        "  1. Offer the great and terrible wizard a " + green + "Green Flower" + white,
                        "  2. Give up and cry..."))
                    {
                    case 1:
                        std::cout << std::endl
                                  << "You don't have any flower... The wizard takes this as a great insult and incinerates you with a " + magenta + "Lighting Bolt" + white + "!" << std::endl
                                  << red << "GAME OVER!" << white << " You have found ending 4/7: '" + magenta + "Lightning Bolt" + white + "'" << std::endl;
                        return 0;
                        break;
                    case 2:
                        std::cout << std::endl
                                  << "You weren't ready for this! It's all just so unfair... The wizard takes pity on you, though. You're so pitiful that the wizard just sort of gives you the " + yellow + "Crown of Kings" + white + "!" << std::endl
                                  << green << "YOU WIN!" << white << " You have completed your quest and found ending 7/7: '" + yellow + "Crown of Kings" + white + "'" << std::endl;
                        return 0;
                        break;
                    }
                }
            }
            break;
        case 2:
            std::cout << std::endl
                      << "You draw your sword and prepare to fight, but you realize you're just a CS nerd and don't know how to use it. You start to notice how heavy your armour is. The " + red + "Bridge Troll" + white + " crushes you in one blow!" << std::endl
                      << red << "GAME OVER!" << white << " You have found ending 3/7: '" + red + "Bridge Troll" + white + "'" << std::endl;
            return 0;
            break;
        }
        break;
    case 3:
        break;
    }

    std::cout << std::endl
              << "You set off like the brilliant knight you are. You hike through the great valleys of New York, across the vast expanses of the endless woods, and set out over the rolling hills of New Jersey. Suddenly, you come across a beautiful " + green + "Green Flower" + white + "!" << std::endl;

    bool hasFlower;

    switch (choice(
        "Would you like to...",
        "  1. Take the " + green + "Green Flower " + white + "for your journey!",
        "  2. Leave it by the trail for another to find."))
    {
    case 1:
        hasFlower = true;
        std::cout << std::endl
                  << "You pick the " + green + "flower" + white + " and feel a wave of courage flow through you! Maybe this will come in handy later on..." << std::endl;
        break;
    case 2:
        hasFlower = false;
        std::cout << std::endl
                  << "You leave the " + green + "flower" + white + " by the trail for another sorry soul and continue on..." << std::endl;
        break;
    }

    std::cout << std::endl
              << "After your surprisingly refreshing stroll through the rolling hills, you come to a small cottage out in the country-side of East-Russia. A maid is carving an impressive ice-sculpture outside the cottage." << std::endl;

    switch (choice(
        "Would you like to...",
        "  1. Give the maid the " + green + "Green Flower" + white + ".",
        "  2. Keep walking. It's YOUR " + green + "Green Flower" + white + " now!"))
    {
    case 1:
        if (hasFlower == true)
        {
            std::cout << std::endl
                      << "You give the maid the " + green + "flower" + white + ", and she falls instantly in love with you. You get married and spend the rest of your life drinking Diet Sprite while your lovely wife supports you both with her fantastic ice-sculptures. You forget your quest quickly and enjoy the rest of your life." << std::endl
                      << red << "GAME OVER!" << white << " You have found ending 5/7: 'Diet Knight'" << std::endl;
        }
        else
        {
            std::cout << std::endl
                      << "But you never grabbed that " + green + "flower" + white + ", so you must pass along and continue your journey, leaving the maid behind you, and eventually coming to the great mountain range of Thuud. You set out with a band of 6 onto the treacherous slopes. You try to pass through, but after 50 continuous minutes of climbing, you run out of energy and give up to die. You freeze and your body is never found." << std::endl
                      << red << "GAME OVER!" << white << " You have found ending 6/7: '" + blue + "Chilly Knight" + white + "'" << std::endl;
        }
        break;
    case 2:
        std::cout << std::endl
                  << "And so you continue your journey, leaving the maid behind you, and eventually coming to the great mountain range of Thuud. You set out with a band of 6 onto the treacherous slopes. You try to pass through, but after 50 continuous minutes of climbing, you run out of energy and give up to die. You freeze and your body is never found." << std::endl
                  << red << "GAME OVER!" << white << " You have found ending 6/7: '" + blue + "Chilly Knight" + white + "'" << std::endl;
        break;
    }

    return 0;
}