/* 0x00272228 — FUN_00272228 (104 bytes). Busy-waits while the server-busy flag DAT_004a92c4 is 1, counting in DAT_004a92d8; past 0x19640000 iterations it prints the timeout message and gives up. Its message names it SRD_WaitForExecServer (CRI), a name hypothesis. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int DAT_004a92c4;
extern volatile unsigned int DAT_004a92d8; /* the timeout counter is volatile so the spin is not optimised away */
extern char s_SRD_SRD_WaitForExecServer_timeout_10sec_004efd28[]; /* 'SRD: SRD_WaitForExecServer timeout.(10sec)\n' */
void FUN_0010d108(const char *format, ...);

void FUN_00272228(void) {
    DAT_004a92d8 = 0;
    while (DAT_004a92c4 == 1) {
        DAT_004a92d8++;
        if (DAT_004a92d8 > 0x19640000) {
            FUN_0010d108(s_SRD_SRD_WaitForExecServer_timeout_10sec_004efd28);
            break;
        }
    }
}

