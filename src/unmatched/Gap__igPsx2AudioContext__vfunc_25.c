#include "dw4/reflected.h"

void FUN_0032d9b0(int *result, igObject *connection, int command, int wait);
int igObject_Destroy(igObject *object);
void FUN_00300f50(igPsx2AudioContext *context, int memory);

void Gap__igPsx2AudioContext__vfunc_25(igPsx2AudioContext *context) {
    igObject *connection;
    int result;

    if (context->_connection != 0) {
        FUN_0032d9b0(&result, (igObject *)context->_connection, 0x30000, 1);
        connection = (igObject *)context->_connection;
        if (connection != 0) {
            connection->_refCount = connection->_refCount - 1;
            if ((connection->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(connection);
            }
        }
        context->_connection = 0;
    }
    if (context->_batchMemory != 0) {
        FUN_00300f50(context, context->_batchMemory);
        context->_batchMemory = 0;
    }
}
