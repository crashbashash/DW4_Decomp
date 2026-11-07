struct R { int vt; unsigned int rc; };
extern "C" {
int igObject_Destroy(...);
extern R * DAT_00587620[4];
void FUN_00333230(R *arg0);
}
void FUN_00333230(R *arg0) {
    R *old;
    if (arg0 != 0) {
        if (arg0 != 0) {
            arg0->rc = arg0->rc + 1;
        }
        old = DAT_00587620[0];
        if (old != 0) {
            old->rc = old->rc - 1;
            if ((old->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(old);
            }
        }
        DAT_00587620[0] = arg0;
    }
}