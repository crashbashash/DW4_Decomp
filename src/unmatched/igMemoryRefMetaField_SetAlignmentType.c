typedef struct AlignmentName { char pad[8]; char *text; } AlignmentName;
typedef struct AlignmentNameList { char pad[4]; int _refCount; int count; int cap; } AlignmentNameList;
typedef struct AlignmentFieldView { char pad[68]; int alignmentType; } AlignmentFieldView;
extern char *DAT_00586dd0;
extern char *DAT_004c22f0;
int igObject_Destroy();
int igStrCmp();
static inline void dropNames(AlignmentNameList *o) {
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if (((unsigned long long)((long long)o->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); }
    }
}
static inline int countOf(AlignmentNameList *l) { if (l != 0) { return l->count; } return 0; }
static inline char *textOf(AlignmentName *s) { char *t = s->text; if (t == 0) { return DAT_004c22f0; } return t; }
void igMemoryRefMetaField_SetAlignmentType(AlignmentFieldView *self, char *name) {
    AlignmentNameList *names;
    AlignmentNameList *held;
    int n;
    int i;
    if (name == 0) {
        self->alignmentType = -1;
        return;
    }
    *(AlignmentNameList *volatile *)&names = *(AlignmentNameList **)(DAT_00586dd0 + 44);
    held = names;
    if (held != 0) { held->_refCount = held->_refCount + 1; }
    n = countOf(names);
    for (i = 0; i < n; i++) {
        if (igStrCmp(textOf((*(AlignmentName ***)((char *)names + 16))[i]), name) == 0) {
            self->alignmentType = i;
            dropNames(names);
            return;
        }
    }
    dropNames(names);
}
