/* Author: Jose Sanchez
 * Course: COSCI 139: C++ Programming I
 * Section: 7475
 *
 * Final.cpp
 * ========
 * This program creates a single Tic Tac Toe game by the use of
 * an array of strings. The user is allowed to enter his or
 * her name and play against a computer player.
 */

#include <iostream>
#include <string>

using namespace std;

string const HUMAN_PLAYER = "H";
string const COMPUTER_PLAYER = "C";
int const MAXIMUM_NUMBER_OF_TURNS = 9;
int const NUMBER_OF_SPACES = 9;

enum StatesOfGame {

        Human_Occupied_Space = 5,
        Computer_Occupied_Space = 3,
        Unoccupied_Space = 0,

};

struct Game {

    bool on = true; // Controls when the program ends.
    bool game_in_progress = true; // Controls the current game.
    string current_player = HUMAN_PLAYER; // Controls player's turn.
    string users_name; // Stores the user's name.
    int current_turn = 1; // Controls the turns in a single game.
};

string PrintAsterisks(int number_of_asterisk);
void PrintSplashScreen();
void ResetGame(Game &g);
void SetBoard(string board[], int board_size);
void DisplayBoard(StatesOfGame states[], string board[], int board_size);
void PlayerMakeMove(StatesOfGame states[], string board[], int board_size, Game g);
int CheckPositionAvailability(string board[], int board_size, int index_selected_by_player);
void AskForUsersName(Game &g);
void ChangePlayer(Game &g) ;
void CheckForWin(StatesOfGame states[], string board[], int board_size, Game &g);
void ExitGame(StatesOfGame states[], string board[], int board_size, Game &g);
void CheckWhetherToContinue(Game &g);
void ValidateToContinue(string &user_input);
void ValidateUsersName(string &user_input);
int ValidatePlayersChoice(string &user_input);
int LocateEmptySpace(string board[], int board_size);
bool isMoveLegal(string board[], int board_size, int index_selected_by_player);
void UpdateBoard(StatesOfGame states[], string board[], int board_size);
void ChangeTurn(StatesOfGame states[], string board[], int board_size, Game &g);
int ValidateComputersChoice(string board[], int board_size, int index_1, int index_2, int index_3);
int CalculateComputersMove(StatesOfGame states[], string board[], int board_size, Game g);


int main()
{

    Game tic_tac_toe;

    string game_board[NUMBER_OF_SPACES];

    /* The state of the game is initialized with unoccupied spaces*/
    StatesOfGame states[NUMBER_OF_SPACES] = {Unoccupied_Space, Unoccupied_Space,
        Unoccupied_Space, Unoccupied_Space, Unoccupied_Space, Unoccupied_Space,
        Unoccupied_Space, Unoccupied_Space, Unoccupied_Space};

    PrintSplashScreen();
    AskForUsersName(tic_tac_toe);

    do {

        SetBoard(game_board, NUMBER_OF_SPACES);

        while (tic_tac_toe.game_in_progress) {

            DisplayBoard(states, game_board, NUMBER_OF_SPACES);
            PlayerMakeMove(states, game_board, NUMBER_OF_SPACES, tic_tac_toe);
            CheckForWin(states, game_board, NUMBER_OF_SPACES, tic_tac_toe);
            ChangePlayer(tic_tac_toe);
            ChangeTurn(states, game_board, NUMBER_OF_SPACES, tic_tac_toe);
        }

        CheckWhetherToContinue(tic_tac_toe);
        ResetGame(tic_tac_toe);

    } while (tic_tac_toe.on);

    cout << "Goodbye." << endl;


    return 0;
}

/* *****************************************************************
 * Returns a single string of asterisks of a size specified by
 * the int variable, number_of_asterisks.
 * *****************************************************************/

string PrintAsterisks(int number_of_asterisk) {

    string string_of_asterisks;

    for (int i = 0; i <= number_of_asterisk; i++) {
        string_of_asterisks += "*";
    }

    return string_of_asterisks;
}

/* *****************************************************************
 * Prints the splash or welcome screen to the console. It invokes
 * the PrintAsterisks() function.
 * *****************************************************************/

