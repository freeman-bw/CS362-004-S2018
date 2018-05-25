/*
 * unit test1.c
 * tests the gainCard function in dominion.c
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

    int p = 1;

    int discardCount = 0;
    int deckCount = 0;
    int handCount = 0;
    
    int bonus = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    struct gameState G;


    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
   initializeGame(numPlayer, k, seed, &G); // initialize a new game
    
    G.discardCount[p] =discardCount;
    G.deckCount[p] = deckCount;
    G.handCount[p] = handCount;                 // set the number of cards on hand
    

    
    #if (NOISY_TEST == 1)
    printf ("****TESTING gainCard*****\n");
    #endif
    gainCard(adventurer, &G, 0, p); //test that supply count is decreased *
    #if (NOISY_TEST == 1)
    printf("Supply count = %d, expected 9 \n", G.supplyCount[adventurer]);
    #endif
    assert(G.supplyCount[adventurer] == 9);
    
    gainCard(adventurer, &G, 0, p); // tests that discardcount  increased *
    #if (NOISY_TEST == 1)
    printf("Discard count = %d, expected 2 \n", G.discardCount[p]);
    #endif
    assert(G.discardCount[p] == 2);
    
    gainCard(adventurer, &G, 1, p); // tests that deckCount increased *
    #if (NOISY_TEST == 1)
    printf("Deck count = %d, expected 1 \n", G.deckCount[p]);
    #endif
    assert( G.deckCount[p] == 1);
    
    gainCard(adventurer, &G, 2, p); // tests that handcount increaseed *
    #if (NOISY_TEST == 1)
    printf("Hand count = %d, expected 1 \n", G.handCount[p]);
    #endif
    assert( G.handCount[p] == 1);
       

    printf("______gainCard test complete______\n");
    
    return 0;
}
