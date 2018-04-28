/*
 * unittest4.c
 * tests the numHandCards function in dominion.c
 *
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

    int i, j;

    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    struct gameState G;


    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
 initializeGame(numPlayer, k, seed, &G); // initialize a new game
    
                // set the number of cards on hand
    
#if (NOISY_TEST == 1)
    printf ("****TESTING numHandCards*****\n");
#endif
    
    for(i = 0; i < 2; i++) {
        
        for(j= 0; j < 10; j++) {
            
            G.whoseTurn = i;
            G.handCount[i] = j;
             #if (NOISY_TEST == 1)
            printf ("player %d has %d cards in hand, expected %d\n", i, numHandCards(&G), j);
            #endif
            assert(numHandCards(&G)==j);
        }
    }
    
#if (NOISY_TEST == 1)

    printf("______numHandCards test complete______\n");
    #endif
    return 0;
}
