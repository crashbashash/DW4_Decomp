struct Rc { int vt; int rc; };
struct E { char pad[96]; int f96; };
struct S0 { char pad32[32]; E *f32; char pad36[24]; char f60; };
extern "C" {
int FUN_00140c00(E *, int);
int FUN_001c31e0(E *);
int igObject_Destroy(void *);
void FUN_001c2eb0(S0 *arg0, Rc *arg1);
}
void FUN_001c2eb0(S0 *arg0, Rc *arg1) {
    Rc *temp_a0;

    if (arg1 != 0) {
        arg1->rc = arg1->rc + 1;
    }
    temp_a0 = (Rc *)arg0->f32;
    if (temp_a0 != 0) {
        temp_a0->rc = temp_a0->rc - 1;
        if ((temp_a0->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->f32 = (E *)arg1;
    arg0->f32->f96 = 0;
    bool b = FUN_00140c00(arg0->f32, 0) != 0;
    if (!b) {
        FUN_001c31e0(arg0->f32);
    }
    arg0->f60 = 0;
}
