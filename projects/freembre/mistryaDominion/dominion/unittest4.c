/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 *unittest4: unittest4.c dominion.o rngs.o
 *	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 *
 * -----------------------------------------------------------------------
 */
/* 
Business requirements for SupplyCount.
- This function must take two perameters.
- The function must return the value of MAX_CARDS as a result of supplyCount.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

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
	int supplyPos;
	int result;
	int expectedValue;
	//int numPlayers;
	
	//Initialize variables.
	supplyPos = 0;
	state.numBuys = 0;
	expectedValue = 0;

    // Print statement that we are testing buyCard function.
	printf("--------------- TESTING buyCard(): ----------------\n");

   // Test:1 state.numBuys = 0
   supplyPos = 0;
   state.numBuys = 0;
   expectedValue = -1;
   result = buyCard(supplyPos, &state);
   if (result == expectedValue){
	    printf("    The result %d matches expectedValue.\n\n", result);
   }else{
	    printf("    The result %d DOES NOT match expectedValue.\n\n", result);   
   }
    CUSTOM_ASSERT(result == expectedValue);
    printf("\n");

   // Test:2 state.numBuys = 1, supplyCount[card] = 0 - pick card that rerturn 0 
   state.numBuys = 1;
   supplyPos = copper;
   state.supplyCount[copper] = 0;
   expectedValue = -1;
   result = buyCard(supplyPos, &state);
   if (result == expectedValue){
	    printf("    The result %d matches expectedValue.\n", result);
   }else{
	    printf("    The result %d DOES NOT match expectedValue.\n", result);   
   }
    CUSTOM_ASSERT(result == expectedValue);
    printf("\n");
   
   // Test:3 state.numBuys = 1, supplyCount[card] = 1, state.coins = 3, supplyPos = gold
   state.numBuys = 1;
   state.supplyCount[gold] = 1;
   state.coins = 4;
   supplyPos = gold;
   expectedValue = -1;
   result = buyCard(supplyPos, &state);
   if (result == expectedValue){
	    printf("    The result %d matches expectedValue.\n", result);
   }else{
	    printf("    The result %d DOES NOT match expectedValue.\n", result);   
   }
    CUSTOM_ASSERT(result == expectedValue);
    printf("\n");
   
   // Test:4 state.numBuys = 1, supplyCount[card] = 1, state.coins = 8,supplyPos = gold
     state.numBuys = 1;
   state.supplyCount[gold] = 1;
   state.coins = 8;
   supplyPos = gold;
   expectedValue = 0;
   result = buyCard(supplyPos, &state);
   if (result == expectedValue){
	    printf("    The result %d matches expectedValue.\n", result);
   }else{
	    printf("    The result %d DOES NOT match expectedValue. Test fails!\n", result);    
   }
    CUSTOM_ASSERT(result == expectedValue);
    printf("\n");
   
    // Print satement when test is done.
	printf("---------------- End of the tests! ----------------\n\n");
	
	return 0;
}
