/*
 * cardtest3.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "council_room"

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
    int numPlayers = 4;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: --------------
	printf("TEST 1: Player 1 Gain +4 cards, other Players Gain +1 card\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	choice1 = 0;
	choice2 = 0;
	choice3 = 0;
	handPos = 0;
	cardEffect(council_room, choice1, choice2, choice3, &testG, handPos, &bonus);

	// technically first player will gain +4 cards but we will have to discard played card so that's why final gain is 3 total
	newCards = 4;
	for(thisPlayer = 0; thisPlayer < numPlayers; thisPlayer++) {

		// the rest of the player only gain 1 new card
		if(thisPlayer > 0){
			newCards = 1;
		} 

		printf("Player%d: hand count = %d, expected = %d\n", thisPlayer, testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards);
		CUSTOM_ASSERT(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards);

		if(thisPlayer == 0) {
			// first player looses 4 cards from the deck count.  1 played and 3 gained
			printf("Player%d: deck count = %d, expected = %d\n", thisPlayer, testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 4);
			CUSTOM_ASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 4);

		} else {
			// rest of player looses only 1 card from the deck count.
			printf("Player%d: deck count = %d, expected = %d\n", thisPlayer, testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 1);
			CUSTOM_ASSERT(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 1);
		}
        printf("\n");
	}

	printf("------------ Completed Testing Card: %s ------------\n\n", TESTCARD);

	return 0;
}


