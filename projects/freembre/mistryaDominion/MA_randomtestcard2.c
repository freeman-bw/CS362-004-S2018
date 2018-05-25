/*
 * randomtestcard2.c
 *
 */

/*
 * Include the following lines in your makefile:
 *
 * randomtestcard2: randomtestcard2.c dominion.o rngs.o
 *      gcc -o randomtestcard2.out -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "smithy"

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
	int newCards = 0;
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
        int r;
	int testnumber = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

        srand(time(NULL));

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

        for(testnumber = 1; testnumber <=100; testnumber++){
                printf("\nTEST Number %d:\n", testnumber);

		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));

		choice1 = 0;
		choice2 = 0;
		choice3 = 0;
		handPos = 0;

	        //  generate handcount between 0 to 4
	        srand(time(NULL));  
	        r = (rand() % 5);
	        testG.deckCount[thisPlayer] = r;
	        printf("Random deckcount: %d\n", r);
		cardEffect(smithy, choice1, choice2, choice3, &testG, handPos, &bonus);

		newCards = 3;
		printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards);
		CUSTOM_ASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards);
		printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 3);
		CUSTOM_ASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 3);
	}
	printf("------------ Completed Testing Card: %s ------------\n\n", TESTCARD);

	return 0;
}


