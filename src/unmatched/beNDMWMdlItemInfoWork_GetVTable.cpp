/* Reflection accessor: builds a beNDMWMdlItemInfoWork on the stack, returns the word at the
 * runtime vtable-slot offset the meta object publishes (+916), then destroys it. */
extern "C" {
extern int DAT_0053d440[4];                 /* beNDMWMdlItemInfoWork vtable */
extern void *DAT_00586dc8[4];               /* the class's meta object */
int beNDMWMdlItemInfoWork_GetVTable(void);
}

/* _itemObject (igObjectRefMetaField). */
struct ItemObjectField { int *p; ItemObjectField() throw(); ~ItemObjectField(); };
/* _fontType (igStringMetaField). */
struct StringRef { int *p; StringRef() throw(); ~StringRef(); };
/* The beModelCtrlInfoWork base. */
struct InfoBase { int *vtable; char baseFields[0xf0 - 4]; InfoBase(); ~InfoBase(); };
/* Stores the derived vtable before the first member constructor runs. */
struct VtableInstall { VtableInstall(int **slot) { *slot = DAT_0053d440; } };

/* matching construct: hand-written view of beNDMWMdlItemInfoWork (see beNDMWMdlPlayerInfoWork_GetVTable) */
struct ItemInfoWork : InfoBase, VtableInstall {
    ItemObjectField itemObject;             /* +240 _itemObject */
    char gap[0x104 - 0xf4];
    StringRef fontType;                     /* +260 _fontType */
    char ownFields[0x110 - 0x108];
    ItemInfoWork() : VtableInstall(&vtable) { }
    ~ItemInfoWork() { vtable = DAT_0053d440; }
};

int beNDMWMdlItemInfoWork_GetVTable(void) {
    ItemInfoWork work;
    return *(int *)((char *)&work + *(int *)((char *)DAT_00586dc8[0] + 916));
}
