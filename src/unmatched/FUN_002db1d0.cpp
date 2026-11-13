struct KeyValueText { int a; int b; char *text; };
struct KeyValuePair { KeyValueText *key; KeyValueText *value; };
struct KeyValuePairList { int vt; int rc; int count; int cap; KeyValuePair **data; };
struct RefHolderObject { int vt; unsigned int _refCount; };
extern "C" {
void *igObject_GetAllocator(void *);
RefHolderObject *igStringObj_Create(void *);
void FUN_00306770(void *, void *, char *, RefHolderObject **, int *, int);
void FUN_00307700(void *, void *, char *, char *);
void igObject_Destroy(void *);
extern char *DAT_004c22f0[4];
extern int DAT_004f7910[4];
void FUN_002db1d0(void *self, KeyValuePairList *list, void *a, void *b);
}
static inline char *text(KeyValueText *s) {
    char *t = s->text;
    if (t == 0) {
        t = DAT_004c22f0[0];
    }
    return t;
}
void FUN_002db1d0(void *self, KeyValuePairList *list, void *a, void *b) {
    char *k;
    int i;
    KeyValuePair *p;
    char *v;
    RefHolderObject *tmp = igStringObj_Create(igObject_GetAllocator(self));
    for (i = 0; i < list->count; i++) {
        p = list->data[i];
        k = p->key->text;
        k = (k == 0) ? DAT_004c22f0[0] : k;
        FUN_00306770(a, b, k, &tmp, DAT_004f7910, 0);
        k = p->key->text;
        k = (k == 0) ? DAT_004c22f0[0] : k;
        v = p->value->text;
        v = (v == 0) ? DAT_004c22f0[0] : v;
        FUN_00307700(a, b, k, v);
    }
    {
        RefHolderObject *held = tmp;
        if (held != 0) {
            held->_refCount = (int)held->_refCount - 1;
            if (((unsigned long long)((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(held);
            }
        }
    }
}
