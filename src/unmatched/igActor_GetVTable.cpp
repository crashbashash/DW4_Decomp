extern "C" {
extern int DAT_005296b0[4];
extern void *DAT_00586dc8[4];
int igActor_GetVTable(void);
}
struct igObjectView { int *vtable; unsigned int refCount; igObjectView(); };
struct igMatrix44fView { float m[16]; igMatrix44fView(); };
struct igActorVtable { igActorVtable(int **slot) { *slot = DAT_005296b0; } };
struct igNodeView : igObjectView {
    int name, bound, parentList, flags, handle, childList;
    igNodeView() { name = 0; bound = 0; parentList = 0; childList = 0; }
    ~igNodeView();
};
struct ActorAnimSystemField { int *p; ActorAnimSystemField() { p = 0; } ~ActorAnimSystemField(); };
struct ActorAppearanceField { int *p; ActorAppearanceField() { p = 0; } ~ActorAppearanceField(); };
struct ActorDatabaseField { int *p; ActorDatabaseField() { p = 0; } ~ActorDatabaseField(); };
struct ActorModifierField { int *p; ActorModifierField() { p = 0; } ~ActorModifierField(); };
struct igActorView : igNodeView, igActorVtable {
    ActorAnimSystemField animationSystem;
    int boneCache, blendCache;
    ActorAppearanceField appearance;
    ActorDatabaseField database;
    ActorModifierField modifierList;
    igMatrix44fView transform;
    char cacheFlags[4];
    igMatrix44fView mvm;
    igMatrix44fView inverseView;
    char tail[4];
    igActorView() : igActorVtable(&vtable) { }
    ~igActorView() { vtable = DAT_005296b0; }
};
int igActor_GetVTable(void) {
    igActorView actor;
    return *(int *)((char *)&actor + *(int *)((char *)DAT_00586dc8[0] + 916));
}