void PrintSplashScreen() {

    cout << PrintAsterisks(26) << endl;
    cout << PrintAsterisks(26) << endl;
    cout << PrintAsterisks(26) << endl;
    cout << PrintAsterisks(6) << "             ";
    cout << PrintAsterisks(6) << endl;
    cout << PrintAsterisks(6) << " TIC TAC TOE ";
    cout << PrintAsterisks(6) << endl;
    cout << PrintAsterisks(6) << "   By Jose   ";
    cout << PrintAsterisks(6) << endl;
    cout << PrintAsterisks(6) << "   Sanchez   ";
    cout << PrintAsterisks(6) << endl;
    cout << PrintAsterisks(6) << "             ";
    cout << PrintAsterisks(6) << endl;
    cout << PrintAsterisks(26) << endl;
    cout << PrintAsterisks(26) << endl;
    cout << PrintAsterisks(26) << endl;
    cout << endl;

}

/* *****************************************************************
 * Resets the game to its initial state by passing a structure
 * of the Game type as a reference.
 * *****************************************************************/

void ResetGame(Game &g) {
    g.game_in_progress = true;
    g.current_player = HUMAN_PLAYER;
    g.current_turn = 1;
}

/* *****************************************************************
 * Fills an array of strings with a string representation of the
 * numbers 0 through 8.
 * *****************************************************************/

void SetBoard(string board[], int board_size){
    for (int i = 0; i < board_size; i++){
        board[i] =  to_string(i);
    }
}

/* *****************************************************************
 * Displays the board on the console in its current states. By
 * invoking the UpdateBoard() function, the array of the states of
 * the game are also updated.
 * *****************************************************************/

void DisplayBoard(StatesOfGame states[], string board[], int board_size) {
    cout << " |-----------|" << endl;
    cout << " | " << board[0] << " | ";
    cout << board[1] << " | ";
    cout << board[2] << " |";
    cout << endl;
    cout << "  -----------" << endl;
    cout << " | " << board[3] << " | ";
    cout << board[4] << " | ";
    cout << board[5] << " |";
    cout << endl;
    cout << "  -----------" << endl;
    cout << " | " << board[6] << " | ";
    cout << board[7] << " | ";
    cout << board[8] << " |";
    cout << endl;
    cout << " |-----------|" << endl;
    cout << endl;

    UpdateBoard(states,board, board_size);
}

/* *****************************************************************
 * If it is the human's turn, it will prompt the user to make a
 * selection. This selection will be validated by invoking the
 * ValidatePlayersChoice() function which checks that the user enters
 * a valid numeric entry between 0 and 8. The user's choice will then
 * be checked to see if the position is available by invoking the
 * CheckPositionAvailability() function.
 *
 * If it is the computer's turn, this function will invoke the
 * CalculateComputersMove() function to determine the computer's
 * best move.
 * *****************************************************************/

void PlayerMakeMove(StatesOfGame states[], string board[], int board_size, Game g) {
    int index_selected_by_player;
    string user_input;

    if (g.current_player == HUMAN_PLAYER) {
        cout << "It is " << g.users_name << "'s turn." << endl;
    } else if (g.current_player == COMPUTER_PLAYER) {
        cout << "It is the computer's turn." << endl;
    }


    if (g.current_player == HUMAN_PLAYER) {
        cout << "Please choose a space." << endl;

        getline(cin, user_input);
        index_selected_by_player = ValidatePlayersChoice(user_input);
        index_selected_by_player = CheckPositionAvailability(board, board_size, index_selected_by_player);
        board[index_selected_by_player] = HUMAN_PLAYER;
    } else {
        index_selected_by_player = CalculateComputersMove(states, board, board_size, g);
        board[index_selected_by_player] = COMPUTER_PLAYER;
    }
}

/* *****************************************************************
 * Checks whether an a position is available by invoking the
 * isMoveLegal() function to check whether the position choosen is
 * an unoccupied position. The user will be prompted to make another
 * selection if the position is currently occupied by either player.
 * After the position has been validated by invoking the
 * ValidatePlayersChoice and verified that it is an unoccupied space,
 * the function will return the valid position choosen by the
 * player.
 * *****************************************************************/

int CheckPositionAvailability(string board[], int board_size, int index_selected_by_player) {
    string user_input;

    while ( !(isMoveLegal(board, board_size, index_selected_by_player)) ) {
        cout << "This space is already taken." << endl;
        cout << "Please make another selection." << endl;

        getline(cin, user_input);
        index_selected_by_player = ValidatePlayersChoice(user_input);
    }

    return index_selected_by_player;
}

