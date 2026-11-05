/* 0x0044b260 — Gap__Bec__beNDMWMdlMapCursor__vfunc_35. Banked by tools/retype_struct_member.py (shape: leadfn1):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int igStrCmp(int, int *);
extern int DAT_0051dc28[4];
int Gap__Bec__beNDMWMdlMapCursor__vfunc_35(int dummy0, int arg1) {
    return igStrCmp(arg1, &DAT_0051dc28[0]) == 0;
}
} /* extern "C" */
