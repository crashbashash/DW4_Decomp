/* src/game/beMemory.c — the beMemory methods
 *
 * beMemory overrides slots 21-27 of its base class with empty bodies (slot 25 reports
 * 0) and returns its class handle from slot 20; it adds no behaviour of its own here.
 *
 * One translation unit: 8 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */

extern int g_beMemory_metaObject[4];
/* 0x003afe80: slot 21, empty override. */
void Gap__Bec__beMemory__vfunc_21(void)
{
}

/* 0x003afe90: slot 22, empty override. */
void Gap__Bec__beMemory__vfunc_22(void)
{
}

/* 0x003afea0: slot 23, empty override. */
void Gap__Bec__beMemory__vfunc_23(void)
{
}

/* 0x003afeb0: slot 24, empty override. */
void Gap__Bec__beMemory__vfunc_24(void)
{
}

/* 0x003afec0: slot 25, empty override returning 0. */
int Gap__Bec__beMemory__vfunc_25(void) {
    return 0;
}

/* 0x003afed0: slot 26, empty override. */
void Gap__Bec__beMemory__vfunc_26(void)
{
}

/* 0x003afee0: slot 27, empty override. */
void Gap__Bec__beMemory__vfunc_27(void)
{
}

/* 0x003afef0: slot 20, MetaObject return (class handle at 0x00589090). */
int Gap__Bec__beMemory__vfunc_20(void)
{
    return g_beMemory_metaObject[0];
}
