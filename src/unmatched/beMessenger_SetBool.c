#include "dw4/reflected.h"
void beMessenger_SetBool(beMessenger *arg0, int arg1, char arg2) {
    igBoolList *l = (igBoolList *)((beMessengerArgData *)arg0->_argData)->_boolList;
    int n = l->_count;
    if (n != 0 && arg1 >= 0 && arg1 < n) {
        ((char *)l->_data)[arg1] = arg2;
    }
}