/* *****************************************************************
 * Prompts the user to enter his or her first name. The entry
 * is validated by invoking the ValidateUsername() function. After
 * a valid name is entered, the Game structure's member variable,
 * users_name, is updated.
 * *****************************************************************/

void AskForUsersName(Game &g) {
    string user_input;

    cout << "Please enter your first name:" << endl;

    getline(cin, user_input);
    ValidateUsersName(user_input);
    g.users_name = user_input;
}

/* *****************************************************************
 * Changes the player's turn.
 * *****************************************************************/

void ChangePlayer(Game &g) {
    if (g.current_player == HUMAN_PLAYER) {
        g.current_player = COMPUTER_PLAYER;
    } else if (g.current_player == COMPUTER_PLAYER) {
        g.current_player = HUMAN_PLAYER;
    }
}

/* *****************************************************************
 * Checks whether the human or the computer player have won by
 * checking all possible winning conditions. If a player has won,
 * a message is printed on console for the appropriate player. The
 * current game ends by invoking the ExitGame().
 * *****************************************************************/

void CheckForWin(StatesOfGame states[], string board[], int board_size, Game &g) {
    string winning_message;

    if (g.current_player == HUMAN_PLAYER) {
        winning_message = g.users_name + " has won the game!";
    } else {
        winning_message = "The computer has won the game!";
    }

    /* Checking all rows to determine whether the current player
     * has choosen three consecutive spaces in a single row,
     * thus indicating a win by the current player. If the
     * current player has won, a winning message will be printed
     * to the console and the current game will end. */

    if (board[0] == g.current_player && board[1]== g.current_player
        && board[2] == g.current_player) {
        cout << winning_message << endl;
        ExitGame(states, board, board_size, g);
    } if (board[3] == g.current_player && board[4]== g.current_player
        && board[5] == g.current_player) {
        cout << winning_message << endl;
        ExitGame(states, board, board_size, g);
    } if (board[6] == g.current_player && board[7]== g.current_player
        && board[8] == g.current_player) {
        cout << winning_message << endl;
        ExitGame(states, board, board_size, g);


        /* Checking all columns to determine whether the current player
         * has choosen three consecutive spaces in a single column. If the
         * current player has won, a winning message will be printed
         * to the console and the current game will end. */


    } else if (board[0] == g.current_player && board[3]== g.current_player
        && board[6] == g.current_player) {
        cout << winning_message << endl;
        ExitGame(states, board, board_size, g);
    } else if (board[1] == g.current_player && board[4]== g.current_player
        && board[7] == g.current_player) {
        cout << winning_message << endl;
        ExitGame(states, board, board_size, g);
    } else if (board[2] == g.current_player && board[5]== g.current_player
        && board[8] == g.current_player) {
        cout << winning_message << endl;
        ExitGame(states, board, board_size, g);

        /* Checking all diagonal lines to determine whether the current player
         * has choosen three consecutive spaces in a single diagonal line. If the
         * current player has won, a winning message will be printed
         * to the console and the current game will end. */

    } else if (board[0] == g.current_player && board[4]== g.current_player
        && board[8] == g.current_player) {
        cout << winning_message << endl;
        ExitGame(states, board, board_size, g);
    } else if (board[2] == g.current_player && board[4]== g.current_player
        && board[6] == g.current_player) {
        cout << winning_message << endl;
        ExitGame(states, board, board_size, g);
    }
}

/* *****************************************************************
 * Exits the current game by accessing the Game structure's member
 * variable, game_in_progress, from true to false.
 * *****************************************************************/

void ExitGame(StatesOfGame states[], string board[], int board_size, Game &g) {
    DisplayBoard(states, board, board_size);
    g.game_in_progress = false;
}

/* *****************************************************************
 * Prompts the user to choose whether to continue by printing a
 * message on console and giving the user the option of pressing
 * y to continue or n to quit. The user's choice is validated to
 * ensure that the user only enters either y/n by invoking the
 * ValidateToContinue() function. The case of the user's input
 * does not matter as it will be converted to a lowercase letter
 * by invoking to tolower() function.
 * *****************************************************************/

void CheckWhetherToContinue(Game &g) {
    string user_input;

    cout << "Would you like to continue? Press y/n." << endl;

    getline(cin, user_input);
    ValidateToContinue(user_input);

    if ( tolower(user_input[0]) != 'y' ) {
        g.on = false;
    }
}

