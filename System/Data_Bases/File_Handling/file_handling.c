#include "file_handling.h"

EN_File_Handling_Error_t readTransactionData(List *plist)
{
    FILE *FileTransactionRead;
    FileTransactionRead = fopen("B:\\project\\System\\Data_Bases\\Data\\TransactionData.txt", "r");
    if (FileTransactionRead == NULL)
    {
        perror("Error opening file for reading");
        return File_NOT_OPENED;
    }
    static int j=0;
    int8_t ReadState[40];
    DataType  element;
    while (fscanf(FileTransactionRead, " %25[^,],%20[^,],%6[^,],%f,%f,%11[^,],%40[^,],%d",
    		element.transactionData.cardHolderData.cardHolderName,
			element.transactionData.cardHolderData.primaryAccountNumber,
			element.transactionData.cardHolderData.cardExpirationDate,
           &element.transactionData.terminalData.transAmount,
           &element.transactionData.terminalData.maxTransAmount,
		    element.transactionData.terminalData.transactionDate,
            ReadState,
           &element.transactionData.transactionSequenceNumber) == 8)
    {
        if (strcmp(ReadState, "APPROVED") == 0)
        {
        	element.transactionData.transState = APPROVED;
        }
        else if (strcmp(ReadState, "FRAUD_CARD") == 0)
        {
        	element.transactionData.transState = FRAUD_CARD;
        }
        else if (strcmp(ReadState, "DECLINED_INSUFFICIENT_FUND") == 0)
        {
        	element.transactionData.transState = DECLINED_INSUFFICIENT_FUND;
        }
        else if (strcmp(ReadState, "DECLINED_STOLEN_CARD") == 0)
        {
        	element.transactionData.transState = DECLINED_STOLEN_CARD;
        }

        else if (strcmp(ReadState, "INTERNAL_SERVER_ERROR") == 0)
        {
        	element.transactionData.transState = INTERNAL_SERVER_ERROR;
        }
        insert_list(plist,element,j++);
    }
    fclose(FileTransactionRead);
    return File_OPENED;
}


EN_File_Handling_Error_t readAccountsData(List *plist) {
	FILE *file;
	file = fopen("B:\\project\\System\\Data_Bases\\Data\\AccountsDataa.txt", "r");
	// open file for reading
if (file == NULL)
{
    perror("Error opening file");
    return File_NOT_OPENED;
}
static int i=0;
char readState[9]; // buffer for reading the state
DataType element;
while (fscanf(file, "%19[^,],%f,%25[^,],%19[^,],%8[^\n]\n",
		readState,
        &element.accountData.balance,
		element.accountData.cardHolderName,
		element.accountData.primaryAccountNumber,
		element.accountData.cardExpirationDate) == 5) {
			  int len = strcspn(element.accountData.cardExpirationDate, "\n");
				if (len < 6) {
					element.accountData.cardExpirationDate[len] = '\0';
				}
    if (strcmp(readState, "RUNNING") == 0) {
    	element.accountData.state = RUNNING;
    } else if (strcmp(readState, "BLOCKED") == 0) {
    	element.accountData.state = BLOCKED;
    }
    insert_list(plist,element,i++);
	}
fclose(file); // close the file
return File_OPENED;

}


