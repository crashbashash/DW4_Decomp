#undef CAST_INLINE

void igAnimationState_UpdateLocalTime(igAnimationState *s, long long t) {
    long long r; float x;
    if (DAT_0048d8c0 != t || DAT_0048d8c8 != s->_timeScale) {
        x = (float)(unsigned int)(int)(t >> 18);
        x *= s->_timeScale;
        DAT_00562570 = __fixsfdi(x);
        DAT_0048d8c0 = t;
        DAT_0048d8c8 = s->_timeScale;
    }
    r = DAT_00562570 << 18;
    r += s->_timeBias;
    s->_localTime = r;
}

void Gap__Sg__igAnimationState__vfunc_23(void) {

}

void Gap__Sg__igAnimationState__vfunc_24(void) {

}

void Gap__Sg__igAnimationState__vfunc_25(void) {

}

void Gap__Sg__igAnimationState__vfunc_26(void) {

}

int FUN_001af620(igAppearanceView *a, void *t) {
    int i;
    int result;
    int n;
    result = 0;
    n = a->_segmentOverrideNameList->_count;
    for (i = 0; i < n; i++) {
        int graph = a->_segmentOverrideGraphList->_data[i];
        FUN_001b7770((igCommonTraversal *)t, overrideName(a, i), graph);
    }
    if (a->_skin != 0) {
        result = FUN_001d9740((void *)a->_skin, (int)(t));
    }
    for (i = 0; i < a->_attachedSkins->_count; i++) {
        FUN_001d9740((void *)a->_attachedSkins->_data[i], (int)(t));
    }
    for (i = 0; i < a->_attachedGraphs->_count; i++) {
        igTraversal_TraverseNode((igTraversal *)t, (igNode *)a->_attachedGraphs->_data[i]);
    }
    for (i = 0; i < n; i++) {
        FUN_001b7920((igCommonTraversal *)t, overrideName(a, i));
    }
    return result;
}

int igAppearance_AttachGraph(igAppearance *appearance, igNode *graph) {
    return ObjectList_AppendRetained(appearance->_attachedGraphs, graph);
}

int igAppearance_DetachGraph(igAppearance *appearance, igNode *graph) {
    return ObjectList_RemoveAllRetained(appearance->_attachedGraphs, graph, 0) > 0;
}

