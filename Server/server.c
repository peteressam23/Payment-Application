#include "server.h"

/***************************************Function Implementations ****************************************************/

EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    /*Please Write Comments 80% overall*/
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{
    //variable to return error state
    EN_serverError_t  errorStateValidAccount = SERVER_OK;
    //Variable to store string compare result
    uint8_t cmpPAN = 0;
    uint8_t iterate = 0;
    //for loop to compare the PAN with the PAN numbers stored in DataBase
    for (iterate = 0; accountsDB!=0; iterate++)
    {
        //Compare two strings together
        cmpPAN = strcmp(cardData->primaryAccountNumber, accountsDB[iterate].primaryAccountNumber);

        if (cmpPAN == 0)
        {
            //if the PAN is found in the DataBase return account refrence in the database
            *accountRefrence = iterate;
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
    uint8_t iterate = 0;
    uint8_t testerName[50];
    uint8_t expectedCase[50];
    ST_cardData_t testCardData;
    ST_accountsDB_t testAccountReference;
    EN_serverError_t expected;
    char result[30];


    printf("Tester Name: ");
    fgets(testerName, sizeof(testerName), stdin);
    
    for (iterate = 1; iterate < 6; iterate++)
    {
        testCardData.primaryAccountNumber=getCardPAN()
        expected = isValidAccount(&testCardData,&testAccountReference);
        printf("Expected Result:");
        fgets(expectedCase, sizeof(expectedCase), stdin);
        switch (expected) {
        case 0:
            strcpy_s(result, 30, "SERVER_OK");
            break;
        case 3:
            strcpy_s(result, 30, "ACCOUNT_NOT_FOUND");
            break;
        default:
            strcpy_s(result, 30, "UNDEFINED");
            printf("\n\nTester Name :%sFunction Name: isValidAccount \nTest case %d:\nInput Data:%s \nExpected result:%sActual result: %s\n-----------------------\n"
                , testerName, iterate, testCardData.primaryAccountNumber, expectedCase, result);

    
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