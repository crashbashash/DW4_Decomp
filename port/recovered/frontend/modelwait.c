#include "modelwait.h"
#define P(a) api->peek(api->user,(a),4)
#define W(a,v) api->poke(api->user,(a),4,(v))
#define CALL(a,...) api->call(api->user,(a),(const int32_t[8]){__VA_ARGS__})
static void assign(const Dw4LoadIntf2Api *api,int32_t work,int32_t name)
{
    int32_t pool=P(0x586f20), fresh, old, refs;
    if (!pool) {
        pool=CALL(0x2eb010,16);
        if (pool) pool=CALL(0x2eadf0,pool);
        W(0x586f20,pool);
    }
    fresh=CALL(0x2eaf60,P(0x586f20),name);
    old=P(work+0x4c);
    if (old) {
        refs=(int32_t)((uint32_t)P(old-4)-1u);
        W(old-4,refs);
        if (!refs) CALL(0x30c940,P(old-8),old-8);
    }
    W(work+0x4c,fresh);
}
int32_t mw_jump(const Dw4LoadIntf2Api *api,int32_t owner,int32_t work,int32_t command)
{
    int32_t name=P(command+8);
    CALL(P(P(owner)+0x8c),owner,work,name ? name : MW_EMPTY);
    return 1;
}
int32_t mw_start(const Dw4LoadIntf2Api *api,int32_t owner,int32_t work,int32_t command)
{
    int32_t name=P(command+8);
    (void)owner;
    assign(api,work,name ? name : MW_EMPTY);
    return 0;
}
void mw_update(const Dw4LoadIntf2Api *api,int32_t owner,int32_t info,int32_t node,int32_t work)
{
    int mode;
    if (!CALL(0x12a4a4,P(work+0x4c),MW_TURNY) ||
        !CALL(0x12a4a4,P(work+0x4c),MW_LANDING)) mode=2;
    else if (!CALL(0x12a4a4,P(work+0x4c),MW_ACTION)) {
        int32_t name=P(info+8), slot=P(node+8);
        CALL(0x38e5f0,P(owner+0x14),MW_ACTION2,name ? name : MW_EMPTY,slot,MW_ISCOMEND);
        if (!CALL(0x38f220,P(owner+0x14),0)) return;
        assign(api,work,0);
        CALL(0x395250,owner,info,node,work);
        return;
    } else if (!CALL(0x12a4a4,P(work+0x4c),MW_MOVING)) mode=0;
    else if (!CALL(0x12a4a4,P(work+0x4c),MW_ROTATION)) mode=1;
    else {
        CALL(P(P(owner)+0xa4),owner,node);
        return;
    }
    if (CALL(0x392be0,owner,node,work,mode)&255) return;
    assign(api,work,0);
    CALL(0x395250,owner,info,node,work);
}
void mw_noop(const Dw4LoadIntf2Api *api) { (void)api; }
