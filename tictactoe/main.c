#include <stdio.h>
#include <stdbool.h>

void printboard(void);
void user(char symbol);
int score(char fplayer, char splayer);
bool win(char *board);
void movesgen();
int engine();
void resetboard();
void change();

char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
char engineboard[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
int points[9] = {3, 2, 3, 2, 4, 2, 3, 2, 3};
int move = 0, possiblemoves[9];

int main(void)
{
    char symbol = 'X', second = 'O';
    int move = 0, best;
    bool end;

    // start game
    printboard();
    user(symbol);

    do
    {
        // second person
        movesgen();
        // user(second);
        change();

        // score(symbol, second);
        end = win(board);
        move++;
        if (end == true)
        {
            return 2;
        }

        // first person
        printboard();
        movesgen();
        // best = engine();
        // printf("the best move is %i\n", best);

        user(symbol);
        end = win(board);
        move++;
        if (end == true)
        {
            return 1;
        }
    } while (move < 8);

    // check for draw or if game has ended
    end = win(board);
    if (end == true)
    {
        return 3;
    }
    else
    {
        printf("It's a draw\n");
    }
}

void printboard(void)
{
    printf("\n");
    int box = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf(" %c |", board[box]);
            box++;
        }
        printf("\n");
    }
}

void user(char symbol)
{
    int select, box;

    printf("%c's move: ", symbol);
    scanf("%i", &select);
    box = board[select - 1] - 48;

    if (select <= 0 || select > 9 || select != box)
    {
        printf("invalid, choose again\n");
        user(symbol);
        return;
    }

    board[select - 1] = symbol;
}

int score(char fplayer, char splayer)
{
    int eval = 0;

    for (int i = 0; i < 9; i++)
    {
        char box = board[i];

        if (box == fplayer)
        {
            eval = eval + points[i];
        }
        if (box == splayer)
        {
            eval = eval - points[i];
        }
    }
    printf("The score is %i\n\n", eval);
}

bool win(char *board)
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i] == board[i + 3])
        {
            if (board[i] == board[i + 6])
            {
                char player = board[i];
                // printf("%c WON!!\n", player);
                // printboard();
                return true;
            }
        }
    }

    for (int j = 0; j < 3; j++)
    {
        if (board[3 * j] == board[3 * j + 1])
        {
            if (board[3 * j] == board[3 * j + 2])
            {
                char player = board[3 * j];
                // printf("%c WON!!\n", player);
                // printboard();
                return true;
            }
        }
    }

    if (board[0] == board[4])
    {
        if (board[4] == board[8])
        {
            char player = board[0];
            // printf("%c WON!!\n", player);
            // printboard();
            return true;
        }
    }

    if (board[2] == board[4])
    {
        if (board[4] == board[6])
        {
            char player = board[0];
            // printf("%c WON!!\n", player);
            // printboard();
            return true;
        }
    }

    return false;
}

void movesgen()
{
    // reset board
    for (int k = 0; k < 9; k++)
    {
        possiblemoves[k] = 10;
    }

    for (int i = 0; i < 9; i++)
    {
        char box = board[i];

        if (box != 'X' && box != 'O')
        {
            possiblemoves[i] = i;
        }
    }

    // check
    //     for (int j = 0; j < 9; j++)
    //     {
    //         printf("%i ", possiblemoves[j]);
    //     }
    //     printf("\n");
}

int engine()
{
    int score = -1, move = 10;
    bool end;

    // first move gen
    for (int i = 0; i < 9; i++)
    {
        resetboard();
        movesgen();

        if (possiblemoves[i] != 10)
        {
            engineboard[i] = 'O';
            end = win(engineboard);
            if (end == true)
            {
                score = 10;
                move = possiblemoves[i] + 1;
                return move;
            }

            // second move gen
            for (int j = 0; j < 9; j++)
            {
                resetboard();
                engineboard[i] = 'O';
                movesgen();

                if (possiblemoves[j] != 10)
                {
                    engineboard[j] = 'X';
                    end = win(engineboard);
                    if (end == true)
                    {
                        move = possiblemoves[j] + 1;
                        return move;
                    }
                }

                // third move gen
                for (int k = 0; k < 9; k++)
                {
                    resetboard();
                    engineboard[i] = 'O';
                    engineboard[j] = 'X';
                    movesgen();

                    if (possiblemoves[k] != 10)
                    {
                        engineboard[k] = 'O';
                        end = win(engineboard);
                        if (end == true)
                        {
                            score = 10;
                            move = possiblemoves[k] + 1;
                        }
                        else
                        {
                            move = possiblemoves[k] + 1;
                        }
                    }
                }
            }
        }
    }
    return move;
}

void resetboard()
{
    for (int i = 0; i < 9; i++)
    {
        engineboard[i] = board[i];
    }
}

void change()
{
    int move = engine();
    board[move - 1] = 'O';
}