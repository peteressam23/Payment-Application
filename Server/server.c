#include "server.h"

/***************************************Global Arrays***********************************************************/
//Create a global array of ST_accountsDB_t for the valid accounts database.
//Fill in the array initially with any valid data.
ST_accountsDB_t accountsDB[255] = 
{

     {2000.0  , RUNNING , "1020304050607080"} ,
     {5000.0  , BLOCKED , "2030405060708010"} ,
     {10000.0 , BLOCKED , "3040506070801020"} ,
     {15500.0 , RUNNING , "4050607080102030"} ,
     {13000.0, RUNNING ,  "5060708010203040"} ,
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

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
    ST_accountsDB_t accountRefrence = { 0 };
    if (isValidAccount(&transData->cardHolderData, &accountRefrence) == 3)
    {
        return FRAUD_CARD;
    }
    if (isBlockedAccount(&accountRefrence) == 5)
    {
        return DECLINED_STOLEN_CARD;
    }
    if (isAmountAvailable(&transData->terminalData, &accountRefrence) == 4)
    {
        return DECLINED_INSUFFECIENT_FUND;
    }
    //update the transaction status ( APPROVED ).
    transData->transState = APPROVED;

    if (saveTransaction(transData) == 1) //saveTransaction(transData) == SAVING_FAILED.
    {
        return INTERNAL_SERVER_ERROR;
    }

    //update the database with the new balance.
    for (int i = 0; i <= 255; i++) {
        if (strcmp(accountsDB[i].primaryAccountNumber, accountRefrence.primaryAccountNumber) == 0)
        {
            accountsDB[i].balance -= transData->terminalData.transAmount;
            break;
        }
    }
    return transData->transState;
}

/**********************************************************************************************************************/

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
    EN_serverError_t errorState = ACCOUNT_NOT_FOUND;
    for (int iterate = 0; iterate <= 255; iterate++)
    {
        /*Check The User Enterd PAN ANd Compare It To The PANs In Data Base*/
        if (strcmp(accountsDB[iterate].primaryAccountNumber, cardData->primaryAccountNumber) == 0)
        {
            *accountRefrence = accountsDB[iterate];
            errorState = SERVER_OK;
        }
    }
    accountRefrence = NULL;
    return errorState;
}

/**********************************************************************************************************************/

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
    EN_serverError_t errorState = BLOCKED_ACCOUNT;
    /*Check Account State If Runnig Return Server OK Else Is Block And Return Block*/
    if (accountRefrence->state == RUNNING)
    {
        errorState = SERVER_OK;
    }
    return errorState;
}

/**********************************************************************************************************************/

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) 
{
    EN_serverError_t errorState = SERVER_OK;
    /*Check And Compare Between Trans Amount in terminal and The Balance in database */
    if (termData->transAmount > accountRefrence->balance) 
    {
        errorState = LOW_BALANCE;
    }
    return errorState;
}

/**********************************************************************************************************************/
EN_serverError_t saveTransaction(ST_transaction_t* transData) 
{
    EN_serverError_t errorState = SAVING_FAILED;
    /*Loop On All Data Base*/
    for (int iterate = 0; iterate < 255; iterate++)
    {
        /*If Seq Num IS 0 it Mean No Trans Is Happen*/
        if (transactionDB_t[iterate].transactionSequenceNumber == 0)
        {
            /*Store*/
            transactionDB_t[iterate].cardHolderData = transData->cardHolderData;
            transactionDB_t[iterate].terminalData = transData->terminalData;
            /*If Seq Num Is Zero IS No Trans And Begin With Init Value*/
            if (iterate == 0)
            {
                transactionDB_t[iterate].transactionSequenceNumber = 1000;
            }
            /*Here To Increment in All Transaction*/
            if (iterate > 0)
            { 
                transactionDB_t[iterate].transactionSequenceNumber = transactionDB_t[iterate - 1].transactionSequenceNumber + 1;
            }
            transactionDB_t[iterate].transState = transData->transState;
            listSavedTransactions();

            errorState = SERVER_OK;
        }
    }
    return errorState;
}

/**********************************************************************************************************************/

