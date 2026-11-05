/* 0x004435c0 - FUN_004435c0 (832 bytes). Fills a menu-row record (out) for entry arg3 of table arg2
 * from the owner context: caches the owner's data-base object, interns the row's name string and
 * copies the row's scalar columns. Build: alternate combat compiler, -O3,p -Iinclude. */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int FUN_002eb010(int);
struct PropertyIntArray *FUN_003a9250(int, int *);
igObject *beMessenger_GetObject(int, int);
int FUN_003fa3b0(beNDMWGameRam *, int, int, int);
int FUN_003fa850(beNDMWGameRam *, int, int, int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
int beDataBase_GetRecordString(int, int, int *);
int beMessenger_SendNamed(int, int *, int *, int, int *);
int igObject_Destroy(igObject *);
extern int DAT_00519420[4];
extern int DAT_00519430[4];
extern int DAT_00519438[4];
extern int DAT_0051d1f8[4];
extern int DAT_0051d208[4];
extern int DAT_0051d210[4];
extern int DAT_00586f20[4];

/* property record returned by FUN_003a9250: its int list sits at +12 (no reflected class
 * recovered for the holder; same shape as PropertyIntArray in beNDMWGameRam_SaveBase.c) */
struct PropertyIntArray { char pad[12]; igIntList *list; };

void FUN_004435c0(beNDMWShinkaObject *out, beNDMWGameRam *ctx, int arg2, int arg3) {
    igObject *o;
    igObject *old;
    int s;
    int pool;
    int ref;
    int oldref;
    int *hdr;
    int cnt;
    struct PropertyIntArray *t1;
    struct PropertyIntArray *t2;
    igIntList *sd;
    out->_id = arg3;
    if (ctx->_dBShinka == 0) {
        beMessenger_SendNamed(ctx->_messenger, &DAT_00519438[0], &DAT_00519430[0], 0, &DAT_00519420[0]);
        o = beMessenger_GetObject(ctx->_messenger, 0);
        if (o != 0) {
            o->_refCount = o->_refCount + 1;
        }
        old = (igObject *)ctx->_dBShinka;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(old);
            }
        }
        ctx->_dBShinka = (int)o;
    }
    s = beDataBase_GetRecordString(ctx->_dBShinka, arg3, &DAT_0051d208[0]);
    if (DAT_00586f20[0] == 0) {
        pool = FUN_002eb010(16);
        if (pool != 0)
            pool = StringPool_Construct(pool);
        DAT_00586f20[0] = pool;
    }
    ref = StringPool_Intern(DAT_00586f20[0], s);
    oldref = out->_name;
    if (oldref != 0) {
        hdr = (int *)(oldref - 8);
        cnt = *(int *)(oldref - 4) - 1;
        *(int *)(oldref - 4) = cnt;
        if (cnt == 0)
            StringChunk_ReleaseHeader(*hdr, hdr);
    }
    out->_name = ref;
    t1 = FUN_003a9250(((int *)((igIntList *)ctx->_playerDataListList)->_data)[arg2], &DAT_0051d1f8[0]);
    out->_level = ((int *)t1->list->_data)[arg3];
    out->_hpMax = FUN_003fa3b0(ctx, arg2, arg3, 1);
    out->_mpMax = FUN_003fa3b0(ctx, arg2, arg3, 0);
    out->_tsuyosa = FUN_003fa850(ctx, arg2, arg3, 0);
    out->_mamori = FUN_003fa850(ctx, arg2, arg3, 1);
    out->_kashikosa = FUN_003fa850(ctx, arg2, arg3, 2);
    out->_seishin = FUN_003fa850(ctx, arg2, arg3, 3);
    out->_subayasa = FUN_003fa850(ctx, arg2, arg3, 4);
    t2 = FUN_003a9250(((int *)((igIntList *)ctx->_playerDataListList)->_data)[arg2], &DAT_0051d210[0]);
    sd = t2->list;
    out->_blunt = *(int *)(sd->_data + arg3 * 36);
    out->_slash = *(int *)(sd->_data + (arg3 * 9 + 1) * 4);
    out->_stab = *(int *)(sd->_data + (arg3 * 9 + 2) * 4);
    out->_bash = *(int *)(sd->_data + (arg3 * 9 + 3) * 4);
    out->_shot = *(int *)(sd->_data + (arg3 * 9 + 4) * 4);
    out->_crush = *(int *)(sd->_data + (arg3 * 9 + 5) * 4);
    out->_blast = *(int *)(sd->_data + (arg3 * 9 + 6) * 4);
    out->_heal = *(int *)(sd->_data + (arg3 * 9 + 7) * 4);
    out->_force = *(int *)(sd->_data + (arg3 * 9 + 8) * 4);
}
} /* extern "C" */
