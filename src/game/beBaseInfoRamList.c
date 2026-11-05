/* src/game/beBaseInfoRamList.c — the beBaseInfoRamList methods
 *
 * One translation unit: 2 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */

extern int g_beBaseInfoRamList_metaObject_00589d20[4];
extern int g_beBaseInfoRam_metaObject_00589d28[4];
/* 0x0036efa0 */
int beBaseInfoRamList_GetMetaObject_Virtual(void)
{
    return g_beBaseInfoRamList_metaObject_00589d20[0];
}

/* 0x00370750 */
int Gap__Bec__beBaseInfoRamList__vfunc_22(void)
{
    return g_beBaseInfoRam_metaObject_00589d28[0];
}
