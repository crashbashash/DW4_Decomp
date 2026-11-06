/* beMemory overrides slots 21-27 of its base class with empty bodies (slot 25 reports 0) and
 * returns its class handle from slot 20; it adds no behaviour of its own here. */

extern int g_beMemory_metaObject[4];
/* Slot 21, empty override. */
void Gap__Bec__beMemory__vfunc_21(void)
{
}

/* Slot 22, empty override. */
void Gap__Bec__beMemory__vfunc_22(void)
{
}

/* Slot 23, empty override. */
void Gap__Bec__beMemory__vfunc_23(void)
{
}

/* Slot 24, empty override. */
void Gap__Bec__beMemory__vfunc_24(void)
{
}

/* Slot 25, empty override returning 0. */
int Gap__Bec__beMemory__vfunc_25(void) {
    return 0;
}

/* Slot 26, empty override. */
void Gap__Bec__beMemory__vfunc_26(void)
{
}

/* Slot 27, empty override. */
void Gap__Bec__beMemory__vfunc_27(void)
{
}

int Gap__Bec__beMemory__vfunc_20(void)
{
    return g_beMemory_metaObject[0];
}
