/* Reports three fixed buffer sizes (0x249E4, 0x9C40, 0x800) through the out pointers and returns
 * their sum. */
int FUN_00299758(int *size0, int *size1, int *size2) {
    *size0 = 0x249E4;
    *size1 = 0x9C40;
    *size2 = 0x800;
    return *size0 + *size1 + *size2;
}
