#ifndef FILEHANDLING_H_
#define FILEHANDLING_H_
#include "../../Data_Structures/List/list.h"
typedef enum 
{
    File_OPENED,
    File_NOT_OPENED
} EN_File_Handling_Error_t;

EN_File_Handling_Error_t readTransactionData(List *plist);
EN_File_Handling_Error_t readAccountsData(List *plist);
EN_File_Handling_Error_t writeTransactionData(ST_transaction_t *transData);
EN_File_Handling_Error_t writeAccountData(ST_accountsDB_t *accountData);
EN_File_Handling_Error_t modifyAccount(int line,ST_accountsDB_t *accountData);
int searchAccountNumber(char *accountNumber);
#endif
