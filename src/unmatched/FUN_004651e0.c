int FUN_00191b10();
struct T { char pad[92]; float f92; float f96; float f100; float f104; float f108; float f112; };
struct S { char pad[8]; struct T *f8; };

void FUN_004651e0(struct S *arg0) {
    float v[3];
    struct T *t;

    t = arg0->f8;
    v[0] = t->f92;
    v[1] = t->f96;
    v[2] = t->f100;
    v[0] = v[0] + t->f104;
    v[1] += t->f108;
    v[2] += t->f112;
    FUN_00191b10((char *)t + 0xC, (char *)t + 0x5C, v, (char *)t + 0x74, t);
}
