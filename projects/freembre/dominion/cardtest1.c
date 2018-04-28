/*
 * cardtest1.c
 *
 * testing the smithy card
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
#include <stdbool.h>

#define TESTCARD "smithy"

int main() {
    int newCards = 0;
    int discarded = 1;


    int i;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int otherPlayer =1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    bool tst = true;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: player recieve 3 cards --------------
	printf("TEST 1: player recieves 3 cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);


	newCards = 3;

	printf("Hand count = %d, expected = %d  ", testG.handCount[thisPlayer] - discarded, G.handCount[thisPlayer] + newCards - discarded);
    
     if(testG.handCount[thisPlayer]- discarded == G.handCount[thisPlayer] + newCards - discarded)
         printf("Pass\n\n");
     else {
         printf("Fail\n\n");
         tst = false;
     }
         
    
    
    // ----------- TEST 2: players deck  count decreases by 3 --------------

    printf("TEST 2: player draws 3 cards from own deck \n");
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    choice1 = 1;
    cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
    
    printf("deck count = %d, expected = %d ", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] -3 );
    
    if(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] -3 )
        printf("Pass\n\n");
    else {
        printf("Fail\n\n");
        tst = false;
    }
    
    
    
   
    // ----------- TEST 3: no change in other players state --------------
    
    printf("TEST 3: player 2 state does not change\n");
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    choice1 = 1;
    cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
    
    printf("Player 2's card count= %d, expected %d ", testG.deckCount[otherPlayer]+ testG.handCount[otherPlayer] + testG.discardCount[otherPlayer], G.deckCount[otherPlayer]+ G.handCount[otherPlayer] + G.discardCount[otherPlayer]);
    if((testG.deckCount[otherPlayer]+ testG.handCount[otherPlayer] + testG.discardCount[otherPlayer]) == (G.deckCount[otherPlayer]+ G.handCount[otherPlayer] + G.discardCount[otherPlayer]))
        printf("Pass\n\n");
    else {
        printf("Fail\n\n");
        tst = false;
    }
    
    // ----------- TEST 4: no change in victory or Kingdom cards --------------
    
    printf("TEST 4: game has same number of victory and Kingdom cards\n");
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    choice1 = 1;
    cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
    
    printf("Victory card count = %d, expected %d ", testG.supplyCount[estate] + testG.supplyCount[duchy] + testG.supplyCount[province], G.supplyCount[estate] + G.supplyCount[duchy] + G.supplyCount[province]);
    
    if((testG.supplyCount[estate] + testG.supplyCount[duchy] + testG.supplyCount[province]) == (G.supplyCount[estate] + G.supplyCount[duchy] + G.supplyCount[province]))
        printf("Pass\n");
    else {
        printf("Fail\n\n");
        tst = false;
    }
    
    for(i = 0; i < 10 ; i++) {
        
        printf("Supply of Kingdom card type %d = %d, expected %d  ", k[i], testG.supplyCount[i], G.supplyCount[i]);
        if( testG.supplyCount[i] == G.supplyCount[i])
            printf("Pass\n");
        else {
            printf("Fail\n\n");
            tst = false;
        }
    }
    

    if (tst == true)
        printf("\n >>>>>Testing complete %s, TEST PASSED <<<<<\n\n", TESTCARD);
    else
        printf("\n >>>>>Testing complete %s, TEST FAILED <<<<<\n\n", TESTCARD);
    


	return 0;
}


