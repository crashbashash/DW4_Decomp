extern "C" {
typedef struct ObjectRefFieldView { int _vtable; int _refCount; char _pad8[30]; unsigned char _flag38; char _pad27[13]; unsigned char _flag52; char _pad35[3]; int _metaObject; } ObjectRefFieldView;
extern int FUN_002eb010(int);
extern int FUN_002fe570(int, ObjectRefFieldView *);
extern int Memory_GetAllocatorBySelector(int);
extern void StringChunk_ReleaseHeader(int, int *);
extern int StringPool_Construct(int);
extern char *StringPool_Intern(int, const char *);
extern int igGeometrySetAttr_GetMetaObject(void);
extern void igMetaField_SetFieldName(ObjectRefFieldView *, char **);
extern ObjectRefFieldView *igObjectRefMetaField_Create(int);
extern void igObject_Destroy(ObjectRefFieldView *);
extern char DAT_004e4630[16];
extern int DAT_00561a38[4];
extern ObjectRefFieldView *DAT_00562768[4];
extern int DAT_00586f20[4];
extern int DAT_00587038[4];
}
static inline char *internText(const char *text) {
    int pool;
    if (text == 0) return 0;
    if (DAT_00586f20[0] == 0) {
        pool = FUN_002eb010(16);
        if (pool != 0) {
            pool = StringPool_Construct(pool);
        }
        DAT_00586f20[0] = pool;
    }
    return StringPool_Intern(DAT_00586f20[0], text);
}
struct FieldHolder { ObjectRefFieldView *p; ~FieldHolder() {} };
extern "C" void FUN_001c51d0(void) {
    FieldHolder field;
    char *name;
    ObjectRefFieldView *held;
    if (DAT_00562768[0] == 0) {
        field.p = igObjectRefMetaField_Create(Memory_GetAllocatorBySelector(DAT_00587038[0]));
        DAT_00562768[0] = field.p;
        name = internText(DAT_004e4630);
        igMetaField_SetFieldName(field.p, &name);
        if (name != 0) {
            int *header = (int *)name - 2;
            int count = ((int *)name)[-1] - 1;
            ((int *)name)[-1] = count;
            if (count == 0) {
                StringChunk_ReleaseHeader(*header, header);
            }
        }
        field.p->_flag52 = 1;
        field.p->_flag38 = 0;
        field.p->_metaObject = igGeometrySetAttr_GetMetaObject();
        FUN_002fe570(DAT_00561a38[0], field.p);
        held = field.p;
        if (held != 0) {
            held->_refCount = held->_refCount - 1;
            if (((unsigned long long)((long long)held->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(held);
            }
        }
    }
}
