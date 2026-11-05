/* 0x001c1c50 - igFrustCullTraversal slot 45: tail-call forwarder (`j 0x1d33a0`) to
 * FUN_001d33a0.  That body (asm/FUN_001d33a0.s) calls igObject slot 7 and, when
 * its second argument is zero, fetches a value through the receiver's slot 30
 * and passes it to slot 28 with flag 1.  Receiver and argument pass through
 * untouched. */
int FUN_001d33a0();

void Gap__Sg__igFrustCullTraversal__vfunc_45(void) {
    FUN_001d33a0();
}
