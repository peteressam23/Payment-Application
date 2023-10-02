#include "app.h"

int main()
{
	appStart();

	return 0;
}








/*Start The Application*/
void appStart(void) 
{
	printf("\t\t------------------------------------------------------------------------------\n");
	printf("\t\t\t\t\tWelcome In Payment Application\t\t\t\t\t\t\n");
	printf("\t\t-------------------------------------------------------------------------------\n");

	ST_transaction_t transaction;
	uint32_t errorState = 0;
	/*If Error State Not equal Card Ok make in if Condition*/
	errorState = getCardData(&transaction.cardHolderData);
	if (errorState != 0) 
	{
		printf("CARD ERROR: %s\n", cardErrorState[errorState]);
		printf("Card DECLINED");
		return;
	}
	/*If Error State Not equal Terminal Ok make in if Condition*/
	errorState = getTerminalData(&transaction.terminalData);
	if (errorState != 0) 
	{
		printf("Terminal ERROR: %s\n", terminalErrorState[errorState]);
		printf("Transaction DECLINED");
		return;
	}
	/*If Error State  equal EXPIRED CARD make in if Condition*/
	if (isCardExpired(&transaction.cardHolderData, &transaction.terminalData) == 2) 
	{
		printf("CARD_ERROR: %s\n", cardErrorState[EXPIRED_CARD]);
		printf("Card DECLINED");
		return;
	}
	/*Choose From List After Know The Return Of Function */
	switch (recieveTransactionData(&transaction))
	{
	case 0:
		printf(" APPROVED");
		break;
	case 1:
		printf("DECLINED_INSUFFECIENT_FUND");
		break;
	case 2:
		printf("DECLINED_STOLEN_CARD");
		break;
	case 3:
		printf("FRAUD CARD");
		break;
	case 4:
		printf("INTERNAL SERVER ERROR");
		break;
	default:
		printf("UNDEFIEND ERROR");
		break;
	}
}

/*To Get All Data In Card*/
EN_cardError_t getCardData(ST_cardData_t* cardData) 
{
	if (getCardHolderName(cardData) == 1) return WRONG_NAME;
	if (getCardExpiryDate(cardData) == 2) return WRONG_EXP_DATE;
	if (getCardPAN(cardData) == 3) return WRONG_PAN;
	return CARD_OK;
}

/*To Get All Data In Terminal*/
EN_terminalError_t getTerminalData(ST_terminalData_t* termData) 
{
	getTransactionDate(termData);
	if (getTransactionAmount(termData) == 4) return INVALID_AMOUNT;
	if (setMaxAmount(termData, MAX_AMOUNT) == 6) return INVALID_MAX_AMOUNT;
	if (isBelowMaxAmount(termData) == 5) return EXCEED_MAX_AMOUNT;
	return TERMINAL_OK;
}


