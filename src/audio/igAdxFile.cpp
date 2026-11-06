extern "C" {
void Gap__Core__igObject__vfunc_01(void);
void Gap__igAdxFile__vfunc_01(void);
}
extern "C" {
void FUN_00261c88(int);
void Gap__igAdxFile__vfunc_24(char *);
}

void Gap__igAdxFile__vfunc_01(void)
{
    Gap__Core__igObject__vfunc_01();
}

void Gap__igAdxFile__vfunc_24(char * p0)
{
    FUN_00261c88(*(int *)((char *)p0 + 96));
}

/* ---- from src/audio/igAdxFile.c ---- */
/* The igAdxFile methods (Gap::igAdxFile, the file class backed by the CRI ADX file system). Most
 * virtual slots are stubs that report the operation as unsupported (-1); slot 20 is the
 * GetMetaObject accessor and slot 37 reads the seek position. */
#include "dw4/reflected.h"
extern "C" {
extern int g_igAdxFile_metaObject[4];
/* Takes the handle held at +96 of the file object (past the reflected fields);
 * returns -3 after logging when it is null, else the value at handle+20. */
int FUN_00262510(int);

/* Slot 20, class meta-object handle getter */
int Gap__igAdxFile__vfunc_20(void)
{
    return g_igAdxFile_metaObject[0];
}

/* Stub, returns -1 */
int Gap__igAdxFile__vfunc_27(void)
{
    return -1;
}

/* Stub, returns -1 */
int Gap__igAdxFile__vfunc_30(void)
{
    return -1;
}

/* Stub, returns -1 */
int Gap__igAdxFile__vfunc_31(void)
{
    return -1;
}

/* Stub, returns -1 */
int Gap__igAdxFile__vfunc_33(void)
{
    return -1;
}

/* Stub, returns 0 */
int Gap__igAdxFile__vfunc_34(void) {
    return 0;
}

/* Stub, returns -1 */
int Gap__igAdxFile__vfunc_35(void)
{
    return -1;
}

/* Slot 37, returns the seek position. The result of the handle query on the field at +96 is
 * discarded. */
int Gap__igAdxFile__vfunc_37(igAdxFile *self) {
    FUN_00262510(*(int *)((char *)self + 96));
    return self->_iSeekPosition;
}

/* Stub, returns -1 */
int Gap__igAdxFile__vfunc_32(void)
{
    return -1;
}
}
