/* Template of the 7 wonders of the world of the 7 colors assigment. */

#include <stdio.h>     /* printf */
#include <stdlib.h>
#include <time.h>



/* We want a 30x30 board game by default */
#define BOARD_SIZE 30



/** Represent the actual current board game
 *
 * NOTE: global variables are usually discouraged (plus encapsulation in
 *     an appropriate data structure would also be preferred), but don't worry.
 *     For this first assignment, no dinosaure will get you if you do that.
 */
char board[BOARD_SIZE * BOARD_SIZE] = { 0 }; // Filled with zeros



/** Retrieves the color of a given board cell */
char get_cell(int x, int y)
{
    if(x<0 || x>=BOARD_SIZE || y<0 || y>=BOARD_SIZE)
		return 0;
		
    return board[y * BOARD_SIZE + x];
}



/** Changes the color of a given board cell */
void set_cell(int x, int y, char color)
{
    board[y * BOARD_SIZE + x] = color;
}


/** Fills the borad with random colors */
void fill_rand(void)
{
	srand(time(NULL));
	
	int i;
	for(i = 0 ; i < BOARD_SIZE*BOARD_SIZE ; i++)
	{
		board[i] = (rand() % 7) + 'A';
	}
	
	set_cell(BOARD_SIZE-1, 0, '^');
	set_cell(0, BOARD_SIZE-1, 'v');
}


/** Play */
void play(char color, char player)
{
	int flag = 1;	
	while(flag)
	{
		flag = 0;
		
		int i;
		for(i = 0 ; i < BOARD_SIZE*BOARD_SIZE ; i++)
		{
			if(board[i] == color)
			{
				if(i == BOARD_SIZE
				if(i % BOARD_SIZE  == 0)
				{
					if(board[i+1] == player\
					|| board[i+BOARD_SIZE] == player\
					|| board[i-BOARD_SIZE] == player)
					{
						board[i] = player;
						flag = 1;
					}
				}
				
				else if(i % BOARD_SIZE  == BOARD_SIZE-1)
				{
					if(board[i-1] == player\
					|| board[i+BOARD_SIZE] == player\
					|| board[i-BOARD_SIZE] == player)
					{
						board[i] = player;
						flag = 1;
					}
				}
				
				else if(i < BOARD_SIZE)
				{
					if(board[i+1] == player\
					|| board[i-1] == player\
					|| board[i+BOARD_SIZE] == player)
					{
						board[i] = player;
						flag = 1;
					}
				}
				
				else if(i > BOARD_SIZE * (BOARD_SIZE - 1))
				{
					if(board[i+1] == player\
					|| board[i-1] == player\
					|| board[i-BOARD_SIZE] == player)
					{
						board[i] = player;
						flag = 1;
					}
				}
				
				else
				{
					if(board[i+1] == player\
					|| board[i-1] == player\
					|| board[i+BOARD_SIZE] == player\
					|| board[i-BOARD_SIZE] == player)
					{
						board[i] = player;
						flag = 1;
					}
				}
			}
		}
	}
}



/** Prints the current state of the board on screen
 *
 * Implementation note: It would be nicer to do this with ncurse or even
 * SDL/allegro, but this is not really the purpose of this assignment.
 */
void print_board(void)
{
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            printf("%c", get_cell(j, i));
        }
        printf("\n");
    }
    
    printf("\n\n\n");
}


/** Game human vs human */
void gamehvh()
{	
	int player = 0;
	
	int flag = 1;	
	while(flag)
	{
		char input_color;
		
		printf("\n\n\n");
		print_board();
		
		if(player == 0)
		{
			printf("Player 1 :");
			scanf("%c", &input_color);
			play(input_color, 'v');
		}
		else if(player == 1)
		{
			printf("Player 2 :");
			scanf("%c", &input_color);
			play(input_color, '^');
		}
		
		player = !player;
	}
}



/** Program entry point */
int main(void)
{
    printf("\n\nWelcome to the 7 wonders of the world of the 7 colors\n"
	   "*****************************************************\n\n"
	   "Current board state:\n");

    fill_rand();
    
    print_board();
    
    //play(get_cell(0, BOARD_SIZE-2), 'v');
    gamehvh();
    
    print_board();

    return 0; // Everything went well
}
