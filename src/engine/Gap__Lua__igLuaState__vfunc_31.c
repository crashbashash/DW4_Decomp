/* Returns 0x50 (the offset FUN_00280810 stores at +76 as the inline-data pointer) plus the int
 * words at +20..+72. The meaning of those words is not recovered; the layout is the one
 * FUN_00280810 constructs, not the reflected igLuaState. */
int Gap__Lua__igLuaState__vfunc_31(void *self) {
    int *word = (int *)self;
    return word[18] + (word[17] + (word[16] + (word[15] + (word[14] + (word[13] + (word[12] + (word[11] + (word[10] + (word[9] + (word[8] + (word[7] + (word[5] + 0x50 + word[6]))))))))))));
}
