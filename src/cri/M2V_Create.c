/* Looks an object up with m2vlib_SearchFreeHn and, when one is found, returns m2vlib_InitHn's result for
 * it; returns 0 otherwise. */
extern void *m2vlib_SearchFreeHn(void);
extern int m2vlib_InitHn(void *object);

int M2V_Create(void) {
    void *object = m2vlib_SearchFreeHn();

    if (object != 0) {
        return m2vlib_InitHn(object);
    }
    return 0;
}
