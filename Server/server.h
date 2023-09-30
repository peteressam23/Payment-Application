#ifndef SERVER_H
#define SERVER_H

#include "../Card/card.h"
#include "../Terminal/terminal.h"

typedef enum EN_transState_t
{
     APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef struct ST_transaction_t
{
     ST_cardData_t cardHolderData;
     ST_terminalData_t terminalData;
     EN_transState_t transState;
     uint32_t transactionSequenceNumber;
}ST_transaction_t;

typedef enum EN_serverError_t 
{
     SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t ;

typedef enum EN_accountState_t
{
     RUNNING,
     BLOCKED
}EN_accountState_t;

typedef struct ST_accountsDB_t
{
     float balance;
     EN_accountState_t state;
     uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

//Create a global array of ST_accountsDB_t for the valid accounts database.
ST_accountsDB_t accountsDB[255];

//Create a global array of ST_transaction_t for the valid transactions database.
ST_transaction_t transactionDB_t[255];

//Fill in the array of transactionDB_t initially with Zeros
transactionDB_t[255] = {0};



//Fill in the array initially with any valid data.
accountsDB[255] = {
     {2000.0 , RUNNING , 1020304050607080} , {5000.0 , BLOCKED , 2030405060708010} , {10000.0 , BLOCKED , 3040506070801020} , {15500.0 , RUNNING , 4050607080102030}
     {100000.0 , RUNNING , 5060708010203040} , {8900.0 , BLOCKED , 6070801020304050} , {6850.0 , RUNNING , 7080102030405060} , 
     {1000.0 , RUNNING , 8010203040506070}
};



//Use the following prototypes as is:
EN_transState_t recieveTransactionData(ST_transaction_t *transData);
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence);
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence);
EN_serverError_t saveTransaction(ST_transaction_t *transData);
void listSavedTransactions(void);


//Test Functions for terminal
void recieveTransactionDataTest(void);
void isValidAccountTest(void);
void isBlockedAccountTest(void);
void isAmountAvailableTest(void);
void saveTransactionTest(void);
void listSavedTransactionsTest(void);


#endif /*SERVER_H*/