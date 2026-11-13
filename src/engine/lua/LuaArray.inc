/* The ig*Array classes: plain C arrays of numbers a script creates, indexes and frees. Each class
 * has a constructor, a `gettable` and a `settable` handler and a `gc` handler; the array is the
 * userdata, the class the upvalue. */

int LuaCharArray_Delete(lua_State *L) {
    delete[] (char *)lua_touserdata(L, 1);
    return 0;
}

int LuaCharArray_Get(lua_State *L) {
    LuaClass *luaClass;
    char *array;

    luaClass = (LuaClass *)lua_touserdata(L, -1);
    if (lua_type(L, 2) != LUA_TNUMBER) {
        LuaError("%s: Non-number array access", luaClass->name);
        return 0;
    }
    array = (char *)lua_touserdata(L, 1);
    lua_pushnumber(L, array[(int)lua_tonumber(L, 2)]);
    return 1;
}


int LuaCharArray_Set(lua_State *L) {
    LuaClass *luaClass;
    char *array;
    int index;

    luaClass = (LuaClass *)lua_touserdata(L, -1);
    if (lua_type(L, 2) != LUA_TNUMBER) {
        LuaError("%s: Non-number array access", luaClass->name);
        return 0;
    }
    array = (char *)lua_touserdata(L, 1);
    index = (int)lua_tonumber(L, 2);
    if (lua_type(L, 3) != LUA_TNUMBER) {
        LuaError("Value to set must be number");
        return 0;
    }
    array[index] = (char)lua_tonumber(L, 3);
    return 0;
}


int LuaCharArray_New(lua_State *L) {
    int count;
    char *array;

    if (lua_gettop(L) != 0) {
        count = (int)lua_tonumber(L, -2);
    } else {
        count = 1;
    }
    array = new char[count];
    lua_pushusertag(L, array, ((LuaClass *)lua_touserdata(L, -1))->instanceTag);
    return 1;
}

int LuaUnsignedCharArray_Delete(lua_State *L) {
    delete[] (unsigned char *)lua_touserdata(L, 1);
    return 0;
}

int LuaUnsignedCharArray_Get(lua_State *L) {
    LuaClass *luaClass;
    unsigned char *array;

    luaClass = (LuaClass *)lua_touserdata(L, -1);
    if (lua_type(L, 2) != LUA_TNUMBER) {
        LuaError("%s: Non-number array access", luaClass->name);
        return 0;
    }
    array = (unsigned char *)lua_touserdata(L, 1);
    lua_pushnumber(L, array[(int)lua_tonumber(L, 2)]);
    return 1;
}


int LuaUnsignedCharArray_Set(lua_State *L) {
    LuaClass *luaClass;
    unsigned char *array;
    int index;

    luaClass = (LuaClass *)lua_touserdata(L, -1);
    if (lua_type(L, 2) != LUA_TNUMBER) {
        LuaError("%s: Non-number array access", luaClass->name);
        return 0;
    }
    array = (unsigned char *)lua_touserdata(L, 1);
    index = (int)lua_tonumber(L, 2);
    if (lua_type(L, 3) != LUA_TNUMBER) {
        LuaError("Value to set must be number");
        return 0;
    }
    array[index] = (unsigned char)lua_tonumber(L, 3);
    return 0;
}


int LuaUnsignedCharArray_New(lua_State *L) {
    int count;
    unsigned char *array;

    if (lua_gettop(L) != 0) {
        count = (int)lua_tonumber(L, -2);
    } else {
        count = 1;
    }
    array = new unsigned char[count];
    lua_pushusertag(L, array, ((LuaClass *)lua_touserdata(L, -1))->instanceTag);
    return 1;
}

int LuaShortArray_Delete(lua_State *L) {
    delete[] (short *)lua_touserdata(L, 1);
    return 0;
}

int LuaShortArray_Get(lua_State *L) {
    LuaClass *luaClass;
    short *array;

    luaClass = (LuaClass *)lua_touserdata(L, -1);
    if (lua_type(L, 2) != LUA_TNUMBER) {
        LuaError("%s: Non-number array access", luaClass->name);
        return 0;
    }
    array = (short *)lua_touserdata(L, 1);
    lua_pushnumber(L, array[(int)lua_tonumber(L, 2)]);
    return 1;
}


