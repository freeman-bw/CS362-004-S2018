/*
 * cardtest1.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

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
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: --------------
	// Gain +2 treasure cards into your hand.
	printf("TEST 1: Gain +2 cards with initial deck\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = 0;
	choice2 = 0;
	choice3 = 0;
	handPos = 0;
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handPos, &bonus);

	newCards = 2;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards);
	CUSTOM_ASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards);

	// ----------- TEST 2:  -----------------------
	// Force a deck shuffle and gain +2 treasure cards into your hand --------------
	// Un-cover a bug where shuffle returning if the deckcount is less than 1
	printf("\nTEST 1: Gain +2 cards with forced deck shuffle\n");
	choice1 = 0;
	choice2 = 0;
	choice3 = 0;
	handPos = 0;
    printf("discard = %d, deck = %d\n", testG.discardCount[thisPlayer], testG.deckCount[thisPlayer]);
	testG.discardCount[thisPlayer] = testG.deckCount[thisPlayer];
	testG.deckCount[thisPlayer] = 0;
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handPos, &bonus);

	newCards = 2;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards);
	CUSTOM_ASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards);

	printf("------------ Completed Testing Card: %s ------------\n\n", TESTCARD);

	return 0;
}


