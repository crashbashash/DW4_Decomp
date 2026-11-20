int igExternalImageEntry_LoadExternalFile(A *arg0) {
    igObject *temp_v0;
    temp_v0 = (igObject *)igImage_CreateInstance((int)igObject_GetAllocator((igObject *)arg0));
    if (FUN_001551f0((S_1551f0 *)arg0, (V_1551f0 *)temp_v0) == 0) {
        temp_v0->_refCount = temp_v0->_refCount - 1;
        if ((temp_v0->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_v0);
        }
        return 0;
    }
    arg0->vX(temp_v0);
    temp_v0->_refCount = temp_v0->_refCount - 1;
    if ((temp_v0->_refCount & 0x7FFFFF) == 0) {
        igObject_Destroy(temp_v0);
    }
    return 1;
}

int FUN_001551f0(S_1551f0 *arg0, V_1551f0 *arg1) {
    char *s1;
    char *buf;
    int n;
    int n2;
    int tot;

    if (arg1->vX(arg0->f32) == 0) {
        s1 = arg0->f32;
        n = strlen(arg0->f40);
        n2 = n + strlen((char *)"/");
        tot = strlen(s1);
        tot = tot + n2;
        buf = (char *)((Gap::Core::igObject *)arg0)->malloc(tot + 1);
        strcpy(buf, arg0->f40);
        strcat(buf, (char *)"/");
        strcat(buf, arg0->f32);
        if (arg1->vX(buf) == 0) {
            ((Gap::Core::igObject *)arg0)->free(buf);
            return 0;
        }
        ((Gap::Core::igObject *)arg0)->free(buf);
    }
    return 1;
}

void igExternalImageEntry_InitDefaults(int arg0) {
    igExternalDirEntry_InitDefaults((igDirEntry *)arg0);
    igExternalDirEntry_SetDirectoryName((igExternalDirEntry *)arg0, (int)&text_igImageDirectory[0]);
}

