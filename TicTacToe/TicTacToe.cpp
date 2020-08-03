// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>

class Player {
    /*
    ADT for Player
    name is a string for the player's name
    score is their score in games
    position is whether they are 1st or 2nd to play
    */
    std::string name;
    int score;
    int position;
    void updatePos(int pos) {
        position = pos;
    }
    public:
        Player(std::string name, int position) : name(name), score(0), position(position) {

        }

        int updateScore() {
            return ++score;
        }
        int getScore() {
            return score;
        }
        int getPos() {
            return position;
        }
        void switchPos(Player* other) {
            int otherScore = other->getScore();
            other->updatePos(this->getScore());
            this->updatePos(otherScore);
        }
        std::string getName() {
            return name;
        }
};

class Board {
    /*
    Board ADT to define the Tic Tac Toe Board and its operations
    board is an array of the Xs and Os represented as 
        0: blank space
        1: X
        2: O
    */
    int board[9];
    public:
        Board() : board{ 0 } {
            
        }

        Board(int givenBoard[9]) : board{ 0 } {
            for (int i = 0; i < 9; i++) {
                board[i] = givenBoard[i];
            }
        }

        //updates board at pos with the player
        //returns nullptr if space is already taken
        Board* updateBoard(int pos, int player) {
            
            if (board[pos] != 0 || pos < 0 || pos >= 9) {
                return nullptr;
            }
            board[pos] = player;
            return this;
        }

        int isGameOver() {
        /*
            returns winning player if game is over
            returns 0 is game is ongoing
            returns -1 if draw
        */
        // across
        if ((board[0] == board[1]) && (board[1] == board[2]) && (board[0] == 1 || board[0] == 2)) {
            return board[0];
        }
        if ((board[3] == board[4]) && (board[4] == board[5]) && (board[3] == 1 || board[3] == 2)) {
            return board[3];
        }
        if ((board[6] == board[7]) && (board[7] == board[8]) && (board[6] == 1 || board[6] == 2)) {
            return board[6];
        }
        // up down
        if ((board[0] == board[3]) && (board[3] == board[6]) && (board[0] == 1 || board[0] == 2)) {
            return board[0];
        }
        if ((board[1] == board[4]) && (board[4] == board[7]) && (board[1] == 1 || board[1] == 2)) {
            return board[1];
        }
        if ((board[2] == board[5]) && (board[5] == board[8]) && (board[2] == 1 || board[2] == 2)) {
            return board[2];
        }
        // diagonal
        if ((board[0] == board[4]) && (board[4] == board[8]) && (board[0] == 1 || board[0] == 2)) {
            return board[0];
        }
        if ((board[2] == board[4]) && (board[4] == board[6]) && (board[2] == 1 || board[2] == 2)) {
            return board[2];
        }
        for (int i = 0; i < 9; i++) {
            if (board[i] == 0)
                return 0;
        }
        return -1;
    }

        //returns string representation of the board
        std::string toString() const {
            std::string ret = "";
            for (int i = 0; i < 3; i++) {
                if (board[i * 3] == 1) {
                    ret += " X |";
                }
                else if (board[i * 3] == 2) {
                    ret += " O |";
                }
                else {
                    ret += " ";
                    ret += std::to_string(i*3);
                    ret += " |";
                }
                if (board[((i * 3) +1)] == 1) {
                    ret += " X |";
                }
                else if (board[((i * 3) + 1)] == 2) {
                    ret += " O |";
                }
                else {
                    ret += " ";
                    ret += std::to_string((i * 3)+1);
                    ret += " |";
                }
                if (board[((i * 3) + 2)] == 1) {
                    ret += " X |\n";
                }
                else if (board[((i * 3) + 2)] == 2) {
                    ret += " O |\n";
                }
                else {
                    ret += " ";
                    ret += std::to_string((i * 3) + 2);
                    ret += " |\n";
                }
                if (i != 2)
                    ret += "--------------\n";
            }
            return ret;
        }
};

std::ostream& operator<<(std::ostream& strm, const Board& b) {
    return strm << b.toString() <<std::endl;
}

