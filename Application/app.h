#ifndef APP_H
#define APP_H

#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"

#define MAX_AMOUNT 50000.0

uint8_t cardErrorState[4][20] = { {"CARD_OK"}
,                                 {"WRONG_NAME"},
                                  {"WRONG_EXP_DATE"} ,
                                  {"WRONG_PAN"} };


uint8_t terminalErrorState[7][20] = { {"TERMINAL_OK"} ,
                                       {"WRONG_DATE"},
                                      {"EXPIRED_CARD"} ,
                                      {"INVALID_CARD"} ,
                                      {"INVALID_AMOUNT"} , 
                                      {"EXCEED_MAX_AMOUNT"},
                                       {"INVALID_MAX_AMOUNT"} };

uint8_t serverErrorState[6][20] = { {"SERVER_OK"},
                                    {"SAVING_FAILED"}, 
                                    {"TRANSACTION_NOT_FOUND"},
                                    {"ACCOUNT_NOT_FOUND"},
                                    {"LOW_BALANCE"}, 
                                    {"BLOCKED_ACCOUNT"}};





void appStart(void);
EN_cardError_t getCardData(ST_cardData_t* cardData);
EN_terminalError_t getTerminalData(ST_terminalData_t* termData);


#endif /*APP_H*/


