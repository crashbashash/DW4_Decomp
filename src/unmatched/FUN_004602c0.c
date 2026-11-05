struct D { char pad[12]; int f12; char pad2[60]; int f76; };
struct C { char pad[68]; struct D *f68; };
struct B { char pad[184]; unsigned char b184; unsigned char b185; unsigned char b186; char p; int f188; };
struct A { char pad[12]; struct B *f12; char pad2[64]; struct C *f80; };
void FUN_004602c0(struct A *arg0) {
    int var_a3;
    struct D *temp_a2;
    struct B *temp_a1;

    temp_a2 = arg0->f80->f68;
    temp_a1 = arg0->f12;
    var_a3 = 0;
    if (temp_a1->b184 != 0) {
        var_a3 |= 0x20;
    }
    if (temp_a1->b185 != 0) {
        var_a3 |= 1;
    }
    if (temp_a1->b186 != 0) {
        var_a3 |= 4;
    }
    temp_a2->f12 = temp_a2->f12 & var_a3;
    temp_a2->f12 = temp_a2->f12 | var_a3;
    temp_a2->f76 = arg0->f12->f188;
}
