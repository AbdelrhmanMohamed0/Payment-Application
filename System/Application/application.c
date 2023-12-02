#include "../Payment_System/Server/server.h"
int main(void)
{

    ST_cardData_t cardData;
    EN_cardError_t cardStatus;

    ST_terminalData_t termData;
    EN_terminalError_t terminalStatus;

    ST_transaction_t transactionData;
    EN_transState_t   state;

while(1){
    printf("Welcome to our payment application\n");


    for (int counter = 1; counter <= 3; counter++)
    {
        cardStatus = getCardHolderName(&cardData);
        if (cardStatus == WRONG_NAME)
        {
            printf("The name should be from 20 to 24 characters\n");
        }
        else
        {
            break;
        }
    }
    if (cardStatus == WRONG_NAME)
    {
        printf("You have reached your max tries\n");
        return 0;
    }


    for (int counter = 1; counter <= 3; counter++)
    {
        cardStatus = getCardPAN(&cardData);
        if (cardStatus == WRONG_PAN)
        {
            printf("The PAN should range from 16 to 19 digits\n");
        }
        else
        {
            break;
        }
    }
    if (cardStatus == WRONG_PAN)
    {
        printf("You have reached your max tries\n");
        return 0;
    }


    for (int counter = 1; counter <= 3; counter++)
    {
        cardStatus = getCardExpiryDate(&cardData);
        if (cardStatus == WRONG_EXP_DATE)
        {
            printf("The card expiry date  should be like this (MM/YY)\n");
        }
        else
        {
            break;
        }
    }
    if (cardStatus == WRONG_EXP_DATE)
    {
        printf("You have reached your max tries\n");
        return 0;
    }


    terminalStatus = isValidCardPAN(&cardData);
    if (terminalStatus == INVALID_CARD)
    {
        printf("Invalid PAN\n");
        return 0;
    }


    for (int counter = 1; counter <= 3; counter++)
    {
        terminalStatus = getTransactionDate(&termData);
        if (terminalStatus == WRONG_DATE)
        {
            printf("Wrong Date\n");
        }
        else
        {
            break;
        }
    }
    if (terminalStatus == WRONG_DATE)
    {
        printf("You have reached your max tries\n");
        return 0;
    }


    terminalStatus = isCardExpired(&cardData, &termData);
    {
        if (terminalStatus == EXPIRED_CARD)
        {
        	printf("EXPIRED_CARD\n");
            return 0;
        }
    }


    f32_t maxAmount = 0;
    for (int counter = 1; counter <= 3; counter++)
    {
        printf("please enter Max Amount \n");
        scanf("%f", &maxAmount);
        terminalStatus = setMaxAmount(&termData, maxAmount);
        if (terminalStatus == INVALID_MAX_AMOUNT)
        {
            printf("INVALID_MAX_AMOUNT");
        }
        else
        {
            break;
        }
    }
    if (terminalStatus == INVALID_MAX_AMOUNT)
    {
        printf("You have reached your max tries\n");
        return 0;
    }


    for (int counter = 1; counter <= 3; counter++)
    {
        terminalStatus = getTransactionAmount(&termData);
        if (terminalStatus == INVALID_AMOUNT)
        {
            printf("Invalid amount\n");
        }
        else
        {
            break;
        }
    }
    if (terminalStatus == INVALID_AMOUNT)
    {
        printf("You have reached your max tries\n");
        return 0;
    }


    terminalStatus = isBelowMaxAmount(&termData);
    if (terminalStatus == EXCEED_MAX_AMOUNT)
    {
        printf("Exceeded max amount\n");
        return 0;
    }


    transactionData.cardHolderData = cardData;
    transactionData.terminalData = termData;

    state=receiveTransactionData(&transactionData);
        switch(state){
        case APPROVED:
        	printf("Approved \n");
            break;
        case DECLINED_INSUFFICIENT_FUND:
        	printf("DECLINED_INSUFFICIENT_FUND \n");
            break;
        case DECLINED_STOLEN_CARD:
        	printf("DECLINED_STOLEN_CARD \n");
            break;
        case FRAUD_CARD:
        	printf("FRAUD_CARD \n");
            break;
        case INTERNAL_SERVER_ERROR:
        	printf("INTERNAL_SERVER_ERROR \n");
            break;
        default:
        	printf("UNKNOWN \n");
            break;
    }
}
    return 0;

}
