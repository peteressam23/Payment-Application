#include "terminal.h"

// Function Implementations

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    //Transaction date format -> 10 digits  (29/09/2023).
    time_t currentTime;
    struct tm localTime;
    uint8_t inputLen;
    uint8_t iterate = 0;
    uint8_t dateString[11];  // "DD/MM/YYYY" plus null terminator.
    *inputFromUser = ' ';

    //Error state with initial state as TERMINAL_OK.
    EN_terminalError_t errorStateTransactionDate = TERMINAL_OK;

    // Get the current time
    time(&currentTime);
    // Convert to local time
    localtime_s(&localTime, &currentTime);
    //store Date in dateString variable 
    sprintf_s(dateString, sizeof(dateString), "%02d/%02d/%04d", localTime.tm_mday, localTime.tm_mon + 1, localTime.tm_year + 1900);
    printf("system date %s \n" , dateString);


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

     //printf("Wrong transaction date - Use system date ");
     strcpy_s(termData->transactionDate, sizeof(termData->transactionDate) ,dateString);
         
     //return error state
     return errorStateTransactionDate;
}


EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
    EN_terminalError_t errorStateCardExpired = TERMINAL_OK;
    uint8_t* endptr;

    //convert string to long integer using strtol and casting its return to uint8_t
    long expMonth = strtol(cardData->cardExpirationDate, &endptr, 10);
    long expYear = strtol(&cardData->cardExpirationDate[3], &endptr, 10);
    long transactionMonth = strtol(&termData->transactionDate[3], &endptr, 10);
    long transactionYear = strtol(&termData->transactionDate[8], &endptr, 10);
   
    //Check if the expiry year is larger than year of transaction date so it's not expired
    if (expYear > transactionYear)
    {
        errorStateCardExpired = TERMINAL_OK;
    }
    else if (expYear == transactionYear)
    {
        //If the years are the same compare the months
        if (expMonth >= transactionMonth)
        {
            errorStateCardExpired = TERMINAL_OK;
        }else {
            errorStateCardExpired = EXPIRED_CARD ;
        }
    }
    else
    {
        errorStateCardExpired = EXPIRED_CARD;
    }
    
    return errorStateCardExpired;
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
    EN_terminalError_t errorStateMaxAmount;

    /*Make This With Initial Value*/
    termData->maxTransAmount;

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
    ST_terminalData_t testTerminalData;
    uint8_t testerName[50]; 
    uint8_t expectedCase[50]; 
    uint8_t iterate = 0; 
    uint8_t result[30]; 
    EN_terminalError_t returnOfFunction;

    printf("\n\nTester Name: ");
    fgets(testerName, sizeof(testerName), stdin);

    for (iterate = 0 ; iterate < 5 ; iterate++)
    {
        returnOfFunction = getTransactionDate(&testTerminalData);

        printf("Expected Result:");
        fgets(expectedCase, sizeof(expectedCase), stdin);
        
        switch (returnOfFunction)
        {
        case 0:
            strcpy_s(result, 30, "TERMINAL_OK");
            break;
        case 1:
            strcpy_s(result, 30, "WRONG_DATE");
            break;
        default:
            strcpy_s(result, 30, "undefined ");
            break;
        }

        printf("____________________________________\n");
        printf("\nTester Name: %s\n", testerName);
        printf("Function Name: getTransactionDate\n");
        printf("Test case %d:\n", iterate + 1);
        printf("Input Data: %s\n", inputFromUser);
        printf("Expected Result: %s", expectedCase);
        printf("Actual Result: %s\n", result);
        printf("____________________________________\n\n");
    }
}

/********************************************************************************************************************************/

void isCardExpriedTest(void)
{
    ST_terminalData_t testTerminalData;
    ST_cardData_t testCardData;
    uint8_t testerName[50];
    uint8_t expectedCase[50];
    uint8_t iterate = 0;
    uint8_t result[30];
    EN_cardError_t returnOfFunction;
    
    printf("\n\nTester Name: ");
    fgets(testerName, sizeof(testerName), stdin);

    getTransactionDate(&testTerminalData);

    for (iterate = 0; iterate < 5; iterate++)
    {
        // Remove trailing newline character, if present
        size_t nameLength = strlen(testerName);
        if (nameLength > 0 && testerName[nameLength - 1] == '\n')
        {
            testerName[nameLength - 1] = '\0';
        }

        returnOfFunction = getCardExpiryDate(&testCardData);

        printf("Expected Result:");
        fgets(expectedCase, sizeof(expectedCase), stdin);

        if(returnOfFunction == 0) //0 refer to card is okay
        { 
            switch (isCardExpired(&testCardData, &testTerminalData))
            {
            case 0:
                strcpy_s(result, 30, "TERMINAL_OK");
                break;

            case 2:
                strcpy_s(result, 30, "EXPIRED_CARD");
                break;

            default:
                strcpy_s(result, 30, "undefined Error");
                break;
            }

            printf("____________________________________\n");
            printf("\nTester Name: %s\n", testerName);
            printf("Function Name: isCardExpired\n");
            printf("Test case %d:\n", iterate + 1);
            printf("Input Data:(%s)&(%s)\n", testTerminalData.transactionDate, inputFromUser);
            printf("Expected Result: %s\n", expectedCase);
            printf("Actual Result: %s\n", result);
            printf("____________________________________\n\n");
            continue;
        } 

        printf("____________________________________\n");
        printf("\nTester Name: %s\n", testerName);
        printf("Function Name: isCardExpired\n");
        printf("Test case %d:\n", iterate + 1);
        printf("Input Data:(%s)&(%s)\n", testTerminalData.transactionDate, inputFromUser);
        printf("Expected Result: %s", expectedCase);
        printf("Actual Result: Wrong Expiry Date\n");
        printf("____________________________________\n\n");
    }
}