int LuaShortArray_Set(lua_State *L) {
    LuaClass *luaClass;
    short *array;
    int index;

    luaClass = (LuaClass *)lua_touserdata(L, -1);
    if (lua_type(L, 2) != LUA_TNUMBER) {
        LuaError("%s: Non-number array access", luaClass->name);
        return 0;
    }
    array = (short *)lua_touserdata(L, 1);
    index = (int)lua_tonumber(L, 2);
    if (lua_type(L, 3) != LUA_TNUMBER) {
        LuaError("Value to set must be number");
        return 0;
    }
    array[index] = (short)lua_tonumber(L, 3);
    return 0;
}


int LuaShortArray_New(lua_State *L) {
    int count;
    short *array;

    if (lua_gettop(L) != 0) {
        count = (int)lua_tonumber(L, -2);
    } else {
        count = 1;
    }
    array = new short[count];
    lua_pushusertag(L, array, ((LuaClass *)lua_touserdata(L, -1))->instanceTag);
    return 1;
}

int LuaUnsignedShortArray_Delete(lua_State *L) {
    delete[] (unsigned short *)lua_touserdata(L, 1);
    return 0;
}

int LuaUnsignedShortArray_Get(lua_State *L) {
    LuaClass *luaClass;
    unsigned short *array;

    luaClass = (LuaClass *)lua_touserdata(L, -1);
    if (lua_type(L, 2) != LUA_TNUMBER) {
        LuaError("%s: Non-number array access", luaClass->name);
        return 0;
    }
    array = (unsigned short *)lua_touserdata(L, 1);
    lua_pushnumber(L, array[(int)lua_tonumber(L, 2)]);
    return 1;
}


int LuaUnsignedShortArray_Set(lua_State *L) {
    LuaClass *luaClass;
    unsigned short *array;
    int index;

    luaClass = (LuaClass *)lua_touserdata(L, -1);
    if (lua_type(L, 2) != LUA_TNUMBER) {
        LuaError("%s: Non-number array access", luaClass->name);
        return 0;
    }
    array = (unsigned short *)lua_touserdata(L, 1);
    index = (int)lua_tonumber(L, 2);
    if (lua_type(L, 3) != LUA_TNUMBER) {
        LuaError("Value to set must be number");
        return 0;
    }
    array[index] = (unsigned short)lua_tonumber(L, 3);
    return 0;
}


int LuaUnsignedShortArray_New(lua_State *L) {
    int count;
    unsigned short *array;

    if (lua_gettop(L) != 0) {
        count = (int)lua_tonumber(L, -2);
    } else {
        count = 1;
    }
    array = new unsigned short[count];
    lua_pushusertag(L, array, ((LuaClass *)lua_touserdata(L, -1))->instanceTag);
    return 1;
}

int LuaIntArray_Delete(lua_State *L) {
    delete[] (int *)lua_touserdata(L, 1);
    return 0;
}

int LuaIntArray_Get(lua_State *L) {
    LuaClass *luaClass;
    int *array;

    luaClass = (LuaClass *)lua_touserdata(L, -1);
    if (lua_type(L, 2) != LUA_TNUMBER) {
        LuaError("%s: Non-number array access", luaClass->name);
        return 0;
    }
    array = (int *)lua_touserdata(L, 1);
    lua_pushnumber(L, array[(int)lua_tonumber(L, 2)]);
    return 1;
}


int LuaIntArray_Set(lua_State *L) {
    LuaClass *luaClass;
    int *array;
    int index;

    luaClass = (LuaClass *)lua_touserdata(L, -1);
    if (lua_type(L, 2) != LUA_TNUMBER) {
        LuaError("%s: Non-number array access", luaClass->name);
        return 0;
    }
    array = (int *)lua_touserdata(L, 1);
    index = (int)lua_tonumber(L, 2);
    if (lua_type(L, 3) != LUA_TNUMBER) {
        LuaError("Value to set must be number");
        return 0;
    }
    array[index] = (int)lua_tonumber(L, 3);
    return 0;
}


int LuaIntArray_New(lua_State *L) {
    int count;
    int *array;

    if (lua_gettop(L) != 0) {
        count = (int)lua_tonumber(L, -2);
    } else {
        count = 1;
    }
    array = new int[count];
    lua_pushusertag(L, array, ((LuaClass *)lua_touserdata(L, -1))->instanceTag);
    return 1;
}

int LuaUnsignedIntArray_Delete(lua_State *L) {
    delete[] (unsigned int *)lua_touserdata(L, 1);
    return 0;
}

