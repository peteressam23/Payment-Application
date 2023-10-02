#include "server.h"

/***************************************Global Arrays***********************************************************/

//Create a global array of ST_accountsDB_t for the valid accounts database.
//Fill in the array initially with any valid data.
ST_accountsDB_t accountsDB[255] = {

     {2000.0  , RUNNING , "1020304050607080"} ,
     {5000.0  , BLOCKED , "2030405060708010"} ,
     {10000.0 , BLOCKED , "3040506070801020"} ,
     {15500.0 , RUNNING , "4050607080102030"} ,
     {13000.0, RUNNING , "5060708010203040"} ,
     {8900.0  , BLOCKED , "6070801020304050"} ,
     {6850.0  , RUNNING , "7080102030405060"} ,
     {1000.0  , RUNNING , "8010203040506070"}
};

//Create a global array of ST_transaction_t for the valid transactions database.
//Fill in the array of transactionDB_t initially with Zeros
ST_transaction_t transactionDB_t[255] = { 0 };


const char* serverErrorStrings[] = {
    "APPROVED",
    "DECLINED_INSUFFECIENT_FUND",
    "DECLINED_STOLEN_CARD"
    "FRAUD_CARD"
    "INTERNAL_SERVER_ERROR"
};



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

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) 
{
    EN_serverError_t errorStateIsValidAccount = ACCOUNT_NOT_FOUND;
    uint8_t iterate = 0;

    for (iterate = 0; iterate <= 255; iterate++)
    {
        if (strcmp(accountsDB[iterate].primaryAccountNumber, cardData->primaryAccountNumber) == 0)
        {
            *accountRefrence = accountsDB[iterate];
            errorStateIsValidAccount = SERVER_OK;
        }
    }
    accountRefrence = NULL;
    return errorStateIsValidAccount;
}

/**********************************************************************************************************************/

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
    //Make Variable To return the errorState
    EN_serverError_t errorStateBlockAccount ;

    //Check on The State Of Account
    if (accountRefrence->state == RUNNING)
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
    EN_serverError_t errorStateAmountAvilavle = SERVER_OK;

    //Check on The Balance Of Account
    if (termData->transAmount > accountRefrence->balance)
    {
        errorStateAmountAvilavle = LOW_BALANCE;
    }

    return errorStateAmountAvilavle;
}

/**********************************************************************************************************************/
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
    uint8_t iterate = 0;
    EN_serverError_t errorStateSaveTrans = SAVING_FAILED;

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
    }
    return errorStateSaveTrans;
}

/**********************************************************************************************************************/

void listSavedTransactions(void) 
{
    uint8_t iterate = 0;
    uint8_t trans[5][30] = { {"APPROVED"}, {"DECLINED_INSUFFECIENT_FUND"}, {"DECLINED_STOLEN_CARD"}, {"FRAUD_CARD"}, {"INTERNAL_SERVER_ERROR"} };

    for (iterate = 0 ; iterate <= 255; iterate++)
    {
        if (transactionDB_t[iterate].transState < 0 || transactionDB_t[iterate].transState > 4)
        {
            break;
        }
        if (transactionDB_t[iterate].transactionSequenceNumber == 0)
        {
            break;
        }
        printf("#####################################################\n");
        printf("Transaction Sequence Number: %d\n", transactionDB_t[iterate].transactionSequenceNumber);
        printf("Transaction Date: %s\n", &transactionDB_t[iterate].terminalData.transactionDate);
        printf("Transaction Amount: %f\n", transactionDB_t[iterate].terminalData.transAmount);
        printf("Transaction State: %s\n", trans[transactionDB_t[iterate].transState]);
        printf("Terminal Max Amount: %f\n", transactionDB_t[iterate].terminalData.maxTransAmount);
        printf("Cardholder Name: %s\n", transactionDB_t[iterate].cardHolderData.cardHolderName);
        printf("PAN: %s\n", transactionDB_t[iterate].cardHolderData.primaryAccountNumber);
        printf("Card Expiration Date: %s\n", transactionDB_t[iterate].cardHolderData.cardExpirationDate);
        printf("#####################################################\n");
    }
}

