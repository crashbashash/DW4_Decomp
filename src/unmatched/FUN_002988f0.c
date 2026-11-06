/* Passes three byte values to FUN_002b3e00 on the object's handle from FUN_00297810. */
extern int FUN_00297810(void *obj);
extern void FUN_002b3e00(int handle, unsigned char a, unsigned char b, unsigned char c);

void FUN_002988f0(void *obj, unsigned char a, unsigned char b, unsigned char c) {
    FUN_002b3e00(FUN_00297810(obj), a, b, c);
}
