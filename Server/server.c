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

/**********************************************************************************************************************/

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{
    EN_serverError_t isValidAccount(ST_cardData_t * cardData, ST_accountsDB_t * accountRefrence)
    {
        //variable to return error state
        EN_serverError_t  errorStateValidAccount = SERVER_OK;
        //Variable to store string compare result
        uint8_t cmpPAN = 0;
        uint8_t iterate = 0;
        //for loop to compare the PAN with the PAN numbers stored in DataBase
        for (iterate = 0; accountsDB != 0; iterate++)
        {
            //Compare two strings together
            cmpPAN = strcmp(cardData->primaryAccountNumber, accountsDB[iterate].primaryAccountNumber);

            if (cmpPAN == 0)
            {
                //if the PAN is found in the DataBase return account refrence in the database
                *accountRefrence = accountsDB[iterate];
                errorStateValidAccount = SERVER_OK;
                break;
            }
            else
            {
                errorStateValidAccount = ACCOUNT_NOT_FOUND;
                *accountRefrence = NULL;
            }

        }
        return errorStateValidAccount;
    }
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
    uint8_t iterate = 0;
    for (iterate = 0; iterate < 255; iterate++)
    {
        printf("###################################\n");
        printf("Transaction Sequence Number: %d\n", transactionDB_t[iterate].transactionSequenceNumber);
        printf("Transaction Date: %s\n", &transactionDB_t[iterate].terminalData.transactionDate);
        printf("Transaction Amount: %f\n", transactionDB_t[iterate].terminalData.transAmount);
        printf("Transaction State: %s\n", transactionDB_t[iterate].transState);
        printf("Terminal Max Amount: %f\n", transactionDB_t[iterate].terminalData.maxTransAmount);
        printf("Cardholder Name: %s\n", transactionDB_t[iterate].cardHolderData.cardHolderName);
        printf("PAN: %s\n", transactionDB_t[iterate].cardHolderData.primaryAccountNumber);
        printf("Card Expiration Date: %s\n", transactionDB_t[iterate].cardHolderData.cardExpirationDate);
        printf("###################################\n");
    }

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