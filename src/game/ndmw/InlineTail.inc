igMetaObject *beNDMWAfsSetupData_GetMeta(void)
{
    return g_beNDMWAfsSetupData_metaObject;
}

igMetaObject *beNDMWAfsSetupDataList_GetMeta(void)
{
    return g_beNDMWAfsSetupDataList_metaObject;
}

igMetaObject *beNDMWAfsSetupInfo_GetMeta(void)
{
    return g_beNDMWAfsSetupInfo_metaObject;
}

igMetaObject *beNDMWGameRamInfo_GetMeta(void)
{
    return g_beNDMWGameRamInfo_metaObject;
}

igMetaObject *beNDMWGameRamInfoRam_GetMeta(void)
{
    return g_beNDMWGameRamInfoRam_metaObject;
}

igMetaObject *beNDMWShinkaObject_GetMeta(void)
{
    return g_beNDMWShinkaObject_metaObject;
}

igMetaObject *beNDMWShinkaObjectList_GetMeta(void)
{
    return g_beNDMWShinkaObjectList_metaObject;
}

igMetaObject *beNDMWShinkaCtrl_GetMeta(void)
{
    return g_beNDMWShinkaCtrl_metaObject;
}

igMetaObject *beNDMWItemBaseList_GetMeta(void)
{
    return g_beNDMWItemBaseList_metaObject;
}

int beNDMWItemBase_Use(void) {
    return 0;
}

int beNDMWItemBase_Pack(void) {
    return 0;
}

void beNDMWItemBase_Unpack(void)
{
}

igMetaObject *beNDMWLoadCtrl2CtrlData_GetMeta(void)
{
    return g_beNDMWLoadCtrl2CtrlData_metaObject;
}

igMetaObject *beNDMWLoadIntf2TextOrder_GetMeta(void)
{
    return g_beNDMWLoadIntf2TextOrder_metaObject;
}

igMetaObject *beLoadIntf2ComMdlData_GetMeta(void)
{
    return g_beLoadIntf2ComMdlData_metaObject;
}

igMetaObject *beLoadIntf2ComMdlDataList_GetMeta(void)
{
    return g_beLoadIntf2ComMdlDataList_metaObject;
}

igMetaObject *beNDMWLoadIntf2ComMdlCtrl_GetMeta(void)
{
    return g_beNDMWLoadIntf2ComMdlCtrl_metaObject;
}

igMetaObject *beNDMWLoadIntf2MesWin_GetMeta(void)
{
    return g_beNDMWLoadIntf2MesWin_metaObject;
}

igMetaObject *beNDMWDegiData_GetMeta(void)
{
    return g_beNDMWDegiData_metaObject;
}

void beNDMWDegiData_userConstruct(beNDMWDegiData *arg0, int arg1) {
    int a;

    Gap__Core__igObject__userConstruct(arg0, arg1);
    igMetaObject_CountInstances(((Obj_3cb2f0 *)arg0)->vX(), 1);
    if (!(arg1 & 0xFF)) {
        arg0->_dataSize = 0x2000;
        a = igObject_GetAllocator(arg0);
        a = g_useOwnerAllocator ? a : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
        arg0->_data = Memory_AllocateBufferDirect(0x2000, a);
    }
}

void beNDMWDegiData_userDestruct(V88 *arg0) {
    int a;

    if (arg0->f28 != 0) {
        a = igObject_GetAllocator(arg0);
        a = g_useOwnerAllocator != 0 ? a : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
        Memory_FreeBufferWithAllocator(arg0->f28, a);
    }
    arg0->f28 = 0;
    igMetaObject_CountInstances(arg0->vX(), 1);
    Gap__Core__igObject__userDestruct(arg0);
}

igMetaObject *beNDMWDegiDataList_GetMeta(void)
{
    return g_beNDMWDegiDataList_metaObject;
}

igMetaObject *beNDMWLoadSlotPlayer_GetMeta(void)
{
    return g_beNDMWLoadSlotPlayer_metaObject;
}

