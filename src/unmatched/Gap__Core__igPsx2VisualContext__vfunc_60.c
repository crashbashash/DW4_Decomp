typedef struct Obj { int w0; unsigned refs; } Obj;
int igObject_Destroy();
extern int DAT_005608c8[4];
void Gap__Core__igPsx2VisualContext__vfunc_60(int *arg0, Obj *arg1) {
    Obj *o;
    if ((Obj *)arg0[236] == arg1) {
        DAT_005608c8[0] += 1;
    }
    if (arg1) {
        arg1->refs++;
    }
    o = (Obj *)arg0[236];
    if (o != 0) {
        --o->refs;
        if ((o->refs & 0x7fffff) == 0) {
            igObject_Destroy(o);
        }
    }
    arg0[236] = (int)arg1;
}
