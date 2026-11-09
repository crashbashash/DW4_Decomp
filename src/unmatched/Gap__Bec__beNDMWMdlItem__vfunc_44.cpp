#include "dw4/igSmartPointer.h"
extern "C" {
void *beBaseInfoDataList_Create(void *);
void *Memory_GetAllocatorBySelector(int);
void *igObject_GetAllocator(void *);
beModelCtrlInfoRamData *igProperty_FindByName(int, int, const char *);
int strcmp(const char *, const char *);
extern char DAT_0051cf58[];                 /* "ONE" */
extern char DAT_0051d0b0[];                 /* "SQ_EXIT" */
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
class MdlItemVt { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void exit(beBaseInfoRam *ram); };

static inline void setDataList(beBaseInfoRam *ram, const igSmartPointer<igObject> &list) {
    igObject *t = list.p;
    if (t != 0) t->_refCount = t->_refCount + 1;
    igRelease((igObject *)ram->_dataList);
    ram->_dataList = (int)t;
}

static inline void adoptDataList(beBaseInfoRam *ram, igObject *created) {
    igSmartPointer<igObject> list(created);
    setDataList(ram, list);
}

extern "C" void Gap__Bec__beNDMWMdlItem__vfunc_44(beNDMWMdlItem *self, beBaseInfoRam *ram) {
    if (ram->_dataList == 0) {
        void *a = igObject_GetAllocator(ram);
        void *al = GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        igObject *created = (igObject *)beBaseInfoDataList_Create(al);
        adoptDataList(ram, created);
    }
    beModelCtrlInfoRamData *one = igProperty_FindByName(ram->_dataList, DAT_00585be0[0], DAT_0051cf58);
    if (strcmp((const char *)((beModelCtrlInfoWork *)one->_work)->_seqCodeName, DAT_0051d0b0) == 0)
        ((MdlItemVt *)self)->exit(ram);
}
