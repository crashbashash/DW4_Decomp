/* 0x002423f0 — FUN_002423f0. hand-matched: struct members keep the base pointers;
 * verified by tools/verify.py. */
typedef struct A { char pad[20]; void *f20; char pad2[4]; int f28; int f32; } A;
typedef struct B { char pad[24]; int f24; } B;

void FUN_002423f0(A *arg0, B *arg1) {
    void *temp_v1;

    if (arg1 != 0) {
        arg0->f32 = arg1->f24;
        temp_v1 = (void *)(arg0->f32);
        if (temp_v1 != 0) {
            *(int *)((char *)(temp_v1) + 28) = (int)(arg0);
        }
        arg1->f24 = (int)(arg0);
        arg0->f28 = 0;
        arg0->f20 = (void *)(arg1);
    }
}
