#ifndef GLOBAL_GLOBAL_H_
#define GLOBAL_GLOBAL_H_
#include"../../Payment_System/Server/server.h"
typedef union {
    ST_transaction_t transactionData;
    ST_accountsDB_t accountData;
    }DataType;

#define ELEMENT_TYPE DataType // Type of elements in the LIST
#endif /* SYSTEM_2_DATA_STRUCTURES_GLOBAL_GLOBAL_H_ */
