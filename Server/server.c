#include "server.h"

/***************************************Function Implementations ****************************************************/

EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    EN_serverError_t errorStateRecieveTrans = SERVER_OK ;
    ST_accountsDB_t referenceInDB = {0}; // To store the accout info from the database.
    uint8_t iterate = 0 ;

    if(isValidAccount(&transData->cardHolderData , &referenceInDB) == 3 )
    {
        errorStateRecieveTrans = FRAUD_CARD;
    }
    else if(isAmountAvailable (transData->terminalData , &referenceInDB) == 4 )
    {
        errorStateRecieveTrans = DECLINED_INSUFFECIENT_FUND ;
    }
    else if (isBlockedAccount(&referenceInDB) == 5 )
    {
        errorStateRecieveTrans = DECLINED_STOLEN_CARD;
    }
    else if (saveTransaction(transData) == 1) //saveTransaction(transData) == SAVING_FAILED.
    {
        errorStateRecieveTrans = INTERNAL_SERVER_ERROR ;
    }
    else 
    {
    //update the transactio status ( APPROVED ) & errorStateRecieveTrans will be APPROVED.
    transData->transState = APPROVED ;
    errorStateRecieveTrans = APPROVED ;
    }

    //update the database with the new balance.
    for(iterate ; iterate < 255 ; iterate++)
    {
        //search by PAN in accountsDB in the database of the server.
        if(strcmp( accountsDB[i].primaryAccountNumber , referenceInDB.primaryAccountNumber ) == 0)
        {
            accountsDB[i].balance -= transData->terminalData.transAmount;
            break;
        }
    }



    //Return the errorstate at the end of the function.
    return errorStateRecieveTrans;
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