/* *****************************************************************
 * Validates the user's choose to continue or to exit by ensuring
 * that the user is only allowed to type y/n regardless of the case
 * of the letter entered.
 * *****************************************************************/

void ValidateToContinue(string &user_input) {

    while (user_input.length() == 0 || user_input.length() > 1) {
        cout << "This is an invalid entry." << endl;
        cout << "Please choose between y/n to continue." << endl;

        getline(cin, user_input);
    }

    if ( tolower(user_input[0]) != 'y' && tolower(user_input[0]) != 'n') {
            cout << "This is an invalid entry." << endl;
            cout << "Please choose between y/n to continue." << endl;

            getline(cin, user_input);
            ValidateToContinue(user_input);
    }
}

/* *****************************************************************
 * Validates the user's name by ensuring that only alphabetic
 * characters are entered. Whitespaces, special characters and
 * numbers are not allowed. The user will be asked to make another
 * entry as long as the user enters an invalid character.
 * *****************************************************************/

void ValidateUsersName(string &user_input) {

    int counter = 0;

    if (user_input.length() == 0) {
        cout << "An empty string is not allowed." << endl;
        cout << "Please enter your first name." << endl;
        getline(cin, user_input);
        ValidateUsersName(user_input);
    }

    while (counter < (int)user_input.length()) {
        if ( !isalpha(user_input[counter]) ) {
            cout << "This is an invalid entry." << endl;
            cout << "Please enter your first name without whitespace ";
            cout << "or special characters." << endl;

            getline(cin, user_input);
            ValidateUsersName(user_input);
        } else {
            counter++;
        }
    }
}

/* *****************************************************************
 * Validates the player's choice by ensuring that only numeric
 * characters or digits are allowed. Whitespaces, letters and special
 * characters are not allowed. The user will be asked to make a new
 * entry for as long as an invalid character is entered. In addition,
 * the user is only allowed to enter 1 single digit that is between
 * 0 and 8.
 * *****************************************************************/

int ValidatePlayersChoice(string &user_input) {

    if (user_input.length() == 0 || user_input.length() > 1) {
        cout << "This is an invalid entry." << endl;
        cout << "Please choose a number from 0 to 8." << endl;

        getline(cin, user_input);
        ValidatePlayersChoice(user_input);
    }

    if ( !isdigit(user_input[0]) ) {
        cout << "The character entered is not a number." << endl;
        cout << "Please choose a number from 0 to 8." << endl;

        getline(cin, user_input);
        ValidatePlayersChoice(user_input);
    }

    if (user_input[0] != '0' && user_input[0] != '1' &&
        user_input[0] != '2' && user_input[0] != '3' &&
        user_input[0] != '4' && user_input[0] != '5' &&
        user_input[0] != '6' && user_input[0] != '7' &&
        user_input[0] != '8') {
             cout << "This is an invalid entry." << endl;
            cout << "Please choose a number from 0 to 8." << endl;

            getline(cin, user_input);
            ValidatePlayersChoice(user_input);

        }
    // converts a string into an int and returns the int.
    return stoi(user_input);
}

/* *****************************************************************
 * Searches through an array of strings which represents the game's
 * board, by comparing whether an index in the array is a legal
 * move, and thus is an unoccupied or empty space, by invoking the
 * isMoveLegal() function for each index in the array. It returns
 * the first index that is empty.
 * *****************************************************************/

int LocateEmptySpace(string board[], int board_size) {
    for (int index = 0; index < board_size; index++) {
        if (isMoveLegal(board, board_size, index)) {
            return index;
        }
    }
}

/* *****************************************************************
 * Checks whether a move is legal by cheecking whether a specied
 * index is an unoccupied space by searching through the contents
 * of the game's board, represented by an array of strings. Returns
 * true if the specied index represents an unoccupied space. Returns
 * false otherwise.
 * *****************************************************************/

bool isMoveLegal(string board[], int board_size, int index_selected_by_player) {
    if (board[index_selected_by_player] == HUMAN_PLAYER ||
        board[index_selected_by_player] == COMPUTER_PLAYER) {
        return false;
    } else {
        return true;
    }
}

/* *****************************************************************
 *  Updates the array of the states of the game by checking
 * the array of the string type, which represents the board of the
 * game. If an index represents a space occupied by either player,
 * the array of states is updated to reflect which spaces are
 * occupied by either player and which, if any, spaces are
 * unoccupied.
 * *****************************************************************/

