extern "C" {
struct T { int w0; int refs; };
int FUN_00100610(T **);
int igObject_Destroy(T *);

struct T **FUN_0033edb0(struct T **arg0, short arg1) {
    struct T *o;
    if (arg0 != 0) {
        o = *arg0;
        if (o != 0) {
            o->refs = o->refs - 1;
            if ((o->refs & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}
}
