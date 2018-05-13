/*
 * randomtestadventurer.c
 *
 * testing the adventurer card
 */

/*
 * Include the following lines in your makefile:
 *
 * randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *    gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TESTCARD "random_adventurer"

int main() {

    int i, d;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

    //int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int otherPlayer =1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    
    int cardDrawn;
    int treasureCount=0;
    int staticCount= 0;
     bool tst = true;
    int numFail = 0;
    int numPass = 0;

	// initialize a game state and player cards
	//initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: verify that hand increases by 2 treasure cards --------------
    
    //top two cards should be treasure, we will check that
	printf("TEST 1: player recieves 2 additional treasure cards\n");

    for(d = 0; d < 10000; d++) {

        treasureCount=0;
        staticCount= 0;
        
        //printf("Rndm #%d\n", d);
        initializeGame(numPlayers, k, rand(), &G);
        // copy the game state to a test case
        //memcpy(&testG, &G, sizeof(struct gameState));
        choice1 = 1;
        //random deck count
        G.deckCount[thisPlayer] = rand() % (MAX_DECK + 1 - 0) + 0;
        G.handCount[thisPlayer] = rand() % (MAX_HAND + 1 - 0) + 0;
        
        memcpy(&testG, &G, sizeof(struct gameState));
        
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
        
        //printf("Tresure card count = %d, expected %d ", treasureCount, staticCount +2);
        
        if(treasureCount == staticCount + 2)
        numPass++;
        else {
            numFail++;
            tst = false;
        }
    }
    printf("Number times passed is %d, number times failed is: %d\n\n", numPass, numFail);
    
    
    //reset counters
    numPass =0;
    numFail=0;
    
    // ----------- TEST 2: players deck increases by 2 cards total --------------

    printf("TEST 2: players hand count increases by 2 \n");
    
    
    for(d = 0; d < 10000; d++) {
        
        //printf("Rndm #%d\n", d);
        initializeGame(numPlayers, k, rand(), &G);
        // copy the game state to a test case
        //
        choice1 = 1;
        //random deck count
        G.deckCount[thisPlayer] = rand() % (MAX_DECK + 1 - 0) + 0;
        G.handCount[thisPlayer] = rand() % (MAX_HAND + 1 - 0) + 0;
        
        G.discardCount[thisPlayer] = rand() % (MAX_HAND + 1 - 0) + 0;
        G.playedCardCount = rand() % (MAX_HAND + 1 - 0) + 0;
        memcpy(&testG, &G, sizeof(struct gameState));
        
        cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
        
        //printf("Total card count = %d, expected %d ", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 2);
        
        if(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 2)
        numPass++;
        else {
            numFail++;
            tst = false;
        }
        
    }
    printf("Number times hand count test passed is %d, number times failed is: %d\n\n", numPass, numFail);
    
    
    //reset counters
    numPass =0;
    numFail=0;
   
    // ----------- TEST 3: no change in other players state --------------
    
    printf("TEST 3: player 2 state does not change\n");
    
    for(d = 0; d < 10000; d++) {

        //printf("Rndm #%d\n", d);
        initializeGame(numPlayers, k, rand(), &G);
        // copy the game state to a test case
        //
        choice1 = 1;
        //random deck count
        G.deckCount[thisPlayer] = rand() % (MAX_DECK + 1 - 0) + 0;
        G.handCount[thisPlayer] = rand() % (MAX_HAND + 1 - 0) + 0;
        
        G.discardCount[thisPlayer] = rand() % (MAX_HAND + 1 - 0) + 0;
        G.playedCardCount = rand() % (MAX_HAND + 1 - 0) + 0;
        memcpy(&testG, &G, sizeof(struct gameState));
  
        cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
        
        //printf("Player 2's card count= %d, expected %d ", testG.deckCount[otherPlayer]+ testG.handCount[otherPlayer] + testG.discardCount[otherPlayer], G.deckCount[otherPlayer]+ G.handCount[otherPlayer] + G.discardCount[otherPlayer]);
        if((testG.deckCount[otherPlayer]+ testG.handCount[otherPlayer] + testG.discardCount[otherPlayer]) == (G.deckCount[otherPlayer]+ G.handCount[otherPlayer] + G.discardCount[otherPlayer]))
        numPass++;
        else {
            numFail++;
            tst = false;
        }
    }
    printf("Number times State Change test passed is %d, number times failed is: %d\n\n", numPass, numFail);
    
    
    //reset counters
    numPass =0;
    numFail=0;
    
    int p2 =0;
    int f2 = 0;
    
    // ----------- TEST 4: no change in victory or Kingdom cards --------------
    
    printf("TEST 4: game has same number of victory and Kingdom cards\n");
    
    for(d = 0; d < 10000; d++) {
        
        initializeGame(numPlayers, k, rand(), &G);
        // copy the game state to a test case
        //memcpy(&testG, &G, sizeof(struct gameState));
        choice1 = 1;
        //random deck count
        G.deckCount[thisPlayer] = rand() % (MAX_DECK + 1 - 0) + 0;
        G.handCount[thisPlayer] = rand() % (MAX_HAND + 1 - 0) + 0;
        
        G.discardCount[thisPlayer] = rand() % (MAX_HAND + 1 - 0) + 0;
        G.playedCardCount = rand() % (MAX_HAND + 1 - 0) + 0;
        
        memcpy(&testG, &G, sizeof(struct gameState));
        cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
        
        //printf("Victory card count = %d, expected %d ", testG.supplyCount[estate] + testG.supplyCount[duchy] + testG.supplyCount[province], G.supplyCount[estate] + G.supplyCount[duchy] + G.supplyCount[province]);
        
        if((testG.supplyCount[estate] + testG.supplyCount[duchy] + testG.supplyCount[province]) == (G.supplyCount[estate] + G.supplyCount[duchy] + G.supplyCount[province]))
        numPass++;
        else {
            numFail++;
            tst = false;
        }
        
        //iterate through all kngsom cards and count them
        for(i = 0; i < 10 ; i++) {
            //printf("Supply of Kingdom card type %d = %d, expected %d  ", k[i], testG.supplyCount[i], G.supplyCount[i]);
            if( testG.supplyCount[i] == G.supplyCount[i])
            p2++;
            else {
                f2++;
                tst = false;
            }
        }
    }
    
printf("Victory Card test, times passed is %d, number times failed is: %d\n", numPass, numFail);
printf("Kingdom Card test, times passed is %d, number times failed is: %d\n\n", p2, f2);
    
    
    if (tst == true)
        printf("\n >>>>>Testing complete %s, TEST PASSED <<<<<\n\n", TESTCARD);
    else
        printf("\n >>>>>Testing complete %s, TEST FAILED <<<<<\n\n", TESTCARD);

	return 0;
}