void beNDMWLoadSlotPlayer_userConstruct(void **arg0) {
    Gap__Core__igObject__userConstruct();
    igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1);
}

static inline int countOf(const beNDMWDegiDataList *l) { return l->_count; }

/* matching construct: the dummy-virtual slots only provide the vtable call at +88; data is read through the reflected class */
void beNDMWLoadSlotPlayer_userDestruct(Obj_3cb470 *arg0) {
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
    Gap__Core__igObject__userDestruct(arg0);
}

igMetaObject *beNDMWLoadSlotPlayerList_GetMeta(void)
{
    return g_beNDMWLoadSlotPlayerList_metaObject;
}

igMetaObject *beNDMWMcSlotPS2_GetMeta(void)
{
    return g_beNDMWMcSlotPS2_metaObject;
}

igMetaObject *beNDMWMcSlotGC_GetMeta(void)
{
    return g_beNDMWMcSlotGC_metaObject;
}

igMetaObject *beNDMWMcSlotXbox_GetMeta(void)
{
    return g_beNDMWMcSlotXbox_metaObject;
}

igMetaObject *beNDMWMcSlotList_GetMeta(void)
{
    return g_beNDMWMcSlotList_metaObject;
}

igMetaObject *beNDMWLoadSavePlWork_GetMeta(void)
{
    return g_beNDMWLoadSavePlWork_metaObject;
}

igMetaObject *beNDMWLoadSavePlWorkList_GetMeta(void)
{
    return g_beNDMWLoadSavePlWorkList_metaObject;
}

igMetaObject *beNDMWMcUtilCtrl_GetMeta(void)
{
    return g_beNDMWMcUtilCtrl_metaObject;
}

void beNDMWMcUtilCtrl_userConstruct(beNDMWMcUtilCtrl *arg0) {
    Gap__Core__igObject__userConstruct();
    igMetaObject_CountInstances(((DW4VC_88_0 *)(((char *)(arg0) + 0)))->vX(), 1);
    beSaveDataDeliver_AllocateData(arg0->_svData, 0x8000);
}

void beNDMWMcUtilCtrl_userDestruct(beNDMWMcUtilCtrl *arg0) {
    beSaveDataDeliver_FreeData(arg0->_svData);
    igMetaObject_CountInstances(((DW4VC_88_0 *)(((char *)(arg0) + 0)))->vX(), 1);
    Gap__Core__igObject__userDestruct(arg0);
}

igMetaObject *beNDMWLoadCtrl2CommonIntf_GetMeta(void)
{
    return g_beNDMWLoadCtrl2CommonIntf_metaObject;
}

static inline int countOf_3cb760(const beNDMWDegiDataList *l) { return l->_count; }

static inline int countOf_3cb760(const beNDMWLoadSavePlWorkList *l) { return l->_count; }

void beNDMWLoadCtrl2CommonIntf_userDestruct(beNDMWLoadCtrl2CommonIntf *arg0) {
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
    Gap__Core__igObject__userDestruct(arg0);
}

igMetaObject *beNDMWLoadCtrl2Info_GetMeta(void)
{
    return g_beNDMWLoadCtrl2Info_metaObject;
}

igMetaObject *beNDMWLoadIntf2CtrlData_GetMeta(void)
{
    return g_beNDMWLoadIntf2CtrlData_metaObject;
}

igMetaObject *beNDMWLoadIntf2MakeChr_GetMeta(void)
{
    return g_beNDMWLoadIntf2MakeChr_metaObject;
}

igMetaObject *beNDMWLoadIntf2DegiState_GetMeta(void)
{
    return g_beNDMWLoadIntf2DegiState_metaObject;
}

igMetaObject *beNDMWLoadIntf2DegiStateList_GetMeta(void)
{
    return g_beNDMWLoadIntf2DegiStateList_metaObject;
}

igMetaObject *beNDMWLoadIntf2DegiStateCtrl_GetMeta(void)
{
    return g_beNDMWLoadIntf2DegiStateCtrl_metaObject;
}

