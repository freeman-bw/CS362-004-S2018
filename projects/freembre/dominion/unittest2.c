/*
 * unit test2.c
 * tests the discardCard function in dominion.c
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
    int i;
    int j = 1;
    
    int discardCount = 0;
    int deckCount = 0;
    int handCount = 5;

    int k[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;


    
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
 initializeGame(numPlayer, k, seed, &G); // initialize a new game
    
    
    G.discardCount[p] =discardCount;
    G.deckCount[p] = deckCount;
    G.handCount[p] = handCount;                 // set the number of cards on hand
    G.playedCardCount = 0;
    //updateCoins(p, &G, bonus);
    //set player )s hand to have 5 different cards
     G.hand[0][0] =5;
     G.hand[0][1] =4;
     G.hand[0][2] =3;
     G.hand[0][3] =2;
     G.hand[0][4] =1;
    memcpy(&testG, &G, sizeof(struct gameState));
    
#if (NOISY_TEST == 1)
    printf ("****TESTING discardCard*****\n");
#endif
    printf("Played card count is trashed\n ");
    for (i = 0; i < G.handCount[p]; i++) {
        //printf("card %d is %d \n", i, G.hand[0][i]);
         discardCard(i, 0, &testG, 0);
        j += i;
        printf("Played card count is %d, expecting %d ", testG.playedCardCount, G.playedCardCount+1 + i);
        if(testG.playedCardCount == G.playedCardCount + 1 + i)
            printf("Pass\n");
        else
            printf("Fail\n");

    }
    
    
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("\nPlayed card count is NOT trashed\n");
    for (i = 0; i < G.handCount[p]; i++) {
        //printf("card %d is %d \n", i, G.hand[0][i]);
        discardCard(i, 0, &testG, 1);
        j += i;
        printf("Played card count is %d, expecting %d ", testG.playedCardCount, G.playedCardCount);
        if(testG.playedCardCount == G.playedCardCount )
            printf("Pass\n");
        else
            printf("Fail\n");
        
    }

    
    memcpy(&testG, &G, sizeof(struct gameState));
    printf("\nPlayer card count is reduced\n");
    for (i = 0; i < G.handCount[p]; i++) {
        //printf("card %d is %d \n", i, G.hand[0][i]);
        discardCard(i, 0, &testG, 1);
        j += i;
        printf("Current card count is %d, expecting %d ", testG.handCount[0], G.handCount[0]-i-1);
        if(testG.handCount[0] == G.handCount[0]-i -1)
            printf("Pass\n");
        else
            printf("Fail\n");
        
    }
   

    printf("______discardCard test complete______\n");
    
    return 0;
}

