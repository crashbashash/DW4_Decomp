typedef struct SgChildList { int _pad0[2]; int _count; int _pad0c; struct SgLinkNode **_data; } SgChildList;
struct SgLinkNode {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30();
    virtual void attach(SgLinkNode *); virtual void detach(SgLinkNode *);
    char _pad4[12];
    SgChildList *_parents;
    char _pad14[8];
    SgChildList *_children;
};
extern "C" void FUN_001d3590(SgLinkNode *);
extern "C" void FUN_001c5b80(SgLinkNode *o) {
    int n;
    int i;
    SgLinkNode *c;
    int have;
    int j;
    SgChildList *l;
    int want;
    int t;
    SgChildList *m;
    int k;
    FUN_001d3590(o);
    n = 0;
    if (o->_children != 0) n = o->_children->_count;
    for (i = 0; i < n; i++) {
        c = o->_children->_data[i];
        if (c != 0) {
            have = 0;
            l = o->_children;
            j = 0;
            goto guardHave;
        nextHave:
            if (l->_data[j] == c) have++;
            j++;
        testHave:
            if (j < n) goto nextHave;
        doneHave:
            m = c->_parents;
            want = 0;
            t = m->_count;
            k = 0;
            goto guardWant;
        nextWant:
            if (m->_data[k] == o) want++;
            k++;
        testWant:
            if (k < t) goto nextWant;
        doneWant:
            for (j = want; j < have; j++) c->attach(o);
            for (; have < want; have++) c->detach(o);
        }
    }
    return;
guardWant:
    if (0 < t) goto testWant;
    goto doneWant;
guardHave:
    if (0 < n) goto testHave;
    goto doneHave;
}
