/* MERGED DRAFT: src/audio/igAdxFile.c folded into src/audio/igAdxFile.cpp (both are the same class; the C unit's functions carry retail exception records, so the class is one C++ translation unit).
 * Functions in retail address order follow; the two header blocks are kept as-is. */
/* src/audio/igAdxFile.cpp — the igAdxFile methods
 *
 * One translation unit: 2 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
extern "C" {
void Gap__Core__igObject__vfunc_01(void);
void Gap__igAdxFile__vfunc_01(void);
}
extern "C" {
void FUN_00261c88(int);
void Gap__igAdxFile__vfunc_24(char *);
}

/* 0x00333800 */
void Gap__igAdxFile__vfunc_01(void)
{
    Gap__Core__igObject__vfunc_01();
}

/* 0x00333d70 */
void Gap__igAdxFile__vfunc_24(char * p0)
{
    FUN_00261c88(*(int *)((char *)p0 + 96));
}

/* ---- from src/audio/igAdxFile.c ---- */
/* src/audio/igAdxFile.c — the igAdxFile methods (Gap::igAdxFile, the file
 * class backed by the CRI ADX file system; reflected handle 0x587668,
 * include/dw4/reflected.h).  Most virtual slots are stubs that report the
 * operation as unsupported (-1); slot 20 is the GetMetaObject accessor and
 * slot 37 reads the seek position.
 *
 * One translation unit: 9 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
#include "dw4/reflected.h"
extern "C" {
extern int g_igAdxFile_metaObject[4];
/* Takes the handle held at +96 of the file object (past the reflected fields);
 * returns -3 after logging when it is null, else the value at handle+20. */
int FUN_00262510(int);

/* 0x003338c0: slot 20, class meta-object handle getter */
int Gap__igAdxFile__vfunc_20(void)
{
    return g_igAdxFile_metaObject[0];
}

/* 0x003341a0: stub, returns -1 */
int Gap__igAdxFile__vfunc_27(void)
{
    return -1;
}

/* 0x00334210: stub, returns -1 */
int Gap__igAdxFile__vfunc_30(void)
{
    return -1;
}

/* 0x00334220: stub, returns -1 */
int Gap__igAdxFile__vfunc_31(void)
{
    return -1;
}

/* 0x00334230: stub, returns -1 */
int Gap__igAdxFile__vfunc_33(void)
{
    return -1;
}

/* 0x00334240: stub, returns 0 */
int Gap__igAdxFile__vfunc_34(void) {
    return 0;
}

/* 0x00334250: stub, returns -1 */
int Gap__igAdxFile__vfunc_35(void)
{
    return -1;
}

/* 0x00334330: slot 37, returns the seek position.  The result of the handle
 * query on the field at +96 is discarded. */
int Gap__igAdxFile__vfunc_37(igAdxFile *self) {
    FUN_00262510(*(int *)((char *)self + 96));
    return self->_iSeekPosition;
}

/* 0x00334360: stub, returns -1 */
int Gap__igAdxFile__vfunc_32(void)
{
    return -1;
}
}