EN_File_Handling_Error_t writeTransactionData(ST_transaction_t *transData)
{
    FILE *FileTransactionWrite;
    FileTransactionWrite = fopen("B:\\project\\System\\Data_Bases\\Data\\TransactionData.txt", "a");

    if (FileTransactionWrite == NULL)
    {
        perror("Error opening file for writing");
        return File_NOT_OPENED;
    }
    int8_t WriteState[40];
    if (transData->transState == APPROVED)
    {
        strcpy(WriteState, "APPROVED");
    }
    else if (transData->transState == DECLINED_INSUFFICIENT_FUND)
    {
        strcpy(WriteState, "DECLINED_INSUFFICIENT_FUND");
    }
    else if (transData->transState == DECLINED_STOLEN_CARD)
    {
        strcpy(WriteState, "DECLINED_STOLEN_CARD");
    }
    else if (transData->transState == FRAUD_CARD)
    {
        strcpy(WriteState, "FRAUD_CARD");
    }
    else if (transData->transState == INTERNAL_SERVER_ERROR)
    {
        strcpy(WriteState, "INTERNAL_SERVER_ERROR");
    }
    fprintf(FileTransactionWrite, "%s,%s,%s,%.2f,%.2f,%s,%s,%d\n",
            transData->cardHolderData.cardHolderName,
            transData->cardHolderData.primaryAccountNumber,
            transData->cardHolderData.cardExpirationDate,
            transData->terminalData.transAmount,
            transData->terminalData.maxTransAmount,
            transData->terminalData.transactionDate,
            WriteState,
            transData->transactionSequenceNumber);
    fclose(FileTransactionWrite);
    return File_OPENED;
}
// A function that searches for the primary account number in the file and returns the line number
int searchAccountNumber(char *accountNumber)
{
    FILE *fileAccountSearch;
    fileAccountSearch = fopen("B:\\project\\System\\Data_Bases\\Data\\AccountsDataa.txt", "r");

    if (fileAccountSearch == NULL)
    {
        perror("Error opening file for searching");
        return -1;
    }

    // A buffer to store each line in the file
    char buffer[100];

    // A variable to store the line number
    int line = 0;

    // A flag to indicate whether the account number is found or not
    int found = 0;

    // Loop through each line in the file
    while (fgets(buffer, 100, fileAccountSearch) != NULL)
    {
        // Increment the line number
        line++;

        // Check if the account number is in the line
        if (strstr(buffer, accountNumber) != NULL)
        {
            // Set the flag to 1 and break the loop
            found = 1;
            break;
        }
    }

    // Close the file
    fclose(fileAccountSearch);

    // If the account number is found, return the line number
    if (found == 1)
    {
        return line;
    }
    // Otherwise, return -1 to indicate an error
    else
    {
        return -1;
    }
}

// A function that modifies the balance in the file based on the line number
EN_File_Handling_Error_t modifyAccount(int line,ST_accountsDB_t *accountData)
{
    FILE *fileAccountModify;
    fileAccountModify = fopen("B:\\project\\System\\Data_Bases\\Data\\AccountsDataa.txt", "r+");

    if (fileAccountModify == NULL)
    {
        perror("Error opening file for modifying");
        return File_NOT_OPENED;
    }

    // Seek the position of the line
    int count = 0;
    char buffer[100];
    long pos;

    while (fgets(buffer, 100, fileAccountModify) != NULL)
    {
        count++;
        if (count == line)
        {
            // Save the position of the line
            pos = ftell(fileAccountModify);
            break;
        }
    }
    pos = pos - strlen(buffer-1);
    // Seek back to the position of the line
    fseek(fileAccountModify, pos, SEEK_SET);

    // Modify the balance in the line
    int8_t writeState[8];
    if (accountData->state == BLOCKED)
    {
        strcpy(writeState, "BLOCKED");
    }
    else if (accountData->state == RUNNING)
    {
        strcpy(writeState, "RUNNING");
    }

    fprintf(fileAccountModify, "%s,%.2f,%s,%s,%s",
            writeState,
            accountData->balance,
            accountData->cardHolderName,
            accountData->primaryAccountNumber,
            accountData->cardExpirationDate);
    fclose(fileAccountModify);
    return File_OPENED;
}

// A function that calls the above two functions to modify the balance based on the account number
EN_File_Handling_Error_t writeAccountData(ST_accountsDB_t *accountData)
{
    // Search for the account number in the file and get the line number
    int line = searchAccountNumber(accountData->primaryAccountNumber);

    // If the line number is valid, modify the balance in the file
    if (line > 0)
    {
        return modifyAccount(line,accountData);
    }
    // Otherwise, return an error
    else
    {
        return 0;
    }
}
