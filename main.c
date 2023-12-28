#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char board[3][3];
char player;
char computer;

void chooseCharacter()
{
    do
    {
        printf("\nChoose your symbol (X/O): ");
        scanf(" %c", &player);
        player = toupper(player);
        getchar();
        
        if(player == 'X')
        {
            computer = 'O';
        }
        else if(player == 'O')
        {
            computer = 'X';
        }
        else {
            printf("\nInvalid character! Choose only between X or O.\n");
        }
    } while (player != 'X' && player != 'O');
    
}

void resetBoard()
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
};

void printBoard()
{
    printf("\n");
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");
};

int checkFreeSpaces()
{
    int freeSpaces = 9;
    
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j] != ' ')
            {
                freeSpaces--;
            }
        }
    }

    return freeSpaces;
};

void printWinner(char winner)
{
    if(winner == player)
    {
        printf("\nYOU WIN!\n");
    }
    else if(winner == computer)
    {
        printf("\nYOU LOSE!\n");
    }
    else {
        printf("\nIT'S A TIE!\n");
    }
};

void playerMove()
{
    int x;
    int y;

    do 
    {
        printf("Enter row number (1 - 3): ");
        scanf("%d", &x);
        x--;

        printf("Enter column number (1 - 3): ");
        scanf("%d", &y);
        y--;

        if(board[x][y] != ' ')
        {
            printf("Invalid Move!\n");
        }
        else
        {
            board[x][y] = player;
            break;
        }
    } while (board[x][y] != ' ');
    
};

void computerMove()
{
    // create a seed based on current time
    srand(time(0));
    int x;
    int y;

    if(checkFreeSpaces() > 0)
    {
        do
        {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');
        
        board[x][y] = computer;
    }
    else
    {
        printWinner(' ');
    }
};

char checkWinner()
{
    // check rows
    for(int i = 0; i < 3; i++)
    {
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
            return board[i][0];
        }
    }

    // check columns
    for(int i = 0; i < 3; i++)
    {
        if(board[0][i] == board[1][i] && board[0][i] == board[2][i])
        {
            return board[0][i];
        }
    }

    // check diagonals
    if(board[0][0] == board[1][1] && board[0][0] == board[2][2])
    {
        return board[0][0];
    }
    if(board[0][2] == board[1][1] && board[0][2] == board[2][0])
    {
        return board[0][2];
    }

    // no winner
    return ' ';
};

int main()
{
    char winner = ' ';
    char response;

    do
    {
        winner = ' ';
        response = ' ';
        chooseCharacter();
        resetBoard();
    
        while(winner == ' ' && checkFreeSpaces() != 0)
        {
            printBoard();
            printf("\n");

            playerMove();
            winner = checkWinner();
            if(winner != ' ' || checkFreeSpaces() == 0)
            {
                break;
            }

            computerMove();
            winner = checkWinner();
            if(winner != ' ' || checkFreeSpaces() == 0)
            {
                break;
            }
        }
        printBoard();
        printWinner(winner);

        printf("Would you like to play again? (y/n): ");
        scanf(" %c", &response);
        response = toupper(response);
        getchar();
    } while (response == 'Y');

    printf("\n======== Thanks for playing! ========\n\n");

    return 0;
}