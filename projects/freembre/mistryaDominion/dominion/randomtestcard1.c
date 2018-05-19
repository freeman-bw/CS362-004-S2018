/*
 * randomtestcard1.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * randomtestcard1: randomtestcard1.c dominion.o rngs.o
 *         gcc -o randomtestcard1.out -g randomtestcard1.c dominion.o rngs.o $(CFLAGS) 
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "minion"

// custom assert function
#define CUSTOM_ASSERT(condition) \
{\
    if(!(condition)) \
    {\
        printf(">>>>> STATUS:  TEST FAILED <<<<<\n");\
    } else {\
        printf(">>>>> STATUS:  TEST PASSED <<<<<\n");\
    }\
}\

int main() {
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int player = 0;
	struct gameState G, testG;
	int testnumber = 1;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int r;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	srand(time(NULL));

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	for(testnumber = 1; testnumber <=100; testnumber++){
		printf("\nTEST Number %d:\n", testnumber);

		// ----------- TEST 1: --------------
		// Choice1 - Gain +2 coins into your hand.
		// Choice2 - current player gains +4 cards.
		// Other players gains +4 cards if they have at least 5 cards in hand 

		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));

        	// generate random number between 1 & 2
	        r = (rand() % 2) + 1;
	        printf("Random choice: %d\n", r);

	        choice1 = 0;
		choice2 = 0;
		choice3 = 0;
		handPos = 0;

		// select choice based upon random selection
		if(r == 1) {
			choice1 = 1;
		} else if (r == 2) {
			choice2 = 1;

			// generate handcount between 1 & 5
			r = (rand() % 5) + 1;
			printf("Random handcount: %d\n", r); 
			for(player = 1; player < numPlayers; player++) {
				testG.handCount[player] += r;
				G.handCount[player] += r; 

				testG.deckCount[player] -= r;
				G.deckCount[player] -= r;
			}
		}
		cardEffect(minion, choice1, choice2, choice3, &testG, handPos, &bonus);

	        if(choice1) {
			printf("coin count = %d, expected = %d\n", testG.coins, G.coins + 2);
			  CUSTOM_ASSERT(testG.coins == G.coins + 2);
	        } else if (choice2) {
        		for(player = 0; player < numPlayers; player++) {
		                // current player always draws 4 hand cards
		                if(player == 0) {
                		printf("Player%d hand count = %d, expected = %d\n", player, testG.handCount[player], 4);
		                CUSTOM_ASSERT(testG.handCount[player] == 4);
	                	} else {
        		        	// all other player draw 4 hand cards only if their hand count is greater than 4
		            		if(G.handCount[player] > 4) {
	        	                	printf("Player%d hand count = %d, expected = %d\n", player, testG.handCount[player], 4);
        	        	       		CUSTOM_ASSERT(testG.handCount[player] == 4);
			                } else {
	                		        printf("Player%d hand count = %d, expected = %d\n", player, testG.handCount[player], G.handCount[player]);
                	        		CUSTOM_ASSERT(testG.handCount[player] == G.handCount[player]);
                    			}
                		}
			}
		}
	}
	printf("------------ Completed Testing Card: %s ------------\n\n", TESTCARD);

	return 0;
}
