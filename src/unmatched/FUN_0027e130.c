/* SVM unlock (the diagnostic string names it svm_unlock): drops the lock count, checks the
 * releasing type against the one that took the lock, and runs the unlock callback. */
void FUN_0027e2f0();

struct Callback0027e0d0 {
    void (*fn)(int arg); /* +0 */
    int arg;             /* +4 */
};

extern struct Callback0027e0d0 DAT_00570ba8; /* unlock callback */
extern volatile int DAT_004baff8;            /* lock nesting count */
extern volatile int DAT_004baffc;            /* lock type recorded by the outermost lock */
extern char DAT_004f2578[];                  /* "2103102:SVM:svm_unlock:lock type miss match.(type org=%d, type now=%d)" */

void FUN_0027e130(int type) {
    if (DAT_00570ba8.fn != 0) {
        DAT_004baff8--;
        if (DAT_004baff8 == 0) {
            if (DAT_004baffc != type) {
                FUN_0027e2f0(DAT_004f2578, DAT_004baffc, type);
            }
            DAT_004baffc = 0;
        }
        DAT_00570ba8.fn(DAT_00570ba8.arg);
    }
}
