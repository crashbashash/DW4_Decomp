/* igGenericCapabilityManager vtable slot 23: always answers 1. The
 * igVisualContextCapabilityManager override forwards the same slot to its igVisualContext, so this
 * is a yes/no capability query where the generic manager says "yes". The receiver is not read. */
int Gap__Gfx__igGenericCapabilityManager__vfunc_23(void) {
    return 1;
}
