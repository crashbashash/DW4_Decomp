static inline char *keyText(IniKeyText *s) { char *t = s->text; if (t == 0) { return (*(char * *)g_stringObjEmptyText); } return t; }

static inline void dropKey(IniKeyText *o) {
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if (((unsigned long long)((long long)o->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); }
    }
}

static inline void dropValues_304b10(IniValueList *o) {
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if (((unsigned long long)((long long)o->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); }
    }
}

void FUN_00304b10(void *self) {
    void *ini;
    int section;
    unsigned int n;
    unsigned int i;
    int j;
    IniKeyText *key;
    IniValueList *values;
    char *string;
    char *text;
    IniValueList *held;
    ini = (*(IniSystemTables * *)g_objectSystem)->ini;
    section = FUN_00306360((IniSectionsView *)ini, PLUGINS, 1);
    if (section >= 0) {
        n = ((unsigned int)FUN_003064b0((int)ini, section));
        for (i = 0; i < n; i++) {
            key = 0;
            if (!igRegistry_GetKeyName((int)ini, section, i, &key)) {
                dropKey(key);
            } else {
                *(IniValueList **)&values = ((IniValueList *)igStringRefList_Create(((int)igObject_GetAllocator((int)self))));
                held = values;
                if (FUN_00306aa0(ini, section, keyText(key), (igStringRefList *)held, 0) == 0) {
                    dropValues_304b10(values);
                    dropKey(key);
                } else {
                    for (j = 0; j < (held = values)->count; j++) {
                        StringList_CopyRetained(&string, values, j);
                        text = string;
                        FUN_00304840((igPluginHelper *)self, (int)(keyText(key)), (int)text);
                        dropString(string);
                    }
                    dropValues_304b10(held);
                    dropKey(key);
                }
            }
        }
    }
}

void Gap__Core__igPluginHelper__vfunc_10(igPluginHelper *self) {
    int count;
    int i;
    igLibrary *library;

    count = ((igLibraryList *)self->_loadedPlugins)->_count;
    for (i = 0; i < count; i++) {
        library = ((igLibrary **)((igLibraryList *)self->_loadedPlugins)->_data)[i];
        if (library != 0) {
            library->_refCount = library->_refCount + 1;
        }
        ((igLibraryLoaderView *)self->_libraryLoader)->vfunc_24(&library);
        if (library != 0) {
            library->_refCount = library->_refCount - 1;
            if ((library->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(library);
            }
        }
    }
}

int FUN_00304e60(Args *args) {
    int key;
    Iter *it;
    igResult (*fn)(int);

    it = args->it;
    fn = args->fn;
    Memory_FreeBuffer((void *)args);
    for (it->vNext(&key, 1); fn(key) == g_resultSuccess; it->vNext(&key, 1)) {
    }
    return 0;
}

void **FUN_00304f00(void *arg0, int arg1, unsigned stackSize) {
    void **a; void *b;
    a = (void **)(((void **)igObject_GetAllocator((int)arg0)));
    b = ((igMemoryPoolView *)a)->Allocate(8);
    *(int *)((char *)(b) + 0) = arg1;
    *(int *)((char *)(b) + 4) = (int)(arg0);
    a = (void **)(((void **)FUN_002b7f40((int)a)));
    ((igPsx2ThreadView *)a)->setFunction((int (*)(...))FUN_00304e60);
    ((igPsx2ThreadView *)a)->setArg((int)b);
    ((igPsx2ThreadView *)a)->setStackSize(stackSize);
    if (((igPsx2ThreadView *)a)->start() == g_resultSuccess) {
        ObjectList_AppendRetained((igObjectList *)(*(int *)((char *)(arg0) + 8)), (igObject *)a);
    }
    return a;
}

int FUN_00305000(igStandardQueueView *queue) {
    igResult terminated, joined;
    int n;
    igPsx2ThreadView *p;
    int c;
    int k;
    igTDataList<igPsx2ThreadView *> *l;
    int i;
    int m;
    igPsx2ThreadView *thread;
    int j;

    n = ((igTDataList<igPsx2ThreadView *> *)queue->_serviceThreads)->_count;
    for (i = 0; i < n; i++) {
        thread = ((igTDataList<igPsx2ThreadView *> *)queue->_serviceThreads)->_data[i];
        if (thread->isRunning()) {
            terminated = thread->terminate();
        }
        if (thread->isRunning()) {
            joined = ((igPsx2ThreadManagerView **)g_threadManager)[0]->getCurrentThread()->join(thread);
        }
        thread->_refCount = thread->_refCount - 1;
        if (((unsigned long long)((long long)(int)thread->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(thread);
        }
    }
    if (n > 0) {
        l = (igTDataList<igPsx2ThreadView *> *)queue->_serviceThreads;
        m = l->_count;
        for (j = 0; j < m; j++) {
            p = l->_data[j];
            if (p != 0) {
                p->_refCount = p->_refCount - 1;
                if (((unsigned long long)((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        c = l->_count;
        for (k = 0; k < c; k++) {
            l->_data[k] = 0;
        }
        l->_count = 0;
    }
}

int thunk_FUN_00305000(int extra0)
{
    return FUN_00305000((igStandardQueueView *)extra0);
}

