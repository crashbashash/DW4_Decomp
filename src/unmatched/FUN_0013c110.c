int igObject_Destroy();
extern void * DAT_0055f4b8[4];
void FUN_0013c110(void) {
    char *o = (char *)DAT_0055f4b8[0];
    if (o != 0) {
        *(int *)(o + 4) = *(int *)(o + 4) - 1;
        if (((unsigned long long) ((long long) *(int *)(o + 4) << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    DAT_0055f4b8[0] = 0;
}