void listSavedTransactions(void)
{
    ST_cardData_t cardData;
    uint8_t iterate = 0;
    uint8_t trans[5][30] = {
                            {"APPROVED"},
                            {"DECLINED_INSUFFECIENT_FUND"}, 
                            {"DECLINED_STOLEN_CARD"}, 
                            {"FRAUD_CARD"},
                            {"INTERNAL_SERVER_ERROR"} };

    for (iterate = 0; iterate <= 255; iterate++)
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
    ST_transaction_t testTransaction;
    uint8_t testerName[30];
    uint8_t expectedCase[30];
    char result[30];
    printf("Enter your name:\n");
    fgets(testerName, sizeof(testerName), stdin);

    for (uint8_t iterate = 1; iterate < 5; iterate++)
    {
        getCardExpiryDate(&testTransaction.cardHolderData);
        getCardHolderName(&testTransaction.cardHolderData);
        getCardPAN(&testTransaction.cardHolderData);
        setMaxAmount(&testTransaction.terminalData, 50000.0);
        getTransactionDate(&testTransaction.terminalData);
        getTransactionAmount(&testTransaction.terminalData);
        printf("Enter expected result:\n");
        fgets(expectedCase, sizeof(expectedCase), stdin);
        switch (recieveTransactionData(&testTransaction))
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
            printf("undefined Error");
            break;
        }
        printf("____________________________________\n");
        printf("\nTester Name: %s\n", testerName);
        printf("Function Name: recieveTransactionData\n");
        printf("Test case %d:\n", iterate);
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

    for (iterate = 1; iterate < 4; iterate++)
    {
        returnOfFunction = getCardPAN(&testCardData);
        printf("Expected Result:");
        fgets(expectedCase, sizeof(expectedCase), stdin);

        if (returnOfFunction == 0)
        {
            switch (isValidAccount(&testCardData, &accountRefrence))
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
            printf("Input Data: %s\n", inputFromUser);
            printf("Expected Result: %s", expectedCase);
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
            printf("Input Data: %s\n", inputFromUser);
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

    for (iterate = 1; iterate < 4; iterate++)
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
            printf("Expected Result: %s", expectedCase);
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

    for (iterate = 1; iterate < 4; iterate++)
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
    ST_transaction_t transDataTest;
    uint8_t testerName[50];
    uint8_t expectedCase[50];
    char result[30];

    printf("\n\nTester Name: ");
    fgets(testerName, sizeof(testerName), stdin);
    for (uint8_t j = 0; j < 253; j++)
    {
        transactionDB_t[j].transactionSequenceNumber = 5;
    }

    for (uint8_t i = 0; i < 3; i++)
    {
        printf("Enter expected result:\n");
        fgets(expectedCase, sizeof(expectedCase), stdin);
        getCardExpiryDate(&transDataTest.cardHolderData);
        getCardHolderName(&transDataTest.cardHolderData);
        getCardPAN(&transDataTest.cardHolderData);
        setMaxAmount(&transDataTest.terminalData, 50000.0);
        getTransactionDate(&transDataTest.terminalData);
        getTransactionAmount(&transDataTest.terminalData);
        transDataTest.transState = i;
        switch (saveTransaction(&transDataTest))
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
        printf("Test case %d:\n", i + 1);
        printf("Expected Result: %s\n", expectedCase);
        printf("Actual Result: %s\n", result);
        printf("____________________________________\n\n");
    }
}

void listSavedTransactionsTest(void)
{
    uint8_t testerName[30];
    uint8_t expectedCase[30];
    ST_transaction_t testTransaction3, testTransaction1, testTransaction2;
    uint8_t result[30];

    testTransaction1.transactionSequenceNumber = 3;
    testTransaction1.transState = 0;
    testTransaction1.terminalData.transAmount = 2000;
    testTransaction1.terminalData.maxTransAmount = 50000;

    strcpy_s(testTransaction1.cardHolderData.cardExpirationDate, 06, 12 / 22);
    strcpy_s(testTransaction1.cardHolderData.cardHolderName, 25, "Mario Saad Mario Saad");
    strcpy_s(testTransaction1.cardHolderData.primaryAccountNumber, 20, "7080102030405060");
    strcpy_s(testTransaction1.terminalData.transactionDate, 12, "11/11/2011");


    testTransaction2.transactionSequenceNumber = 11;
    testTransaction2.transState = 4;
    testTransaction2.terminalData.transAmount = 55000;
    testTransaction2.terminalData.maxTransAmount = 50000;

    strcpy_s(testTransaction2.cardHolderData.cardExpirationDate, 6, 05 / 26);
    strcpy_s(testTransaction2.cardHolderData.cardHolderName, 25, "Nadeen Adel Mohammed Mo");
    strcpy_s(testTransaction2.cardHolderData.primaryAccountNumber, 20, "1020304050607080");
    strcpy_s(testTransaction2.terminalData.transactionDate, 12, "01/10/2023");

    testTransaction3.transactionSequenceNumber = 20;
    testTransaction3.transState = 1;
    testTransaction3.terminalData.transAmount = 500;
    testTransaction3.terminalData.maxTransAmount = 50000;

    strcpy_s(testTransaction3.cardHolderData.cardExpirationDate, 6, 12 / 23);
    strcpy_s(testTransaction3.cardHolderData.cardHolderName, 25, "Peter Essam Peter Essamm");
    strcpy_s(testTransaction3.cardHolderData.primaryAccountNumber, 20, "3040506070801020");
    strcpy_s(testTransaction3.terminalData.transactionDate, 12, "25/09/2023");


    transactionDB_t[0] = testTransaction1;
    transactionDB_t[1] = testTransaction2;
    transactionDB_t[2] = testTransaction3;
    printf("Enter Your Name: ");
    fgets(testerName, sizeof(testerName), stdin);

    printf("Enter Expected Result: ");
    fgets(expectedCase, sizeof(expectedCase), stdin);
    listSavedTransactions();
    strcpy_s(result, 30, "SERVER_OK");

    printf("____________________________________\n");
    printf("\nTester Name: %s\n", testerName);
    printf("Function Name: listSavedTransactions\n");
    printf("Test case :\n");
    printf("Expected Result: %s\n", expectedCase);
    printf("Actual Result: %s\n", result);
    printf("____________________________________\n\n");
}