void UpdateBoard(StatesOfGame states[], string board[], int board_size) {
    for (int index = 0; index < board_size; index++) {
        if (board[index] == HUMAN_PLAYER) {
            states[index] = Human_Occupied_Space;
        } else if (board[index] == COMPUTER_PLAYER) {
            states[index] = Computer_Occupied_Space;
        } else {
            states[index] = Unoccupied_Space;
        }
    }
}

/* *****************************************************************
 * Changes the current turn by updating the Game structure's
 * member variable, current_turn, and increasing it by 1. If the
 * number of turns exceeds the number of turns, that is, the
 * total number of spaces in the board, the game exits by invoking
 * the ExitGame() function. This represents that all spaces are now
 * occupied and that there is no winner, which means the game is a
 * tie.
 * *****************************************************************/

void ChangeTurn(StatesOfGame states[], string board[], int board_size, Game &g) {
    g.current_turn++;

    if (g.current_turn >= board_size + 1) {
        ExitGame(states, board, board_size, g);

        cout << "The game is a tie!" << endl;
    }
}

/* *****************************************************************
 * Validatess the computer's choices by checking three possible
 * choices made by the computer and checking to see if any of the
 * choices are valid by invoking the isMoveLegal() function. Returns
 * the first legal choice.
 * *****************************************************************/

int ValidateComputersChoice(string board[], int board_size, int index_1, int index_2, int index_3) {
    if (isMoveLegal(board, board_size, index_1)) {
        return index_1;
    } else if (isMoveLegal(board, board_size, index_2)) {
        return index_2;
    } else {
        return index_3;
    }
}

/* *****************************************************************
 * Calculates the computer's move by taking into consideration a
 * total of three factors: what is the current turn, is there a
 * possibility of the computer making a choice that will result in
 * a win, and whether there is a possibility of the computer player
 * losing if it does not block the human's next move.
 *
 * The computer player will always choose the position labeled 4
 * on the board on its first turn if it is unoccupied and will choose
 * the position labeled 0 if position 4 was choosen by the human
 * player on its first move.
 *
 * The game's current state is checked by checking the array of
 * the state of the game, Spaces occupied by the human player are
 * represented in the array by the number 5, the spaces occupied by
 * the computer player are represented by the number 3, and the
 * unoccupied spaces are represented by the number 0.
 *
 * By checking the state of the board by stepping through the state
 * of game array, the computer can check whether there are any rows,
 * columns or diagnoal lines where the computer player can win by
 * making a selection at an unoccupied space. This is represented by
 * the states, whose values are represented by numbers. If there
 * are two computer occupied spaces in a single row, column or
 * diagonal line, their sum equals 6. If this case exists, the
 * computer player will make a selection at the occupied space to
 * win the game.
 *
 * If there are no winning moves, the array is stepped through to
 * determine whether there are any rows, columns or diagonal lines
 * where the human player occupies two spaces. This condition is
 * represented by adding the values of two states whose sum equals
 * 10. If this case exists, the computer player will make a make
 * a selection at an unoccupied space that will block the computer
 * player from wining.
 *
 * If none of the previous conditions exists, the computer will
 * make a selection at the first unoccupied space, which is
 * represented by the value 0 in the array of states.
 *
 * The computer's choice in either case is validated to ensure
 * that it is a legal move by invoking the isMoveLegal() function.
 * *****************************************************************/

