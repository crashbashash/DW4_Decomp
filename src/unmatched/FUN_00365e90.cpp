extern "C" {
struct Rc { int vt; int rc; };

int FUN_00100610(void **);
int igObject_Destroy(Rc *);
void **FUN_00365e90(void **arg0, long long arg1);
}

void **FUN_00365e90(void **arg0, long long arg1) {
    struct Rc *a;
    if (arg0 != 0) {
        a = (struct Rc *)*arg0;
        if (a != 0) { a->rc = a->rc - 1; if ((a->rc & 0x7FFFFF) == 0) { igObject_Destroy(a); } }
        if ((short)arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}
