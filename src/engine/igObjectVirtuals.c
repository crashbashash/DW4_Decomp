/* Shared default virtual slots that almost every class inherits, so most are empty or return a
 * constant. The slot number is the only name evidence, so the bodies are documented by what they
 * do. The `__<addr>` names are distinct bodies resolved to the same slot. */

#include "dw4/reflected.h"
extern int g_beModelCtrlInfo_metaObject[4];
int Gap__Core__igObject__vfunc_08__002ff0f0();

/* Default slot 21: constant 4. */
int Gap__Core__igObject__vfunc_21(void)
{
    return 4;
}

/* Second copy of the slot 8 forwarder. */
int Gap__Core__igObject__vfunc_08__001ce700()
{
    return Gap__Core__igObject__vfunc_08__002ff0f0();
}

/* Third copy of the slot 8 forwarder. */
int Gap__Core__igObject__vfunc_08__001d3390()
{
    return Gap__Core__igObject__vfunc_08__002ff0f0();
}

/* Slot 36, shared by igTransform descendants: store the igTransform::_target field (+96). */
void Gap__Core__igObject__vfunc_36(igTransform *self, int target)
{
    self->_target = target;
}

/* Slot 28 default: empty. */
void Gap__Core__igObject__vfunc_28(void)
{
}

/* Slot 34 default: always 0. */
int Gap__Core__igObject__vfunc_34(void) {
    return 0;
}

/* Slot 33 default: always 0. */
int Gap__Core__igObject__vfunc_33(void) {
    return 0;
}

/* Slot 22 default: empty. */
void Gap__Core__igObject__vfunc_22(void)
{
}

/* Slot 24 default: empty. */
void Gap__Core__igObject__vfunc_24(void)
{
}

/* Slot 30 default: first word of the beModelCtrlInfo MetaObject record. */
int Gap__Core__igObject__vfunc_30(void)
{
    return g_beModelCtrlInfo_metaObject[0];
}

/* Slot 39 default: empty. */
void Gap__Core__igObject__vfunc_39(void)
{
}

/* Slot 46 default: empty. */
void Gap__Core__igObject__vfunc_46(void)
{
}

/* Slot 45 default: empty. */
void Gap__Core__igObject__vfunc_45(void)
{
}

/* Slot 44 default: empty. */
void Gap__Core__igObject__vfunc_44(void)
{
}

/* Slot 43 default: empty. */
void Gap__Core__igObject__vfunc_43(void)
{
}

/* Slot 41 default: empty. */
void Gap__Core__igObject__vfunc_41(void)
{
}

/* Slot 40 default: empty. */
void Gap__Core__igObject__vfunc_40(void)
{
}

/* Slot 42 default: empty. */
void Gap__Core__igObject__vfunc_42(void)
{
}

/* Slot 47 default: always 0. */
int Gap__Core__igObject__vfunc_47(void) {
    return 0;
}