igMetaObject *beNDMWLoadIntf2DataSelIntf_GetMeta(void)
{
    return g_beNDMWLoadIntf2DataSelIntf_metaObject;
}

igMetaObject *beNDMWLoadIntf2Diffselect_GetMeta(void)
{
    return g_beNDMWLoadIntf2Diffselect_metaObject;
}

igMetaObject *beNDMWLoadIntf2SelSlot_GetMeta(void)
{
    return g_beNDMWLoadIntf2SelSlot_metaObject;
}

igMetaObject *beNDMWLoadIntf2ChrDataSel_GetMeta(void)
{
    return g_beNDMWLoadIntf2ChrDataSel_metaObject;
}

igMetaObject *beNDMWLoadIntf2NameSel_GetMeta(void)
{
    return g_beNDMWLoadIntf2NameSel_metaObject;
}

igMetaObject *beNDMWLoadIntf2Info_GetMeta(void)
{
    return g_beNDMWLoadIntf2Info_metaObject;
}

igMetaObject *beNDMWLogoCtrlData_GetMeta(void)
{
    return g_beNDMWLogoCtrlData_metaObject;
}

igMetaObject *beNDMWLogoInfo_GetMeta(void)
{
    return g_beNDMWLogoInfo_metaObject;
}

igMetaObject *beNDMWMdlEnemyInfoWork_GetMeta(void)
{
    return g_beNDMWMdlEnemyInfoWork_metaObject;
}

igMetaObject *beNDMWMdlItemInfoWork_GetMeta(void)
{
    return g_beNDMWMdlItemInfoWork_metaObject;
}

igMetaObject *beNDMWMdlPlayerInfoWork_GetMeta(void)
{
    return g_beNDMWMdlPlayerInfoWork_metaObject;
}

igMetaObject *beNDMWMdlPlayer2InfoWork_GetMeta(void)
{
    return g_beNDMWMdlPlayer2InfoWork_metaObject;
}

igMetaObject *beNDMWPanelObject_GetMeta(void) {
    return g_beNDMWPanelObject_metaObject;
}

igMetaObject *beNDMWPanelWazaInfoWork_GetMeta(void)
{
    return g_beNDMWPanelWazaInfoWork_metaObject;
}

void beNDMWPanelWazaInfoWork_userConstruct(beNDMWPanelWazaInfoWork *arg0) {
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

    Gap__Core__igObject__userConstruct();
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
        q[k] = g_beNDMWPanelWazaInfoWork_textColorNone;
    }
}

void beNDMWPanelWazaInfoWork_TrimCapacity(beNDMWPanelWazaInfoWork *arg0) {
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
    FUN_003cc3d0((igIntList *)FUN_003cc480(arg0), &g_beNDMWPanelWazaInfoWork_textColorNoneReset);
    ((PanelVirtualShim *)arg0->_panelWaza)->vX();
    ((PanelVirtualShim *)arg0->_panelItem)->vX();
    ((PanelVirtualShim *)arg0->_panelStat)->vX();
}

