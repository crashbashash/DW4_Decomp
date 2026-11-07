void *FUN_002be270();
int ObjectList_AppendRetained();
int igNamedObject_SetName();
int igObject_Destroy();
int igObject_GetAllocator();
typedef struct Obj { int vt; int _refCount; } Obj;
typedef struct Dir { char pad[8]; void *names; void *objects; } Dir;
void FUN_00303cd0(Dir *self, int name, void *object) {
    Obj *entry;
    Obj *held;

    *(Obj *volatile *)&entry = FUN_002be270(igObject_GetAllocator());
    igNamedObject_SetName(entry, name);
    ObjectList_AppendRetained(self->names, entry);
    ObjectList_AppendRetained(self->objects, object);
    held = entry;
    if (held != 0) {
        held->_refCount = held->_refCount - 1;
        if (((unsigned long long)((long long)held->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(held);
        }
    }
}
