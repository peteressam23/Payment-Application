
#include "app.h"
#define MAX_AMOUNT  50000.0

void main(void)
{

    /*Card Section*/
    ST_cardData_t  appCardData;
    EN_cardError_t appCardError;

    /*Terminal Section*/
    ST_terminalData_t  appTerminalData;
    EN_terminalError_t appTerminalError;

    /*Server Section*/
    ST_accountsDB_t  appAccountRef;
    ST_transaction_t appServerData; 
    EN_serverError_t appServerError; 

    //Card Holder Name With Test
    appCardError = getCardHolderName(&appCardData);
    printf("This Is Enum Appear In Decimel : (%d)\n", appCardError);
    getCardHolderNameTest();


    //Card Expire Date With Test
    appCardError = getCardExpiryDate(&appCardData);
    printf("This Is Enum Appear In Decimel : (%d)\n", appCardError);
    getCardExpiryDateTest();

    //Card PAN With Test
    appCardError = getCardPAN(&appCardData);
    printf("This Is Enum Appear In Decimel : (%d)\n", appCardError);
    getCardPANTest();

    //Get Transaction Date With Test
    appTerminalError = getTransactionDate(&appTerminalData);
    printf("This Is Enum Appear In Decimel : (%d)\n", appTerminalError);
    getTransactionDateTest();

    //Is Card Expired With Test
    appTerminalError = isCardExpired(&appCardData, &appTerminalData);
    printf("This Is Enum Appear In Decimel : (%d)\n", appTerminalError);
    isCardExpriedTest();

   //Get Transaction Amount With Test
   appTerminalError = getTransactionAmount(&appTerminalData);
   printf("This Is Enum Appear In Decimel : (%d)\n", appTerminalError);
   getTransactionAmountTest();
   
   //Set Max Amount With Test
   appTerminalError = setMaxAmount(&appTerminalData, MAX_AMOUNT);
   printf("This Is Enum Appear In Decimel : (%d)\n", appTerminalError);
   setMaxAmountTest();
   
   //Is Below Max Amount With Test
   appTerminalError = isBelowMaxAmount(&appTerminalData);
   printf("This Is Enum Appear In Decimel : (%d)\n", appTerminalError);
   isBelowMaxAmountTest();


   //Is Valid Account With Test
   appServerError = isValidAccount(&appCardData, &appAccountRef); 
   printf("This Is Enum Appear In Decimel : (%d)\n", appServerError); 
   isValidAccountTest();


   //Is Valid Account With Test
   appServerError = isBlockedAccount(&appAccountRef);
   printf("This Is Enum Appear In Decimel : (%d)\n", appServerError);
   isBlockedAccountTest();

   //Is Valid Account With Test
   appServerError = isBlockedAccount(&appAccountRef);
   printf("This Is Enum Appear In Decimel : (%d)\n", appServerError);
   isBlockedAccountTest();

   //Is Amount Available
   appServerError = isAmountAvailable(& appAccountRef , &appAccountRef);
   printf("This Is Enum Appear In Decimel : (%d)\n", appServerError);
   isAmountAvailableTest();


   //Save Transaction With Test
   appServerError = saveTransaction(&appServerData);
   printf("This Is Enum Appear In Decimel : (%d)\n", appServerError);
   saveTransactionTest();


   //List Save Transaction With Test
   listSavedTransactions();

 



 



 








   


  
    







  
  
  
 
    

}


