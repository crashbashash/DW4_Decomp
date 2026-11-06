/* SVM_DelCbSvr (named by its diagnostic string): clears server slot `slot` of `group` under the
 * SVM lock. */
void FUN_0027e1c0(void); /* SVM lock, type 1 */
void FUN_0027e1d8(void); /* SVM unlock, type 1 */
void FUN_0027e398(const char *message);

struct CbSvr0027e600 {
    int fn;  /* +0: 0 = free */
    int arg; /* +4 */
};

extern struct CbSvr0027e600 DAT_005709e0[][6];
extern char DAT_004f25f8[]; /* "1051002:SVM_DelCbSvr:illegal id" */

void FUN_0027e6d0(int group, unsigned int slot) {
    if (slot >= 6) {
        FUN_0027e398(DAT_004f25f8);
    }
    FUN_0027e1c0();
    DAT_005709e0[group][slot].fn = 0;
    DAT_005709e0[group][slot].arg = 0;
    FUN_0027e1d8();
}
