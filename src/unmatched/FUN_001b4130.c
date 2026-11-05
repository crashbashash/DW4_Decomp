struct Rc { int vt; int rc; int w8; int w12; int f16; };
struct M { char pad[12]; int f12; };
struct A { char pad[8]; int f8; };
struct O { char pad0[32]; struct M *f32; char pad1[20]; struct A *f56; char pad2[100]; struct Rc *f160; };
struct Rc *FUN_00140c00();
int FUN_001b4120();
int igObject_Destroy();

int FUN_001b4130(struct O *arg0) {
    struct Rc *temp_a0;
    struct Rc *temp_v0;

    if ((arg0->f32 == 0) || (FUN_001b4120() == 0) || (arg0->f56->f8 == 0)) {
        return 0;
    }
    if (arg0->f160 == 0) {
        temp_v0 = FUN_00140c00(arg0->f32->f12, 0);
        if (temp_v0 != 0) {
            temp_v0->rc = temp_v0->rc + 1;
        }
        temp_a0 = arg0->f160;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->f160 = temp_v0;
        if (arg0->f160 == 0) {
            return 0;
        }
    }
    if (arg0->f160->f16 != 1) {
        return 0;
    }
    return 1;
}
