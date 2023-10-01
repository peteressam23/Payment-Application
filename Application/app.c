
#include "app.h"

void main(void)
{
    /*Card Section*/
    /*
    Test Card Holder Name
     getCardHolderNameTest();
    */
   

    /*
    Test Card Expire Date
    getCardExpiryDateTest();
    */
    

    /*
     Test Card PAN
     getCardPANTest();
     */



    /*Terminal Section*/
    /*
    Test Transaction Date
     getTransactionDateTest();
    */


    /*
    Test Card Expire Date
    isCardExpriedTest();
    */


    /*
     Test Transaction Amount
     getTransactionAmountTest();
     */
    
    /*
     Test Below MaxAmount
     isBelowMaxAmountTest();
    */

    /*
     Test Set MAx Amount
     setMaxAmountTest();
    */

    
    /*Server Section*/




   // isBlockedAccountTest();
   //recieveTransactionDataTest();
  
  
    ST_transaction_t test;
    test.terminalData.transAmount = 10000;

    EN_transState_t error;
    error = recieveTransactionData(&test);
    printf("%d", error);
    

}


