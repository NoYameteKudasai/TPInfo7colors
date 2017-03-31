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
#define ANSI_COLOR_CYAN		"\x1b[30;46m"
#define ANSI_COLOR_WHITE	"\x1b[30;47m"
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
	int i;
	for(i = 0 ; i < BOARD_SIZE*BOARD_SIZE ; i++)
	{
		// Setting a random value between 'A' and 'G'
		board[i] = (rand() % 7) + 'A';
	}
	
	// Setting the start cells for each player in the corners
	set_cell(BOARD_SIZE-1, 0, '^');
	set_cell(0, BOARD_SIZE-1, 'v');
}


/** Play */
void updateBoard(char* boardToUpdate, char color, char player_c)
{
	// Checking the entry
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
    
    // Defining those not to compute them at each iteration ...
    int BB = BOARD_SIZE * BOARD_SIZE;
    int BBMO = BOARD_SIZE * (BOARD_SIZE-1);
    
    
    /* NON RECURSIVE WAY
     */
    
    /* While flag=1 the check continues
	 * if flag=0 at the end of the loop, the check ends
	 */
	int flag = 1;
	while(flag)
	{
		flag = 0;
		
		int i;
		for(i = 0 ; i < BB ; i++)
		{
			/* If the block is not at the top of the board, checking if the upper block belongs to player
             * '' left '' left ''
             * '' bottom '' lower ''
             * '' right '' right ''
			 * the order in the && blocks prevent any segfault
             */
            if(boardToUpdate[i] == color &&
                ( (i >= BOARD_SIZE && boardToUpdate[i-BOARD_SIZE] == player_c) ||
                ((i % BOARD_SIZE) && boardToUpdate[i-1] == player_c) ||
                ((i < BBMO) && boardToUpdate[i+BOARD_SIZE] == player_c) ||
                ((i % BOARD_SIZE != BOARD_SIZE - 1) && boardToUpdate[i+1] == player_c) ) )
            {
                boardToUpdate[i] = player_c;
				
				// If a change is made, continue checking
                flag = 1;
            }
		}
		
		// If no change is made, flag remains equal to 0 and the loop ends
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
    
    printf("\n\n");
}



float rate(char* boardToCheck, char character)
{
	int count = 0;
	int BB = BOARD_SIZE*BOARD_SIZE;
	
	int i;
	for(i = 0; i < BB; i++)
	{
		// Increment the counter at each encounter
		if(boardToCheck[i] == character)
			count ++;
	}
	
	return (float)count/BB;
}


/** Game human vs human */
int gamehvh()
{	
	int player = 1;
    char input_color;
	
	/* The game continues until one player wins (return)
	 */
	while(1)
	{
		if(player) // Player 1
		{
			// Getting Player1's entry
			printf("Player 1 : ");
			scanf(" %c", &input_color);
			// Updating the board according to it
			updateBoard(board, toupper(input_color), 'v');
		}
		else // Player 2
		{
			// Ditto ...
			printf("Player 2 : ");
			scanf(" %c", &input_color);
			updateBoard(board, toupper(input_color), '^');
		}
		/* On remarquera qu'en mettant un espace devant %c,
		 * on évite de récupérer le caractère de fin de la saisie précédente,
		 * et donc d'outrepasser la saisie de l'un des deux joueurs
		 * http://stackoverflow.com/questions/32236684/c-scanf-issues
		 */
		
		printf("\n");
		print_board();
		
		// Getting the fraction of the board belonged by each player
		float rate1 = rate(board, 'v');
		float rate2 = rate(board, '^');
		printf("Player 1 : %f %% \t\tPlayer 2 : %f %% \n\n", 100*rate1, 100*rate2);
		
		// If a player gets more than half the board
		if(rate1 >= 0.5f)
		{
			// The game finishes and 1 wins
			return 1;
		}
		else if(rate2 >= 0.5f)
		{
			// The game finishes and 2 wins
			return 2;
		}
		
		// The other player's turn
		player = !player;
	}
}


/** Game human vs bot */
int gamehvb(char (*AIFunc)(char))
{	
	char input_color;
	
	/* The game continues until one player wins (return)
	 */
	while(1)
	{
		// Player's turn
		printf("Player : ");
		scanf(" %c", &input_color);
		updateBoard(board, toupper(input_color), 'v');
		
		// Bot's turn, according to the given AI function
		updateBoard(board, (*AIFunc)('^'), '^');
		
		printf("\n");
		print_board();
		
		// Getting the fraction of the board belonged by each player
		float rate1 = rate(board, 'v');
		float rate2 = rate(board, '^');
		printf("Player : %f %% \t\tAI : %f %% \n\n", 100*rate1, 100*rate2);
		
		// If a player gets more than half the board
		if(rate1 >= 0.5f)
		{
			// The game finishes and 1 wins
			return 1;
		}
		else if(rate2 >= 0.5f)
		{
			// The game finishes and 2 wins
			return 2;
		}
	}
}



/** Game bot vs bot */
int gamebvb(char (*AIFunc1)(char), char (*AIFunc2)(char))
{	
	float rate1, rate2;
	
	/* The game continues until one player wins (return)
	 */
	while(1)
	{
		// Bot 1 turn
		updateBoard(board, (*AIFunc1)('v'), 'v');
		
		// Bot 2 turn
		updateBoard(board, (*AIFunc2)('^'), '^');
		
		printf("\n");
		print_board();
		
		// Getting the fraction of the board belonged by each player
		rate1 = rate(board, 'v');
		rate2 = rate(board, '^');
		
		printf("AI1 : %f %% \t\tAI2 : %f %% \n\n", 100*rate1, 100*rate2);
		
		// If a player gets more than half the board
		if(rate1 >= 0.5f)
		{
			// The game finishes and 1 wins
			return 1;
		}
		else if(rate2 >= 0.5f)
		{
			// The game finishes and 2 wins
			return 2;
		}
	}
}



char dumbRandBotAI(char botChar)
{
	// Returning a random character between 'A' and 'G'
	return 'A' + rand()%7;
}


char lessDumbBotAI(char botChar)
{
	int BB = BOARD_SIZE*BOARD_SIZE;
	
	/* Copy of the board
	 * used to foresee the future plays
	 */
	char* futureBoard = malloc(BB * sizeof(char));
	
	// Rate before the hypothetic plays
	float prevRate = rate(board, botChar);
	
	float curRate;
	
	int availableColorCnt = 0;
	
	// List of the colors that make the AI gain ground
	char* chosenColors = malloc(7 * sizeof(char));
	
	// Loop for each color
	char c;
	for(c = 'A'; c <= 'G'; c++)
	{
		// Reset the copy
		int i;
		for(i = 0; i < BB; i++)
			futureBoard[i] = board[i];
		
		// Simulate a play with a color
		updateBoard(futureBoard, c, botChar);
		
		// Checking if the territory has expanded
		curRate = rate(futureBoard, botChar);
		if(curRate > prevRate)
		{
			// If so, add the color to the possibly chosen colors
			chosenColors[availableColorCnt] = c;
			availableColorCnt++;
		}
	}
	
	free(futureBoard);
	
	// Randomly choose one of the selected colors
	char chosenColor = chosenColors[rand()%availableColorCnt];
	
	free(chosenColors);
	
	return chosenColor;
}


char greedyBotAI(char botChar)
{	
	int BB = BOARD_SIZE*BOARD_SIZE;
	
	/* Copy of the board
	 * used to foresee the future plays and choose the best
	 */
	char* futureBoard = malloc(BB * sizeof(char));
	
	char chosenColor;
	
	float curRate;
	float maxRate;
	
	// Loop for each color
	char c;
	for(c = 'A'; c <= 'G'; c++)
	{
		// Reset the copy
		int i;
		for(i = 0; i < BB; i++)
			futureBoard[i] = board[i];
		
		// Simulate a play with each color
		updateBoard(futureBoard, c, botChar);
		
		// Finding the color with maximum rate
		curRate = rate(futureBoard, botChar);
		if(curRate > maxRate)
		{
			maxRate = curRate;
			chosenColor = c;
		}
	}
	
	free(futureBoard);
	
	return chosenColor;
}


char greedy2BotAI(char botChar)
{	
	int BB = BOARD_SIZE*BOARD_SIZE;
	
	/* Copy of the board
	 * used to foresee the future plays and choose the best
	 */
	char* futureBoard = malloc(BB * sizeof(char));
	
	char chosenColor;
	
	float curRate;
	float maxRate;
	
	// Loop for each color
	char c1, c2;
	for(c1 = 'A'; c1 <= 'G'; c1++)
	for(c2 = 'A'; c2 <= 'G'; c2++)
	{
		// Reset the copy
		int i;
		for(i = 0; i < BB; i++)
			futureBoard[i] = board[i];
		
		// Simulate a play with each pair of colors
		updateBoard(futureBoard, c1, botChar);
		updateBoard(futureBoard, c2, botChar);
		
		// Finding the color with maximum rate
		curRate = rate(futureBoard, botChar);
		if(curRate > maxRate)
		{
			maxRate = curRate;
			chosenColor = c1;
		}
	}
	
	free(futureBoard);
	
	return chosenColor;
}



float contestbvb(char (*AIFunc1)(char), char (*AIFunc2)(char))
{
	// Victory count of AI1
	int victoryCnt1 = 0;
	
	int i;
	for(i = 0; i < 100; i++)
	{
		// Reset the board before each round
		fill_rand();
		
		// Fight !
		int winner = gamebvb(AIFunc1, AIFunc2);
		
		if(winner == 1)
			victoryCnt1++;
	}
	
	return (float)victoryCnt1/100;
}



/** Program entry point */
int main(void)
{
    printf("\n\nWelcome to the 7 wonders of the world of the 7 colors\n"
	   "*****************************************************\n\n"
	   "Current board state:\n");
	
	// Setting the rand seed to UNIX time
	srand(time(NULL));

    fill_rand();
	
	print_board();
    
    //gamehvh();
	gamehvb(&lessDumbBotAI);
	//gamebvb(&greedyBotAI, &dumbRandBotAI);
	//float a = contestbvb(&greedy2BotAI, &greedyBotAI);
	//printf("%f\n", a);

    return 0; // Everything went well
}
