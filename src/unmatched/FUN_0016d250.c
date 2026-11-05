typedef struct Obj { int w0; unsigned refs; } Obj;
int igObject_Destroy();
extern int DAT_005608c4[4];
void FUN_0016d250(int *arg0, Obj *arg1) {
    Obj *o;
    if ((Obj *)arg0[237] == arg1) {
        DAT_005608c4[0] += 1;
    }
    if (arg1) {
        arg1->refs++;
    }
    o = (Obj *)arg0[237];
    if (o != 0) {
        --o->refs;
        if ((o->refs & 0x7fffff) == 0) {
            igObject_Destroy(o);
        }
    }
    arg0[237] = (int)arg1;
}
