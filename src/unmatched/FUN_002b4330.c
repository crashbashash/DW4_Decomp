/* 0x002b4330 — FUN_002b4330 (40 bytes). Releases an entry taken by FUN_002b4270: clears its in-use word and decrements the count DAT_004bf010. Null is ignored. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

extern int DAT_004bf010;                  /* count of entries handed out */

/* matching construct: manual — the in-use word is written through a volatile pointer; retail leaves the branch delay slot empty */
void FUN_002b4330(volatile int *entry) {
    if (entry != 0) {
        *entry = 0;
        DAT_004bf010--;
    }
}
