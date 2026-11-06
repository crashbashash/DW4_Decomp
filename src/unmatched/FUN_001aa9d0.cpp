/* FUN_001aa9d0: scalar deleting destructor shape (release member, delete when flags > 0).py. */
extern "C" int FUN_00100610(void *);
extern "C" int igObject_Destroy(void *);
struct S_temp_a0 { char pad4[4]; int f4; };
struct O { S_temp_a0 *m; };
extern "C" O *FUN_001aa9d0(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}
