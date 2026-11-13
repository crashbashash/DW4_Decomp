ThreadLocalEntry::ThreadLocalEntry(void *thread, int slot, void *value) {
    key = (unsigned int)thread ^ slot;
    next = 0;
    prev = 0;
    ThreadLocalTable_Insert(this);
    this->slot = slot;
    this->value = value;
    this->thread = thread;
}

ThreadLocalEntry::~ThreadLocalEntry() {
}

/* Sets the calling thread's value of a slot. */
void ThreadLocal_Set(int slot, void *value) {
    ThreadLocal_SetForThread(g_threadManager->getCurrentThread(), slot, value);
}

/* Takes the next slot, giving it `value` on the calling thread. */
int ThreadLocal_NewSlot(void *value) {
    if (g_threadLocalSemaphore == 0) {
        LuaSemaphoreView *semaphore = FUN_002ba650(0);
        g_threadLocalSemaphore = semaphore;
        semaphore->initialize();
    } else {
        g_threadLocalSemaphore->_refCount = g_threadLocalSemaphore->_refCount + 1;
    }
    LuaSemaphoreLock lock(g_threadLocalSemaphore);
    new ThreadLocalEntry(g_threadManager->getCurrentThread(), g_threadLocalNextSlot++, value);
    return g_threadLocalNextSlot - 1;
}

/* Makes a state the one the bindings run in: per thread, or for every thread. */
void igLuaState_MakeCurrent(Gap::Lua::igLuaState *state) {
    if (g_luaStatePerThread != 0) {
        ThreadLocal_Set(g_luaStateSlot, state);
        return;
    }
    g_currentLuaState = state;
}

/* Opens the Lua state in the object's memory pool with the standard libraries and the glue's. */
void Gap::Lua::igLuaState::userConstruct() {
    ::igObject *pool;
    ::igObject *old;
    lua_State *L;

    pool = igObject_GetAllocator(this);
    pool = g_useOwnerAllocator != 0 ? pool : (::igObject *)Memory_GetAllocatorBySelector(g_defaultAllocatorKey);
    if (pool != 0) {
        pool->_refCount = pool->_refCount + 1;
    }
    old = _memPool;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    _memPool = pool;
    _luaState = lua_open(0, (igMemoryPoolView *)_memPool);
    if (g_luaStatePerThread == 0) {
        igLuaState_MakeCurrent(this);
    }
    g_luaStateSlot = ThreadLocal_NewSlot(_luaState);
    L = _luaState;
    lua_baselibopen(L);
    lua_strlibopen(L);
    lua_mathlibopen(L);
    LuaGlue_OpenLibrary(L);
}

void Gap::Lua::igLuaState::userDestruct() {
    lua_close(_luaState);
    ThreadLocal_FreeSlot(g_luaStateSlot);
}

int Gap::Lua::igLuaState::runString(const char *source) {
    int status = lua_dostring(_luaState, source);
    if (status != 0) {
        LuaError("igLuaState::runString() failed - reason %s", g_luaErrorNames[status]);
    }
    return status;
}

int Gap::Lua::igLuaState::runFile(const char *path) {
    int status = lua_dofile(_luaState, path);
    if (status != 0) {
        LuaError("igLuaState::runFile(%s) failed - reason %s", path, g_luaErrorNames[status]);
    }
    return status;
}

int Gap::Lua::igLuaState::runBuffer(const char *buffer, unsigned int size, const char *name) {
    int status = lua_dobuffer(_luaState, buffer, size, name);
    if (status != 0) {
        LuaError("igLuaState::runBuffer(%s) failed - reason %s", name, g_luaErrorNames[status]);
    }
    return status;
}

void LuaBinding_SetErrorHandler(LuaErrorHandler handler, void *data) {
    g_luaErrorHandler = handler;
    g_luaErrorHandlerData = data;
}

LuaErrorHandler LuaBinding_GetErrorHandler(void **data) {
    if (data) {
        *data = g_luaErrorHandlerData;
    }
    return g_luaErrorHandler;
}

/* Formats a binding error and hands it to the registered handler. */
void LuaError(const char *format, ...) {
    char message[4096];
    va_list args;

    va_start(args, format);
    vsprintf(message, format, args);
    if (g_luaErrorHandler != 0) {
        g_luaErrorHandler(message, g_luaErrorHandlerData);
    }
}
