/*
 * cardtest4.c
 *
 * testing the great hall card
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <stdbool.h>

#define TESTCARD "great_hall"

int main() {


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
    
    // ----------- TEST 1: players deck increases by 1 cards total --------------
    // count wont really increase as it decreases by one aafter being played...
    
    printf("TEST 1: players hand count increases by 1 \n");
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    choice1 = 1;
    cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);
    
 printf("Total card count = %d, expected %d ", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
    
    if(testG.handCount[thisPlayer] == G.handCount[thisPlayer] )
        printf("Pass\n\n");
    else {
        printf("Fail\n\n");
        tst = false;
    }
    // ----------- TEST 2: Actions increase by 2 --------------
    
    printf("TEST 2: players actions increase by 2\n");
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    choice1 = 1;
    cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);
    
    printf("Total actions = %d, expected %d ", testG.numActions, G.numActions + 1);
    
    if(testG.numActions == G.numActions + 1)
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
    cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);
    
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
    cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);
    
    printf("Victory card count = %d, expected %d ", testG.supplyCount[estate] + testG.supplyCount[duchy] + testG.supplyCount[province], G.supplyCount[estate] + G.supplyCount[duchy] + G.supplyCount[province]);
    
    if((testG.supplyCount[estate] + testG.supplyCount[duchy] + testG.supplyCount[province]) == (G.supplyCount[estate] + G.supplyCount[duchy] + G.supplyCount[province]))
        printf("Pass\n");
    else
        printf("Fail\n");
    
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


