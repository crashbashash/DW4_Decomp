/* 0x00155330
 * igGenericCapabilityManager vtable slot 23: always answers 1 (`jr ra; li v0,1`). The
 * igVisualContextCapabilityManager override (0x00167210) forwards the same slot to its
 * igVisualContext, so this is a yes/no capability query where the generic manager says
 * "yes". What exactly is asked is not recovered; the receiver is not read. */
int Gap__Core__igGenericCapabilityManager__vfunc_23(void) {
    return 1;
}