struct Game {
    /*
    ADT for Game
    boards is a list of boards of tic tac toe between the players
    p1 is Player 1
    p2 is Player 2
    */
    std::vector<Board*> boards;
    Player p1;
    Player p2;

    Game(std::string name1, std::string name2) : p1(Player(name1, 1)), p2(Player(name2, 2)) {
        //startNewGame();
    }
    Game(Player player1, Player player2) : p1(player1), p2(player2) {
        //startNewGame();
    }
    // creates a new board and adds it to the list and switches p1 and p2
    Board* startNewGame() {
        Board* board = new Board();
        boards.push_back(board);
        p1.switchPos(&p2);
        return board;
    }

    // attempts to play a move
    // returns 0 if game has ended
    // returns 1 if game is still going
    // returns -1 if an invalid move was played
    int playMove(Board* board, int player, int pos) {
        Board* check = board->updateBoard(pos, player);
        if (check == nullptr)
            return -1;
        if (board->isGameOver() != 0) {
            if (board->isGameOver() == 1)
                std::cout << p1.getName() << " Wins!\n" << p1.getName() << " - " << p2.getName() << "\nScore is " << p1.updateScore() << "-" << p2.getScore() << std::endl;
            else if (board->isGameOver() == 2)
                std::cout << p2.getName() << " Wins!\n" << p1.getName() << " - " << p2.getName() << "\nScore is " << p1.getScore() << "-" << p2.updateScore() << std::endl;
            else
                std::cout << "Tie!\n" << p1.getName() << " - " << p2.getName() << "\nScore is " << p1.getScore() << "-" << p2.getScore() << std::endl;
            return 0;
        }
        return 1;
    }

    // gets the current game board of Tic Tac Toe
    Board* getCurrentGame() {
        return boards[boards.size() - 1];
    }

    // gets a game of tic tac toe
    // returns nullptr if invalid gameNumber is given
    Board* getGame(int gameNumber) {
        if (gameNumber < boards.size() && gameNumber >= 0) {
            return boards[gameNumber];
        }
        return nullptr;
    }

    //cleans up memory of boards
    void endGame() {
        for (Board* b : boards) {
            delete b;
        }
    }
};

//runs a turn of tic tac toe
bool runGame(Player* player, Game* game) {

    std::string pos;
    int isGameGoing;
    Board* board = game->getCurrentGame();
    std::cout << player->getName() << " where do you want to go?" << std::endl;
    std::cout << *board << std::endl;
    while (1) {
        std::cin >> pos;
        try {
            isGameGoing = game->playMove(board, player->getPos(), std::stoi(pos));
            if (isGameGoing == -1)
                throw "NOT VALID";
            break;
        }
        catch (...) {
            std::cout << "that's not a valid position" << std::endl;
        }
    }

    
    if (isGameGoing == 1)
        return true;
    std::cout << *board << std::endl;
    return false;
}
template<typename T>
void swap(T& a, T& b)
{
    T t = a;
    a = b;
    b = t;
}

int main()
{
    std::cout << "welcome to tic tac toe" << std::endl;
    std::cout << "what's the name of PLAYER 1: " << std::endl;
    std::string player0Name;
    std::string player1Name;
    std::cin >> player0Name;
    std::cout << "what's the name of PLAYER 2: " << std::endl;
    std::cin >> player1Name;
    Player player0(player0Name, 1);
    Player player1(player1Name, 2);
    Player* players[2] = { &player0, &player1 };
    Game game(player0, player1);
    bool keepPlaying = true;
    

    while (keepPlaying) {
        game.startNewGame();
        swap(players[0], players[1]);
        while (1) {
            if (!runGame(players[0], &game))
                break;
            if (!runGame(players[1], &game))
                break;
        }
        std::string type;
        while (true) {
            std::cout << "would u like to play again? [y/n]" << std::endl;
            std::cin >> type;

            if ((type == "y") || (type == "n")) {
                break;
            }
        }
        keepPlaying = type == "y";
    }
    game.endGame();

}
