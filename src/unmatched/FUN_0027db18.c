/* Increments a use counter, running the one-time initialiser FUN_002736b8 when it is still zero. */
void FUN_002736b8();
extern char *volatile DAT_004ba478; /* read and discarded: the retail load survives, so it is volatile */
extern int DAT_004ba47c;          /* use count */

void FUN_0027db18(void) {
    DAT_004ba478;
    if (DAT_004ba47c == 0) {
        FUN_002736b8();
    }
    DAT_004ba47c++;
}
