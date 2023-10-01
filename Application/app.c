
#include "app.h"

void main(void)
{
    /*Card Section*/
    //Card Holder Name
    ST_cardData_t appCardData;
    EN_cardError_t appCardError;
    appCardError = getCardHolderName(&appCardData);
    printf("%d\n", appCardError);

    //Card Expire Date
    appCardError = getCardExpiryDate(&appCardData);
    printf("%d\n", appCardError);

    //Card PAN
    appCardError = getCardPAN(&appCardData);
    printf("%d\n", appCardError);


    //////////////////////////////////////////////////////////////////////////////////

    /*Terminal Section*/
    //Get Transaction Date
    ST_terminalData_t appTerminalData;
    EN_terminalError_t appTerminalError;
    appTerminalError = getTransactionDate(&appTerminalData);
    printf("%d\n", appTerminalError);

    //Is Card Expired 
    appTerminalError = isCardExpired(&appCardData , &appTerminalData);
    printf("%d\n", appTerminalError);









   
   // printf("\n___________ Calling Test Function Card Test______________________________\n\n");
    /*
    getCardHolderNameTest();
    getCardExpiryDateTest();
    getCardPANTest();
    */

    printf("\n___________ Calling Test Function Terminal Test______________________________\n\n");
    /*
    getTransactionDateTest();
    */
    isCardExpriedTest();

    
   







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
  
  
 
    

}


