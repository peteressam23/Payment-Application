#ifndef CARD_H
#define CARD_H

#include<stdio.h>
#include<string.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>


//Global array to save and print user input when do test 
uint8_t inputFromUser[40];


typedef struct ST_cardData_t
{
     uint8_t cardHolderName[25];
     uint8_t primaryAccountNumber[20];
     uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
     CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

//Use the following prototypes as is:
EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);


//Test Functions for card
void getCardHolderNameTest(void);
void getCardExpiryDateTest(void);
void getCardPANTest(void);


#endif /*CARD_H*/ 