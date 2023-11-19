#include "market_display.h"


void place_token_in_board(struct token_t *tokens[NUM_TOKENS], \
struct token_t* board[(int) sqrt(NUM_TOKENS)][(int) sqrt(NUM_TOKENS)], \
char* tags[(int) sqrt(NUM_TOKENS)][(int) sqrt(NUM_TOKENS)])
{
    int dx = 1;
    int dy = 0;
    int i = 0;
    int j = 0;
    int board_size = sqrt(NUM_TOKENS);

    int steps = 0;
    int step_limit = board_size ;
    int direction_changes = 0;
    
    for (int index = 0; index < NUM_TOKENS ; ++index )
    {
        if((i < board_size ) && (i  >= 0) && (j < board_size) && (j >= 0))
        {
            
            board[i][j] = tokens[index];
            
        }

        ++steps;

        if(steps == step_limit)
        {
            steps = 1;
            

            if (direction_changes == 2)
            {
                direction_changes = 0;
                --step_limit;
            }
            ++direction_changes;

            int tmp = dx;
            dx = -dy;
            dy = tmp;
        }

        if((i < board_size ) && (i  >= 0) && (j < board_size) && (j >= 0))
        {
            
            if (dx == 1) // we are going to the rigt
            {
                tags[i][j] = "→";
            }
            if (dx == -1 ) //we are going to the left
            {
                tags[i][j] = "←";
            }
            if (dy == 1) // we are going down
            {
                tags[i][j] = "↓";
            }
            if (dy == -1 ) // we are going up
            {
                tags[i][j] = "↑";
            }
            if (index == NUM_TOKENS -1 ) // last position
            {
                tags[i][j] = "•";
            }
        }
        i += dy;
        j += dx;
    }


}

void display_board(struct token_t* board[(int) sqrt(NUM_TOKENS)][(int) sqrt(NUM_TOKENS)], char* tags[(int) sqrt(NUM_TOKENS)][(int) sqrt(NUM_TOKENS)]) {
    int size = sqrt(NUM_TOKENS);
    int i = 0;
    int j = 0;
    for (j = 0; j < size ; ++j) {
        printf((j != 0 ) ? "┬" : "┌");
        for (int i = 0; i < 14 ; ++i)
        {
            printf("─");
        }
    }
    printf("┐\n");

    

    // Display the board with borders
    for (i = 0; i < size; i++) {
        for (int line = 0; line < 3; line++) {
            printf("│");
            for (j = 0; j < size; j++) {

                if (line == 1)
                {
                    if( board[i][j] != NULL) {
                        printf("    ");
                        token_short_diplay(*board[i][j]);
                        printf("    │");
                    }
                    else {
                        printf("              │");
                    }
                }
                else if(line == 0)
                {

                    printf("           %s %s%s │" ,RED, tags[i][j], CRESET);
                }
                else {
                    printf("              │");
                }
            }
            printf("\n");
        }

        // Display borders between rows
        for (j = 0; j < size ; ++j) {
            printf((i != size-1) ? ((j != 0) ? "┼" : "├") : ((j != 0) ? "┴" : "└"));
            for (int i = 0; i < 14 ; ++i)
            {
                printf("─");
            }
        }
        printf((i != size -1 ) ? "┤\n" : "┘\n");
    }
}

