/*
 * randomcardtest1.c
 *
 * testing the smithy card
 */

/*
 * Include the following lines in your makefile:
 *
 * randomtestcard1: randomtestcard1.c dominion.o rngs.o
 *     gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <stdbool.h>

#define TESTCARD "random_smithy"

int main() {
    int newCards = 0;
    int discarded = 1;


    int i, d;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

    //int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int otherPlayer =1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    bool tst = true;
    int numFail = 0;
    int numPass = 0;
    

	// initialize a game state and player cards
	//initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    
    
    

	// ----------- TEST 1: player recieve 3 cards --------------
	printf("TEST 1: player recieves 3 cards\n");

    for(d =0; d < 1000; d++) {
        
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
        
        cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
        
        newCards = 3;
        
        //printf("Hand count = %d, expected = %d  ", testG.handCount[thisPlayer] - discarded, G.handCount[thisPlayer] + newCards - discarded);
        
        if(testG.handCount[thisPlayer] - discarded == G.handCount[thisPlayer] + newCards - discarded)
        numPass++;
        else {
            numFail++;
            tst = false;
        }
    }
    printf("Number times Test 1 passed is %d, number times failed is: %d\n\n", numPass, numFail);
    
    //reset counters
    numPass =0;
    numFail=0;
    
    // ----------- TEST 2: players deck  count decreases by 3 --------------

    printf("TEST 2: player draws 3 cards from own deck \n");
    
    for(d =0; d < 1000; d++) {
        
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
        
        cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
        
        //printf("deck count = %d, expected = %d \n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] -3 );
        
        if(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] -3 )
        numPass++;
        else {
            numFail++;
            tst = false;
        }
    }
    
    printf("Number times Test 2 passed is %d, number times failed is: %d\n\n", numPass, numFail);
    
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
        
        cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
        
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
        cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
        
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


