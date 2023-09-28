
#include "card.h"

// Function Implementations 

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    //Start with card ok state
    EN_cardError_t Error_state = CARD_OK;
    *inputFromUser = ' ';
    //Get card holder name from the user
    printf("\nEnter Card Holder Name: \n");
    fgets(inputFromUser, sizeof(inputFromUser), stdin);

    int inputLen = strlen(inputFromUser);

    //Remove the newline from the holder name
    if (inputFromUser[inputLen - 1] == '\n')
    {
        inputFromUser[inputLen - 1] = 0;
    }
    //Check if the input is null
    if (strlen(inputFromUser) == 0)
    {
        Error_state = WRONG_NAME;
    }
    //Check the length of the name to be min 20 characters
    if (strlen(inputFromUser) < 20)
    {
        Error_state = WRONG_NAME;
    }
    //Check the length of the name to be max 24 characters
    if (strlen(inputFromUser) > 24)
    {
        Error_state = WRONG_NAME;
    }
    //Check if the length is in the acceptable range
    if (strlen(inputFromUser) >= 20 && (strlen(inputFromUser) <= 24))
    {
        //This condition to check if the name is in the right format contains only alphabetic characters and spaces
        for (int i = 0; i < strlen(inputFromUser); i++)
        {
            if (!isalpha(inputFromUser[i]) && !isspace(inputFromUser[i]))
            {
                Error_state = WRONG_NAME;
                break;
            }
        }
    }
    if (Error_state == CARD_OK)
    {
        strcpy_s(cardData->cardHolderName, sizeof(inputFromUser), inputFromUser);
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
    uint8_t iterate = 0;
    uint8_t testerName[50];
    ST_cardData_t testCardData;
    uint8_t expectedCase[50];
    EN_cardError_t expected;
    char result[20];

    //To Get The Name Of Tester
    printf("Tester Name: ");
    fgets(testerName, sizeof(testerName), stdin);

    //Iterations for different test cases
    for (iterate = 1; iterate < 6; iterate++)
    {
        expected = getCardHolderName(testCardData.cardHolderName);
        printf("Expected Result:");
        fgets(expectedCase, sizeof(expectedCase), stdin);
        switch (expected) {

        case 0:
            strcpy_s(result, 20, "CARD_OK");
            break;
        case 1:
            strcpy_s(result, 20, "WRONG_NAME");
            break;
        default:
            strcpy_s(result, 20, "UNDEFINED");
        }
        printf("Tester Name :%sFunction Name: getCardExpiryDate \nTest case %d:\nInput Data:%s\nExpected result:%sActual result: %s\n-----------------------\n"
            , tester_name, iterate, inputFromUser, expected_case, result);


    }
}

void getCardExpiryDateTest(void)
{
    /*Please Write Comments 80% overall*/

}



void getCardPANTest(void)
{
    uint8_t Ittierate;
    uint8_t TesterName[50];
    ST_cardData_t testCardData;
    uint8_t expectedCase[50];

    /*The Name Of Tester*/
    printf("Tester Name: ");
    gets(TesterName);

    /*Print Function Name*/
    printf("Function Name: getCardPAN\n");



    for (Ittierate = 0; Ittierate < 4 ; Ittierate++)
    {
        /*Print Number Of Test Case Then ittierate*/
        printf("Test Case %d :\n", Ittierate + 1);

        switch (getCardPAN(testCardData.primaryAccountNumber))
        {
        case 0:
            printf("Expected Result :");
            gets(expectedCase);
            printf("Expected Result :");
            printf("Actual Result : CARD_OK\n\n");
            break;

        case 3:
            gets(expectedCase);
            printf("Expected Result : %s\n", expectedCase);
            printf("Actual Result : WRONG_PAN\n\n");
            break;

        default:

            break;
        }

        
    }
}

 
    
    






