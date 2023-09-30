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
    else if(isAmountAvailable (&transData->terminalData , &referenceInDB) == 4 )
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
        if(strcmp( accountsDB[iterate].primaryAccountNumber, referenceInDB.primaryAccountNumber) == 0)
        {
            accountsDB[iterate].balance -= transData->terminalData.transAmount;
            break;
        }
    }



    //Return the errorstate at the end of the function.
    return errorStateRecieveTrans;
}

/**********************************************************************************************************************/



EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
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
                accountRefrence = NULL;
            }

        }
        return errorStateValidAccount;
}


/**********************************************************************************************************************/



EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
    //Make Variable To return the errorState
    EN_serverError_t errorStateBlockAccount;

    //Check on The State Of Account
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
    //Make Variable To return the errorState
    EN_serverError_t errorStateAmountAvilavle;

    //Check on The Balance Of Account
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

            if (iterate == 0) 
            { 
                transactionDB_t[iterate].transactionSequenceNumber = 1000; 
            }

            if (iterate > 0) 
            {
                transactionDB_t[iterate].transactionSequenceNumber = transactionDB_t[iterate - 1].transactionSequenceNumber + 1;
            }

            transactionDB_t[iterate].transState = transData->transState;
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
    EN_serverError_t errorState ;

    for (iterate = 0; iterate < 255; iterate++)
    {

        if (transactionDB_t[iterate].transactionSequenceNumber == 0)
        {
            break;
        }
        printf("###################################\n");

        printf("Transaction Sequence Number: %d\n", transactionDB_t[iterate].transactionSequenceNumber);

        printf("Transaction Date: %s\n", &transactionDB_t[iterate].terminalData.transactionDate);

        printf("Transaction Amount: %f\n", transactionDB_t[iterate].terminalData.transAmount);

        printf("Transaction State: %s\n", serverErrorStrings[transactionDB_t[iterate].transState]);

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
    ST_transaction_t testTransaction ; 
    uint8_t testerName[30];
    uint8_t expectedCase[30];
    uint8_t result[30];
    uint8_t iterate = 1;
    EN_serverError_t returnOfFunction;

    
    printf("Enter your name: ");
    fgets(testerName, sizeof(testerName), stdin);

    for(iterate ; iterate <6 ; iterate++)
    {
        //call recieveTransactionData function.
        returnOfFunction = recieveTransactionData(&testTransaction);
        
        //Call all functions of card to test the transacrion.
        getCardHolderName(&testTransaction.cardHolderData);
        getCardExpiryDate(&testTransaction.cardHolderData);
        getCardPAN(&testTransaction.cardHolderData);

        //call all functions needed of terminal to test.
        getTransactionDate(&testTransaction.terminalData);
        getTransactionAmount(&testTransaction.terminalData);
        setMaxAmount(&testTransaction.terminalData,50000);
     
        printf("Expected Result:");
        fgets(expectedCase, sizeof(expectedCase), stdin);

        switch (returnOfFunction)
        {
        case 0:
            strcpy_s(result, 30, "APPROVED");
            break;
        
        case 1:
            strcpy_s(result, 30, "DECLINED_INSUFFECIENT_FUND");
            break;

        case 2:
            strcpy_s(result, 30, "DECLINED_STOLEN_CARD");
            break;

        case 3:
            strcpy_s(result, 30, "FRAUD_CARD");
            break;

        case 4:
            strcpy_s(result, 30, "INTERNAL_SERVER_ERROR");
            break;
        
        default:
            strcpy_s(result, 30, "UNDEFINED");
            break;
        }

          printf("\n\nTester Name :%sFunction Name: recieveTransactionData \nTest case %d:\nInput Data: %s\nExpected result:%sActual result: %s\n--------------------------\n"
            , testerName, iterate, inputFromUser, expectedCase, result);
    }
}

void isValidAccountTest(void)
{

    uint8_t iterate = 0;
    uint8_t testerName[30];
    uint8_t expectedCase[30];
    ST_cardData_t testCardData;
    ST_accountsDB_t testAccountReference;
    EN_serverError_t returnOfFunction;
    uint8_t result[30];


    printf("Tester Name: ");
    fgets(testerName, sizeof(testerName), stdin);

    for (iterate = 1; iterate < 3; iterate++)
    {
        returnOfFunction = isValidAccount(&testCardData, &testAccountReference);
        printf("Expected Result:");
        fgets(expectedCase, sizeof(expectedCase), stdin);
        switch (returnOfFunction) {
        case 0:
            strcpy_s(result, 30, "SERVER_OK");
            break;
        case 3:
            strcpy_s(result, 30, "ACCOUNT_NOT_FOUND");
            break;
        default:
            strcpy_s(result, 30, "UNDEFINED");
            printf("\n\nTester Name :%sFunction Name: isValidAccount \nTest case %d:\nInput Data:%s \nExpected result:%sActual result: %s\n-----------------------\n"
                , testerName, iterate, inputFromUser, expectedCase, result);
        }
    }

}

