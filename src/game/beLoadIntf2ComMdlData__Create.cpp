/* Factory for beLoadIntf2ComMdlData: FUN_003c75a0 is the class's static-init step (it passes its
 * own address block to the class registrar), then the metaobject is instantiated with the given
 * allocator. */
extern "C" {
extern int g_beLoadIntf2ComMdlData_metaObject[4];
int igMetaObject_CreateInstance(int, int);
int FUN_003c75a0();
void beLoadIntf2ComMdlData__Create(int allocator);
}

void beLoadIntf2ComMdlData__Create(int allocator) {
    FUN_003c75a0();
    igMetaObject_CreateInstance(g_beLoadIntf2ComMdlData_metaObject[0], allocator);
}
