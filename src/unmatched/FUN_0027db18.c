/* Increments a use counter, running the one-time initialiser DTX_Init when it is still zero. */
void DTX_Init();
extern char *volatile DAT_004ba478; /* read and discarded: the retail load survives, so it is volatile */
extern int DAT_004ba47c;          /* use count */

void FUN_0027db18(void) {
    DAT_004ba478;
    if (DAT_004ba47c == 0) {
        DTX_Init();
    }
    DAT_004ba47c++;
}
