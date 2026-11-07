/* beNDMWShopCtrl00 factory and metadata forwards plus the published parent-class accessor. The
 * shop controller is created by the shared igMetaObject machinery: the metadata handle is
 * registered lazily and the instance comes from igMetaObject_CreateInstance, not a C++
 * constructor. */
#include "dw4/reflected.h"
struct StaticInitCallbacks;
/* Published metadata handles of beNDMWShopCtrl00 and its base class beNDMWWindowCtrl, the slots
 * passed to their registrars. */
extern igMetaObject *g_beNDMWShopCtrl00_metaObject[],*g_beNDMWWindowCtrl_metaObject[];
extern "C" void *igMetaObject_CreateInstance(igMetaObject *,void *);
extern "C" void igMetaObject_RunStaticInit(StaticInitCallbacks *(*)());
extern "C" StaticInitCallbacks *beNDMWShopCtrl00_Register();
extern "C" igMetaObject *beNDMWShopCtrl00_ResolveMetaObject();
extern "C" void beNDMWShopCtrl00_EnsureRegistered();
/* Parent-class accessor handed to the registrar; returns the current published word without
 * registering or resolving the parent. */
extern "C" igMetaObject *beNDMWWindowCtrl_GetPublishedMetaObject(){return g_beNDMWWindowCtrl_metaObject[0];}
/* Factory used by the SUBWND lifecycle; registers on demand, then creates the instance from the
 * (possibly just published) metadata. */
extern "C" void *beNDMWShopCtrl00_Create(void *allocator){
    beNDMWShopCtrl00_EnsureRegistered();return igMetaObject_CreateInstance(g_beNDMWShopCtrl00_metaObject[0],allocator);
}
/* Lazy accessor. A null handle, or one whose _validity word lacks bit 4, runs the registrar; the
 * handle is re-read afterwards because the callback may publish a different object. */
igMetaObject *beNDMWShopCtrl00_ResolveMetaObject(){
    igMetaObject *meta=g_beNDMWShopCtrl00_metaObject[0];
    if(!meta||((meta->_validity&4)!=0)==false){
        beNDMWShopCtrl00_EnsureRegistered();
    }
    return g_beNDMWShopCtrl00_metaObject[0];
}
extern "C" void beNDMWShopCtrl00_EnsureRegistered(){igMetaObject_RunStaticInit(beNDMWShopCtrl00_Register);}
extern "C" igMetaObject *beNDMWShopCtrl00_GetMetaObject(){return beNDMWShopCtrl00_ResolveMetaObject();}