/**********************************************************************************************************************/

//Test Functions for server
void recieveTransactionDataTest(void)
{
    ST_transaction_t testTransaction ; 
    uint8_t testerName[30];
    uint8_t expectedCase[30];
    uint8_t result[30];
    uint8_t iterate = 1;
    EN_serverError_t returnOfFunction;

    
    printf("\n\nTester Name: ");
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
        printf("____________________________________\n");
        printf("Tester Name: %s\n", testerName);
        printf("Function Name: recieveTransactionData\n");
        printf("Test case %d:\n", iterate);
        printf("Input Data: %s\n", inputFromUser);
        printf("Expected Result: %s\n", expectedCase); 
        printf("Actual Result: %s\n", result); 
        printf("____________________________________\n\n");
    }
}


void isValidAccountTest(void)
{
    ST_cardData_t testCardData;
    ST_accountsDB_t accountRefrence;
    uint8_t iterate = 0;
    uint8_t testerName[30];
    uint8_t expectedCase[30];
    uint8_t result[30];
    EN_serverError_t returnOfFunction;


    printf("\n\nTester Name: ");
    fgets(testerName, sizeof(testerName), stdin);

    for (iterate = 1; iterate < 6 ; iterate++)
    {
        returnOfFunction = getCardPAN(&testCardData);
        printf("Expected Result:");
        fgets(expectedCase, sizeof(expectedCase), stdin);

        if (returnOfFunction == 0)
        {
            switch (isValidAccount(&testCardData , &accountRefrence))
            {
            case 0:
                strcpy_s(result, 30, "SERVER_OK");
                break;
            case 3:
                strcpy_s(result, 30, "ACCOUNT_NOT_FOUND");
                break;
            default:
                printf("undefined Error");
                break;
            }

            printf("____________________________________\n");
            printf("\nTester Name: %s\n", testerName);
            printf("Function Name: isValidAccount\n");
            printf("Test case %d:\n", iterate);
            printf("Input Data: %s\n", accountRefrence.primaryAccountNumber);
            printf("Expected Result: %s\n", expectedCase);
            printf("Actual Result: %s\n", result);
            printf("____________________________________\n\n");

        }
        else
        {
            strcpy_s(result, 30, "WRONG PAN");

            printf("____________________________________\n");
            printf("\nTester Name: %s\n", testerName);
            printf("Function Name: isValidAccount\n");
            printf("Test case %d:\n", iterate);
            printf("Input Data: %s\n", accountRefrence.primaryAccountNumber);
            printf("Expected Result: %s\n", expectedCase);
            printf("Actual Result: %s\n", result);
            printf("____________________________________\n\n");
        }
    }
}


void isBlockedAccountTest(void)
{
    ST_cardData_t testCardData;
    ST_accountsDB_t accountRefrence;
    uint8_t testerName[30];
    uint8_t expectedCase[30];
    uint8_t result[30];
    uint8_t iterate = 1;
    EN_serverError_t returnOfFunction;

    printf("\n\nTester Name: ");
    fgets(testerName, sizeof(testerName), stdin);

    for (iterate = 1; iterate < 6; iterate++)
    {
        returnOfFunction = isBlockedAccount(&accountRefrence);

        printf("Expected Result:");
        fgets(expectedCase, sizeof(expectedCase), stdin);

        if (getCardPAN(&testCardData) == 0 && isValidAccount(&testCardData, &accountRefrence) == 0)
        {
            switch (returnOfFunction)
            {
            case 0:
                strcpy_s(result, 30, "SERVER_OK");
                break;
            case 5:
                strcpy_s(result, 30, "BLOCKED_ACCOUNT");
                break;
            default:
                printf("undefined Error");
                break;
            }
            printf("____________________________________\n");
            printf("\nTester Name: %s\n", testerName);
            printf("Function Name: isBlockedAccount\n");
            printf("Test case %d:\n", iterate);
            printf("Input Data: %s\n", inputFromUser);
            printf("Expected Result: %s\n", expectedCase);
            printf("Actual Result: %s\n", result);
            printf("____________________________________\n\n");
        }
        else
        {
            strcpy_s(result, sizeof(result), " WRONG PAN ");
            printf("____________________________________\n");
            printf("\nTester Name: %s\n", testerName);
            printf("Function Name: isBlockedAccount\n");
            printf("Test case %d:\n", iterate);
            printf("Input Data: %s\n", inputFromUser);
            printf("Expected Result: %s\n", expectedCase);
            printf("Actual Result: %s\n", result);
            printf("____________________________________\n\n");
        }
    }
}




