struct R { int vt; unsigned int rc; };
void *FUN_001435c0();
int igObject_Destroy();
int igObject_GetAllocator();
extern struct R * DAT_0055f5d0[4];
void Gap__Core__igPsx2AudioContext__vfunc_11(void) {
    int temp_s0;
    struct R *old;

    temp_s0 = igObject_GetAllocator();
    old = DAT_0055f5d0[0];
    if (old != 0) {
        old->rc = old->rc - 1;
        if ((old->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    DAT_0055f5d0[0] = (struct R *)FUN_001435c0(temp_s0);
}