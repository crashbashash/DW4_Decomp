/* 0x003c7450
 * Factory for beLoadIntf2ComMdlData: FUN_003c75a0 is the class's static-init
 * step (it passes its own address block to the class registrar at 0x2fe940),
 * then the metaobject (also returned by vfunc_20 in src/game/beLoadIntf2ComMdlData.c)
 * is instantiated with the given allocator (findings: igMetaObject_CreateInstance(*0x58be70, allocator)). */
extern "C" {
extern int g_beLoadIntf2ComMdlData_metaObject_0058be70[4];
int igMetaObject_CreateInstance(int, int);
int FUN_003c75a0();
void beLoadIntf2ComMdlData__Create(int allocator);
}

void beLoadIntf2ComMdlData__Create(int allocator) {
    FUN_003c75a0();
    igMetaObject_CreateInstance(g_beLoadIntf2ComMdlData_metaObject_0058be70[0], allocator);
}
