/* Shared default virtual slots that almost every class inherits, so most are empty or return a
 * constant. The slot number is the only name evidence, so the bodies are documented by what they
 * do. The `__<addr>` names are distinct bodies resolved to the same slot. */

#include "dw4/reflected.h"
extern int g_beModelCtrlInfo_metaObject[4];

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

int Gap__Core__igObject__vfunc_00()
{
    return Gap__Core__igObject__vfunc_00__002ff0a0();
}

void Gap__Core__igObject__vfunc_00__002ff0a0(void)
{
}

/* Slot 1 default: empty. */
void Gap__Core__igObject__vfunc_01(void)
{
}

/* Slot 2 default: empty. */
void Gap__Core__igObject__vfunc_02(void)
{
}

/* Slot 3 default: empty. */
void Gap__Core__igObject__vfunc_03(void)
{
}

/* Slot 7 default: empty. */
void Gap__Core__igObject__vfunc_07(void)
{
}

void Gap__Core__igObject__vfunc_08__002ff0f0(void)
{
}

/* Slot 4 default: empty. */
void Gap__Core__igObject__vfunc_04(void)
{
}

/* Slot 5 default: always 1. */
int Gap__Core__igObject__vfunc_05(void)
{
    return 1;
}

/* Slot 6 default: always 1. */
int Gap__Core__igObject__vfunc_06(void)
{
    return 1;
}

/* Slot 11 default: empty. */
void Gap__Core__igObject__vfunc_11(void)
{
}

/* Slot 9 default: empty. */
void Gap__Core__igObject__vfunc_09(void)
{
}

/* Slot 10 default: empty. */
void Gap__Core__igObject__vfunc_10(void)
{
}

/* Slot 12 default: empty. */
void Gap__Core__igObject__vfunc_12(void)
{
}

/* Slot 13 default: empty. */
void Gap__Core__igObject__vfunc_13(void)
{
}

/* Slot 15 default: empty. */
void Gap__Core__igObject__vfunc_15(void)
{
}

/* Slot 14 default: empty. */
void Gap__Core__igObject__vfunc_14(void)
{
}

/* Slot 16 default: empty. */
void Gap__Core__igObject__vfunc_16(void)
{
}

/* Slot 17 default: empty. */
void Gap__Core__igObject__vfunc_17(void)
{
}

/* Slot 18 default: empty. */
void Gap__Core__igObject__vfunc_18(void)
{
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
