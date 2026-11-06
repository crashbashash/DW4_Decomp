/* SVM lock (counterpart of FUN_0027e130, which the string names svm_unlock): runs the lock
 * callback, records the lock type on the outermost lock and counts the nesting. */
struct Callback0027e0d0 {
    void (*fn)(int arg); /* +0 */
    int arg;             /* +4 */
};

extern struct Callback0027e0d0 DAT_00570ba0;
extern volatile int DAT_004baff8; /* lock nesting count (re-read after the store: volatile) */
extern volatile int DAT_004baffc; /* lock type recorded by the outermost lock */

void FUN_0027e0d0(int type) {
    if (DAT_00570ba0.fn != 0) {
        DAT_00570ba0.fn(DAT_00570ba0.arg);
        if (DAT_004baff8 == 0) {
            DAT_004baffc = type;
        }
        DAT_004baff8++;
    }
}
