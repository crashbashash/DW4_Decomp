#include "dw4/reflected.h"
struct R { int v; R() {} int get() { return v; } };
class OV;
class OV { public:
  virtual void d0();
  virtual void d1();
  virtual void d2();
  virtual void d3();
  virtual void d4();
  virtual void d5();
  virtual void d6();
  virtual void d7();
  virtual void d8();
  virtual void d9();
  virtual void d10();
  virtual void d11();
  virtual void d12();
  virtual void d13();
  virtual void d14();
  virtual void d15();
  virtual void d16();
  virtual void d17();
  virtual void d18();
  virtual void d19();
  virtual void d20();
  virtual void d21();
  virtual R v96(int a, long long b, int c);
  virtual void d23();
  virtual void d24();
  virtual void d25();
  virtual void d26();
  virtual void d27();
  virtual void v120();
  virtual void d29();
  virtual void d30();
  virtual int v132();
  virtual void d32();
  virtual void d33();
  virtual void d34();
  virtual void d35();
  virtual void d36();
  virtual void d37();
  virtual void d38();
  virtual void d39();
  virtual void d40();
  virtual R v172(int a);
  virtual void d42();
  virtual R v180(igMemoryPoolInfo *c);
  virtual void d44();
  virtual void d45();
  virtual void d46();
  virtual void d47();
  virtual void d48();
  virtual void d49();
  virtual void d50();
  virtual void d51();
  virtual int v216(int a);
  virtual void d53();
  virtual void d54();
  virtual void d55();
  virtual void d56();
  virtual void d57();
  virtual void d58();
  virtual void d59();
  virtual void d60();
  virtual void d61();
  virtual void d62();
  virtual void d63();
  virtual void d64();
  virtual void d65();
  virtual void d66();
  virtual void d67();
  virtual void d68();
  virtual void d69();
  virtual void d70();
  virtual void d71();
  virtual void d72();
  virtual void d73();
  virtual void d74();
  virtual void d75();
  virtual void d76();
  virtual void d77();
  virtual void d78();
  virtual void d79();
  virtual void d80();
  virtual void d81();
  virtual void d82();
  virtual void d83();
  virtual void d84();
  virtual void d85();
  virtual void d86();
  virtual void d87();
  virtual void d88();
  virtual void d89();
  virtual void d90();
  virtual void d91();
  virtual void d92();
  virtual void d93();
  virtual void d94();
  virtual void d95();
  virtual void d96();
  virtual void d97();
  virtual void v400(igMemoryPool *o);
};
struct Slot { igMemoryPool *obj; char p[128]; igMemoryPoolInfo *cfg; int f136; int f140; };
class MC { public:
  virtual void d0();
  virtual void d1();
  virtual void d2();
  virtual void d3();
  virtual void d4();
  virtual void d5();
  virtual void d6();
  virtual void d7();
  virtual void d8();
  virtual void d9();
  virtual void d10();
  virtual void d11();
  virtual void d12();
  virtual void d13();
  virtual void d14();
  virtual void d15();
  virtual void d16();
  virtual void d17();
  virtual void d18();
  virtual void d19();
  virtual void d20();
  virtual void d21();
  virtual igMemoryPool *v96(char *n);
  virtual void v100(int i, igMemoryPool *o);
  virtual void d24();
  virtual void d25();
  virtual void d26();
  virtual int v116(char *n);
  virtual void d28();
  virtual void d29();
  virtual void d30();
  virtual void d31();
  virtual void d32();
  virtual void d33();
  virtual void d34();
  virtual void d35();
  virtual void d36();
  virtual void d37();
  virtual void d38();
  virtual void d39();
  virtual void d40();
  virtual void d41();
  virtual void d42();
  virtual void d43();
  virtual void d44();
  virtual void d45();
  virtual void d46();
  virtual void d47();
  virtual void d48();
  virtual R v204(int i, int f);
  int a4, a8, flags, a16;
  Slot slots[8];
};
class Gl { public:
  virtual void d0();
  virtual void d1();
  virtual void d2();
  virtual void d3();
  virtual void d4();
  virtual void d5();
  virtual void d6();
  virtual void d7();
  virtual void d8();
  virtual void d9();
  virtual void d10();
  virtual void d11();
  virtual void d12();
  virtual void d13();
  virtual void d14();
  virtual int v68(int a, int b);
  virtual void d16();
  virtual void d17();
  virtual void d18();
  virtual int v84();
};
extern "C" {
igMemoryPool *Memory_GetAllocatorBySelector(int);
int FUN_0012aff0(char *, char *);
int strcmp(char *, char *);
igMemoryPool *igAliasMemoryPool_Create(igMemoryPool *);
igMemoryPool *igMetaObject_CreateInstance(int, igMemoryPool *);
int igObjectSystem_FindMetaByNameDefault(char *);
int igObject_Destroy(igMemoryPool *);
void MemoryContext_BuildAllocator(int *out, igMemoryPoolContextInfo *arg1, int idx, int flag);
extern int DAT_00586a88[4];
extern int DAT_00587018[4];
extern int DAT_00587020[4];
extern int DAT_00587030[4];
extern int DAT_00587040[4];
extern Gl *DAT_00587218[4];
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
extern char DAT_004fa2a8[], DAT_004fa2b0[], DAT_004fa5e8[], DAT_004fa5f0[], DAT_004fa600[], DAT_004fa620[], DAT_004fa630[], DAT_004fa638[], DAT_004fa640[], DAT_004fa648[], DAT_004fa658[], DAT_004fa668[], DAT_004fa678[], DAT_004fa680[], DAT_004fa688[], DAT_004fa690[], DAT_004fa698[];
}
#define RC(o) ((unsigned long long)(long long)(int)(o)->_refCount & 0x7fffffULL)
void MemoryContext_BuildAllocator(int *out, igMemoryPoolContextInfo *arg1, int idx, int flag) {
    MC *ctx = (MC *)arg1;
    R r0, r1, r2, r3, r4, r5, r6, r7;
    igMemoryPool *obj;
    int meta;
    Slot *slot;
    igMemoryPool *allocA;
    igMemoryPoolInfo *cfg;
    int al;
    int aligned;
    igMemoryPool *mbc;
    char *sub;
    igMemoryPool *allocB;
    igMemoryPool **pslot;
    bool owned;
    igMemoryPool *a;
    slot = &ctx->slots[idx];
    meta = DAT_00586a88[0];
    allocA = ctx->slots[0].obj;
    allocB = ctx->slots[1].obj;
    mbc = ctx->slots[3].obj;
    cfg = slot->cfg;
    owned = true;
    obj = slot->obj;
    if (allocA == 0) allocA = Memory_GetAllocatorBySelector(DAT_00587018[0]);
    if (allocB == 0) {
        allocB = Memory_GetAllocatorBySelector(DAT_00587020[0]);
        if (allocB == 0) allocB = allocA;
    }
    if (mbc == 0) Memory_GetAllocatorBySelector(DAT_00587030[0]);
    if (idx == 2) {
        slot->obj = allocB;
        allocB->_refCount = allocB->_refCount + 1;
    }
    if (cfg == 0) {
        if (idx >= 30) { *out = DAT_004fb410[0]; return; }
        *out = DAT_004fb418[0];
        return;
    }
    if (cfg->_scope != 0) {
        slot->f140 = 0;
        if (FUN_0012aff0((char *)cfg->_scope, DAT_004fa620) == 0) {
            if (FUN_0012aff0((char *)cfg->_scope, DAT_004fa2a8) != 0) slot->f140 = slot->f140 | 1;
            else if (FUN_0012aff0((char *)cfg->_scope, DAT_004fa2b0) != 0) slot->f140 = slot->f140 | 2;
        }
        if (FUN_0012aff0((char *)cfg->_scope, DAT_004fa630) != 0) slot->f140 = slot->f140 | 0x01000000;
        if (FUN_0012aff0((char *)cfg->_scope, DAT_004fa638) != 0) slot->f140 = slot->f140 | 0x02000000;
        if (FUN_0012aff0((char *)cfg->_scope, DAT_004fa600) != 0) slot->f140 = slot->f140 | 0x04000000;
        if (flag == 0) {
            int f = slot->f140;
            if ((((unsigned long long)((long long)f << 0x28)) >> 0x28) != 0 && (f & 0x05000000) != 0) {
                *out = DAT_004fb410[0];
                return;
            }
        }
    }
    if (obj != 0) {
        int size = cfg->_size;
        if (size != 0 && (cfg->_arenaType == 0 || strcmp((char *)cfg->_arenaType, DAT_004fa640) == 0)) {
            r0 = ((OV *)obj)->v172(size);
        }
    } else {
        char *name = (char *)cfg->_aliasedTo;
        if (name != 0 && *name != 0) {
            int j = ctx->v116(name);
            obj = 0;
            if (j != -1) {
                Slot *o = (Slot *)((char *)(j * 144) + (int)ctx + 20);
                pslot = &o->obj;
                obj = o->obj;
                if (obj == 0) {
                    int rv = ctx->v204(j, flag).get();
                    if (rv != DAT_004fb410[0]) { *out = DAT_004fb418[0]; return; }
                    obj = *pslot;
                }
            }
            if (obj != 0) {
                int refMode = !!(ctx->flags & 4);
                if (refMode) {
                    if (cfg->_scope != 0) {
                        if ((FUN_0012aff0((char *)cfg->_scope, DAT_004fa600) != 0 || FUN_0012aff0((char *)cfg->_scope, DAT_004fa648) != 0 || FUN_0012aff0((char *)cfg->_scope, DAT_004fa658) != 0) && flag == 0) {
                            *out = DAT_004fb410[0];
                            return;
                        }
                    }
                    if (idx == 5) {
                        if (Memory_GetAllocatorBySelector(DAT_00587040[0]) == 0) ctx->slots[5].obj = allocA;
                    }
                    {
                        igMemoryPool *old = obj;
                        obj = igAliasMemoryPool_Create(allocA);
                        ((OV *)obj)->v400(old);
                    }
                    if (idx == 5 && ctx->slots[5].obj == allocA) ctx->slots[5].obj = 0;
                } else {
                    owned = false;
                }
                ctx->v100(idx, obj);
                if (owned) {
                    obj->_refCount = obj->_refCount - 1;
                    if (RC(obj) == 0) igObject_Destroy(obj);
                }
                if (((OV *)obj)->v132() == 0) ((OV *)obj)->v120();
                *out = DAT_004fb410[0];
                return;
            }
        }
    {
        char *mname = (char *)cfg->_class;
        if (mname != 0 && *mname != 0) {
            int m = igObjectSystem_FindMetaByNameDefault(mname);
            meta = m;
            if (m == 0) meta = DAT_00586a88[0];
        }
    }
    {
        obj = igMetaObject_CreateInstance(meta, allocA);
        igMemoryPool *o2 = obj;
        int size = cfg->_size;
        al = size + (DAT_00587218[0]->v84() - 1);
        aligned = al & ~(DAT_00587218[0]->v84() - 1);
        if (size != 0) {
            char *kind = (char *)cfg->_arenaType;
            if (kind == 0 || strcmp(kind, DAT_004fa640) == 0) {
                r2 = ((OV *)o2)->v172(size);
            } else if (strcmp((char *)cfg->_arenaType, DAT_004fa5e8) == 0) {
                sub = (char *)cfg->_source;
                if (sub == 0 || *sub == 0) { a = allocB; goto common; }
                if (strcmp(sub, DAT_004fa668) == 0) {
b78:
                    int v = DAT_00587218[0]->v68(0, aligned);
                    r3 = ((OV *)o2)->v96(v, aligned, 0);
                    slot->f136 = slot->f136 | 2;
                } else if (strcmp(sub, DAT_004fa678) == 0 || strcmp(sub, DAT_004fa680) == 0 || strcmp(sub, DAT_004fa688) == 0) {
                    goto b78;
                } else if (strcmp(sub, DAT_004fa5f0) == 0) {
                    int dfl = cfg->_address;
                    int a2;
                    if (dfl != 0) a2 = dfl;
                    else a2 = 0x70000000;
                    r4 = ((OV *)o2)->v96(a2, (long long)size, 0);
                } else if (strcmp(sub, DAT_004fa690) != 0 && strcmp(sub, DAT_004fa698) != 0) {
                    a = ctx->v96(sub);
                    if (a == 0) a = allocB;
common:
                    if (((OV *)a)->v132() == 0) ((OV *)a)->v120();
                    r5 = ((OV *)o2)->v96(((OV *)a)->v216(size), (long long)size, 1);
                    a->_refCount = a->_refCount + 1;
                    slot->f136 = slot->f136 | 1;
                }
            }
        }
        r6 = ((OV *)o2)->v180(cfg);
        ctx->v100(idx, o2);
        o2->_refCount = o2->_refCount - 1;
        if (RC(o2) == 0) igObject_Destroy(o2);
    }
    }
    if (((OV *)obj)->v132() == 0) ((OV *)obj)->v120();
    *out = DAT_004fb410[0];
}
