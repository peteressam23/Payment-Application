#include "terminal.h"

// Function Implementations

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{ //Transaction date format -> 10 digits  (29/09/2023).
    /*Nadeen*/
    time_t currentTime;
    struct tm *timeInfo;
    uint8_t inputLen;
    uint8_t iterate = 0;
    uint8_t dateString[11];  // "DD/MM/YYYY" plus null terminator.
    *inputFromUser = ' ';

    //Error state with initial state as TERMINAL_OK.
    EN_terminalError_t errorStateTransactionDate = TERMINAL_OK;

    //Save the system date in dateString Variable.
    time(&currentTime);
    localtime_s(&timeInfo, &currentTime);
    strftime(dateString, sizeof(dateString), "%d/%m/%Y", &timeInfo);


    //Get the transaction date from user
     printf("Enter the transaction date in a this format , e.g (DD/MM/YYYY) : ");
     fgets(inputFromUser , sizeof(inputFromUser) , stdin);
     inputLen = strlen(inputFromUser);

     //Remove the newline from InputExp to calculate the length.
     if(inputFromUser[inputLen-1] == '\n')
     {
        inputFromUser[inputLen-1] = 0;
     }

     //Checking the length of inputFromUser.
     if( strlen(inputFromUser) != 10 || inputFromUser == NULL)
     {
         errorStateTransactionDate = WRONG_DATE;
     }

     //Checking the format.
     for(iterate ; iterate < strlen(inputFromUser) ; iterate++)
     {
         // iterate = 2 or 5 that the '/'
         if( (isdigit(inputFromUser[iterate])) == 0  && iterate != 2 && iterate != 5 )
         {
             errorStateTransactionDate = WRONG_DATE;
         }
          if((iterate == 2 || iterate == 5 )&& inputFromUser[iterate] != 47)
        {
            errorStateTransactionDate = WRONG_DATE;
        }
     }

     //Check error state to return the correct error
     if (errorStateTransactionDate == WRONG_DATE )
     {
         printf("Wrong transaction date - Use system date ");
         strcpy_s(termData->transactionDate, sizeof(termData->transactionDate) ,asctime(&timeInfo));
         return errorStateTransactionDate;

     }
     else if (errorStateTransactionDate == TERMINAL_OK )
     {
         strcpy_s(termData->transactionDate, sizeof(termData->transactionDate), inputFromUser);
	     return TERMINAL_OK;
     }

}

/********************************************************************************************************************************/

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
    /*Please Write Comments 80% overall*/
}


EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    *inputFromUser = 0;
    /*This is The Error State To Return In The End Of Function*/
    EN_terminalError_t errorStateTransactionAmount = INVALID_AMOUNT;
    uint8_t iterate = 0;
    uint8_t* storeFirstInvalidChar;

    /*Ask User To Input Amount Transaction*/
    printf("Enter The Transaction Amount: ");
    fgets(inputFromUser, sizeof(inputFromUser), stdin);

    /*Check The User Input Is Numbers Only and Not Spaces*/
    for (iterate = 0; iterate < strlen(inputFromUser) - 1; iterate++)
    {
        if (isdigit(inputFromUser[iterate]))
        {
            errorStateTransactionAmount = TERMINAL_OK;
        }
        if (isspace(inputFromUser[iterate]) && inputFromUser[iterate] != '.')
        {
            errorStateTransactionAmount = INVALID_AMOUNT;
            break;
        }
    }
    /*
    The &storeFirstInvalidChar argument is used to store the address of the first invalid character
    encountered during the conversion. After the conversion,
    storeFirstInvalidChar will point to the first character
    that couldn't be converted to a float.
    This can be useful if you need to check for errors
    or process any remaining characters in the input string that were not converted.
    */
    termData->transAmount = strtof(inputFromUser , & storeFirstInvalidChar);

    if (termData->transAmount <= 0)
    {
        errorStateTransactionAmount =  INVALID_AMOUNT;
    }

    return errorStateTransactionAmount;
}

/********************************************************************************************************************************/


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    EN_terminalError_t errorStateBelwMax = TERMINAL_OK;
   if(termData->transAmount > termData->maxTransAmount )
   {
       // transaction amount is larger than the terminal max allowed amount
       errorStateBelwMax = EXCEED_MAX_AMOUNT;
   }
   return errorStateBelwMax;

}

/********************************************************************************************************************************/


EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount)
{
    /*This is The Error State To Return In The End Of Function*/
    EN_terminalError_t errorStateMaxAmount = INVALID_MAX_AMOUNT;

    /*Make This With Initial Value*/
    termData->maxTransAmount = 0;

    /*Check If Max Amount Less Than 0 Or Equal*/
    if (maxAmount <= 0)
    {
        errorStateMaxAmount = INVALID_MAX_AMOUNT;
    }
    else
    {
        errorStateMaxAmount = TERMINAL_OK;
    }
    termData->maxTransAmount = maxAmount;
    return errorStateMaxAmount;
}

/********************************************************************************************************************************/

EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData)// Optional
{
    /*Please Write Comments 80% overall*/

}


/********************************************************************************************************************************/

//Test Functions for terminal
void getTransactionDateTest(void)
{
    /*Please Write Comments 80% overall*/

}

/********************************************************************************************************************************/

void isCardExpriedTest(void)
{
    /*Please Write Comments 80% overall*/


}


/********************************************************************************************************************************/



void getTransactionAmountTest(void)
{
    ST_terminalData_t testTerminalData;
    uint8_t testerName[50];
    uint8_t expectedCase[50];
    uint8_t iterate = 0;
    uint8_t result[30];
    EN_cardError_t returnOfFunction;

    printf("Enter your name: ");
    fgets(testerName, sizeof(testerName), stdin);

    for (iterate = 0 ; iterate < 5 ; iterate++)
    {
        returnOfFunction = getTransactionAmount(&testTerminalData);

        printf("Enter expected result: ");
        fgets(expectedCase, sizeof(expectedCase), stdin);


        switch (returnOfFunction)
        {
        case 0:
            strcpy_s(result, 30, "TERMINAL_OK");
            break;
        case 4:
            strcpy_s(result, 30, "INVALID_AMOUNT");
            break;
        default:
            strcpy_s(result, 30, "undefined Error");
            break;
        }

        printf("\n\nTester Name :%sFunction Name: getTransactionAmount \nTest case %d:\nInput Data:%s Expected result:%sActual result: %s\n-----------------\n"
            , testerName, iterate + 1, inputFromUser, expectedCase, result);
    }


}


/********************************************************************************************************************************/


void isBelowMaxAmountTest(void)
{

    /*Please Write Comments 80% overall*/
}

/********************************************************************************************************************************/

void setMaxAmountTest(void)
{
    /*Please Write Comments 80% overall*/












}

/********************************************************************************************************************************/

void isValidCardPANTest(void)
{
    /*Please Write Comments 80% overall*/

}


/********************************************************************************************************************************/
