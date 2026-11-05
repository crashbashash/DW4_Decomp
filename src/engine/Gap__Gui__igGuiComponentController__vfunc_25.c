/* 0x004558a0
 * igGuiComponentController vtable slot 25. Default virtual that returns 0 ("not handled")
 * without touching the receiver (retail body is `jr ra; move v0,zero`, asm/Gap__Gui__igGuiComponentController__vfunc_25.s).
 * Slots 25-27 are three adjacent stubs (0x4558a0/0x455890/0x455880) for subclasses to override. */
int Gap__Gui__igGuiComponentController__vfunc_25(void) {
    return 0;
}
