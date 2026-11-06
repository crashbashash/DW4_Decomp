/* Releases an entry taken by FUN_002b2f48: clears its in-use word and decrements the count
 * DAT_004beb58. Null is ignored. */

extern int DAT_004beb58;                  /* count of entries handed out */

/* matching construct: manual — the in-use word is written through a volatile pointer; retail leaves the branch delay slot empty */
void FUN_002b3030(volatile int *entry) {
    if (entry != 0) {
        *entry = 0;
        DAT_004beb58--;
    }
}