void isBlockedAccountTest(void)
{
    ST_transaction_t testTransaction ;
    ST_accountsDB_t testAccountRefrence; 
    uint8_t testerName[30];
    uint8_t expectedCase[30];
    uint8_t result[30];
    uint8_t iterate = 1;
    EN_serverError_t returnOfFunction;


    
    printf("Enter your name: ");
    fgets(testerName, sizeof(testerName), stdin);

    for(iterate ; iterate <4 ; iterate++)
    {
        //call getTransactionAmount function to check transaction amount.
        returnOfFunction = getTransactionAmount(&testTransaction);

        printf("Expected Result:");
        fgets(expectedCase, sizeof(expectedCase), stdin);

        if(returnOfFunction == TERMINAL_OK)
        {
            switch (isBlockedAccount(&testTransaction , &testAccountRefrence))
        {
        case 0:
            strcpy_s(result, 30, "SERVER_OK");
            break;

        case 5:
            strcpy_s(result, 30, "BLOCKED_ACCOUNT");
            break;

        default:
            strcpy_s(result, 30, "UNDEFINED");
            break;
        }
        }
    }
     printf("\n\nTester Name :%sFunction Name: isBlockedAccount \nTest case %d:\nInput Data: %s\nExpected result:%sActual result: %s\n--------------------------\n"
            , testerName, iterate, inputFromUser, expectedCase, result);

}




void isAmountAvailableTest(void)
{
    ST_transaction_t testTransaction ;
    ST_accountsDB_t testAccountRefrence; 
    uint8_t testerName[30];
    uint8_t expectedCase[30];
    uint8_t result[30];
    uint8_t iterate = 1;
    EN_serverError_t returnOfFunction;

    
    printf("Enter your name: ");
    fgets(testerName, sizeof(testerName), stdin);

    for(iterate ; iterate <4 ; iterate++)
    {
        //call recieveTransactionData function
        returnOfFunction = isAmountAvailable(&testTransaction , &testAccountRefrence);

        printf("Expected Result:");
        fgets(expectedCase, sizeof(expectedCase), stdin);

        switch (returnOfFunction)
        {
        case 0:
            strcpy_s(result, 30, "SERVER_OK");
            break;

        case 4:
            strcpy_s(result, 30, "LOW_BALANCE");
            break;

        default:
            strcpy_s(result, 30, "UNDEFINED");
            break;
        }
    }
     printf("\n\nTester Name :%sFunction Name: isAmountAvailable \nTest case %d:\nInput Data: %s\nExpected result:%sActual result: %s\n--------------------------\n"
            , testerName, iterate, inputFromUser, expectedCase, result);

}



void saveTransactionTest(void) {

    ST_transaction_t testTransaction;
    uint8_t testerName[30];
    uint8_t expectedCase[30];
    uint8_t result[30];
    uint8_t iterate_1 = 0;
    uint8_t iterate_2 = 0;
    EN_serverError_t returnOfFunction;


    printf("Enter your name:\n");
    fgets(testerName, sizeof(testerName), stdin);

    for (iterate_1 = 0; iterate_1 < 255; iterate_1++)
    {
        transactionDB_t[iterate_1].transactionSequenceNumber = 5;
    }

    for (iterate_2 = 0; iterate_2 < 3; iterate_2++)
    {
        printf("Enter expected result:\n");
        fgets(expectedCase, sizeof(expectedCase), stdin);

        returnOfFunction = saveTransaction(&testTransaction);

        getCardExpiryDate(&testTransaction.cardHolderData);

        getCardHolderName(&testTransaction.cardHolderData);

        getCardPAN(&testTransaction.cardHolderData);

        setMaxAmount(&testTransaction.terminalData, 20000.0);

        getTransactionDate(&testTransaction.terminalData);

        getTransactionAmount(&testTransaction.terminalData);

        testTransaction.transState = iterate_2;

        switch (returnOfFunction)
        {
        case 0:
            strcpy_s(result, 30, "SERVER_OK");
            break;
        case 1:
            strcpy_s(result, 30, "INTERNAL_SERVER_ERROR");
            break;
        default:
            printf("undefined Error");
            break;
        }
        printf("Tester Name :%sFunction Name: saveTransaction \nTest case %d:\nExpected result : %sActual result: %s\n-----------------\n"
            , testerName,iterate_2+ 1, expectedCase, result);


    }
}

/*
void listSavedTransactionsTest(void)
{

    //Please Write Comments 80% overall
}
*/