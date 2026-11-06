/* Gap::Bec::be is the base class of the game's reflected objects (name, insight core reference,
 * string-reference list). The class supplies empty default bodies for the virtual slots its
 * subclasses override, plus the metaobject accessor in slot 20. */

extern int g_be_metaObject[4];

/* Default body of slot 21, does nothing. */
void Gap__Bec__be__vfunc_21(void)
{
}

/* Default body of slot 22, does nothing. */
void Gap__Bec__be__vfunc_22(void)
{
}

/* Default body of slot 24, does nothing. */
void Gap__Bec__be__vfunc_24(void)
{
}

/* Default body of slot 25, returns 0. */
int Gap__Bec__be__vfunc_25(void) {
    return 0;
}

/* Default body of slot 27, does nothing. */
void Gap__Bec__be__vfunc_27(void)
{
}

int Gap__Bec__be__vfunc_20(void)
{
    return g_be_metaObject[0];
}
