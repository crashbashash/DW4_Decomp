/* Looks an object up with FUN_0028ae28 and, when one is found, returns FUN_0028ae78's result for
 * it; returns 0 otherwise. */
extern void *FUN_0028ae28(void);
extern int FUN_0028ae78(void *object);

int FUN_0028adf0(void) {
    void *object = FUN_0028ae28();

    if (object != 0) {
        return FUN_0028ae78(object);
    }
    return 0;
}
