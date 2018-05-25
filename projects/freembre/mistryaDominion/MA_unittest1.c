/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 *unittest1: unittest1.c dominion.o rngs.o
 *	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 *
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define MAX_CARDS  28

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
    int i;
	int result;
	int cardNumber[MAX_CARDS] = {curse, estate, duchy, province, copper, silver, gold, 
	                      adventurer, council_room, feast, gardens, mine, remodel,
						  smithy, village, baron, great_hall, minion, steward, tribute,
 						  ambassador, cutpurse, embargo, outpost, salvager, sea_hag,
						  treasure_map, 127};
	int expectedValue[MAX_CARDS] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3,
	                         5, 3, 4, 2, 5, 4, 4, 4, -1};
							 
	// Print statement that we are teasting getCost function.
	printf("---- UnitTest#1 : TESTING getCost() function: -----\n");
    
	/* Test:1 Loop through each Max_CARDS, print cardnumber and store expected value of the card
	   in result variable.*/
	for(i=0; i < MAX_CARDS; i++){
	    printf("Calling getCost() for cardNumber %d...\n", i);
	    result = getCost(cardNumber[i]);
        
        printf("result = %d, expected = %d\n", result, expectedValue[i]);
	    CUSTOM_ASSERT(result == expectedValue[i]);
        printf("\n");
	}
	
	// Print satement when test is done.
	printf("---------------- End of the tests! ----------------\n\n");
	
	return 0;
}
