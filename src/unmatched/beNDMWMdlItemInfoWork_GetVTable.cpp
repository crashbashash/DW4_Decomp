/* 0x003c1480 beNDMWMdlItemInfoWork_GetVTable: builds a beNDMWMdlItemInfoWork on the stack and returns the
 * word at the runtime vtable-slot offset the meta object publishes (DAT_00586dc8[0] + 916), then destroys it.
 * Reflection accessor; the exception table (a tag-0x07 member, then the tag-0x86 base, dtors 0x3c1520 and
 * 0x350410) is reproduced by the inline constructor of a derived view whose base and members have out-of-line
 * ctors/dtors (finding #3886). The view's own inline destructor is emitted out of line by MWCC and was
 * dead-stripped by the retail linker: the `stripped` entry of this unit's row (finding #3888). */
extern "C" {
extern int DAT_0053d440[4];                 /* beNDMWMdlItemInfoWork vtable */
extern void *DAT_00586dc8[4];               /* the class's meta object */
int beNDMWMdlItemInfoWork_GetVTable(void);
}

/* _itemObject (igObjectRefMetaField): ctor 0x3c15a0, dtor 0x3c1520 (bound as externals) */
struct ItemObjectField { int *p; ItemObjectField() throw(); ~ItemObjectField(); };
/* _fontType (igStringMetaField): ctor 0x229270, dtor 0x130720 */
struct StringRef { int *p; StringRef() throw(); ~StringRef(); };
/* the beModelCtrlInfoWork base: ctor 0x3bf650, dtor 0x350410 */
struct InfoBase { int *vtable; char baseFields[0xf0 - 4]; InfoBase(); ~InfoBase(); };
/* stores the derived vtable before the first member constructor runs, as retail does */
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