int LuaUnsignedIntArray_Get(lua_State *L) {
    LuaClass *luaClass;
    unsigned int *array;

    luaClass = (LuaClass *)lua_touserdata(L, -1);
    if (lua_type(L, 2) != LUA_TNUMBER) {
        LuaError("%s: Non-number array access", luaClass->name);
        return 0;
    }
    array = (unsigned int *)lua_touserdata(L, 1);
    lua_pushnumber(L, array[(int)lua_tonumber(L, 2)]);
    return 1;
}


int LuaUnsignedIntArray_Set(lua_State *L) {
    LuaClass *luaClass;
    unsigned int *array;
    int index;

    luaClass = (LuaClass *)lua_touserdata(L, -1);
    if (lua_type(L, 2) != LUA_TNUMBER) {
        LuaError("%s: Non-number array access", luaClass->name);
        return 0;
    }
    array = (unsigned int *)lua_touserdata(L, 1);
    index = (int)lua_tonumber(L, 2);
    if (lua_type(L, 3) != LUA_TNUMBER) {
        LuaError("Value to set must be number");
        return 0;
    }
    array[index] = (unsigned int)lua_tonumber(L, 3);
    return 0;
}


int LuaUnsignedIntArray_New(lua_State *L) {
    int count;
    unsigned int *array;

    if (lua_gettop(L) != 0) {
        count = (int)lua_tonumber(L, -2);
    } else {
        count = 1;
    }
    array = new unsigned int[count];
    lua_pushusertag(L, array, ((LuaClass *)lua_touserdata(L, -1))->instanceTag);
    return 1;
}

int LuaLongArray_Delete(lua_State *L) {
    delete[] (long long *)lua_touserdata(L, 1);
    return 0;
}

int LuaLongArray_Get(lua_State *L) {
    LuaClass *luaClass;
    long long *array;

    luaClass = (LuaClass *)lua_touserdata(L, -1);
    if (lua_type(L, 2) != LUA_TNUMBER) {
        LuaError("%s: Non-number array access", luaClass->name);
        return 0;
    }
    array = (long long *)lua_touserdata(L, 1);
    lua_pushnumber(L, array[(int)lua_tonumber(L, 2)]);
    return 1;
}


int LuaLongArray_Set(lua_State *L) {
    LuaClass *luaClass;
    long long *array;
    int index;

    luaClass = (LuaClass *)lua_touserdata(L, -1);
    if (lua_type(L, 2) != LUA_TNUMBER) {
        LuaError("%s: Non-number array access", luaClass->name);
        return 0;
    }
    array = (long long *)lua_touserdata(L, 1);
    index = (int)lua_tonumber(L, 2);
    if (lua_type(L, 3) != LUA_TNUMBER) {
        LuaError("Value to set must be number");
        return 0;
    }
    array[index] = (long long)lua_tonumber(L, 3);
    return 0;
}


int LuaLongArray_New(lua_State *L) {
    int count;
    long long *array;

    if (lua_gettop(L) != 0) {
        count = (int)lua_tonumber(L, -2);
    } else {
        count = 1;
    }
    array = new long long[count];
    lua_pushusertag(L, array, ((LuaClass *)lua_touserdata(L, -1))->instanceTag);
    return 1;
}

int LuaUnsignedLongArray_Delete(lua_State *L) {
    delete[] (unsigned long long *)lua_touserdata(L, 1);
    return 0;
}

int LuaUnsignedLongArray_Get(lua_State *L) {
    LuaClass *luaClass;
    unsigned long long *array;

    luaClass = (LuaClass *)lua_touserdata(L, -1);
    if (lua_type(L, 2) != LUA_TNUMBER) {
        LuaError("%s: Non-number array access", luaClass->name);
        return 0;
    }
    array = (unsigned long long *)lua_touserdata(L, 1);
    lua_pushnumber(L, array[(int)lua_tonumber(L, 2)]);
    return 1;
}


int LuaUnsignedLongArray_Set(lua_State *L) {
    LuaClass *luaClass;
    unsigned long long *array;
    int index;

    luaClass = (LuaClass *)lua_touserdata(L, -1);
    if (lua_type(L, 2) != LUA_TNUMBER) {
        LuaError("%s: Non-number array access", luaClass->name);
        return 0;
    }
    array = (unsigned long long *)lua_touserdata(L, 1);
    index = (int)lua_tonumber(L, 2);
    if (lua_type(L, 3) != LUA_TNUMBER) {
        LuaError("Value to set must be number");
        return 0;
    }
    array[index] = (unsigned long long)lua_tonumber(L, 3);
    return 0;
}


