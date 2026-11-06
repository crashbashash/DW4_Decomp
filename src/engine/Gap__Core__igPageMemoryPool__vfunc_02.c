/* igPageMemoryPool slot 2: tail-call forwarder to the igObject slot-0 body at 0x002ff0a0, which is
 * empty; the pool adds no teardown of its own in this slot. */
int Gap__Core__igObject__vfunc_00();

void Gap__Core__igPageMemoryPool__vfunc_02(void) {
    Gap__Core__igObject__vfunc_00();
}
