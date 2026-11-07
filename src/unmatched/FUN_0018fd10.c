typedef struct ListSlotArrayView { int pad[2]; int count; int cap; int *data; } ListSlotArrayView;
extern ListSlotArrayView *DAT_00561130[4];
void FUN_0018fd10(int *arg0, int arg1) {
    ListSlotArrayView *list = DAT_00561130[0];
    int i = arg0[2];
    if (list->count != 0 && i >= 0 && i < list->count) {
        list->data[i] = arg1;
    }
}
