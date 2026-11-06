/* The field is volatile so it is reloaded for the read-modify-write. */
struct S { char pad0[48]; int f48; char pad1[18]; volatile signed char f70 : 7; unsigned char x : 1; };
void FUN_0020c840(struct S *arg0, int arg1) {
    if (arg0->f70 != 1) {
        arg0->f70 = 6;
    }
    arg0->f48 = arg1;
}
