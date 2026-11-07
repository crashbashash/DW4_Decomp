typedef struct Obj { int w0; unsigned refs; } Obj;
int igObject_Destroy();
int igObject_GetAllocator();
void Gap__Core__igPageMemoryPool__vfunc_90(int *arg0, Obj *arg1) {
    Obj *o;
    if (arg1 == 0 || (int *)igObject_GetAllocator(arg1) != arg0) {
        if (arg1 != 0) {
            arg1->refs++;
        }
        o = (Obj *)arg0[32];
        if (o != 0) {
            --o->refs;
            if ((o->refs & 0x7fffff) == 0) {
                igObject_Destroy(o);
            }
        }
        arg0[32] = (int)arg1;
    }
}
