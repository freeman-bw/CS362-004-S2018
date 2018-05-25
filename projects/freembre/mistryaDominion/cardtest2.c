/*
 * cardtest2.c
 *
 * testing the adventurer card
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <stdbool.h>

#define TESTCARD "adventurer"

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
    
    int cardDrawn;
    int treasureCount;
    int staticCount= 0;
     bool tst = true;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: verify that hand increases by 2 treasure cards --------------
    
    //top two cards should be treasure, we will check that
	printf("TEST 1: player recieves 2 additional treasure cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
    
    
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    
    for(i = 0; i < testG.handCount[thisPlayer]; i ++) {
        
        cardDrawn = testG.hand[thisPlayer][i];
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) {
            treasureCount++;
        }


    }
    
    
    for(i = 0; i < G.handCount[thisPlayer]; i ++) {

        cardDrawn = G.hand[thisPlayer][i];
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) {
            staticCount++;
        }

    }
    
    printf("Tresure card count = %d, expected %d ", treasureCount, staticCount +2);
    
    if(treasureCount == staticCount + 2)
        printf("Pass\n\n");
    else {
        printf("Fail\n\n");
        tst = false;
    }
    
    
    
    // ----------- TEST 2: players deck increases by 2 cards total --------------

    printf("TEST 2: players hand count increases by 2 \n");
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    choice1 = 1;
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
    
 printf("Total card count = %d, expected %d ", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 2);
    
    if(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 2)
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
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
    
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
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
    
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


