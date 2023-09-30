#include "server.h"
/***************************************Global Arrays***********************************************************/

//Create a global array of ST_accountsDB_t for the valid accounts database.
//Fill in the array initially with any valid data.
ST_accountsDB_t accountsDB[255] = {

     {2000.0  , RUNNING , "1020304050607080"} ,
     {5000.0  , BLOCKED , "2030405060708010"} ,
     {10000.0 , BLOCKED , "3040506070801020"} ,
     {15500.0 , RUNNING , "4050607080102030"} ,
     {100000.0, RUNNING , "5060708010203040"} ,
     {8900.0  , BLOCKED , "6070801020304050"} ,
     {6850.0  , RUNNING , "7080102030405060"} ,
     {1000.0  , RUNNING , "8010203040506070"}
};

//Create a global array of ST_transaction_t for the valid transactions database.
//Fill in the array of transactionDB_t initially with Zeros
ST_transaction_t transactionDB_t[255] = { 0 };


/***************************************Function Implementations ****************************************************/

EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    /*Please Write Comments 80% overall*/
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{
    /*Please Write Comments 80% overall*/
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
    /*Please Write Comments 80% overall*/
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence)
{
    /*Please Write Comments 80% overall*/
}

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    /*Please Write Comments 80% overall*/
}

void listSavedTransactions(void)
{
    /*Please Write Comments 80% overall*/
}



//Test Functions for terminal
void recieveTransactionDataTest(void)
{
    /*Please Write Comments 80% overall*/

}

void isValidAccountTest(void)
{

    /*Please Write Comments 80% overall*/
}

void isBlockedAccountTest(void)
{
    /*Please Write Comments 80% overall*/
}

void isAmountAvailableTest(void)
{
    /*Please Write Comments 80% overall*/

}

void saveTransactionTest(void)
{
    /*Please Write Comments 80% overall*/

}

void listSavedTransactionsTest(void)
{

    /*Please Write Comments 80% overall*/
}