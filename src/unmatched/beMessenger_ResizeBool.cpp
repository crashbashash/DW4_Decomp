#include "dw4/reflected.h"
extern "C" {
int List_Resize(igBoolList *, int, int);
void beMessenger_ResizeBool(beMessenger *arg0, int arg1);
}
void beMessenger_ResizeBool(beMessenger *arg0, int arg1) {
    igBoolList *temp_a0;
    temp_a0 = (igBoolList *)((beMessengerArgData *)arg0->_argData)->_boolList;
    if (arg1 >= 0) {
        if (arg1 <= temp_a0->_capacity) {
            temp_a0->_count = arg1;
            return;
        }
        List_Resize(temp_a0, arg1, 1);
    }
}