void isAmountAvailableTest(void) 
{
 
    ST_terminalData_t testTerminalData;
    ST_accountsDB_t accountRefrence = accountsDB[2];
    uint8_t testerName[30];
    uint8_t expectedCase[30];
    uint8_t result[30];
    uint8_t iterate = 1;
    EN_serverError_t returnOfFunction;


    printf("\n\nTester Name: ");
    fgets(testerName, sizeof(testerName), stdin);

    for (iterate = 1; iterate < 6; iterate++)
    {
        returnOfFunction = getTransactionAmount(&testTerminalData);

        printf("Expected Result:");
        fgets(expectedCase, sizeof(expectedCase), stdin);

        if (returnOfFunction == 0)
        {
            switch (isAmountAvailable(&testTerminalData, &accountRefrence))
            {
            case 0:
                strcpy_s(result, 30, "SERVER_OK");
                break;
            case 4:
                strcpy_s(result, 30, "LOW_BALANCE");
                break;
            default:
                printf("undefined Error");
                break;
            }
            printf("____________________________________\n");
            printf("\nTester Name: %s\n", testerName);
            printf("Function Name: isAmountAvailable\n");
            printf("Test case %d:\n", iterate);
            printf("Input Data: %s\n", inputFromUser);
            printf("Expected Result: %s\n", expectedCase);
            printf("Actual Result: %s\n", result);
            printf("____________________________________\n\n");
        }
        else 
        {
            strcpy_s(result, 30, "INVALID_AMOUNT");
            printf("____________________________________\n");
            printf("\nTester Name: %s\n", testerName);
            printf("Function Name: isAmountAvailable\n");
            printf("Test case %d:\n", iterate);
            printf("Input Data: %s\n", inputFromUser);
            printf("Expected Result: %s\n", expectedCase);
            printf("Actual Result: %s\n", result);
            printf("____________________________________\n\n");
        }
    }
}



void saveTransactionTest(void) 
{
    ST_transaction_t testTransaction;
    uint8_t testerName[30];
    uint8_t expectedCase[30];
    uint8_t result[30];
    EN_serverError_t returnOfFunction;

    printf("\n\nTester Name: ");
    fgets(testerName, sizeof(testerName), stdin);

    for (int j = 0; j < 253; j++)
    { 
        transactionDB_t[j].transactionSequenceNumber = 5;
    }

    for (int i = 0; i < 3; i++) 
    {
        returnOfFunction = saveTransaction(&testTransaction);

        printf("Expected Result:");
        fgets(expectedCase, sizeof(expectedCase), stdin);

        getCardExpiryDate(&testTransaction.cardHolderData);

        getCardHolderName(&testTransaction.cardHolderData);

        getCardPAN(&testTransaction.cardHolderData);

        setMaxAmount(&testTransaction.terminalData, 20000.0);

        getTransactionDate(&testTransaction.terminalData);

        getTransactionAmount(&testTransaction.terminalData);

        testTransaction.transState = i;

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
        printf("____________________________________\n");
        printf("\nTester Name: %s\n", testerName);
        printf("Function Name: saveTransaction\n");
        printf("Test case %d:\n", i+1);
        printf("Expected Result: %s\n", expectedCase);
        printf("Actual Result: %s\n", result);
        printf("____________________________________\n\n");
    }
}

/*
void listSavedTransactionsTest(void)
{

    //Please Write Comments 80% overall
}
*/