/* Reports three fixed buffer sizes (0x6952C, 0x13C68, 0x2000) through the out pointers and returns
 * their sum. */
int FUN_00299788(int *size0, int *size1, int *size2) {
    *size0 = 0x6952C;
    *size1 = 0x13C68;
    *size2 = 0x2000;
    return *size0 + *size1 + *size2;
}
