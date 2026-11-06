/* beNDMWShopCtrl00 factory and metadata forwards (0x003b8d90..0x003b8f4c) plus the
 * published parent-class accessor at 0x003b65b0, walked through in
 * docs/engine/shop-root-metadata.md.  The shop controller is created by the
 * shared igMetaObject machinery: the metadata handle is registered lazily and
 * the instance comes from igMetaObject_CreateInstance, not a C++ constructor.
 */
#include "dw4/reflected.h"
struct StaticInitCallbacks;
/* Published metadata handles: beNDMWShopCtrl00 (0x0058ae30) and its base class
 * beNDMWWindowCtrl (0x0058b010), the slots passed to the registrars in
 * src/game/beNDMWShopCtrl00_Register.c and beNDMWWindowCtrl_Register.c. */
extern igMetaObject *g_beNDMWShopCtrl00_metaObject[],*g_beNDMWWindowCtrl_metaObject[];
extern "C" void *igMetaObject_CreateInstance(igMetaObject *,void *);
extern "C" void igMetaObject_RunStaticInit(StaticInitCallbacks *(*)());
extern "C" StaticInitCallbacks *beNDMWShopCtrl00_Register();
extern "C" igMetaObject *beNDMWShopCtrl00_ResolveMetaObject();
extern "C" void beNDMWShopCtrl00_EnsureRegistered();
/* 0x003b65b0: parent-class accessor handed to the registrar; returns the current
 * published word without registering or resolving the parent. */
extern "C" igMetaObject *beNDMWWindowCtrl_GetPublishedMetaObject(){return g_beNDMWWindowCtrl_metaObject[0];}
/* 0x003b8d90: factory used by the SUBWND lifecycle; registers on demand, then
 * creates the instance from the (possibly just published) metadata. */
extern "C" void *beNDMWShopCtrl00_Create(void *allocator){
    beNDMWShopCtrl00_EnsureRegistered();return igMetaObject_CreateInstance(g_beNDMWShopCtrl00_metaObject[0],allocator);
}
/* 0x003b8dd0: lazy accessor.  A null handle, or one whose _validity word lacks bit 4,
 * runs the registrar; the handle is re-read afterwards because the callback may
 * publish a different object.
 * The null branch enters at ensure; only the non-null/not-ready path executes
 * the retail padding instruction. */
igMetaObject *beNDMWShopCtrl00_ResolveMetaObject(){
    igMetaObject *meta=g_beNDMWShopCtrl00_metaObject[0];bool validityBit4Set;
    if(!meta)goto ensure;
    if(!(validityBit4Set=meta->_validity&4)){
        asm { nop }
ensure:
        beNDMWShopCtrl00_EnsureRegistered();
    }
    return g_beNDMWShopCtrl00_metaObject[0];
}
/* 0x003b8ea0: run the class registrar through the shared static-init runner. */
extern "C" void beNDMWShopCtrl00_EnsureRegistered(){igMetaObject_RunStaticInit(beNDMWShopCtrl00_Register);}
/* 0x003b8f30: the class's own metadata accessor forwards to the lazy accessor. */
extern "C" igMetaObject *beNDMWShopCtrl00_GetMetaObject(){return beNDMWShopCtrl00_ResolveMetaObject();}