int CalculateComputersMove(StatesOfGame states[], string board[], int board_size, Game g) {
    int index_selected_by_computer;

    /* Checks whether the spot labeled 4--the center of the  board--is taken.
     * If it has not been chosen by the human player, this will be the first
     * selection made by the computer. Otherwise, the computer will select
     * the spot labeled 0. */

    if (g.current_turn == 2 && board[4] != HUMAN_PLAYER) {
        index_selected_by_computer = 4;
        if(isMoveLegal(board, board_size, index_selected_by_computer)) {
            return index_selected_by_computer;
        }
    } else if (g.current_turn == 2 && board[4] == HUMAN_PLAYER) {
        index_selected_by_computer = 0;
        if(isMoveLegal(board, board_size, index_selected_by_computer)) {
            return index_selected_by_computer;
        }


    } else {

        /* By adding the elements of the state of the game array, the computer can
         * determine whether it is possible for it to win if the sum of any row,
         * column or diagonal line is 6. If the sum of these elements is 6, the
         * computer will select a space to win. */

        /* Checking if possible to win by completing either row 1, 2, or 3. */

        if ( (states[0] + states[1] + states[2]) == 6) {
            index_selected_by_computer = ValidateComputersChoice(board, board_size, 0, 1, 2);
            return index_selected_by_computer;
        } else if ( (states[3] + states[4] + states[5]) == 6) {
            index_selected_by_computer = ValidateComputersChoice(board, board_size, 3, 4, 5);
            return index_selected_by_computer;
        } else if ( (states[6] + states[7] + states[8]) == 6) {
            index_selected_by_computer = ValidateComputersChoice(board, board_size, 6, 7, 8);
            return index_selected_by_computer;

        /* Checking if possible to win by completing either column 1, 2, or 3. */

        } else if ( (states[0] + states[3] + states[6]) == 6) {
            index_selected_by_computer = ValidateComputersChoice(board, board_size, 0, 3, 6);
            return index_selected_by_computer;
        } else if ( (states[1] + states[4] + states[7]) == 6) {
            index_selected_by_computer = ValidateComputersChoice(board, board_size, 1, 4, 7);
            return index_selected_by_computer;
        } else if ( (states[2] + states[5] + states[8]) == 6) {
            index_selected_by_computer = ValidateComputersChoice(board, board_size, 2, 5, 8);
            return index_selected_by_computer;

        /* Checking if possible to win by completing diagonal or reverse dignonal lines. */

        } else if ( (states[0] + states[4] + states[8]) == 6) {
            index_selected_by_computer = ValidateComputersChoice(board, board_size, 0, 4, 8);
            return index_selected_by_computer;
        } else if ( (states[2] + states[4] + states[6]) == 6) {
            index_selected_by_computer = ValidateComputersChoice(board, board_size, 2, 4, 6);
            return index_selected_by_computer;

            /* By adding the elements of the state of the game array, the computer can
             * determine whether it is possible for it to lose if the sum of any row,
             * column or diagonal line is 10. If the sum of these elements is 10, the
             * computer will select a space in the row, column or diagonal line where
             * it can lose by not making a selection there. */


        /* Checking if possible to lose if the human player completes row 1, 2, or 3. */

        } else if ( (states[0] + states[1] + states[2]) == 10) {
            index_selected_by_computer = ValidateComputersChoice(board, board_size, 0, 1, 2);
            return index_selected_by_computer;
        } else if ( (states[3] + states[4] + states[5]) == 10) {
            index_selected_by_computer = ValidateComputersChoice(board, board_size, 3, 4, 5);
            return index_selected_by_computer;
        } else if ( (states[6] + states[7] + states[8]) == 10) {
            index_selected_by_computer = ValidateComputersChoice(board, board_size, 6, 7, 8);
            return index_selected_by_computer;

        /* Checking if possible to lose if the human player completes column 1, 2, or 3. */

        } else if ( (states[0] + states[3] + states[6]) == 10) {
            index_selected_by_computer = ValidateComputersChoice(board, board_size, 0, 3, 6);
            return index_selected_by_computer;
        } else if ( (states[1] + states[4] + states[7]) == 10) {
            index_selected_by_computer = ValidateComputersChoice(board, board_size, 1, 4, 7);
            return index_selected_by_computer;
        } else if ( (states[2] + states[5] + states[8]) == 10) {
            index_selected_by_computer = ValidateComputersChoice(board, board_size, 2, 5, 8);
            return index_selected_by_computer;

        /* Checking if possible to lose if the human player completes diagonal or reverse dignonal lines. */

        } else if ( (states[0] + states[4] + states[8]) == 10) {
            index_selected_by_computer = ValidateComputersChoice(board, board_size, 0, 4, 8);
            return index_selected_by_computer;
        } else if ( (states[2] + states[4] + states[6]) == 10) {
            index_selected_by_computer = ValidateComputersChoice(board, board_size, 2, 4, 6);
            return index_selected_by_computer;
        } else {
            index_selected_by_computer = LocateEmptySpace(board, board_size);
            return index_selected_by_computer;
        }
    }


    index_selected_by_computer = LocateEmptySpace(board, board_size);
            return index_selected_by_computer;
}
