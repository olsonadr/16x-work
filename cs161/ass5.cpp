#include <iostream>
#include <ctime>
#include "lib/help.h"

using namespace std;

void main_menu();
void game_turn(int, int[]);
int get_move(int[], int[], int);
bool arrays_equal(int[], int[], int, int);
void get_combos(int[], int[]);
int calculate_extra_points(int[]);
int index_of(int, int[], int);
int calculate_move_points(int[], int);
void roll_dice(int[], int);
void display_dice(int[]);
void display_scoreboard(int[], int);
int determine_winner(int[], int, int);

int main()
{
	system("cls");
	system("clear");
	main_menu();
	return 0;
}

// Main menu, in which game customization and run-time takes place.
void main_menu()
{
	cout << "Welcome to Farkle!" << endl
		 << "------------------" << endl
		 << endl;
	int player_count = HelperLib::getIntInputInRange("How many players? (2-100)", 2,
					   100);
	int score_target =
		HelperLib::getIntInputInRange("What will you play to? (100-100000; 10000 default)",
									  100, 100000);
	int first_winner = -1, first_winner_score = -1, final_winner = -1;
	bool keep_going = true;
	int * scores = new int[player_count];

	for (int i = 0; i < player_count; i++)
	{
		scores[i] = 0;
	}

	while (keep_going)
	{
		for (int player = 1; player <= player_count; player++)
		{
			game_turn(player, scores);
		}

		display_scoreboard(scores, player_count);
		first_winner = determine_winner(scores, player_count, score_target);
		first_winner_score = scores[first_winner];

		if (first_winner >= 0)
		{
			keep_going = false;
		}
	}

	cout << "Player " << first_winner + 1 << " has reached " << score_target <<
		 " points!" << endl;
	cout << "Everyone gets one more round to try to beat their score!" << endl;
	cout << "Player " << first_winner + 1 <<
		 ", your score this round won't count, but you can play anyway!" << endl;

	for (int player = 1; player <= player_count; player++)
	{
		game_turn(player, scores);
	}

	scores[first_winner] = first_winner_score;
	final_winner = determine_winner(scores, player_count, score_target);
	display_scoreboard(scores, player_count);
	cout << "Player " << final_winner << " has won! Congratulations!" << endl
		 << endl;
	delete[] scores;

	while (true)
	{
		int input = HelperLib::getIntInput("Play again? (0 -> No, 1 -> Yes)");

		if (input == 0)
		{
			return;
		}
		else if (input == 1)
		{
			main_menu();
		}
		else
		{
			cout << "**ERROR! Not an option!**" << endl
				 << endl;
		}
	}
}

// A single game turn, during which a player earns points.
void game_turn(int player, int scores[])
{
	bool keep_going = true;
	int dice[6] = {0, 0, 0, 0, 0, 0}, move[6] = {0, 0, 0, 0, 0, 0};
	int dice_count = 6, points = 0, move_points = 0, input = 1, move_degree = 0;
	cout << endl
		 << endl
		 << "Player " << player << "'s turn!" << endl
		 << "----------------*" << endl
		 << endl;

	while (keep_going)
	{
		roll_dice(dice, dice_count);

		while (true)
		{
			cout << "Current score: " << points << endl;
			display_dice(dice);
			move_degree = get_move(move, dice, dice_count);
			move_points = calculate_move_points(move, move_degree);

			if (move_points < 0)
			{
				cout << endl << "**ERROR! Use of non-scoring dice!**" << endl << endl;
			}
			else
			{
				break;
			}
		}

		points += move_points;
		cout << endl;

		if (move_points == 0 || move_degree == 0)
		{
			points = 0;
			keep_going = false;
		}

		dice_count -= move_degree;

		if (points >= 500) //|| dice_count < 1)
		{
			while (true)
			{
				cout << "Current score: " << points << endl;
				input = HelperLib::getIntInput("Roll again? (0 -> No, 1 -> Yes)");

				if (input == 0 || input == 1)
				{
					break;
				}
				else
				{
					cout << "**ERROR! Not an option!**" << endl;
				}
			}

			if (input == 0)
			{
				keep_going = false;
			}

			if (dice_count < 1)
			{
				dice_count = 6;
			}
		}

		cout << endl;
	}

	if (points >= 500)
	{
		scores[player - 1] += points;
		cout << endl
			 << "Good round! You've earned " << points << " points this round!" << endl
			 << endl;
	}
	else
	{
		cout << "Farkle! You only got " << points << " points!" << endl;
	}
}

// Takes current dice and dice_count, as well as new array of ints of length 6. Takes user input to modify move array.
int get_move(int move[], int dice[], int dice_count)
{
	for (int i = 0; i < 6; i++)
	{
		move[i] = 0;
	}

	std::string prompt =
		"1 to score a die, 0 to keep it;\nsubmit one number, e.g. 011011:";
	std::string input = HelperLib::getIntInputAsString(prompt);
	//std::string input = to_string(HelperLib::getIntInput(prompt));
	int count = 0;

	if (input.length() < dice_count - 1)
	{
		input += "000000";
	}

	for (int i = 0; i < dice_count; i++)
	{
		if (input[i] == '1')
		{
			count++;
			move[dice[i] - 1] += 1;
		}
	}

	return count;
}

