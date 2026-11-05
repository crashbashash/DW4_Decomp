/* 0x002ea3d0
 * igInfoList vtable slot 53: constant-4 leaf (`jr ra; li v0,4`). The sibling list classes
 * igDirectoryList, igPluginRepositoryList and igNonRefCountedThreadList return 4 from the
 * same slot, igRegistryValueList returns 2. Slot role is not recovered (4 matches the
 * size of one 32-bit element of the list's `_data` memory block, but that is a
 * hypothesis). The receiver is not read. */
int Gap__Core__igInfoList__vfunc_53(void) {
    return 4;
}
