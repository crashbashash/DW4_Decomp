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

void beNDMWDegiData_userConstruct(beNDMWDegiData *self, int flag) {
    int allocator;

    Gap__Core__igObject__userConstruct((igObject *)self);
    igMetaObject_CountInstances(((igObjectDispatchView *)self)->GetMeta(), 1);
    if (!(flag & 0xFF)) {
        self->_dataSize = 0x2000;
        allocator = (int)((Gap::Core::igObject *)self)->getMemoryPool();
        allocator = g_useOwnerAllocator ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        self->_data = (int)Memory_AllocateBufferDirect(0x2000, (igMemoryPoolView *)allocator);
    }
}

void beNDMWDegiData_userDestruct(beNDMWDegiData *self) {
    int allocator;

    if (self->_data != 0) {
        allocator = (int)((Gap::Core::igObject *)self)->getMemoryPool();
        allocator = g_useOwnerAllocator != 0 ? allocator : (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
        Memory_FreeBufferWithAllocator((void *)self->_data, (igMemoryPoolView *)allocator);
    }
    self->_data = 0;
    igMetaObject_CountInstances(((igObjectDispatchView *)self)->GetMeta(), 1);
    Gap__Core__igObject__userDestruct(self);
}

igMetaObject *beNDMWDegiDataList_GetMeta(void)
{
    return g_beNDMWDegiDataList_metaObject;
}

igMetaObject *beNDMWLoadSlotPlayer_GetMeta(void)
{
    return g_beNDMWLoadSlotPlayer_metaObject;
}

void beNDMWLoadSlotPlayer_userConstruct(beNDMWLoadSlotPlayer *self) {
    Gap__Core__igObject__userConstruct(self);
    igMetaObject_CountInstances(((igObjectDispatchView *)self)->GetMeta(), 1);
}

static inline int countOf(const beNDMWDegiDataList *l) { return l->_count; }

void beNDMWLoadSlotPlayer_userDestruct(beNDMWLoadSlotPlayer *self) {
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
            igObject::release(((igObject **)l->_data)[i]);
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
    igMetaObject_CountInstances(((igObjectDispatchView *)self)->GetMeta(), 1);
    Gap__Core__igObject__userDestruct(self);
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

void beNDMWMcUtilCtrl_userConstruct(beNDMWMcUtilCtrl *self) {
    Gap__Core__igObject__userConstruct(self);
    igMetaObject_CountInstances(((igObjectDispatchView *)self)->GetMeta(), 1);
    beSaveDataDeliver_AllocateData((beSaveDataDeliver *)self->_svData, 0x8000);
}

void beNDMWMcUtilCtrl_userDestruct(beNDMWMcUtilCtrl *self) {
    beSaveDataDeliver_FreeData((beSaveDataDeliver *)self->_svData);
    igMetaObject_CountInstances(((igObjectDispatchView *)self)->GetMeta(), 1);
    Gap__Core__igObject__userDestruct(self);
}

igMetaObject *beNDMWLoadCtrl2CommonIntf_GetMeta(void)
{
    return g_beNDMWLoadCtrl2CommonIntf_metaObject;
}

static inline int countOf(const beNDMWLoadSavePlWorkList *l) { return l->_count; }

void beNDMWLoadCtrl2CommonIntf_userDestruct(beNDMWLoadCtrl2CommonIntf *self) {
    beNDMWDegiDataList *l = (beNDMWDegiDataList *)self->_gameUseData;
    if (countOf(l) > 0) {
        int n = l->_count;
        int i;
        igObject *o;
        for (i = 0; i < n; i++) {
            o = ((igObject **)l->_data)[i];
            igObject::release(o);
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
    beNDMWLoadSavePlWorkList *l2 = (beNDMWLoadSavePlWorkList *)self->_flagWork;
    if (countOf(l2) > 0) {
        int n = l2->_count;
        int i;
        igObject *o;
        for (i = 0; i < n; i++) {
            o = ((igObject **)l2->_data)[i];
            igObject::release(o);
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
    Gap__Core__igObject__userDestruct(self);
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

void beNDMWPanelWazaInfoWork_userConstruct(beNDMWPanelWazaInfoWork *self) {
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

    Gap__Core__igObject__userConstruct(self);
    l = (igDataList *)self->_textSetList;
    if (l->_count < 0x31) {
        ((Gap::Core::igDataList *)l)->setCapacity(0x30, 4);
    }
    StringList_Resize((igTDataList<char *> *)self->_textSetList, 0x30);
    {
        /* every text slot takes a share of one empty token */
        HeldStringRef empty(0);
        l = (igDataList *)self->_textSetList;
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
                    StringChunk_ReleaseHeader((StringChunk *)*a1, (StringTokenHeader *)a1);
                }
            }
            *p = empty.p;
            p++;
        }
    }
    l = (igDataList *)self->_textColorList;
    if (l->_count < 0x31) {
        ((Gap::Core::igDataList *)l)->setCapacity(0x30, 4);
    }
    l = (igDataList *)self->_textColorList;
    if (l->_capacity >= 0x30) {
        l->_count = 0x30;
    } else {
        ((Gap::Core::igDataList *)l)->resizeAndSetCount(0x30, 4);
    }
    l = (igDataList *)self->_textColorList;
    n2 = l->_count;
    q = (int *)l->_data;
    for (k = 0; k < n2; k++) {
        q[k] = g_beNDMWPanelWazaInfoWork_textColorNone;
    }
}

void beNDMWPanelWazaInfoWork_TrimCapacity(beNDMWPanelWazaInfoWork *self) {
    int *header;
    int refCount;
    int pool;
    int *oldLabel;
    int *empty;
    igObject *playerWork;

    self->_retIsFire = 0;
    if (g_stringPool == 0) {
        pool = (int)StringPool_Allocate(0x10);
        if (pool != 0) {
            pool = (int)StringPool_Construct((StringPool *)pool);
        }
        g_stringPool = (StringPool *)pool;
    }
    empty = (int *)StringPool_Intern(g_stringPool, 0);
    oldLabel = (int *)self->_retWazaLabel;
    if (oldLabel != 0) {
        header = oldLabel - 2;
        refCount = oldLabel[-1] - 1;
        oldLabel[-1] = refCount;
        if (refCount == 0) {
            StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
        }
    }
    self->_retWazaLabel = (int)empty;
    playerWork = (igObject *)self->_playerWork;
    igObject::release(playerWork);
    self->_playerWork = 0;
    {
        InternedStringRef empty(0);
        beNDMWPanelWazaInfoWork_igStringRefList_SetAll((igDataList *)(((void *)beNDMWPanelWazaInfoWork_GetTextSetList(self))), (char **)&empty);
    }
    beNDMWPanelWazaInfoWork_igIntList_SetAll((igIntList *)beNDMWPanelWazaInfoWork_GetTextColorList(self), &g_beNDMWPanelWazaInfoWork_textColorNoneReset);
    ((igObjectDispatchView *)self->_panelWaza)->TrimCapacity();
    ((igObjectDispatchView *)self->_panelItem)->TrimCapacity();
    ((igObjectDispatchView *)self->_panelStat)->TrimCapacity();
}

void beNDMWPanelObjectStat_TrimCapacity(beNDMWPanelObjectStat *self) {
/* matching construct: locals zero-initialised and declared in the order that reproduces retail register assignment */
    igDataList *l = 0;
    int n = 0;
    int i = 0;
    const char *held = 0;
    const char **slot = 0;
    const char *tok = 0;
    int off = 0;
    igObject::release((igObject *)self->_playerDataList);
    self->_playerDataList = 0;
    igObject::release((igObject *)self->_playerWork);
    self->_playerWork = 0;
    l = (igDataList *)self->_listFolder;
    n = l->_count;
    i = 0;
    if (0 < n) {
        off = 0;
        do {
            slot = (const char **)((char *)l->_data + off);
            if (((void *)g_stringPool) == 0) {
                void *pool = ((void *)StringPool_Allocate(0x10));
                if (pool != 0) pool = ((void *)StringPool_Construct((StringPool *)pool));
                ((void *)g_stringPool) = pool;
            }
            tok = ((const char *)StringPool_Intern((StringPool *)g_stringPool, 0));
            held = *slot;
            if (held != 0) {
                int *hd = (int *)held - 2;
                int cnt = ((int *)held)[-1] - 1;
                ((int *)held)[-1] = cnt;
                if (cnt == 0) StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd);
            }
            i++;
            *slot = tok;
            off += 4;
        } while (i < n);
    }
    l->_count = 0;
    ((igDataList *)self->_listColor)->_count = 0;
}

void beNDMWPanelObjectItem_TrimCapacity(beNDMWPanelObjectItem *self) {
    igObjectList *l;
    igObject::release((igObject *)self->_playerDataList);
    self->_playerDataList = 0;
    l = (igObjectList *)self->_listFolder;
    int n = l->_count;
    int i = 0;
    int off;
    int j;
    if (0 < n) {
        off = 0;
        do {
            igObject::release(*(igObject **)((char *)l->_data + off));
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
    ((igDataList *)self->_listColor)->_count = 0;
}

void beNDMWPanelObjectWaza_TrimCapacity(beNDMWPanelObjectWaza *self) {
    igObjectList *l;
    igObject::release((igObject *)self->_playerDataList);
    self->_playerDataList = 0;
    l = (igObjectList *)self->_listFolder;
    int n = l->_count;
    int i = 0;
    int off;
    int j;
    if (0 < n) {
        off = 0;
        do {
            igObject::release(*(igObject **)((char *)l->_data + off));
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
    ((igObjectList *)self->_listColor)->_count = 0;
}

void beNDMWPanelWazaInfoWork_igIntList_SetAll(igIntList *list, int *value) {
    int n = list->_count;
    int *d = (int *)list->_data;
    int i;
    for (i = 0; i < n; i++) {
        d[i] = *value;
    }
}

int beNDMWPanelWazaInfoWork_GetTextColorList(beNDMWPanelWazaInfoWork *p)
{
    return p->_textColorList;
}

void beNDMWPanelWazaInfoWork_igStringRefList_SetAll(igDataList *list, char **token) {
    int *header;
    int count;
    int refCount;
    char **slot;
    int i;
    char *shared;
    char *held;

    count = list->_count;
    slot = (char **)list->_data;
    i = 0;
    if (0 < count) {
        do {
            shared = *token;
            if (shared != 0) {
                *(int *)(shared - 4) = *(int *)(shared - 4) + 1;
            }
            held = *slot;
            if (held != 0) {
                header = (int *)(held - 8);
                refCount = *(int *)(held - 4) - 1;
                *(int *)(held - 4) = refCount;
                if (refCount == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
                }
            }
            i += 1;
            *slot = *token;
            slot += 1;
        } while (i < count);
    }
}

/* +40 is _textSetList, a 4-byte arena/object handle. */
int beNDMWPanelWazaInfoWork_GetTextSetList(beNDMWPanelWazaInfoWork *p)
{
    return p->_textSetList;
}

int *beNDMWPanelWazaInfoWork_igStringRef_ConstructFromText(int *ref, int text) {
    int token;
    int pool;

    if (text == 0) {
        token = 0;
    } else {
        if (g_stringPool == 0) {
            pool = (int)StringPool_Allocate(0x10);
            if (pool != 0) {
                pool = (int)StringPool_Construct((StringPool *)pool);
            }
            g_stringPool = (StringPool *)pool;
        }
        token = ((int)StringPool_Intern(g_stringPool, (const char *)text));
    }
    *ref = token;
    return ref;
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

