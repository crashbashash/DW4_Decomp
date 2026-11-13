/* Runs every server function registered for `group` (see SVM_SetCbSvr) with its argument, flagging
 * the group busy around each call; ORs the results and counts the pass. */
struct CbSvr0027e600 {
    int (*fn)(int arg); /* +0: 0 = free */
    int arg;            /* +4 */
};

extern struct CbSvr0027e600 DAT_005709e0[][6];
extern int DAT_004bb020[];  /* per group: non-zero while one of its server functions runs */
extern int DAT_004bb000[];  /* per group: number of passes */

int FUN_0027e910(int group) {
    struct CbSvr0027e600 *slot;
    int result;
    int i;

    result = 0;
    slot = DAT_005709e0[group];
    for (i = 0; i < 6; i++, slot++) {
        if (slot->fn != 0) {
            DAT_004bb020[group] = 1;
            result |= slot->fn(slot->arg);
            DAT_004bb020[group] = 0;
        }
    }
    DAT_004bb000[group]++;
    return result;
}
