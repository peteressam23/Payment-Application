
#include "card.h"

// Function Implementations 

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
    //Start with card ok state
    EN_cardError_t errorStateHolderName = CARD_OK;
    uint8_t inputLen;
    uint8_t iterate = 0;
    *inputFromUser = ' ';

    //Get card holder name from the user
    printf("\nEnter Card Holder Name: \n");
    fgets(inputFromUser, sizeof(inputFromUser), stdin);

     inputLen = strlen(inputFromUser);

    //Remove the newline from the holder name
    if (inputFromUser[inputLen - 1] == '\n')
    {
        inputFromUser[inputLen - 1] = 0;
    }
    //Check if the input is null
    if (strlen(inputFromUser) == 0)
    {
        errorStateHolderName = WRONG_NAME;
    }
    //Check the length of the name to be min 20 characters
    if (strlen(inputFromUser) < 20)
    {
        errorStateHolderName = WRONG_NAME;
    }
    //Check the length of the name to be max 24 characters
    if (strlen(inputFromUser) > 24)
    {
        errorStateHolderName = WRONG_NAME;
    }
    //Check if the length is in the acceptable range
    if (strlen(inputFromUser) >= 20 && (strlen(inputFromUser) <= 24))
    {
        //This condition to check if the name is in the right format contains only alphabetic characters and spaces
        for ( iterate  = 0; iterate < strlen(inputFromUser); iterate++)
        {
            if (!isalpha(inputFromUser[iterate]) && !isspace(inputFromUser[iterate]))
            {
                errorStateHolderName = WRONG_NAME;
                break;
            }
        }
    }
    if (errorStateHolderName == CARD_OK)
    {
        strcpy_s(cardData->cardHolderName, sizeof(inputFromUser), inputFromUser);
    }
    return errorStateHolderName;

}

/*************************************************************************************************************************************/


EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
     uint8_t inputLen;
     uint8_t returnStatus = 1;
     *inputFromUser = ' ';
     uint8_t iterate = 0;

     //Get the expiration date from user
     printf("Enter Card Expiry Date: the format (MM/YY), e.g (05/25) \n");
     fgets(inputFromUser , sizeof(inputFromUser) , stdin);          

      inputLen = strlen(inputFromUser);

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
     for(iterate = 0 ; iterate < 5 ; iterate++)
     {
        if( (isdigit(inputFromUser[iterate])) == 0  && iterate != 2  )
        {
            returnStatus = 0;
        }
        if(iterate == 2 && inputFromUser[iterate] != 47)
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

/*************************************************************************************************************************************/

EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    /*To Make Error State For PAN And Return This Error State*/
    EN_cardError_t ErrorStatePAN = CARD_OK;
    *inputFromUser = ' ';
    uint8_t iterate = 0;

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

    //Numeric chars check
    for (iterate = 0; iterate < strlen(inputFromUser); iterate++) {
        if (isdigit(inputFromUser[iterate]) == 0) 
        {
            if (isspace(inputFromUser[iterate]) == 0) 
            {

                ErrorStatePAN = WRONG_PAN;
            }
        }
    }
    if (ErrorStatePAN == CARD_OK)
    {
        strcpy_s(cardData->primaryAccountNumber, sizeof(cardData->primaryAccountNumber), inputFromUser);
    }
  
    return ErrorStatePAN;
}

/*************************************************************************************************************************************/

//Test Functions for card

void getCardHolderNameTest(void)
{
    uint8_t iterate = 0;
    uint8_t testerName[50];
    ST_cardData_t testCardData;
    uint8_t expectedCase[50];
    EN_cardError_t returnOfFunction;
    char result[30];

    //To Get The Name Of Tester
    printf("Tester Name: ");
    fgets(testerName, sizeof(testerName), stdin);

    //Iterations for different test cases
    for (iterate = 1; iterate < 6; iterate++)
    {
        returnOfFunction = getCardHolderName(testCardData.cardHolderName);
        printf("Expected Result:");
        fgets(expectedCase, sizeof(expectedCase), stdin);
        switch (returnOfFunction) 
        {

        case 0:
            strcpy_s(result, 30, "CARD_OK");
            break;
        case 1:
            strcpy_s(result, 30, "WRONG_NAME");
            break;
        default:
            strcpy_s(result, 30, "UNDEFINED");
        }
        printf("\n\nTester Name :%sFunction Name: getCardHolderName \nTest case %d:\nInput Data:%s\nExpected result:%sActual result: %s\n-----------------------\n"
            , testerName, iterate, inputFromUser, expectedCase, result);
    }
}

/*************************************************************************************************************************************/

void getCardExpiryDateTest(void)
{
    ST_cardData_t testCardData;
    uint8_t testerName[50];
    uint8_t expectedCase[50];
    uint8_t iterate = 0;
    char result[30];
    EN_cardError_t returnOfFunction;

    printf("Enter your name:\n");
    fgets(testerName, sizeof(testerName), stdin);

    for (iterate = 0; iterate < 5 ; iterate++)
    {
        returnOfFunction = getCardExpiryDate(testCardData.cardExpirationDate);
        printf("Enter expected result:\n");
        fgets(expectedCase, sizeof(expectedCase), stdin);
        switch (returnOfFunction)
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
            , testerName, iterate+1 , inputFromUser, expectedCase, result);
    }

}

/*************************************************************************************************************************************/

void getCardPANTest(void)
{
    ST_cardData_t testCardData;
    uint8_t testerName[50];
    uint8_t expectedCase[50];
    char result[30];
    EN_cardError_t returnOfFunction;
    uint8_t iterate = 0;


    printf("Enter your name:\n");
    gets(testerName);

    for (iterate = 0 ; iterate < 5 ; iterate++)
    {
        returnOfFunction = getCardPAN(testCardData.primaryAccountNumber);
        
        
        printf("Enter expected result:\n");
        gets(expectedCase);

        switch (returnOfFunction)
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
        printf("\n\nTester Name :%sFunction Name: getCardPAN \nTest case %d:\nInput Data:%s\nExpected result : %s\nActual result: %s\n-----------------\n"
            , testerName, iterate+1, inputFromUser, expectedCase, result);
    }
}

/*************************************************************************************************************************************/
    