void beNDMWPanelObjectStat_TrimCapacity(beNDMWPanelObjectStat *arg0) {
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

void beNDMWPanelObjectItem_TrimCapacity(beNDMWPanelObjectItem *arg0) {
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

void beNDMWPanelObjectWaza_TrimCapacity(beNDMWPanelObjectWaza *arg0) {
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

igMetaObject *beNDMWPanelWazaInfoRam_GetMeta(void)
{
    return g_beNDMWPanelWazaInfoRam_metaObject;
}

igMetaObject *beNDMWPanelWazaInfo_GetMeta(void)
{
    return g_beNDMWPanelWazaInfo_metaObject;
}

igMetaObject *beNDMWSaveCtrlCtrlData_GetMeta(void)
{
    return g_beNDMWSaveCtrlCtrlData_metaObject;
}

igMetaObject *beNDMWSaveCtrlInfo_GetMeta(void)
{
    return g_beNDMWSaveCtrlInfo_metaObject;
}

igMetaObject *beNDMWSaveIntfCtrlData_GetMeta(void)
{
    return g_beNDMWSaveIntfCtrlData_metaObject;
}

igMetaObject *beSaveIntfComMdlData_GetMeta(void)
{
    return g_beSaveIntfComMdlData_metaObject;
}

igMetaObject *beSaveIntfComMdlDataList_GetMeta(void)
{
    return g_beSaveIntfComMdlDataList_metaObject;
}

igMetaObject *beNDMWSaveIntfComMdlCtrl_GetMeta(void)
{
    return g_beNDMWSaveIntfComMdlCtrl_metaObject;
}

igMetaObject *beNDMWSaveIntfInfo_GetMeta(void)
{
    return g_beNDMWSaveIntfInfo_metaObject;
}

igMetaObject *beNDMWStageCtlInfo_GetMeta(void)
{
    return g_beNDMWStageCtlInfo_metaObject;
}

igMetaObject *beNDMWStageCtlInfoRam_GetMeta(void)
{
    return g_beNDMWStageCtlInfoRam_metaObject;
}

igMetaObject *beNDMWWindowCtrl_GetMeta(void)
{
    return g_beNDMWWindowCtrl_metaObject;
}

igMetaObject *beNDMWStatusInfoWork_GetMeta(void)
{
    return g_beNDMWStatusInfoWork_metaObject;
}

igMetaObject *beNDMWStatusInfoRam_GetMeta(void)
{
    return g_beNDMWStatusInfoRam_metaObject;
}

igMetaObject *beNDMWStatusInfo_GetMeta(void)
{
    return g_beNDMWStatusInfo_metaObject;
}

igMetaObject *beNDMWWindow_GetMeta(void)
{
    return g_beNDMWWindow_metaObject;
}

igMetaObject *beNDMWTitle2CtrlData_GetMeta(void)
{
    return g_beNDMWTitle2CtrlData_metaObject;
}

igMetaObject *beNDMWTitle2Option_GetMeta(void)
{
    return g_beNDMWTitle2Option_metaObject;
}

igMetaObject *beNDMWTitle2Info_GetMeta(void)
{
    return g_beNDMWTitle2Info_metaObject;
}

igMetaObject *beNDMWWindowList_GetMeta(void)
{
    return g_beNDMWWindowList_metaObject;
}

igMetaObject *beNDMWAfsSetupDataList_GetElementMeta(void)
{
    return g_beNDMWAfsSetupData_metaObject;
}

igMetaObject *beNDMWShinkaObjectList_GetElementMeta(void)
{
    return g_beNDMWShinkaObject_metaObject;
}

igMetaObject *beNDMWLoadIntf2DegiStateList_GetElementMeta(void)
{
    return g_beNDMWLoadIntf2DegiState_metaObject;
}

igMetaObject *beSaveIntfComMdlDataList_GetElementMeta(void)
{
    return g_beSaveIntfComMdlData_metaObject;
}

igMetaObject *beNDMWItemBaseList_GetElementMeta(void)
{
    return g_beNDMWItemBase_metaObject;
}

igMetaObject *beNDMWLoadSavePlWorkList_GetElementMeta(void)
{
    return g_beNDMWLoadSavePlWork_metaObject;
}

igMetaObject *beNDMWMcSlotList_GetElementMeta(void)
{
    return g_beNDMWMcSlot_metaObject;
}

igMetaObject *beNDMWLoadSlotPlayerList_GetElementMeta(void)
{
    return g_beNDMWLoadSlotPlayer_metaObject;
}

igMetaObject *beNDMWDegiDataList_GetElementMeta(void)
{
    return g_beNDMWDegiData_metaObject;
}

igMetaObject *beLoadIntf2ComMdlDataList_GetElementMeta(void)
{
    return g_beLoadIntf2ComMdlData_metaObject;
}

igMetaObject *beNDMWWindowList_GetElementMeta(void)
{
    return g_beNDMWWindow_metaObject;
}

