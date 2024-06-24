#include <stdio.h>
#include <stdbool.h>

void printboard(void);
void user(char symbol);
bool win(char *board);
void movesgen();
int engine();
void resetboard();
void change();

char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
char engineboard[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
int move = 0, possiblemoves[9];

int main(void)
{
    char symbol = 'X';
    bool end;

    // start game
    printboard();
    user(symbol);

    do
    {
        // second person (engine)
        movesgen();
        change();
        printboard();
        end = win(board);
        if (end)
        {
            printf("O wins!\n");
            return 2;
        }
        move++;

        // first person (user)
        user(symbol);
        printboard();
        end = win(board);
        if (end)
        {
            printf("X wins!\n");
            return 1;
        }
        move++;
    } while (move < 9);

    printf("It's a draw\n");
    return 0;
}

void printboard(void)
{
    printf("\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf(" %c |", board[i * 3 + j]);
        }
        printf("\n");
    }
}

void user(char symbol)
{
    int select;

    printf("%c's move: ", symbol);
    scanf("%i", &select);
    select--; // Adjust for 0-based index

    if (select < 0 || select > 8 || board[select] == 'X' || board[select] == 'O')
    {
        printf("Invalid move, choose again\n");
        user(symbol);
        return;
    }

    board[select] = symbol;
}

bool win(char *board)
{
    // Check rows and columns
    for (int i = 0; i < 3; i++)
    {
        if ((board[i] == board[i + 3] && board[i] == board[i + 6]) ||
            (board[i * 3] == board[i * 3 + 1] && board[i * 3] == board[i * 3 + 2]))
        {
            return true;
        }
    }

    // Check diagonals
    if ((board[0] == board[4] && board[0] == board[8]) ||
        (board[2] == board[4] && board[2] == board[6]))
    {
        return true;
    }

    return false;
}

void movesgen()
{
    for (int i = 0; i < 9; i++)
    {
        possiblemoves[i] = (board[i] != 'X' && board[i] != 'O') ? i : 10;
    }
}

int engine()
{
    for (int i = 0; i < 9; i++)
    {
        resetboard();
        if (possiblemoves[i] != 10)
        {
            engineboard[i] = 'O';
            if (win(engineboard))
            {
                return i + 1;
            }

            for (int j = 0; j < 9; j++)
            {
                resetboard();
                engineboard[i] = 'O';
                if (possiblemoves[j] != 10)
                {
                    engineboard[j] = 'X';
                    if (win(engineboard))
                    {
                        return j + 1;
                    }
                }
            }
        }
    }
    for (int i = 0; i < 9; i++)
    {
        if (possiblemoves[i] != 10)
        {
            return i + 1;
        }
    }
    return 1; // Default move if no better option
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
