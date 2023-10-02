
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
    printf("Enter Card Holder Name: ");
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
    //Check the length of the name to be min 20 and max 24 characters
    if (strlen(inputFromUser) < 20 || strlen(inputFromUser) > 24)
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
        //To store the input only if it is right
        strcpy_s(cardData->cardHolderName, sizeof(inputFromUser), inputFromUser);
    }
    return errorStateHolderName;
}

/*************************************************************************************************************************************/


EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
     uint8_t inputLen;
     EN_cardError_t errorStateExpireDate = WRONG_EXP_DATE;
     *inputFromUser = ' ';
     uint8_t iterate = 0;

     //Get the expiration date from user
     printf("Enter Card Expiry Date: the format (MM/YY), e.g (05/25): ");
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
         errorStateExpireDate = CARD_OK;
     }

     //Check the format
     for(iterate = 0 ; iterate < 5 ; iterate++)
     {
        if( (isdigit(inputFromUser[iterate])) == 0  && iterate != 2  )
        {
            errorStateExpireDate = CARD_OK;
        }
        if(iterate == 2 && inputFromUser[iterate] != 47)
        {
            errorStateExpireDate = CARD_OK;
        }
     }

     //Check the return status
     if(errorStateExpireDate == CARD_OK)
     {
         errorStateExpireDate = WRONG_EXP_DATE;
        
     }
     else
     {
       strcpy_s(cardData->cardExpirationDate , sizeof(inputFromUser) , inputFromUser );
       errorStateExpireDate =  CARD_OK;
     }
     return errorStateExpireDate;
}

/*************************************************************************************************************************************/

EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    /*To Make Error State For PAN And Return This Error State*/
    EN_cardError_t ErrorStatePAN = CARD_OK;
    *inputFromUser = ' ';
    uint8_t iterate = 0;

    printf("Enter Primary Account Number: ");
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
    uint8_t result[30];

    //To Get The Name Of Tester
    printf("\n\nTester Name: ");
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

        printf("____________________________________\n");
        printf("\nTester Name: %s\n", testerName);
        printf("Function Name: getCardHolderName\n");
        printf("Test case %d:\n" , iterate);
        printf("Input Data: %s\n", inputFromUser);
        printf("Expected Result: %s", expectedCase);
        printf("Actual Result: %s\n", result);
        printf("____________________________________\n\n");
    }
}

/*************************************************************************************************************************************/
void getCardExpiryDateTest(void)
{
    ST_cardData_t testCardData;
    uint8_t testerName[50];
    uint8_t expectedCase[50];
    uint8_t iterate = 0;
    uint8_t result[30];
    EN_cardError_t returnOfFunction;

    printf("\n\nTester Name: ");
    fgets(testerName, sizeof(testerName), stdin);

    for (iterate = 0; iterate < 5 ; iterate++)
    {
        returnOfFunction = getCardExpiryDate(testCardData.cardExpirationDate);
        printf("Expected Result:");
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


        printf("____________________________________\n");
        printf("\nTester Name: %s\n", testerName);
        printf("Function Name: getCardExpiryDate\n");
        printf("Test case %d:\n", iterate+1);
        printf("Input Data: %s\n", inputFromUser);
        printf("Expected Result: %s", expectedCase);
        printf("Actual Result: %s\n", result);
        printf("____________________________________\n\n");

    }
}

/*************************************************************************************************************************************/

void getCardPANTest(void)
{
    ST_cardData_t testCardData;
    uint8_t testerName[50];
    uint8_t expectedCase[50];
    uint8_t result[30];
    EN_cardError_t returnOfFunction;
    uint8_t iterate = 0;


    printf("\n\nTester Name: ");
    gets(testerName);

    for (iterate = 0 ; iterate < 5 ; iterate++)
    {
        returnOfFunction = getCardPAN(testCardData.primaryAccountNumber);
        
        printf("Expected Result:");
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

        printf("____________________________________\n");
        printf("\nTester Name: %s\n", testerName);
        printf("Function Name: getCardPAN\n");
        printf("Test case %d:\n", iterate + 1);
        printf("Input Data: %s\n", inputFromUser);
        printf("Expected Result: %s\n", expectedCase);
        printf("Actual Result: %s\n", result);
        printf("____________________________________\n\n");
    }
}

/*************************************************************************************************************************************/
    






