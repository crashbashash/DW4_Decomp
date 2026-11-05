#include "dw4/reflected.h"
extern "C" {
int List_Resize(igLongList *, int, int);
void beMessenger_AppendLong(beMessenger *arg0, long long arg1);
}
void beMessenger_AppendLong(beMessenger *arg0, long long arg1) {
    int temp_s2;
    beMessengerArgData *args;
    igLongList *temp_s1;

    args = (beMessengerArgData *)arg0->_argData;
    temp_s1 = (igLongList *)args->_longList;
    temp_s2 = temp_s1->_count;
    if (temp_s2 < temp_s1->_capacity) {
        temp_s1->_count = temp_s2 + 1;
    } else {
        List_Resize(temp_s1, temp_s2 + 1, 8);
    }
    ((long long *)temp_s1->_data)[temp_s2] = arg1;
}
