/* Gap::Bec::be - the base class of the game's reflected objects (name, insight
 * core reference, string-reference list; see include/dw4/reflected.h).  The
 * class supplies empty default bodies for the virtual slots its subclasses
 * override, plus the metaobject accessor in slot 20.  Functions are in retail
 * address order. */

/* Reflected metaobject of `be` (handle 0x58a030 in include/dw4/reflected.h). */
extern int g_be_metaObject_0058a030[4];

/* 0x00371a10: default body of slot 21, does nothing. */
void Gap__Bec__be__vfunc_21(void)
{
}

/* 0x00371a20: default body of slot 22, does nothing. */
void Gap__Bec__be__vfunc_22(void)
{
}

/* 0x00371ac0: default body of slot 24, does nothing. */
void Gap__Bec__be__vfunc_24(void)
{
}

/* 0x00371ad0: default body of slot 25, returns 0. */
int Gap__Bec__be__vfunc_25(void) {
    return 0;
}

/* 0x00371c00: default body of slot 27, does nothing. */
void Gap__Bec__be__vfunc_27(void)
{
}

/* 0x00375df0: slot 20, returns the class's metaobject handle (the same
 * accessor shape as the ParticleInfo override). */
int Gap__Bec__be__vfunc_20(void)
{
    return g_be_metaObject_0058a030[0];
}
