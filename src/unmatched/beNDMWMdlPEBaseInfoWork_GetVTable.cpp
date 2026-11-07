/* Reflection accessor: builds a beNDMWMdlPEBaseInfoWork on the stack, returns the word at the
 * runtime vtable-slot offset the meta object publishes (+916), then destroys it. */
extern "C" {
extern int DAT_00540520[4];                 /* beNDMWMdlPEBaseInfoWork vtable */
extern void *DAT_00586dc8[4];               /* the class's meta object */
int beNDMWMdlPEBaseInfoWork_GetVTable(void);
}

/* An igObjectRefMetaField member. */
struct ObjectRefField { int *p; ObjectRefField() throw(); ~ObjectRefField(); };
/* A 12-byte list member. */
struct PEBaseListField { int *p[3]; PEBaseListField() throw(); ~PEBaseListField(); };
/* The beModelCtrlInfoWork base. */
struct InfoBase { int *vtable; char baseFields[0xf0 - 4]; InfoBase(); ~InfoBase(); };
/* Stores the derived vtable before the first member constructor runs. */
struct VtableInstall { VtableInstall(int **slot) { *slot = DAT_00540520; } };

/* matching construct: hand-written view of beNDMWMdlPEBaseInfoWork (see beNDMWMdlPlayerInfoWork_GetVTable) */
struct PEBaseInfoWorkObj : InfoBase, VtableInstall {
    ObjectRefField ref0;                    /* +240 */
    ObjectRefField ref1;                    /* +244 */
    ObjectRefField ref2;                    /* +248 */
    PEBaseListField list;                   /* +252 */
    ObjectRefField ref3;                    /* +264 */
    ObjectRefField ref4;                    /* +268 */
    char ownFields[0x114 - 0x110];
    PEBaseInfoWorkObj() : VtableInstall(&vtable) { }
    ~PEBaseInfoWorkObj() { vtable = DAT_00540520; }
};

int beNDMWMdlPEBaseInfoWork_GetVTable(void) {
    PEBaseInfoWorkObj work;
    return *(int *)((char *)&work + *(int *)((char *)DAT_00586dc8[0] + 916));
}
