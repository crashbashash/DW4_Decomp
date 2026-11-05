typedef struct R { char pad4[4]; int f4; } R;
typedef struct S { char pad8[8]; R *ref; char pad12[60]; unsigned char flags; } S;
int igObject_Destroy();

void FUN_001aba30(S *arg0) {
    R *temp_a0;

    arg0->flags = arg0->flags & 0xFE;
    temp_a0 = arg0->ref;
    if (temp_a0 != 0) {
        temp_a0->f4 = temp_a0->f4 - 1;
        if ((temp_a0->f4 & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->ref = 0;
}
