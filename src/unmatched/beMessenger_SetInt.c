#include "dw4/reflected.h"
void beMessenger_SetInt(beMessenger *arg0, int arg1, int arg2) {
    beMessengerArgData *args = (beMessengerArgData *)arg0->_argData;
    igIntList *a3 = (igIntList *)args->_intList;
    int n = a3->_count;
    if ((n != 0) && (arg1 >= 0) && (arg1 < n)) {
        ((int *)a3->_data)[arg1] = arg2;
    }
}
