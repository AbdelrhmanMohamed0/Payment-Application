#include "server.h"
#include "../../Data_Bases/File_Handling/file_handling.h"
ST_accountsDB_t *accountReference;
ST_transaction_t *transaction_Reference;
uint32_t sequenceNum = 1;
int8_t flag = 1;
char  ptr[20];
static List ls1;
static List ls2;
EN_transState_t receiveTransactionData(ST_transaction_t *transData)
{
    if (flag == 1)
    {
        list_init(&ls1);
        list_init(&ls2);
        readAccountsData(&ls1);
        flag = 0;
    }
    accountReference = ls1.head;
    *accountReference = ls1.head->data.accountData;
    if (isValidAccount(&transData->cardHolderData, accountReference))
    {
        transData->transState = FRAUD_CARD;
        return FRAUD_CARD;
    }
    if (isAmountAvailable(&transData->terminalData, accountReference))
    {
        transData->transState = DECLINED_INSUFFICIENT_FUND;
        return DECLINED_INSUFFICIENT_FUND;
    }
    if (isBlockedAccount(accountReference))
    {
        transData->transState = DECLINED_STOLEN_CARD;
        writeAccountData(accountReference);
        return DECLINED_STOLEN_CARD;
    }
    if (SAVING_FAILED == saveTransaction(transData))
    {
        transData->transState = INTERNAL_SERVER_ERROR;
        return INTERNAL_SERVER_ERROR;
    }

    /* Updates the account balance by subtracting the transaction amount */
    accountReference->balance -= transData->terminalData.transAmount;
    transData->transState = APPROVED;
    writeAccountData(accountReference);
    return APPROVED;
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountReference)
{
    int pos = search_list_for_accountData(&ls1, cardData->primaryAccountNumber);
    if (pos != -1)
    {
        retrieve_list(&ls1, accountReference, pos);
        return SERVER_OK;
    }
    return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountReference)
{
    if (accountReference->state == RUNNING)
        return SERVER_OK;
    return BLOCKED_ACCOUNT;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountReference)
{
    if (termData->transAmount > accountReference->balance)
        return LOW_BALANCE;
    return SERVER_OK;
}

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    transData->transactionSequenceNumber = sequenceNum;
    transData->transState = APPROVED;
    writeTransactionData(transData);
    strcpy(ptr,transData->cardHolderData.primaryAccountNumber);
    listSavedTransactions();
    sequenceNum++;
    return SERVER_OK;
}

void listSavedTransactions(void)
{
    readTransactionData(&ls2);
    transaction_Reference = ls2.head;
    int pos = search_list_for_transactionData(&ls2,ptr);
    if (pos != -1)
    {
        retrieve_list(&ls2, transaction_Reference, pos);
        printf("#########################\n");
        printf("Transaction Sequence Number: %ld\n", transaction_Reference->transactionSequenceNumber);
        printf("Transaction Date: %s\n", transaction_Reference->terminalData.transactionDate);
        printf("Transaction Amount: %.2f\n", transaction_Reference->terminalData.transAmount);
        printf("Transaction State: %s\n", "APPROVED");
        printf("Terminal Max Amount: %.2f\n", transaction_Reference->terminalData.maxTransAmount);
        printf("Cardholder Name: %s\n", transaction_Reference->cardHolderData.cardHolderName);
        printf("PAN: %s\n", transaction_Reference->cardHolderData.primaryAccountNumber);
        printf("Card Expiration Date: %s\n", transaction_Reference->cardHolderData.cardExpirationDate);
        printf("#########################\n");
    }
}
