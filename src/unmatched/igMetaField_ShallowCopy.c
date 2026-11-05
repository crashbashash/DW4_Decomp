int igMetaField_CopyByTechnique();

void igMetaField_ShallowCopy(int a0, int a1, int a2, int a3) {
    igMetaField_CopyByTechnique(a0, a1, a2, *(char *)((char *)a0 + 39));
}
