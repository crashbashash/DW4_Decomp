/* beNDMWMdlPlayerInfoWork_GetVTable: builds a beNDMWMdlPlayerInfoWork on the stack and returns the
 * word at the runtime vtable-slot offset the meta object publishes (DAT_00586dc8[0] + 916), then
 * destroys it. Reflection accessor; its exception table (tag 0x86 base subobject, dtor 0x3bfde0)
 * is reproduced by the inline constructor of a derived view whose base and member have out-of-line
 * ctors/dtors. The view's own inline destructor is emitted out of line by MWCC and was dead-
 * stripped by the retail linker: it is the `stripped` entry of this unit's row in
 * config/SLUS-20836/unit-objects.json. */
extern "C" {
extern int DAT_0053d4a0[4];                 /* beNDMWMdlPlayerInfoWork vtable */
extern void *DAT_00586dc8[4];               /* the class's meta object */
int beNDMWMdlPlayerInfoWork_GetVTable(void);
}

/* an igObjectRefMetaField member: ctor 0x1510d0, dtor 0x150eb0 (bound as externals) */
struct ObjectRefField { int *p; ObjectRefField() throw(); ~ObjectRefField(); };
/* the beNDMWMdlPEBaseInfoWork base: ctor 0x3c0120 (beNDMWMdlPEBaseInfoWork_Construct), dtor 0x3bfde0 */
struct PEBaseInfoWorkView { int *vtable; char baseFields[0x114 - 4]; PEBaseInfoWorkView(); ~PEBaseInfoWorkView(); };
/* stores the derived vtable before the first member constructor runs, as retail does */
struct VtableInstall { VtableInstall(int **slot) { *slot = DAT_0053d4a0; } };

/* matching construct: hand-written view of beNDMWMdlPlayerInfoWork (the second empty base places the vtable
 * store; a real virtual class would reference __vt__ data that unit-objects cannot bind) */
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