int LuaUnsignedLongArray_New(lua_State *L) {
    int count;
    unsigned long long *array;

    if (lua_gettop(L) != 0) {
        count = (int)lua_tonumber(L, -2);
    } else {
        count = 1;
    }
    array = new unsigned long long[count];
    lua_pushusertag(L, array, ((LuaClass *)lua_touserdata(L, -1))->instanceTag);
    return 1;
}

int LuaBoolArray_Delete(lua_State *L) {
    delete[] (bool *)lua_touserdata(L, 1);
    return 0;
}

int LuaBoolArray_Get(lua_State *L) {
    LuaClass *luaClass;
    bool *array;

    luaClass = (LuaClass *)lua_touserdata(L, -1);
    if (lua_type(L, 2) != LUA_TNUMBER) {
        LuaError("%s: Non-number array access", luaClass->name);
        return 0;
    }
    array = (bool *)lua_touserdata(L, 1);
    lua_pushnumber(L, array[(int)lua_tonumber(L, 2)]);
    return 1;
}


int LuaBoolArray_New(lua_State *L) {
    int count;
    bool *array;

    if (lua_gettop(L) != 0) {
        count = (int)lua_tonumber(L, -2);
    } else {
        count = 1;
    }
    array = new bool[count];
    lua_pushusertag(L, array, ((LuaClass *)lua_touserdata(L, -1))->instanceTag);
    return 1;
}

int LuaFloatArray_Delete(lua_State *L) {
    delete[] (float *)lua_touserdata(L, 1);
    return 0;
}

int LuaFloatArray_Get(lua_State *L) {
    LuaClass *luaClass;
    float *array;

    luaClass = (LuaClass *)lua_touserdata(L, -1);
    if (lua_type(L, 2) != LUA_TNUMBER) {
        LuaError("%s: Non-number array access", luaClass->name);
        return 0;
    }
    array = (float *)lua_touserdata(L, 1);
    lua_pushnumber(L, array[(int)lua_tonumber(L, 2)]);
    return 1;
}


int LuaFloatArray_Set(lua_State *L) {
    LuaClass *luaClass;
    float *array;
    int index;

    luaClass = (LuaClass *)lua_touserdata(L, -1);
    if (lua_type(L, 2) != LUA_TNUMBER) {
        LuaError("%s: Non-number array access", luaClass->name);
        return 0;
    }
    array = (float *)lua_touserdata(L, 1);
    index = (int)lua_tonumber(L, 2);
    if (lua_type(L, 3) != LUA_TNUMBER) {
        LuaError("Value to set must be number");
        return 0;
    }
    array[index] = (float)lua_tonumber(L, 3);
    return 0;
}


int LuaFloatArray_New(lua_State *L) {
    int count;
    float *array;

    if (lua_gettop(L) != 0) {
        count = (int)lua_tonumber(L, -2);
    } else {
        count = 1;
    }
    array = new float[count];
    lua_pushusertag(L, array, ((LuaClass *)lua_touserdata(L, -1))->instanceTag);
    return 1;
}

int LuaDoubleArray_Delete(lua_State *L) {
    delete[] (double *)lua_touserdata(L, 1);
    return 0;
}

int LuaDoubleArray_Get(lua_State *L) {
    LuaClass *luaClass;
    double *array;

    luaClass = (LuaClass *)lua_touserdata(L, -1);
    if (lua_type(L, 2) != LUA_TNUMBER) {
        LuaError("%s: Non-number array access", luaClass->name);
        return 0;
    }
    array = (double *)lua_touserdata(L, 1);
    lua_pushnumber(L, array[(int)lua_tonumber(L, 2)]);
    return 1;
}


int LuaDoubleArray_Set(lua_State *L) {
    LuaClass *luaClass;
    double *array;
    int index;

    luaClass = (LuaClass *)lua_touserdata(L, -1);
    if (lua_type(L, 2) != LUA_TNUMBER) {
        LuaError("%s: Non-number array access", luaClass->name);
        return 0;
    }
    array = (double *)lua_touserdata(L, 1);
    index = (int)lua_tonumber(L, 2);
    if (lua_type(L, 3) != LUA_TNUMBER) {
        LuaError("Value to set must be number");
        return 0;
    }
    array[index] = (double)lua_tonumber(L, 3);
    return 0;
}


int LuaDoubleArray_New(lua_State *L) {
    int count;
    double *array;

    if (lua_gettop(L) != 0) {
        count = (int)lua_tonumber(L, -2);
    } else {
        count = 1;
    }
    array = new double[count];
    lua_pushusertag(L, array, ((LuaClass *)lua_touserdata(L, -1))->instanceTag);
    return 1;
}
