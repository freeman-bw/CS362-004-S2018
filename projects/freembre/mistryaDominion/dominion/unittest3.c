/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 *unittest3: unittest3.c dominion.o rngs.o
 *	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 *
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

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
	int result;
	int expectedValue;
	int i;
	

   // Print statement that we are testing isGameOver function.
    printf("------- UnitTest#3: TESTING isGameOver(): ---------\n");
	
   // Initilize province card.
   state.supplyCount[province] = 0;
   
   // Perform functin isGameOver to check if stack of province card is empty.
   // Store result in result variable.
    result = isGameOver(&state);
	printf("    The result is %d.. \n", result);
	expectedValue = 1;
	
	// Compare expectedValue and result, if both matches then print message.
    if (result == expectedValue){
		printf("    Expected value %d returned.\n", result);
		printf("    The pile of supplycount of province card is empty!\n");
		printf("    The game is over!\n");
	   }
	CUSTOM_ASSERT(result == expectedValue);
    printf("\n");
    
	// Perform functin isGameOver to check if three supply pile is empty.
    for(i = 0; i < 25; i++){
	 // Initilize supplyCount.
    state.supplyCount[province] = 1;
	}
	result = isGameOver(&state);
	printf("    The result is %d.. \n", result);
	expectedValue = 1;
	
	// Compare expectedValue and result, if both matches then print message.
    if (result == expectedValue){
		printf("    Expected value %d returned.\n", result);
		printf("    Three supply piles are empty!\n");
		printf("    The game is over!\n");
	   }
    CUSTOM_ASSERT(result == expectedValue);
    printf("\n");
    
	//  Perform functin isGameOver to check if three supply pile is empty with changed value of
	// supplyCount.
    for(i = 0; i < 25; i++){
	state.supplyCount[i] = 1;      	// Initilize supplyCount.
	}
	
	result = isGameOver(&state);
	printf("    The  The result is %d.. \n", result);
	expectedValue = 0;
	
	// Compare expectedValue and result, if both matches then print message.
    if (result == expectedValue){
		printf("    Expected value %d returned.\n", result);
		printf("    Three supply piles are NOT empty!\n");
		printf("    The game is NOT over!\n");
	   }
	CUSTOM_ASSERT(result == expectedValue);
    
	// Print satement when test is done.
	printf("---------------- End of the tests! ----------------\n\n");
	
	return 0;
}
