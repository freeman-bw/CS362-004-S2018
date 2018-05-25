/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 *unittest2: unittest2.c dominion.o rngs.o
 *	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 *
 * -----------------------------------------------------------------------
 */
 

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define MAX_CARDS  10

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
	
	// Declare variables.
    struct gameState state;
	int numPlayers = 2;
	int player;
	int result;
	int expectedValue;
	int i;
   
	// Print statement that we are teasting fullDeckCount function.
	printf("------ UnitTest#2 :TESTING fullDeckCount(): -------\n");

	// Test#1: Initialize the deck of 30 cards with all estate
	for(player = 0; player < numPlayers; player++){
		// initialize total counts
		state.deckCount[player] = MAX_CARDS;
		state.handCount[player] = MAX_CARDS;
		state.discardCount[player] = MAX_CARDS;
		
		// default each category of card to estate
        for(i = 0; i < state.deckCount[player]; i++){
		    state.deck[player][i] = estate;
			state.hand[player][i] = estate;
			state.discard[player][i] = estate;
		}
		
		// perform full deck count
	    result = fullDeckCount(player, estate, &state);
		expectedValue = state.deckCount[player] + state.handCount[player] + state.discardCount[player];
		printf("Perform full %d deck count with all cards as same type...\n", expectedValue);
		if(result == expectedValue){
		    printf("   player%d count %d matches expected count %d\n", 
			       player, expectedValue, result);	
		} else {
		    printf("   player%d count %d does not match expected count %d\n", 
			       player, expectedValue, result);	
		}
        CUSTOM_ASSERT(result == expectedValue);
        printf("\n");
        
		// Test#2: change some of the cards to non-estate
		printf("Perform full %d deck count with 3 cards as different type...\n", expectedValue);
		state.deck[player][0] = copper;
		state.hand[player][0] = copper;
		state.discard[player][0] = copper;
		expectedValue = (state.deckCount[player] + 
		                 state.handCount[player] + 
						 state.discardCount[player]) - 3;

		// perform full deck count
	    result = fullDeckCount(player, estate, &state);
		if(result == expectedValue){
		    printf("    player%d count %d matches expected count %d\n", 
			       player, expectedValue, result);	
		} else {
		    printf("    player%d count %d does not match expected count %d\n", 
			       player, expectedValue, result);	
		}
        CUSTOM_ASSERT(result == expectedValue);
        printf("\n");		
	}	
	
	// Print satement when test is done.
	printf("---------------- End of the tests! ----------------\n\n");
	
	return 0;
}