// Takes 2 arrays and their lengths to determine whether they are equal.
bool arrays_equal(int arr1[], int arr2[], int arr1_length, int arr2_length)
{
	if (arr1_length != arr2_length)
	{
		return false;
	}

	for (int i = 0; i < arr1_length; i++)
	{
		if (arr1[i] != arr2[i])
		{
			return false;
		}
	}

	return true;
}

// Fills a provided combos array of ints with the number of combinations of index+2 elements (index==2 --> pairs) found in move.
void get_combos(int combos[], int move[])
{
	for (int i = 0; i < 5; i++)
	{
		combos[i] = 0;
	}

	for (int i = 0; i < 6; i++)
	{
		if (move[i] == 6)
		{
			combos[4]++;
			;
		}
		else if (move[i] == 5)
		{
			combos[3]++;
		}
		else if (move[i] == 4)
		{
			combos[2]++;
		}
		else if (move[i] == 3)
		{
			combos[1]++;
		}
		else if (move[i] == 2)
		{
			combos[0]++;
		}
	}
}

// Returns the extra possible points of single 1s and 5s in provided move array as int.
int calculate_extra_points(int move[], int & used_dice)
{
	int result = 0;

	if (move[0] < 3)
	{
		result += move[0] * 100;
		used_dice += move[0];
	}

	if (move[4] < 3)
	{
		result += move[4] * 50;
		used_dice += move[4];
	}

	return result;
}

// Returns the index of a given element in given arr, -1 if it is not contained within.
int index_of(int item, int arr[], int arr_length)
{
	for (int i = 0; i < arr_length; i++)
	{
		if (arr[i] == item)
		{
			return i;
		}
	}

	return -1;
}

// Returns the number of points a given move would provide, or -1 if non-scoring dice were played.
int calculate_move_points(int move[], int move_degree)
{
	int combos[5];
	int straight[6] = {1, 1, 1, 1, 1, 1};
	get_combos(combos, move);
	int used_dice = 0;
	int extra_points = calculate_extra_points(move, used_dice);
	int result;

	if (combos[1] == 2)
	{
		result = 2500;
		used_dice += 6;
	}
	else if (combos[2] == 1 && combos[0] == 1)
	{
		result = 1500;
		used_dice += 6;
	}
	else if (combos[0] == 3)
	{
		result = 1500;
		used_dice += 6;
	}
	else if (arrays_equal(move, straight, 6, 6))
	{
		result = 1500;
		used_dice += 6;
	}
	else if (combos[4] == 1)
	{
		result = 3000;
		used_dice += 6;
	}
	else if (combos[3] == 1)
	{
		result = 2000 + extra_points;
		used_dice += 5;
	}
	else if (combos[2] == 1)
	{
		result = 1000 + extra_points;
		used_dice += 4;
	}
	else if (combos[1] == 1)
	{
		int score = (index_of(3, move, 6) + 1) * 100;

		if (score == 100)
		{
			score = 300;
		}

		result = score + extra_points;
		used_dice += 3;
	}
	else
	{
		result = extra_points;
	}

	if (used_dice < move_degree)
	{
		return -1;
	}
	else
	{
		return result;
	}
}

// Randomizes the values of the values of the first <dice_count> dice in the dice[] array, leaving the others as 0
void roll_dice(int dice[], int dice_count)
{
	for (int i = 0; i < 6; i++)
	{
		if (i < dice_count)
		{
			dice[i] = (std::rand() % 6) + 1;
		}
		else
		{
			dice[i] = 0;
		}
	}
}

// Prints the contents of the passed dice[] array.
void display_dice(int dice[])
{
	for (int i = 0; i < 6; i++)
	{
		if (dice[i] != 0)
		{
			cout << "  [" << dice[i] << "]";
		}
		else
		{
			cout << "  [-]";
		}
	}

	cout << endl;
}

// Prints the score-board as it stands in scores[] array.
void display_scoreboard(int scores[], int scores_length)
{
	cout << endl << endl
		 << "*------------*----------------*" << endl;

	for (int i = 0; i < scores_length; i++)
	{
		cout << "|  Player " << i + 1 << "  |  ";

		for (int j = 0; j < 5 - to_string(scores[i]).length(); j++)
		{
			cout << " ";
		}

		cout << scores[i] << " Points  |" << endl
			 << "*------------*----------------*" << endl;
	}

	cout << endl;
}

// Determines if there is a winner at a given point, and returns their number, or -1 if there is no current winner.
int determine_winner(int scores[], int scores_length, int score_target)
{
	int max = -1;
	int best_player = -1;

	for (int player = 0; player < scores_length; player++)
	{
		if (scores[player] >= score_target && scores[player] > max)
		{
			best_player = player;
			max = scores[best_player];
		}
	}

	return best_player;
}
