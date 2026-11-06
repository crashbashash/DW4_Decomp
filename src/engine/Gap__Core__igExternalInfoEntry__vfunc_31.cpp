/* Resolves an external info reference of a directory being loaded: finds the info named _infoName
 * (igDirectory_FindInfoByName) in external directory
 * number _directoryIndex of `directory` (_externalDirectoryList, whose _data holds one pointer per
 * directory), asks it for the value stored under _key (virtual slot 22) and writes that into entry
 * _index of `directory` (FUN_002d7da0). A missing info
 * stores 0. Field roles from include/dw4/reflected.h (igExternalInfoEntry, igDirectory,
 * igDirectoryList). */
#include "dw4/reflected.h"
extern "C" {
int FUN_002d7da0(...);
void **igDirectory_FindInfoByName(...);
void Gap__Core__igExternalInfoEntry__vfunc_31(igExternalInfoEntry *self, igDirectory *directory);
}
class DW4VC_96_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(int); };
void Gap__Core__igExternalInfoEntry__vfunc_31(igExternalInfoEntry *self, igDirectory *directory) {
    void **info;

    info = (void **)(igDirectory_FindInfoByName(*(int *)(((igDirectoryList *)directory->_externalDirectoryList)->_data + (self->_directoryIndex * 4)), self->_infoName));
    if (info != 0) {
        FUN_002d7da0(directory, self->_index, ((DW4VC_96_1 *)(info))->vX((int)(self->_key)));
        return;
    }
    FUN_002d7da0(directory, self->_index, 0);
}
