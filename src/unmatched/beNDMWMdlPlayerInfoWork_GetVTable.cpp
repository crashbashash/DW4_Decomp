/* Reflection accessor: builds a beNDMWMdlPlayerInfoWork on the stack, returns the word at the
 * runtime vtable-slot offset the meta object publishes (+916), then destroys it. */
extern "C" {
extern int DAT_0053d4a0[4];                 /* beNDMWMdlPlayerInfoWork vtable */
extern void *DAT_00586dc8[4];               /* the class's meta object */
int beNDMWMdlPlayerInfoWork_GetVTable(void);
}

/* An igObjectRefMetaField member. */
struct ObjectRefField { int *p; ObjectRefField() throw(); ~ObjectRefField(); };
/* The beNDMWMdlPEBaseInfoWork base. */
struct PEBaseInfoWorkView { int *vtable; char baseFields[0x114 - 4]; PEBaseInfoWorkView(); ~PEBaseInfoWorkView(); };
/* Stores the derived vtable before the first member constructor runs. */
struct VtableInstall { VtableInstall(int **slot) { *slot = DAT_0053d4a0; } };

/* matching construct: hand-written view of beNDMWMdlPlayerInfoWork (the second empty base places the
 * vtable store; a real virtual class would need __vt__ data that the build cannot bind) */
struct PlayerInfoWorkView : PEBaseInfoWorkView, VtableInstall {
    ObjectRefField turnAtkTimer;            /* +276 _turnAtkTimer */
    char ownFields[0x130 - 0x118];
    PlayerInfoWorkView() : VtableInstall(&vtable) { }
    ~PlayerInfoWorkView() { vtable = DAT_0053d4a0; }
};

int beNDMWMdlPlayerInfoWork_GetVTable(void) {
    PlayerInfoWorkView work;
    return *(int *)((char *)&work + *(int *)((char *)DAT_00586dc8[0] + 916));
}
