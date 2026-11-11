/* beKeyboardReceiver holds only a _keyboard reference. Slot 20 is the class's GetMetaObject accessor
 * and returns the class handle word; slot 21 is an empty override that returns 0. */

extern int g_beKeyboardReceiver_metaObject[4];
/* Slot 21, empty override returning 0. */
int Gap__Bec__beKeyboardReceiver__vfunc_21(void) {
    return 0;
}

/* Slot 20, GetMetaObject. */
int Gap__Bec__beKeyboardReceiver__vfunc_20(void)
{
    return g_beKeyboardReceiver_metaObject[0];
}
