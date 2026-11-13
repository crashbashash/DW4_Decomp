void FUN_001c0f00(int mode) {
    if ((mode & 0xFF) != GPR_00554b90) {
        int saved = 0;
        List_1c0f00 *list = ((List_1c0f00 *)g_igAnimationStatePool_instance.p);
        if (list != 0) {
            saved = list->getCount();
            list->clear();
        }
        if (mode != 0) {
            DAT_00562728[0] = ((Meta *)((void *)igAnimationState_GetMetaObject()))->f60;
            Meta *m2 = (Meta *)igAnimationState_GetMetaObject();
            m2->f60 = (void *)FUN_001c10e0;
            int a = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem[0]);
            g_igEnbayaContextPool_instance.release();
            g_igEnbayaContextPool_instance.p = (igEnbayaContextPool *)igEnbayaContextPool_Create(a);
        } else {
            ((Meta *)((void *)igAnimationState_GetMetaObject()))->f60 = DAT_00562728[0];
            g_igEnbayaContextPool_instance.clear();
        }
        if (g_igAnimationStatePool_instance.p != 0) ObjectList_ResizeRetained((List_1c0f00 *)g_igAnimationStatePool_instance.p, saved);
        GPR_00554b90 = mode;
    }
}

igMetaObject *FUN_001c10e0(void) {
    return g_igEnbayaAnimationState_metaObject[0];
}

void FUN_001c10f0(void) {
    FUN_001c0f00(1);
}

void FUN_001c1100(void) {
    FUN_001c0f00(0);
}

void Gap__Sg__igEnbayaAnimationState__vfunc_17(void **arg0) {
    if (GPR_00554b90 != 0) {
        ((DW4VC_92_0 *)(arg0))->vX();
    }
}

void Gap__Sg__igEnbayaAnimationState__vfunc_23(igEnbayaAnimationState *arg0) {
    int found;
    int i;
    igAnimationTrackList *l;
    int n;
    igAnimationTrack *e;
    igEnbayaTransformSource *c;
    found = 0;
    l = (igAnimationTrackList *)((igAnimation *)arg0->_animation)->_trackList;
    n = l->_count;
    for (i = 0; i < n; i++) {
        e = (igAnimationTrack *)((int *)l->_data)[i];
        if (e != 0 && (c = (igEnbayaTransformSource *)e->_source) != 0 && igObject_IsKindOf(c, g_igEnbayaTransformSource_metaObject[0]) != 0) {
            found = ((igEnbayaAnimationSource *)c->_enbayaAnimationSource)->_enbayaAnimationStream;
            break;
        }
    }
    if (found != 0) {
        arg0->_context = FUN_001c1560((T_1c1560 *)g_igEnbayaContextPool_instance.p, ((igAnimationTrackList *)((igAnimation *)arg0->_animation)->_trackList)->_count);
        if (GPR_00554b94 == 0) {
            arg0->_fastCacheDecodingState = 0;
        }
        FUN_0027ef50(arg0->_context, FUN_002808f0(found), arg0->_fastCacheDecodingState);
    }
}

void Gap__Sg__igEnbayaAnimationState__vfunc_24(void *arg0) {
    int temp_a1;

    temp_a1 = *(int *)((char *)(arg0) + 160);
    if (temp_a1 != 0) {
        FUN_001c16a0(g_igEnbayaContextPool_instance.p, temp_a1, *(int *)((char *)(*(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 20)) + 8));
    }
}

void Gap__Sg__igEnbayaAnimationState__vfunc_25(void *arg0) {
    DAT_00562720[0] = *(int *)((char *)(arg0) + 160);
}

void Gap__Sg__igEnbayaAnimationState__vfunc_26(void *arg0) {
    void *temp_a0;

    DAT_00562720[0] = 0;
    temp_a0 = (void *)(*(int *)((char *)(arg0) + 160));
    if ((temp_a0 != 0) && (*(unsigned char *)((char *)(temp_a0) + 171) != 0)) {
        FUN_002800d0(temp_a0);
    }
}

