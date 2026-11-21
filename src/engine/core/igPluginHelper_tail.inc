static inline char *keyText(igStringObj *s) { char *t = (char *)s->_buffer; if (t == 0) { return (g_stringObjEmptyText); } return t; }

static inline void dropKey(igStringObj *o) {
    igObject::release(o);
}

static inline void dropValues(igTDataList<char *> *o) {
    IG_OBJECT_RELEASE(o);
}

void igPluginHelper_LoadPluginsFromRegistry(void *self) {
    void *ini;
    int section;
    unsigned int n;
    unsigned int i;
    int j;
    igStringObj *key;
    igTDataList<char *> *values;
    char *string;
    char *text;
    igTDataList<char *> *held;
    ini = g_objectSystem->configRegistry;
    section = igRegistry_GetSectionIndex((igRegistry *)ini,"PLUGINS", 1);
    if (section >= 0) {
        n = ((unsigned int)igRegistry_GetNumValuesInSection((int)ini, section));
        for (i = 0; i < n; i++) {
            key = 0;
            if (!igRegistry_GetKeyName((int)ini, section, i, &key)) {
                dropKey(key);
            } else {
                *(igTDataList<char *> **)&values = ((igTDataList<char *> *)igStringRefList_Create(((int)((Gap::Core::igObject *)self)->getMemoryPool())));
                held = values;
                if (!igRegistry_GetValueStringList(ini, section, keyText(key), (igStringRefList *)held, 0)) {
                    dropValues(values);
                    dropKey(key);
                } else {
                    for (j = 0; j < (held = values)->_count; j++) {
                        igStringRef string = StringList_CopyRetained((igStringRefList *)values, j);
                        text = string.p;
                        igPluginHelper_AddRepositoryFromConfig((igPluginHelper *)self, (int)(keyText(key)), (const char *)text);
                    }
                    dropValues(held);
                    dropKey(key);
                }
            }
        }
    }
}

void Gap__Core__igPluginHelper__userDestruct(igPluginHelper *self) {
    int count;
    int i;
    igLibrary *library;

    count = ((igLibraryList *)self->_loadedPlugins)->_count;
    for (i = 0; i < count; i++) {
        library = ((igLibrary **)((igLibraryList *)self->_loadedPlugins)->_data)[i];
        igObject::ref(library);
        ((igLibraryLoaderView *)self->_libraryLoader)->UnloadLibrary(&library);
        if (library != 0) {
            library->_refCount = library->_refCount - 1;
            if ((library->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(library);
            }
        }
    }
}

int igPluginHelper_ThreadLoop(Args *args) {
    int key;
    igStandardQueueView *queue;
    igResult (*fn)(int);

    queue = args->queue;
    fn = args->fn;
    Memory_FreeBuffer((void *)args);
    for (queue->Remove(&key, 1); fn(key) == g_resultSuccess; queue->Remove(&key, 1)) {
    }
    return 0;
}

void **igQueue_StartServiceThread(void *queue, int function, unsigned stackSize) {
    void **a; Args *args;
    a = (void **)(((void **)((Gap::Core::igObject *)queue)->getMemoryPool()));
    args = (Args *)((igMemoryPoolView *)a)->Allocate(8);
    args->fn = (igResult (*)(int))function;
    args->queue = (igStandardQueueView *)queue;
    a = (void **)(((void **)igThread_Create((int)a)));
    ((igPsx2ThreadView *)a)->SetFunction((int (*)(...))igPluginHelper_ThreadLoop);
    ((igPsx2ThreadView *)a)->SetArg((int)args);
    ((igPsx2ThreadView *)a)->SetStackSize(stackSize);
    if (((igPsx2ThreadView *)a)->Start() == g_resultSuccess) {
        ((Gap::Core::igObjectList *)(((igStandardQueueView *)queue)->_serviceThreads))->append((Gap::Core::igObject *)a);
    }
    return a;
}

igPsx2ThreadManagerView *g_threadManager;

int igStandardQueue_StopServiceThreads(igStandardQueueView *queue) {
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
        if (thread->IsRunning()) {
            terminated = thread->Terminate();
        }
        if (thread->IsRunning()) {
            joined = ((igPsx2ThreadManagerView **)&g_threadManager)[0]->GetCurrentThread()->Join(thread);
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

int igQueue_ReleaseDefaults(int extra0)
{
    return igStandardQueue_StopServiceThreads((igStandardQueueView *)extra0);
}

