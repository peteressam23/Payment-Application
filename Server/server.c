#include "server.h"

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