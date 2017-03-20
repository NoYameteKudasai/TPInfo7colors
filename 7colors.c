/* Template of the 7 wonders of the world of the 7 colors assigment. */

#include <stdio.h>     /* printf */
#include <stdlib.h>
#include <time.h>
#include <ctype.h>


// On définit des alias pour les couleurs dans le terminal
#define ANSI_COLOR_RED		"\x1b[0;41m"
#define ANSI_COLOR_GREEN	"\x1b[0;42m"
#define ANSI_COLOR_YELLOW	"\x1b[0;43m"
#define ANSI_COLOR_BLUE		"\x1b[0;44m"
#define ANSI_COLOR_MAGENTA	"\x1b[0;45m"
#define ANSI_COLOR_CYAN		"\x1b[0;46m"
#define ANSI_COLOR_WHITE	"\x1b[0;46m"
#define ANSI_COLOR_RESET	"\x1b[0;0m"



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
	// On vérifie tout d'abord que le caractère entré est valide
    if((color != 'A') &&
        (color != 'B') &&
        (color != 'C') &&
        (color != 'D') &&
        (color != 'E') &&
        (color != 'F') &&
        (color != 'G'))
    {
        printf("Invalid entry");
        return;
    }
    
    // Pour éviter d'avoir à les calculer à chaque fois ...
    int BB = BOARD_SIZE * BOARD_SIZE;
    int BBMO = BOARD_SIZE * (BOARD_SIZE-1);
    
    
    /* MÉTHODE NON RÉCURSIVE
     */
    
    int flag = 1;
	while(flag)
	{
		flag = 0;
		
		int i;
		for(i = 0 ; i < BB ; i++)
		{            
            /* Si le bloc n'est pas en haut du plateau, on contrôle le bloc directement au-dessus de lui
             * '' gauche ''
             * '' bas ''
             * '' droite ''
             * pas besoin d'imbriquer les if, la premère condition de chaque && le court-circuite, et évite tout segfault
             */
            if(board[i] == color &&
                ( (i >= BOARD_SIZE && board[i-BOARD_SIZE] == player) ||
                ((i % BOARD_SIZE) && board[i-1] == player) ||
                ((i < BBMO) && board[i+BOARD_SIZE] == player) ||
                ((i % BOARD_SIZE != BOARD_SIZE - 1) && board[i+1] == player) ) )
            {
                board[i] = player;
                flag = 1;
            }            
		}
	}
	
	
	/* MÉTHODE RÉCURSIVE
     */
    
    
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
			switch(get_cell(j, i))
			{
				case 'A':
					printf(ANSI_COLOR_RED "A" ANSI_COLOR_RESET);
					break;
				case 'B':
					printf(ANSI_COLOR_GREEN "B" ANSI_COLOR_RESET);
					break;
				case 'C':
					printf(ANSI_COLOR_YELLOW "C" ANSI_COLOR_RESET);
					break;
				case 'D':
					printf(ANSI_COLOR_BLUE "D" ANSI_COLOR_RESET);
					break;
				case 'E':
					printf(ANSI_COLOR_MAGENTA "E" ANSI_COLOR_RESET);
					break;
				case 'F':
					printf(ANSI_COLOR_CYAN "F" ANSI_COLOR_RESET);
					break;
				case 'G':
					printf(ANSI_COLOR_WHITE "G" ANSI_COLOR_RESET);
					break;
				default:
					printf("%c", get_cell(j, i));
					break;
			};			
        }
        printf("\n");
    }
    
    printf("\n\n\n");
}


/** Game human vs human */
void gamehvh()
{	
	int player = 0;
    char input_color;
	
	int flag = 1;
	while(flag)
	{
		printf("\n\n\n");
		print_board();
		
		if(player == 0)
		{
			printf("Player 1 : ");
			scanf(" %c", &input_color);
			play(toupper(input_color), 'v');
		}
		else if(player == 1)
		{
			printf("Player 2 : ");
			scanf(" %c", &input_color);
			play(toupper(input_color), '^');
		}
		/* On remarquera qu'en mettant un espace devant %c,
         * on évite de récupérer le caractère de fin de la saisie précédente,
         * et donc d'outrepasser la saisie de l'un des deux joueurs
         * http://stackoverflow.com/questions/32236684/c-scanf-issues
         */
		
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
