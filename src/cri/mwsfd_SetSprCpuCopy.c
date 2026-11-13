/* Non-zero: scratchpad save/restore copies with memcpy instead of DMA channels 8/9. */
extern int mwsfd_spr_cpu_copy;

void mwsfd_SetSprCpuCopy(int on) {
    mwsfd_spr_cpu_copy = on;
}
