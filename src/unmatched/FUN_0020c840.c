/* 0x0020c840 - 56 bytes. Sets a 7-bit signed field (offset 70) to 6 unless it is already 1, then stores arg1.
 * The field is volatile: retail reloads it for the read-modify-write. */
struct S { char pad0[48]; int f48; char pad1[18]; volatile signed char f70 : 7; unsigned char x : 1; };
void FUN_0020c840(struct S *arg0, int arg1) {
    if (arg0->f70 != 1) {
        arg0->f70 = 6;
    }
    arg0->f48 = arg1;
}
