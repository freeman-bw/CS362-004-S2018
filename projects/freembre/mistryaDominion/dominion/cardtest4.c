/*
 * cardtest4.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "sea_hag"

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
    int numPlayers = 4;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: --------------
	printf("TEST 1: Each of the other players except first player ends up with 'curse' top card\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = 0;
	choice2 = 0;
	choice3 = 0;
	handPos = 0;
	cardEffect(sea_hag, choice1, choice2, choice3, &testG, handPos, &bonus);

        // Check if top card is curse card
	for(thisPlayer = 0; thisPlayer < numPlayers; thisPlayer++) {
		if(thisPlayer > 0) {
			printf("Player%d: top deck card = %d, expected = %d\n", thisPlayer, testG.deck[thisPlayer][testG.deckCount[thisPlayer] + 1], curse);
			CUSTOM_ASSERT(testG.deck[thisPlayer][testG.deckCount[thisPlayer] + 1] == curse);
		}
        printf("\n");
	}

	printf("------------ Completed Testing Card: %s ------------\n\n", TESTCARD);

	return 0;
}


