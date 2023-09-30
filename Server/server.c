#include "server.h"

/***************************************Function Implementations ****************************************************/

EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    /*Please Write Comments 80% overall*/
}

/**********************************************************************************************************************/

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{
    /*Please Write Comments 80% overall*/
}

/**********************************************************************************************************************/

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
    /*Make Variable To return the errorState*/
    EN_serverError_t errorStateBlockAccount;

    /*Check on The State Of Account*/
    if (accountRefrence->state == "RUNNING")
    {
        errorStateBlockAccount = SERVER_OK;
    }
    else
    {
        errorStateBlockAccount = BLOCKED_ACCOUNT;
    }
    return errorStateBlockAccount;
}
/**********************************************************************************************************************/


EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence)
{
    /*Make Variable To return the errorState*/
    EN_serverError_t errorStateAmountAvilavle;

    /*Check on The Balance Of Account*/
    if (termData->transAmount > accountRefrence->balance)
    {
        errorStateAmountAvilavle = LOW_BALANCE;
    }
    else
    {
        errorStateAmountAvilavle = SERVER_OK;
    }
    return errorStateAmountAvilavle;
}
/**********************************************************************************************************************/


EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    uint8_t iterate = 0;
    EN_serverError_t errorStateSaveTrans;

    for (iterate = 0; iterate < 255; iterate++)
    {
        if (transactionDB_t[iterate].transactionSequenceNumber == 0)
        {
            transactionDB_t[iterate].cardHolderData = transData->cardHolderData;
            transactionDB_t[iterate].terminalData = transData->terminalData;
            listSavedTransactions();
            errorStateSaveTrans = SERVER_OK;
        }
        else
        {
            errorStateSaveTrans = SAVING_FAILED;
        }
    }
    return errorStateSaveTrans;
}

/**********************************************************************************************************************/



void listSavedTransactions(void)
{
    /*Please Write Comments 80% overall*/
}

/**********************************************************************************************************************/

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