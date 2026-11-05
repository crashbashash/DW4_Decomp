/* src/engine/igObject.c — the igObject methods
 *
 * One translation unit: 40 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time.
 *
 * These are the shared default virtual slots that RTTI vtable naming
 * resolves to igObject (docs/engine/rtti-and-vtables.md, findings #283 and
 * #410): almost every class inherits them, so most are empty or return a
 * constant.  The slot number is the only name evidence, so the bodies are
 * documented by what they do, not by an invented role.  The `__<addr>`
 * names are distinct bodies the vtable pass resolved to the same slot. */

#include "dw4/reflected.h"
extern int g_beModelCtrlInfo_metaObject_00588ba0[4];

/* 0x00142ba0 — default slot 21: constant 4. */
int Gap__Core__igObject__vfunc_21(void)
{
    return 4;
}

/* 0x001b6ca0 — slot 8 default: forwards to the empty slot-8 body. */
int Gap__Core__igObject__vfunc_08()
{
    return Gap__Core__igObject__vfunc_08__002ff0f0();
}

/* 0x001ce700 — second copy of the slot 8 forwarder. */
int Gap__Core__igObject__vfunc_08__001ce700()
{
    return Gap__Core__igObject__vfunc_08__002ff0f0();
}

/* 0x001d3390 — third copy of the slot 8 forwarder. */
int Gap__Core__igObject__vfunc_08__001d3390()
{
    return Gap__Core__igObject__vfunc_08__002ff0f0();
}

/* 0x001e2d90 — slot 36, shared by igTransform descendants: store the
 * igTransform::_target field (+96). */
void Gap__Core__igObject__vfunc_36(igTransform *self, int target)
{
    self->_target = target;
}

/* 0x002f0030 — slot 0 default: forwards to the empty slot-0 body. */
int Gap__Core__igObject__vfunc_00()
{
    return Gap__Core__igObject__vfunc_00__002ff0a0();
}

/* 0x002ff0a0 — the empty slot-0 body that the slot 0 forwarder calls. */
void Gap__Core__igObject__vfunc_00__002ff0a0(void)
{
}

/* 0x002ff0b0 — slot 1 default: empty. */
void Gap__Core__igObject__vfunc_01(void)
{
}

/* 0x002ff0c0 — slot 2 default: empty. */
void Gap__Core__igObject__vfunc_02(void)
{
}

/* 0x002ff0d0 — slot 3 default: empty. */
void Gap__Core__igObject__vfunc_03(void)
{
}

/* 0x002ff0e0 — slot 7 default: empty. */
void Gap__Core__igObject__vfunc_07(void)
{
}

/* 0x002ff0f0 — the empty slot-8 body that the slot 8 forwarders call. */
void Gap__Core__igObject__vfunc_08__002ff0f0(void)
{
}

/* 0x002ff100 — slot 4 default: empty. */
void Gap__Core__igObject__vfunc_04(void)
{
}

/* 0x002ff110 — slot 5 default: always 1. */
int Gap__Core__igObject__vfunc_05(void)
{
    return 1;
}

/* 0x002ff120 — slot 6 default: always 1. */
int Gap__Core__igObject__vfunc_06(void)
{
    return 1;
}

/* 0x002ff130 — slot 11 default: empty. */
void Gap__Core__igObject__vfunc_11(void)
{
}

/* 0x002ff140 — slot 9 default: empty. */
void Gap__Core__igObject__vfunc_09(void)
{
}

/* 0x002ff150 — slot 10 default: empty. */
void Gap__Core__igObject__vfunc_10(void)
{
}

/* 0x002ff160 — slot 12 default: empty. */
void Gap__Core__igObject__vfunc_12(void)
{
}

/* 0x002ff170 — slot 13 default: empty. */
void Gap__Core__igObject__vfunc_13(void)
{
}

/* 0x002ff180 — slot 15 default: empty. */
void Gap__Core__igObject__vfunc_15(void)
{
}

/* 0x002ff190 — slot 14 default: empty. */
void Gap__Core__igObject__vfunc_14(void)
{
}

/* 0x002ff1a0 — slot 16 default: empty. */
void Gap__Core__igObject__vfunc_16(void)
{
}

/* 0x002ff1b0 — slot 17 default: empty. */
void Gap__Core__igObject__vfunc_17(void)
{
}

/* 0x002ff1c0 — slot 18 default: empty. */
void Gap__Core__igObject__vfunc_18(void)
{
}

/* 0x00378400 — slot 28 default: empty. */
void Gap__Core__igObject__vfunc_28(void)
{
}

/* 0x00378410 — slot 34 default: always 0. */
int Gap__Core__igObject__vfunc_34(void) {
    return 0;
}

/* 0x00378700 — slot 33 default: always 0. */
int Gap__Core__igObject__vfunc_33(void) {
    return 0;
}

/* 0x00378720 — slot 22 default: empty. */
void Gap__Core__igObject__vfunc_22(void)
{
}

/* 0x00378790 — slot 24 default: empty. */
void Gap__Core__igObject__vfunc_24(void)
{
}

/* 0x00390dd0 — slot 30 default: first word of the beModelCtrlInfo
 * MetaObject record (see src/game/beModelCtrlInfo.c, which has the same body). */
int Gap__Core__igObject__vfunc_30(void)
{
    return g_beModelCtrlInfo_metaObject_00588ba0[0];
}

/* 0x00394f90 — slot 39 default: empty. */
void Gap__Core__igObject__vfunc_39(void)
{
}

/* 0x003960e0 — slot 46 default: empty. */
void Gap__Core__igObject__vfunc_46(void)
{
}

/* 0x00398da0 — slot 45 default: empty. */
void Gap__Core__igObject__vfunc_45(void)
{
}

/* 0x00398db0 — slot 44 default: empty. */
void Gap__Core__igObject__vfunc_44(void)
{
}

/* 0x00398dc0 — slot 43 default: empty. */
void Gap__Core__igObject__vfunc_43(void)
{
}

/* 0x00398dd0 — slot 41 default: empty. */
void Gap__Core__igObject__vfunc_41(void)
{
}

/* 0x00398de0 — slot 40 default: empty. */
void Gap__Core__igObject__vfunc_40(void)
{
}

/* 0x00398df0 — slot 42 default: empty. */
void Gap__Core__igObject__vfunc_42(void)
{
}

/* 0x00398e00 — slot 47 default: always 0. */
int Gap__Core__igObject__vfunc_47(void) {
    return 0;
}
