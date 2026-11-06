/* Looks an object up with FUN_0028dac0 and, when one is found, returns FUN_0028db18's result for
 * it; returns 0 otherwise. */
extern void *FUN_0028dac0(void);
extern int FUN_0028db18(void *object);

int FUN_0028da88(void) {
    void *object = FUN_0028dac0();

    if (object != 0) {
        return FUN_0028db18(object);
    }
    return 0;
}
