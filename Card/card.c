
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
    /* Note : Month Format */
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
    EN_cardError_t ErrorStatePAN = CARD_OK;
    *inputFromUser = ' ';

    printf("Enter Primary Account Number : ");
    gets(inputFromUser);

    //Remove the newline from InputExp to calculate the length
    uint8_t inputLen = strlen(inputFromUser);
    if (inputFromUser[inputLen - 1] == '\n')
    {
        inputFromUser[inputLen - 1] = 0;
    }

    /*This Condition If User Input Null (Dont Input Any Thing*/
    if (strlen(inputFromUser) == NULL || strlen(inputFromUser) < 16 || strlen(inputFromUser) > 19)
    {
        ErrorStatePAN = WRONG_PAN;
    }

    //numeric chars check
    for (int i = 0; i < strlen(inputFromUser); i++) {
        if (isdigit(inputFromUser[i]) == 0) {
            if (isspace(inputFromUser[i]) == 0) {

                ErrorStatePAN = WRONG_PAN;
            }
        }
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
    ST_cardData_t test;
    uint8_t tester_name[50];
    uint8_t expected_case[50];
    uint8_t iterate = 0;
    char result[30];
    EN_cardError_t expected;

    printf("Enter your name:\n");
    fgets(tester_name, sizeof(tester_name), stdin);

    for (iterate = 0; iterate < 5 ; iterate++)
    {
        expected = getCardExpiryDate(test.cardExpirationDate);
        printf("Enter expected result:\n");
        fgets(expected_case, sizeof(expected_case), stdin);
        switch (expected) 
        {
        case 0:
            strcpy_s(result, 30, "CARD_OK");
            break;
        case 2:
            strcpy_s(result, 30, "WRONG_EXP_DATE");
            break;
        default:
            strcpy_s(result, 30, "undefined Error");
            break;
        }

        printf("\n\nTester Name :%sFunction Name: getCardExpiryDate \nTest case %d:\nInput Data:%s\nExpected result:%sActual result: %s\n-----------------\n"
            , tester_name, iterate+1 , inputFromUser, expected_case, result);
    }

}



void getCardPANTest(void)
{
    uint8_t Ittierate;
    uint8_t TesterName[50];
    ST_cardData_t testCardData;
    uint8_t expectedCase[50];
    EN_cardError_t expected;
    char result[30];
    
    /*The Name Of Tester*/
    printf("Tester Name: ");
    gets(TesterName);

    for (Ittierate = 0; Ittierate < 4 ; Ittierate++)
    {
        expected = getCardPAN(testCardData.primaryAccountNumber);
        printf("Enter expected result:\n");
        gets(expectedCase);
        switch (expected)
        {
        case 0:
            strcpy_s(result, 30, "CARD_OK");
            break;
        case 3:
            strcpy_s(result, 30, "WRONG_PAN");
            break;
        default:
            strcpy_s(result, 30, "undefined Error");
            break;
        }
       

        printf("\n\nTester Name :%sFunction Name: getCardPAN \nTest case %d:\nInput Data:%s\nExpected result:%sActual result: %s\n-----------------\n"
            , TesterName, Ittierate + 1, inputFromUser, expectedCase, result);
    }
}

 
    







