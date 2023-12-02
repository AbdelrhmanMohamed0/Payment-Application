#include "card.h"
EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    int8_t name[30];
    printf("Enter cardholder name (20-24 alphabetic characters): ");
    fflush(stdin); fflush(stdout);
    gets(name);

    if (name[0] == '\0' || strlen(name) < 20 || strlen(name) > 24)
    {
        return WRONG_NAME;
    }

    strcpy(cardData->cardHolderName, name);
    return CARD_OK;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    int8_t expiryDate[7];
    uint16_t cardMonth , cardYear;
    printf("Enter card expiry date (MM/YY): ");
    fflush(stdin); fflush(stdout);
    gets(expiryDate);

    if (expiryDate[0] == '\0' || strlen(expiryDate) != 5)
    {
        return WRONG_EXP_DATE;
    }
	cardMonth = (expiryDate[0] - '0') * 10 + (expiryDate[1] - '0');
	cardYear  = (expiryDate[3] - '0') * 10 + (expiryDate[4] - '0');
	if ((cardMonth > 12 || cardMonth < 1) || (cardYear < 0 || cardYear > 99))
	{
		return WRONG_EXP_DATE;
	}
    for (int i = 0; i < 5; i++)
    {
        if (i == 2)
        {
            if (expiryDate[i] != '/')
            {
                return WRONG_EXP_DATE;
            }
        }
        else
        {
            if (expiryDate[i] < '0' || expiryDate[i] > '9')
            {
                return WRONG_EXP_DATE;
            }
        }
    }

    strcpy(cardData->cardExpirationDate, expiryDate);
    return CARD_OK;
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    int8_t pan[22];
    printf("Enter card PAN (16-19 numeric characters): ");
    fflush(stdin); fflush(stdout);
    gets(pan);
    if (pan[0] == '\0' || strlen(pan) < 16 || strlen(pan) > 19)
    {
        return WRONG_PAN;
    }

    strcpy(cardData->primaryAccountNumber, pan);
    return CARD_OK;
}
