int igMetaField_IsAlikeByTechnique();

void igMetaField_IsAlikeDeep(int a0, int a1, int a2, int a3) {
    igMetaField_IsAlikeByTechnique(a0, a1, a2, *(char *)((char *)a0 + 43));
}
