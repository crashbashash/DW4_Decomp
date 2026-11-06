/* 0x00180c20: igPsx2UserUCodeExt vtable slot 54. Unlike the class's own published-MetaObject accessor, this
 * leaf (lui/lw) returns the class handle slot g_igPsx2PointSpriteExt_metaObject of the sibling class igPsx2PointSpriteExt
 * (registered in src/engine/igPsx2PointSpriteExt_Register.c). Read through the array extern so the
 * load stays absolute; slot role not established beyond the returned handle. */
extern int g_igPsx2PointSpriteExt_metaObject[4];
int Gap__Core__igPsx2UserUCodeExt__vfunc_54(void) {
    return g_igPsx2PointSpriteExt_metaObject[0];
}
