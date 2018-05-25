/*
 * randomtestadventurer.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *      gcc -o randomtestadventurer.out -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "adventurer"

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
	int testnumber = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	srand(time(NULL));

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	for(testnumber = 1; testnumber <=100; testnumber++) { 
		// Force a deck shuffle and gain +2 treasure cards into your hand --------------
		// Un-cover a bug where shuffle returning if the deckcount is less than 1
		printf("\nTEST Number %d:\n", testnumber);
		choice1 = 0;
		choice2 = 0;
		choice3 = 0;
		handPos = 0;
		testG.discardCount[thisPlayer] = testG.deckCount[thisPlayer];
		testG.deckCount[thisPlayer] = ( rand() % 2);
		printf("Random deckCount: %d\n", testG.deckCount[thisPlayer]);
		cardEffect(adventurer, choice1, choice2, choice3, &testG, handPos, &bonus);

		newCards = 2;
		printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards);
		CUSTOM_ASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards);

	}
	printf("------------ Completed Testing Card: %s ------------\n\n", TESTCARD);

	return 0;
}


