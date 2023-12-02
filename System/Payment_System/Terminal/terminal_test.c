
#include "terminal.h"
#define TEST_CASES_NUM 3

ST_cardData_t cardData;
ST_terminalData_t termData;

void getTransactionDateTest(void);
void isCardExpiredTest(void);
void getTransactionAmountTest(void);
void isBelowMaxAmountTest(void);
void setMaxAmountTest(void);
void isValidCardPANTest(void);

int main(void){
    getTransactionDateTest();
    isCardExpiredTest();
    getTransactionAmountTest();
    isBelowMaxAmountTest();
    setMaxAmountTest();
    isValidCardPANTest();
    return 0;
}

void getTransactionDateTest(void){
    printf("Tester Name: Abdelrhman Mohamed\n");
    printf("Function Name: getTransactionDate()\n");
    EN_terminalError_t error = getTransactionDate(&termData);
    printf("Input Data: 28/11/2023\n");
    printf("Expected Result: %d\n", TERMINAL_OK);
    printf("Actual Result: %d\n", error);
}

void isCardExpiredTest(void){
    strcpy(cardData.cardExpirationDate, "08/24");
    printf("\nTester Name: Abdelrhman Mohamed\n");
    printf("Function Name: isCardExpired()\n");
    for(int i=1; i<TEST_CASES_NUM; i++){
        printf("Test Case %d:\n", i);
        EN_terminalError_t error; 
        switch(i){
            case 1:
                strcpy(termData.transactionDate, "15/08/2022");
                error = isCardExpired(&cardData, &termData);
                printf("Input Data: %s\n", termData.transactionDate);
                printf("Expected Result: %d\n", TERMINAL_OK);
                printf("Actual Result: %d\n", error); 
                break;
            case 2:
                strcpy(termData.transactionDate, "20/11/2024");
                error = isCardExpired(&cardData, &termData);
                printf("Input Data: %s\n", termData.transactionDate);
                printf("Expected Result: %d\n", EXPIRED_CARD);
                printf("Actual Result: %d\n", error);
                break;
        }
    }
}

void getTransactionAmountTest(void){
    printf("\nTester Name: Abdelrhman Mohamed\n");
    printf("Function Name: getTransactionAmount()\n");
    for(int i=1; i<=TEST_CASES_NUM; i++){
        printf("Test Case %d:\n", i);
        EN_terminalError_t error = getTransactionAmount(&termData);
        switch(i){
            case 1:
                printf("Input Data: 0\n");
                printf("Expected Result: %d\n", INVALID_AMOUNT);
                printf("Actual Result: %d\n", error); 
                break;
            case 2:
                printf("Input Data: -100\n");
                printf("Expected Result: %d\n", INVALID_AMOUNT);
                printf("Actual Result: %d\n", error);
                break;
            case 3:
                printf("Input Data: 500.5\n");
                printf("Expected Result: %d\n", TERMINAL_OK);
                printf("Actual Result: %d\n", error);
                break;
        }
    }
}

void isBelowMaxAmountTest(void){
    printf("\nTester Name: Abdelrhman Mohamed\n");
    printf("Function Name: isBelowMaxAmount()\n");
    termData.maxTransAmount = 5000;
    for(int i=1; i<TEST_CASES_NUM; i++){
        printf("Test Case %d:\n", i);
        EN_terminalError_t error;
        switch(i){
            case 1:
                termData.transAmount = 8000;
                error = isBelowMaxAmount(&termData);
                printf("Input Data: %.2f\n", termData.transAmount);
                printf("Expected Result: %d\n", EXCEED_MAX_AMOUNT);
                printf("Actual Result: %d\n", error); 
                break;
            case 2:
                termData.transAmount = 1000;
                error = isBelowMaxAmount(&termData);
                printf("Input Data: %.2f\n", termData.transAmount);
                printf("Expected Result: %d\n", TERMINAL_OK);
                printf("Actual Result: %d\n", error);
                break;
        }
    }
}

void setMaxAmountTest(void){
    printf("\nTester Name: Abdelrhman Mohamed\n");
    printf("Function Name: setMaxAmount()\n");
    EN_terminalError_t error;
    for(int i=1; i<=TEST_CASES_NUM; i++){
        printf("Test Case %d:\n", i);
        switch(i){
            case 1:
                printf("Input Data: 0\n");
                error = setMaxAmount(&termData, 0);
                printf("Expected Result: %d\n", INVALID_MAX_AMOUNT);
                printf("Actual Result: %d\n", error); 
                break;
            case 2:
                printf("Input Data: -0.5\n");
                error = setMaxAmount(&termData, -100);
                printf("Expected Result: %d\n", INVALID_MAX_AMOUNT);
                printf("Actual Result: %d\n", error);
                break;
            case 3:
                printf("Input Data: 1000\n");
                error = setMaxAmount(&termData, 1000);
                printf("Expected Result: %d\n", TERMINAL_OK);
                printf("Actual Result: %d\n", error);
                break;
        }
    }
}

void isValidCardPANTest(void){
    printf("\nTester Name: Abdelrhman Mohamed\n");
    printf("Function Name: isValidCardPAN()\n");
    EN_terminalError_t error;
    for(int i=1; i<TEST_CASES_NUM; i++){
        printf("Test Case %d:\n", i);
        switch(i){
            case 1:
                strcpy(cardData.primaryAccountNumber, "159874563258741369");
                error = isValidCardPAN(&cardData);
                printf("Input Data: %s\n", cardData.primaryAccountNumber);
                printf("Expected Result: %d\n", INVALID_CARD);
                printf("Actual Result: %d\n", error); 
                break;
            case 2:
                strcpy(cardData.primaryAccountNumber, "150281306615902503");
                error = isValidCardPAN(&cardData);
                printf("Input Data: %s\n", cardData.primaryAccountNumber);
                printf("Expected Result: %d\n", TERMINAL_OK);
                printf("Actual Result: %d\n", error);
                break;
        }
    }
}