/********************************************************************************************************************************/

void getTransactionAmountTest(void)
{
    ST_terminalData_t testTerminalData;
    uint8_t testerName[50];
    uint8_t expectedCase[50];
    uint8_t iterate = 0;
    uint8_t result[30];
    EN_terminalError_t returnOfFunction;

    printf("\n\nTester Name: ");
    fgets(testerName, sizeof(testerName), stdin);

    for (iterate = 0; iterate < 5; iterate++)
    {
        returnOfFunction = getTransactionAmount(&testTerminalData);

        printf("Expected Result:");
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

        printf("____________________________________\n");
        printf("\nTester Name: %s", testerName);
        printf("Function Name: getTransactionAmount\n");
        printf("Test case %d:\n", iterate + 1);
        printf("Input Data: %s",inputFromUser);
        printf("Expected Result: %s", expectedCase);
        printf("Actual Result: %s\n", result);
        printf("____________________________________\n\n");
    }
}

/********************************************************************************************************************************/

void isBelowMaxAmountTest(void) 
{	
	ST_terminalData_t testTerminalData;
	testTerminalData.maxTransAmount = 50000;   //Set maxTransAmount for testing.
    uint8_t testerName[50];
    uint8_t expectedCase[50];
    uint8_t iterate = 0;
    uint8_t result[30];
    EN_terminalError_t returnOfFunction;

	
    printf("\n\nTester Name: ");
	fgets(testerName, sizeof(testerName), stdin);
	
	for ( iterate ; iterate < 3; iterate++) 
	{
	    returnOfFunction = getTransactionAmount(&testTerminalData);
		
        printf("Expected Result:");
		fgets(expectedCase, sizeof(expectedCase), stdin);

        if(returnOfFunction == 0)
        {
            switch (isBelowMaxAmount(&testTerminalData))
            {
            case 0:
                strcpy_s(result, 30, "TERMINAL_OK");
                break;
            case 5:
                strcpy_s(result, 30, "EXCEED_MAX_AMOUNT");
                break;
            default:
                strcpy_s(result, 30, "undefined Error");
                break;
            }
        }
        else
        {
            strcpy_s(result, 30, "INVALID_AMOUNT");
        }
        printf("____________________________________\n");
        printf("\nTester Name: %s", testerName);
        printf("Function Name: isBelowMaxAmount\n");
        printf("Test case %d:\n", iterate + 1);
        printf("Input Data: %s", inputFromUser);
        printf("Expected Result: %s\n", expectedCase);
        printf("Actual Result: %s\n", result);
        printf("____________________________________\n\n");	
	}
}

/********************************************************************************************************************************/

void setMaxAmountTest(void) 
{
    ST_terminalData_t testTerminalData;
    uint8_t testerName[50];
    uint8_t expectedCase[50];
    uint8_t iterate = 1;
    char result[30];
    float maxAmountTest;
    EN_terminalError_t returnOfFunction;


    printf("\n\nTester Name: ");
    fgets(testerName, sizeof(testerName), stdin);

    for ( iterate = 1; iterate < 4; iterate++) 
    {
        printf("Enter transaction max amount: ");
        scanf_s("%f", &maxAmountTest);

        returnOfFunction = setMaxAmount(&testTerminalData , maxAmountTest);

        printf("Expected Result:");
        fgets(expectedCase, sizeof(expectedCase), stdin);

        // Remove trailing newline character, if present
       
        size_t nameLength = strlen(expectedCase);
        if (nameLength > 0 && expectedCase[nameLength - 1] == '\n')
        {
            expectedCase[nameLength - 1] = '\0';
        }
       
        switch (returnOfFunction)
        {
        case 0:

            strcpy_s(result, 30, "TERMINAL_OK");
            break;
        case 6:
            strcpy_s(result, 30, "INVALID_MAX_AMOUNT");
            break;
        default:
            strcpy_s(result, 30, "undefined Error");
            break;
        }
        printf("\n____________________________________\n");
        printf("\nTester Name: %s", testerName);
        printf("Function Name: setMaxAmountTest\n");
        printf("Test case %d:\n", iterate);
        printf("Input Data: %f\n", maxAmountTest);
        printf("Expected Result: %s\n", expectedCase);
        printf("Actual Result: %s\n", result);
        printf("____________________________________\n\n");
    }
}

/********************************************************************************************************************************/

void isValidCardPANTest(void)
{
    /*Please Write Comments 80% overall*/

}


/********************************************************************************************************************************/
