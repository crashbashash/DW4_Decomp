/* Struct member access and the forwarded receiver argument; verified by tools/verify.py. */
typedef struct L { char pad[8]; int count; int cap; int *data; } L;
int memcpy();
int List_Resize();

void List_AppendWords(L *arg0, int arg1, int arg2) {
    int temp_a1;
    int temp_s0;

    if ((arg1 >= 0) && (arg1 != 0)) {
        temp_s0 = arg0->count;
        temp_a1 = temp_s0 + arg1;
        if (temp_a1 <= arg0->cap) {
            arg0->count = temp_a1;
        } else {
            List_Resize(arg0, temp_a1, 4);
        }
        memcpy(arg0->data + temp_s0, arg2, arg1 * 4);
    }
}
