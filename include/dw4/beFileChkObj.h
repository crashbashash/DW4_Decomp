#ifndef DW4_BEFILECHKOBJ_H
#define DW4_BEFILECHKOBJ_H

struct beFileChkObj;

#ifdef __cplusplus
extern "C" {
#endif

struct beFileChkObj *beFileChkObj_Create(int allocator);
int beFileChkObj_FileExists(struct beFileChkObj *checker, const char *fileName);

#ifdef __cplusplus
}
#endif

#endif
