extern int g_igLuaState_metaObject[4];

/* Virtual slot 22 of igLuaState: returns the igLuaState MetaObject handle (first word of the
 * class's MetaObject global, the one its `_GetMetaObject` accessor fills). */
int Gap__Lua__igLuaState__vfunc_22(void) {
    return g_igLuaState_metaObject[0];
}
