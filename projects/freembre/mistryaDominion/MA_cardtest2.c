*
 * cardtest2.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

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
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: --------------
	// Gain +3 cards into your hand.
	printf("TEST 1: Gain +3 cards with initial deck\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = 0;
	choice2 = 0;
	choice3 = 0;
	handPos = 0;
	cardEffect(smithy, choice1, choice2, choice3, &testG, handPos, &bonus);

	newCards = 3;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards);
	CUSTOM_ASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 3);
	CUSTOM_ASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 3);

	printf("------------ Completed Testing Card: %s ------------\n\n", TESTCARD);

	return 0;
}


