/*
 * unit test3.c
 * tests the getCost function in dominion.c
 * getCost should return the proper cost values associated with each card
 *
 *
 */


#include "dominion.h"

#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {

    int seed = 1000;
    int numPlayer = 2;

    int i;


    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    struct gameState G;


    int costVal[27] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};
    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game

    
#if (NOISY_TEST == 1)
    printf ("\n****TESTING getCost*****\n");
#endif
    int j = 0;
    for( i=curse; i <= treasure_map; i++) {
        #if (NOISY_TEST == 1)
        printf( "GetCost value = %d, expected value = %d\n", getCost(i), costVal[j]);
         #endif
        assert(getCost(i)== costVal[j]);
        j++;
    
    }
    
 
    printf( "GetCost value = %d, expected value = %d\n", getCost(-999), -1);
    assert(getCost(-999) == -1);
    

    printf("______getCost test complete______\n\n");
    
    return 0;
}
