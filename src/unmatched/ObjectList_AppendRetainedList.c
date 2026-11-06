typedef struct R { char pad4[4]; int f4; } R;
typedef struct L { char pad8[8]; int f8; char pad12[4]; R **f16; } L;
int List_AppendWords();
void ObjectList_AppendRetainedList(int arg0, L *arg1) {
    R **data = arg1->f16;
    int cnt = arg1->f8;
    int i;
    R *p;
    for (i = 0; i < cnt; i++) {
        p = data[i];
        if (p != 0) {
            p->f4 = p->f4 + 1;
        }
    }
    List_AppendWords(arg0, arg1->f8, arg1->f16);
}
