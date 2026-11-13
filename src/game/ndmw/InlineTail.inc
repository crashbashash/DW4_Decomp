igMetaObject *Gap__Bec__beNDMWAfsSetupData__vfunc_20(void)
{
    return g_beNDMWAfsSetupData_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWAfsSetupDataList__vfunc_20(void)
{
    return g_beNDMWAfsSetupDataList_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWAfsSetupInfo__vfunc_20(void)
{
    return g_beNDMWAfsSetupInfo_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWGameRamInfo__vfunc_20(void)
{
    return g_beNDMWGameRamInfo_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWGameRamInfoRam__vfunc_20(void)
{
    return g_beNDMWGameRamInfoRam_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWShinkaObject__vfunc_20(void)
{
    return g_beNDMWShinkaObject_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWShinkaObjectList__vfunc_20(void)
{
    return g_beNDMWShinkaObjectList_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWShinkaCtrl__vfunc_20(void)
{
    return g_beNDMWShinkaCtrl_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWItemBaseList__vfunc_20(void)
{
    return g_beNDMWItemBaseList_metaObject[0];
}

int Gap__Bec__beNDMWItemBase__vfunc_24(void) {
    return 0;
}

int Gap__Bec__beNDMWItemBase__vfunc_25(void) {
    return 0;
}

void Gap__Bec__beNDMWItemBase__vfunc_26(void)
{
}

igMetaObject *Gap__Bec__beNDMWLoadCtrl2CtrlData__vfunc_20(void)
{
    return g_beNDMWLoadCtrl2CtrlData_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWLoadIntf2TextOrder__vfunc_20(void)
{
    return g_beNDMWLoadIntf2TextOrder_metaObject[0];
}

igMetaObject *Gap__Bec__beLoadIntf2ComMdlData__vfunc_20(void)
{
    return g_beLoadIntf2ComMdlData_metaObject[0];
}

igMetaObject *Gap__Bec__beLoadIntf2ComMdlDataList__vfunc_20(void)
{
    return g_beLoadIntf2ComMdlDataList_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWLoadIntf2ComMdlCtrl__vfunc_20(void)
{
    return g_beNDMWLoadIntf2ComMdlCtrl_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWLoadIntf2MesWin__vfunc_20(void)
{
    return g_beNDMWLoadIntf2MesWin_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWDegiData__vfunc_20(void)
{
    return g_beNDMWDegiData_metaObject[0];
}

void Gap__Bec__beNDMWDegiData__vfunc_07(beNDMWDegiData *arg0, int arg1) {
    int a;

    Gap__Core__igObject__vfunc_07(arg0, arg1);
    igMetaObject_CountInstances(((Obj_3cb2f0 *)arg0)->vX(), 1);
    if (!(arg1 & 0xFF)) {
        arg0->_dataSize = 0x2000;
        a = igObject_GetAllocator(arg0);
        a = g_useOwnerAllocator ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        arg0->_data = Memory_AllocateBufferDirect(0x2000, a);
    }
}

void Gap__Bec__beNDMWDegiData__vfunc_08(V88 *arg0) {
    int a;

    if (arg0->f28 != 0) {
        a = igObject_GetAllocator(arg0);
        a = g_useOwnerAllocator != 0 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        Memory_FreeBufferWithAllocator(arg0->f28, a);
    }
    arg0->f28 = 0;
    igMetaObject_CountInstances(arg0->vX(), 1);
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}

igMetaObject *Gap__Bec__beNDMWDegiDataList__vfunc_20(void)
{
    return g_beNDMWDegiDataList_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWLoadSlotPlayer__vfunc_20(void)
{
    return g_beNDMWLoadSlotPlayer_metaObject[0];
}

void Gap__Bec__beNDMWLoadSlotPlayer__vfunc_07(void **arg0) {
    Gap__Core__igObject__vfunc_07();
    igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1);
}

static inline int countOf(const beNDMWDegiDataList *l) { return l->_count; }

/* matching construct: the dummy-virtual slots only provide the vtable call at +88; data is read through the reflected class */
void Gap__Bec__beNDMWLoadSlotPlayer__vfunc_08(Obj_3cb470 *arg0) {
    beNDMWLoadSlotPlayer *self = (beNDMWLoadSlotPlayer *)arg0;
    beNDMWDegiDataList *l = (beNDMWDegiDataList *)self->_saveDataList;
    int n;
    if (countOf(l) > 0) {
    n = l->_count;
    int i = 0;
    int off;
    int j;
    if (0 < n) {
        off = 0;
        do {
            Rel::go(((igObject **)l->_data)[i]);
            i++;
            off += 4;
        } while (i < n);
    }
    int n2 = l->_count;
    int v = 0;
    if (0 < n2) {
        int lim;
        int off3;
        int off4;
        if (n2 > 8) {
            lim = n2 - 8;
            off3 = 0;
            do {
                v += 8;
                ((int *)(l->_data + off3))[0] = 0;
                ((int *)(l->_data + off3))[1] = 0;
                ((int *)(l->_data + off3))[2] = 0;
                ((int *)(l->_data + off3))[3] = 0;
                ((int *)(l->_data + off3))[4] = 0;
                ((int *)(l->_data + off3))[5] = 0;
                ((int *)(l->_data + off3))[6] = 0;
                ((int *)(l->_data + off3))[7] = 0;
                off3 += 32;
            } while (v < lim);
        }
        off4 = v * 4;
        if (v < n2) {
            do {
                v++;
                ((int *)(l->_data + off4))[0] = 0;
                off4 += 4;
            } while (v < n2);
        }
    }
    l->_count = 0;
    }
    {
        igIntList *l2 = (igIntList *)self->_accessPlList;
        if (l2->_count > 0) {
            l2->_count = 0;
        }
    }
    igMetaObject_CountInstances(arg0->v88(), 1);
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}

igMetaObject *Gap__Bec__beNDMWLoadSlotPlayerList__vfunc_20(void)
{
    return g_beNDMWLoadSlotPlayerList_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWMcSlotPS2__vfunc_20(void)
{
    return g_beNDMWMcSlotPS2_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWMcSlotGC__vfunc_20(void)
{
    return g_beNDMWMcSlotGC_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWMcSlotXbox__vfunc_20(void)
{
    return g_beNDMWMcSlotXbox_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWMcSlotList__vfunc_20(void)
{
    return g_beNDMWMcSlotList_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWLoadSavePlWork__vfunc_20(void)
{
    return g_beNDMWLoadSavePlWork_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWLoadSavePlWorkList__vfunc_20(void)
{
    return g_beNDMWLoadSavePlWorkList_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWMcUtilCtrl__vfunc_20(void)
{
    return g_beNDMWMcUtilCtrl_metaObject[0];
}

void Gap__Bec__beNDMWMcUtilCtrl__vfunc_07(beNDMWMcUtilCtrl *arg0) {
    Gap__Core__igObject__vfunc_07();
    igMetaObject_CountInstances(((DW4VC_88_0 *)(((char *)(arg0) + 0)))->vX(), 1);
    beSaveDataDeliver_AllocateData(arg0->_svData, 0x8000);
}

void Gap__Bec__beNDMWMcUtilCtrl__vfunc_08(beNDMWMcUtilCtrl *arg0) {
    beSaveDataDeliver_FreeData(arg0->_svData);
    igMetaObject_CountInstances(((DW4VC_88_0 *)(((char *)(arg0) + 0)))->vX(), 1);
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}

igMetaObject *Gap__Bec__beNDMWLoadCtrl2CommonIntf__vfunc_20(void)
{
    return g_beNDMWLoadCtrl2CommonIntf_metaObject[0];
}

static inline int countOf_3cb760(const beNDMWDegiDataList *l) { return l->_count; }

static inline int countOf_3cb760(const beNDMWLoadSavePlWorkList *l) { return l->_count; }

void Gap__Bec__beNDMWLoadCtrl2CommonIntf__vfunc_08(beNDMWLoadCtrl2CommonIntf *arg0) {
    beNDMWDegiDataList *l = (beNDMWDegiDataList *)arg0->_gameUseData;
    if (countOf_3cb760(l) > 0) {
        int n = l->_count;
        int i;
        igObject *o;
        for (i = 0; i < n; i++) {
            o = ((igObject **)l->_data)[i];
            if (o != 0) {
                o->_refCount = (int)o->_refCount - 1;
                if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(o);
                }
            }
        }
        {
            int m = l->_count;
            int j;
            for (j = 0; j < m; j++) {
                ((igObject **)l->_data)[j] = 0;
            }
        }
        l->_count = 0;
    }
    {
    beNDMWLoadSavePlWorkList *l2 = (beNDMWLoadSavePlWorkList *)arg0->_flagWork;
    if (countOf_3cb760(l2) > 0) {
        int n = l2->_count;
        int i;
        igObject *o;
        for (i = 0; i < n; i++) {
            o = ((igObject **)l2->_data)[i];
            if (o != 0) {
                o->_refCount = (int)o->_refCount - 1;
                if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(o);
                }
            }
        }
        {
            int m = l2->_count;
            int j;
            for (j = 0; j < m; j++) {
                ((igObject **)l2->_data)[j] = 0;
            }
        }
        l2->_count = 0;
    }
    }
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}

igMetaObject *Gap__Bec__beNDMWLoadCtrl2Info__vfunc_20(void)
{
    return g_beNDMWLoadCtrl2Info_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWLoadIntf2CtrlData__vfunc_20(void)
{
    return g_beNDMWLoadIntf2CtrlData_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWLoadIntf2MakeChr__vfunc_20(void)
{
    return g_beNDMWLoadIntf2MakeChr_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWLoadIntf2DegiState__vfunc_20(void)
{
    return g_beNDMWLoadIntf2DegiState_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWLoadIntf2DegiStateList__vfunc_20(void)
{
    return g_beNDMWLoadIntf2DegiStateList_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWLoadIntf2DegiStateCtrl__vfunc_20(void)
{
    return g_beNDMWLoadIntf2DegiStateCtrl_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWLoadIntf2DataSelIntf__vfunc_20(void)
{
    return g_beNDMWLoadIntf2DataSelIntf_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWLoadIntf2Diffselect__vfunc_20(void)
{
    return g_beNDMWLoadIntf2Diffselect_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWLoadIntf2SelSlot__vfunc_20(void)
{
    return g_beNDMWLoadIntf2SelSlot_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWLoadIntf2ChrDataSel__vfunc_20(void)
{
    return g_beNDMWLoadIntf2ChrDataSel_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWLoadIntf2NameSel__vfunc_20(void)
{
    return g_beNDMWLoadIntf2NameSel_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWLoadIntf2Info__vfunc_20(void)
{
    return g_beNDMWLoadIntf2Info_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWLogoCtrlData__vfunc_20(void)
{
    return g_beNDMWLogoCtrlData_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWLogoInfo__vfunc_20(void)
{
    return g_beNDMWLogoInfo_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWMdlEnemyInfoWork__vfunc_20(void)
{
    return g_beNDMWMdlEnemyInfoWork_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWMdlItemInfoWork__vfunc_20(void)
{
    return g_beNDMWMdlItemInfoWork_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWMdlPlayerInfoWork__vfunc_20(void)
{
    return g_beNDMWMdlPlayerInfoWork_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWMdlPlayer2InfoWork__vfunc_20(void)
{
    return g_beNDMWMdlPlayer2InfoWork_metaObject[0];
}

igMetaObject *FUN_003cbb40(void) {
    return g_beNDMWPanelObject_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWPanelWazaInfoWork__vfunc_20(void)
{
    return g_beNDMWPanelWazaInfoWork_metaObject[0];
}

void Gap__Bec__beNDMWPanelWazaInfoWork__vfunc_07(beNDMWPanelWazaInfoWork *arg0) {
    int n;
    char **p;
    igDataList *l;
    char *old;
    int n2;
    int *q;
    int i;
    int k;
    int *a1;
    int rc;
    char *t;

    Gap__Core__igObject__vfunc_07();
    l = (igDataList *)arg0->_textSetList;
    if (l->_count < 0x31) {
        List_Reserve(l, 0x30, 4);
    }
    StringList_Resize((igDataList *)arg0->_textSetList, 0x30);
    {
        /* every text slot takes a share of one empty token */
        StringRef_3cbb60 empty(0);
        l = (igDataList *)arg0->_textSetList;
        n = l->_count;
        p = (char **)l->_data;
        for (i = 0; i < n; i++) {
            t = empty.p;
            if (t != 0) {
                ((int *)t)[-1] = ((int *)t)[-1] + 1;
            }
            old = *p;
            if (old != 0) {
                a1 = (int *)old - 2;
                rc = ((int *)old)[-1] - 1;
                ((int *)old)[-1] = rc;
                if (rc == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
            *p = empty.p;
            p++;
        }
    }
    l = (igDataList *)arg0->_textColorList;
    if (l->_count < 0x31) {
        List_Reserve(l, 0x30, 4);
    }
    l = (igDataList *)arg0->_textColorList;
    if (l->_capacity >= 0x30) {
        l->_count = 0x30;
    } else {
        List_Resize(l, 0x30, 4);
    }
    l = (igDataList *)arg0->_textColorList;
    n2 = l->_count;
    q = (int *)l->_data;
    for (k = 0; k < n2; k++) {
        q[k] = DAT_004c9228[0];
    }
}

void Gap__Bec__beNDMWPanelWazaInfoWork__vfunc_16(beNDMWPanelWazaInfoWork *arg0) {
    int *temp_a1;
    int temp_v0;
    int var_v0;
    int *old;
    int *s1;
    igObject *t;

    arg0->_retIsFire = 0;
    if (g_stringPool[0] == 0) {
        var_v0 = StringPool_Allocate(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        g_stringPool[0] = var_v0;
    }
    s1 = (int *)StringPool_Intern(g_stringPool[0], 0);
    old = (int *)arg0->_retWazaLabel;
    if (old != 0) {
        temp_a1 = old - 2;
        temp_v0 = old[-1] - 1;
        old[-1] = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    arg0->_retWazaLabel = (int)s1;
    t = (igObject *)arg0->_playerWork;
    if (t != 0) {
        t->_refCount = t->_refCount - 1;
        if ((t->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->_playerWork = 0;
    {
        StringRef_3cbd80 empty(0);
        FUN_003cc490((igDataList *)(((void *)FUN_003cc540(arg0))), (char **)&empty);
    }
    FUN_003cc3d0((igIntList *)FUN_003cc480(arg0), &DAT_004c9220[0]);
    ((PanelVirtualShim *)arg0->_panelWaza)->vX();
    ((PanelVirtualShim *)arg0->_panelItem)->vX();
    ((PanelVirtualShim *)arg0->_panelStat)->vX();
}

void Gap__Bec__beNDMWPanelObjectStat__vfunc_16(beNDMWPanelObjectStat *arg0) {
/* matching construct: locals zero-initialised and declared in the order that reproduces retail register assignment */
    igDataList *l = 0;
    int n = 0;
    int i = 0;
    const char *held = 0;
    const char **slot = 0;
    const char *tok = 0;
    int off = 0;
    RefRelease::go((igObject *)arg0->_playerDataList);
    arg0->_playerDataList = 0;
    RefRelease::go((igObject *)arg0->_playerWork);
    arg0->_playerWork = 0;
    l = (igDataList *)arg0->_listFolder;
    n = l->_count;
    i = 0;
    if (0 < n) {
        off = 0;
        do {
            slot = (const char **)((char *)l->_data + off);
            if (((void * *)g_stringPool)[0] == 0) {
                void *pool = ((void *)StringPool_Allocate(0x10));
                if (pool != 0) pool = ((void *)StringPool_Construct(pool));
                ((void * *)g_stringPool)[0] = pool;
            }
            tok = ((const char *)StringPool_Intern(((void * *)g_stringPool)[0], 0));
            held = *slot;
            if (held != 0) {
                int *hd = (int *)held - 2;
                int cnt = ((int *)held)[-1] - 1;
                ((int *)held)[-1] = cnt;
                if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd);
            }
            i++;
            *slot = tok;
            off += 4;
        } while (i < n);
    }
    l->_count = 0;
    ((igDataList *)arg0->_listColor)->_count = 0;
}

void Gap__Bec__beNDMWPanelObjectItem__vfunc_16(beNDMWPanelObjectItem *arg0) {
    igObjectList *l;
    ReleaseRef::go((igObject *)arg0->_playerDataList);
    arg0->_playerDataList = 0;
    l = (igObjectList *)arg0->_listFolder;
    int n = l->_count;
    int i = 0;
    int off;
    int j;
    if (0 < n) {
        off = 0;
        do {
            ReleaseRef::go(*(igObject **)((char *)l->_data + off));
            i++;
            off += 4;
        } while (i < n);
    }
    int n2 = l->_count;
    int v = 0;
    if (0 < n2) {
        int lim;
        int off3;
        int off4;
        /* matching construct: hand-unrolled by 8 like the retail zero loop */
        if (n2 > 8) {
            lim = n2 - 8;
            off3 = 0;
            do {
                v += 8;
                *(int *)((char *)l->_data + off3) = 0;
                *(int *)((char *)l->_data + off3 + 4) = 0;
                *(int *)((char *)l->_data + off3 + 8) = 0;
                *(int *)((char *)l->_data + off3 + 12) = 0;
                *(int *)((char *)l->_data + off3 + 16) = 0;
                *(int *)((char *)l->_data + off3 + 20) = 0;
                *(int *)((char *)l->_data + off3 + 24) = 0;
                *(int *)((char *)l->_data + off3 + 28) = 0;
                off3 += 32;
            } while (v < lim);
        }
        off4 = v * 4;
        if (v < n2) {
            do {
                v++;
                *(int *)((char *)l->_data + off4) = 0;
                off4 += 4;
            } while (v < n2);
        }
    }
    l->_count = 0;
    ((igDataList *)arg0->_listColor)->_count = 0;
}

void Gap__Bec__beNDMWPanelObjectWaza__vfunc_16(beNDMWPanelObjectWaza *arg0) {
    igObjectList *l;
    ReleaseRef::go((igObject *)arg0->_playerDataList);
    arg0->_playerDataList = 0;
    l = (igObjectList *)arg0->_listFolder;
    int n = l->_count;
    int i = 0;
    int off;
    int j;
    if (0 < n) {
        off = 0;
        do {
            ReleaseRef::go(*(igObject **)((char *)l->_data + off));
            i++;
            off += 4;
        } while (i < n);
    }
    int n2 = l->_count;
    int v = 0;
    if (0 < n2) {
        int lim;
        int off3;
        int off4;
        if (n2 > 8) {
            lim = n2 - 8;
            off3 = 0;
            do {
                v += 8;
                *(int *)((char *)l->_data + off3) = 0;
                *(int *)((char *)l->_data + off3 + 4) = 0;
                *(int *)((char *)l->_data + off3 + 8) = 0;
                *(int *)((char *)l->_data + off3 + 12) = 0;
                *(int *)((char *)l->_data + off3 + 16) = 0;
                *(int *)((char *)l->_data + off3 + 20) = 0;
                *(int *)((char *)l->_data + off3 + 24) = 0;
                *(int *)((char *)l->_data + off3 + 28) = 0;
                off3 += 32;
            } while (v < lim);
        }
        off4 = v * 4;
        if (v < n2) {
            do {
                v++;
                *(int *)((char *)l->_data + off4) = 0;
                off4 += 4;
            } while (v < n2);
        }
    }
    l->_count = 0;
    ((igObjectList *)arg0->_listColor)->_count = 0;
}

void FUN_003cc3d0(igIntList *arg0, int *arg1) {
    int n = arg0->_count;
    int *d = (int *)arg0->_data;
    int i;
    for (i = 0; i < n; i++) {
        d[i] = *arg1;
    }
}

int FUN_003cc480(beNDMWPanelWazaInfoWork *p)
{
    return p->_textColorList;
}

void FUN_003cc490(igDataList *arg0, char **arg1) {
    int *temp_a1;
    int temp_s2;
    int temp_v1;
    char **var_s1;
    int var_s0;
    char *temp_a0;
    char *temp_a0_2;

    temp_s2 = arg0->_count;
    var_s1 = (char **)arg0->_data;
    var_s0 = 0;
    if (0 < temp_s2) {
        do {
            temp_a0 = *arg1;
            if (temp_a0 != 0) {
                *(int *)(temp_a0 - 4) = *(int *)(temp_a0 - 4) + 1;
            }
            temp_a0_2 = *var_s1;
            if (temp_a0_2 != 0) {
                temp_a1 = (int *)(temp_a0_2 - 8);
                temp_v1 = *(int *)(temp_a0_2 - 4) - 1;
                *(int *)(temp_a0_2 - 4) = temp_v1;
                if (temp_v1 == 0) {
                    StringChunk_ReleaseHeader(*temp_a1, temp_a1);
                }
            }
            var_s0 += 1;
            *var_s1 = *arg1;
            var_s1 += 1;
        } while (var_s0 < temp_s2);
    }
}

/* +40 is _textSetList, a 4-byte arena/object handle. */
int FUN_003cc540(beNDMWPanelWazaInfoWork *p)
{
    return p->_textSetList;
}

int *FUN_003cc550(int *arg0, int arg1) {
    int var_v0;
    int var_v0_2;

    if (arg1 == 0) {
        var_v0 = 0;
    } else {
        if (g_stringPool[0] == 0) {
            var_v0_2 = StringPool_Allocate(0x10);
            if (var_v0_2 != 0) {
                var_v0_2 = StringPool_Construct(var_v0_2);
            }
            g_stringPool[0] = var_v0_2;
        }
        var_v0 = ((int)StringPool_Intern(g_stringPool[0], arg1));
    }
    *arg0 = var_v0;
    return arg0;
}

igMetaObject *Gap__Bec__beNDMWPanelWazaInfoRam__vfunc_20(void)
{
    return g_beNDMWPanelWazaInfoRam_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWPanelWazaInfo__vfunc_20(void)
{
    return g_beNDMWPanelWazaInfo_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWSaveCtrlCtrlData__vfunc_20(void)
{
    return g_beNDMWSaveCtrlCtrlData_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWSaveCtrlInfo__vfunc_20(void)
{
    return g_beNDMWSaveCtrlInfo_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWSaveIntfCtrlData__vfunc_20(void)
{
    return g_beNDMWSaveIntfCtrlData_metaObject[0];
}

igMetaObject *Gap__Bec__beSaveIntfComMdlData__vfunc_20(void)
{
    return g_beSaveIntfComMdlData_metaObject[0];
}

igMetaObject *Gap__Bec__beSaveIntfComMdlDataList__vfunc_20(void)
{
    return g_beSaveIntfComMdlDataList_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWSaveIntfComMdlCtrl__vfunc_20(void)
{
    return g_beNDMWSaveIntfComMdlCtrl_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWSaveIntfInfo__vfunc_20(void)
{
    return g_beNDMWSaveIntfInfo_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWStageCtlInfo__vfunc_20(void)
{
    return g_beNDMWStageCtlInfo_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWStageCtlInfoRam__vfunc_20(void)
{
    return g_beNDMWStageCtlInfoRam_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWWindowCtrl__vfunc_20(void)
{
    return g_beNDMWWindowCtrl_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWStatusInfoWork__vfunc_20(void)
{
    return g_beNDMWStatusInfoWork_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWStatusInfoRam__vfunc_20(void)
{
    return g_beNDMWStatusInfoRam_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWStatusInfo__vfunc_20(void)
{
    return g_beNDMWStatusInfo_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWWindow__vfunc_20(void)
{
    return g_beNDMWWindow_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWTitle2CtrlData__vfunc_20(void)
{
    return g_beNDMWTitle2CtrlData_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWTitle2Option__vfunc_20(void)
{
    return g_beNDMWTitle2Option_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWTitle2Info__vfunc_20(void)
{
    return g_beNDMWTitle2Info_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWWindowList__vfunc_20(void)
{
    return g_beNDMWWindowList_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWAfsSetupDataList__vfunc_22(void)
{
    return g_beNDMWAfsSetupData_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWShinkaObjectList__vfunc_22(void)
{
    return g_beNDMWShinkaObject_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWLoadIntf2DegiStateList__vfunc_22(void)
{
    return g_beNDMWLoadIntf2DegiState_metaObject[0];
}

igMetaObject *Gap__Bec__beSaveIntfComMdlDataList__vfunc_22(void)
{
    return g_beSaveIntfComMdlData_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWItemBaseList__vfunc_22(void)
{
    return g_beNDMWItemBase_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWLoadSavePlWorkList__vfunc_22(void)
{
    return g_beNDMWLoadSavePlWork_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWMcSlotList__vfunc_22(void)
{
    return g_beNDMWMcSlot_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWLoadSlotPlayerList__vfunc_22(void)
{
    return g_beNDMWLoadSlotPlayer_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWDegiDataList__vfunc_22(void)
{
    return g_beNDMWDegiData_metaObject[0];
}

igMetaObject *Gap__Bec__beLoadIntf2ComMdlDataList__vfunc_22(void)
{
    return g_beLoadIntf2ComMdlData_metaObject[0];
}

igMetaObject *Gap__Bec__beNDMWWindowList__vfunc_22(void)
{
    return g_beNDMWWindow_metaObject[0];
}

