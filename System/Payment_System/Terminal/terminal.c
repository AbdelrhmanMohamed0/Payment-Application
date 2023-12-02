#include "terminal.h"
#include <time.h>
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    uint8_t date[11];
    time_t t;                                // not a primitive datatype
    struct tm *tm;                           // a structure to hold the time information
    time(&t);                                // get the current time
    tm = localtime(&t);                      // convert the time to local time
    strftime(date, 11, "%d/%m/%Y", tm);      // format the date string
    strcpy(termData->transactionDate, date); // copy the string to termData->transactionDate
    return TERMINAL_OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
    int32_t cardYear = 2000 + atoi(cardData->cardExpirationDate + 3);
    int32_t cardMonth = atoi(cardData->cardExpirationDate);
    int32_t cardDay = 1; // assume the card expires on the first day of the month
    int32_t transYear, transMonth, transDay;
    sscanf(termData->transactionDate, "%d/%d/%d", &transDay, &transMonth, &transYear);
    if ((cardYear < transYear) || (cardYear == transYear && cardMonth < transMonth))
    {
        return EXPIRED_CARD;
    }
    return TERMINAL_OK;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    f32_t amount;
    printf("Enter transaction amount: ");

    scanf("%f", &amount);
    if (amount <= 0)
    {
        return INVALID_AMOUNT;
    }
    termData->transAmount = amount;
    return TERMINAL_OK;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, f32_t maxAmount)
{
    if (maxAmount <= 0|| maxAmount >MAX_AMOUNT)
    {
        return INVALID_MAX_AMOUNT;
    }
    termData->maxTransAmount = maxAmount;
    return TERMINAL_OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    if (termData->transAmount > termData->maxTransAmount)
    {
        return EXCEED_MAX_AMOUNT;
    }
    return TERMINAL_OK;
}

EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData)
{
    int32_t sum = 0;
    int8_t alternate = 0;
    int8_t len = strlen(cardData->primaryAccountNumber);
    for (int32_t i = len - 1; i >= 0; i--)
    {
        if (cardData->primaryAccountNumber[i] == '\0')
        {
            continue;
        }
        if (cardData->primaryAccountNumber[i] < '0' || cardData->primaryAccountNumber[i] > '9')
        {
            return WRONG_PAN;
        }
        int32_t digit = cardData->primaryAccountNumber[i] - '0';
        if (alternate)
        {
            digit *= 2;
            if (digit > 9)
            {
                digit -= 9;
            }
        }
        sum += digit;
        alternate = !alternate;
    }
    if (sum % 10 != 0)
    {
        return INVALID_CARD;
    }
    return TERMINAL_OK;
}
