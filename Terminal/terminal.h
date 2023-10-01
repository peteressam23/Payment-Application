#ifndef TERMINAL_H
#define TERMINAL_H

#include <time.h>
#include "../Card/card.h"


//Global array to save and print user input when do test 
uint8_t inputFromUser[40];

typedef struct ST_terminalData_t
{
     float transAmount;
     float maxTransAmount;
     uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
     TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t ;

//Use the following prototypes as is:
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount);
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData); // Optional


//Test Functions for terminal
void getTransactionDateTest(void);
void isCardExpriedTest(void);
void getTransactionAmountTest(void);
void isBelowMaxAmountTest(void);
void setMaxAmountTest(void);
void isValidCardPANTest(void);

#endif /*TERMINAL_H*/ 