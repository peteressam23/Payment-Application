
#include "card.h"

// Function Implementations 

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    //Start with wrong name state 
    EN_cardError_t Error_state = WRONG_NAME;
    //Get card holder name from the user
    printf("\nEnter Card Holder Name: \n");
    gets(cardData->cardHolderName);

    //Check if the input is null
    if (strlen(cardData->cardHolderName) == 0)
    {
        Error_state = WRONG_NAME;
    }
    //Check the length of the name to be min 20 characters
    if (strlen(cardData->cardHolderName) < 20)
    {
        Error_state = WRONG_NAME;
    }
    //Check the length of the name to be max 24 characters
    if (strlen(cardData->cardHolderName) > 24)
    {
        Error_state = WRONG_NAME;
    }
    //Check if the length is in the acceptable range 
    if (strlen(cardData->cardHolderName) >= 20 && (strlen(cardData->cardHolderName) <= 24))
    {
        //This condition to check if the name is in the right format contains only alphabetic characters and spaces
        if (isalpha(cardData->cardHolderName) || (isspace(cardData->cardHolderName)))
        {
            Error_state = CARD_OK;
        }
    }
    return Error_state;

}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{

      int returnStatus = 1;
     *inputFromUser = ' ';
     printf("Enter Card Expiry Date: the format (MM/YY), e.g (05/25) \n");
     fgets(inputFromUser , sizeof(inputFromUser) , stdin);          //Get the expiration date from user

     int inputLen = strlen(inputFromUser);

     //Remove the newline from InputExp to calculate the length
     if(inputFromUser[inputLen-1] == '\n')
     {
        inputFromUser[inputLen-1] = 0;
     }

     //Check the length of Exp date
     if(strlen(inputFromUser) !=5)
     {
        returnStatus = 0;
     }

     //Check the format
     for(int i = 0 ; i<5 ; i++)
     {
        if( (isdigit(inputFromUser[i])) == 0  && i != 2  )
        {
            returnStatus = 0;
        }
        if( i == 2 && inputFromUser[i] != 47)
        {
            returnStatus = 0;
        }
     }

     //Check the return status
     if(returnStatus == 0)
     {
        return WRONG_EXP_DATE;
     }
     else
     {
       strcpy_s(cardData->cardExpirationDate , sizeof(inputFromUser) , inputFromUser );
       return CARD_OK;
     }

}



EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    /*To Make Error State For PAN And Return This Error State*/
    EN_cardError_t ErrorStatePAN = WRONG_PAN;

    
    printf("Enter Primary Account Number : ");
    gets(cardData->primaryAccountNumber);

    /*This Condition If User Input Null (Dont Input Any Thing*/
    if (strlen(cardData->primaryAccountNumber) == NULL)
    {
        ErrorStatePAN = WRONG_PAN;
    }
    /*This Condition If User Input Value Less Than 16 And More Than 19*/
    else if (strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19)
    {
        ErrorStatePAN = WRONG_PAN;
    }
    /*This Condition If User Input Value Start From 16 And End In 19 */
    else
    {
        ErrorStatePAN = CARD_OK;
    }   
    return ErrorStatePAN;
}

//Test Functions for card
void getCardHolderNameTest(void)
{
    /*Please Write Comments 80% overall*/


}

void getCardExpiryDateTest(void)
{
    /*Please Write Comments 80% overall*/

}



void getCardPANTest(void)
{
    uint8_t Ittierate = 0;
    uint8_t TesterName[50];
    ST_cardData_t CardData;
    EN_cardError_t ResultPANTestFun = WRONG_PAN;

 

    while (ResultPANTestFun == WRONG_PAN)
    {
        /*The Name Of Tester*/
        printf("Tester Name: ");

        /*To Input The Name Of Tester*/
        gets(TesterName);

        /*Print Number Of Test Case Then ittierate*/
        printf("Test Case %d :\n" , Ittierate+1);
        Ittierate++;

        /*Print Function Name*/
        printf("Function Name: getCardPAN\n");

        /*Input Data By The Function */
        printf("Input Data : ");
        ResultPANTestFun = getCardPAN(CardData.primaryAccountNumber);
        if (ResultPANTestFun == WRONG_PAN)
        {
            printf("Expected Result : WRONG_PAN\n");
            printf("Actual Result : WRONG_PAN\n\n");
        }
        else
        {
            printf("Expected Result : CARD_OK\n");
            printf("Actual Result : CARD_OK\n\n");
            break;
        }
    }
}





