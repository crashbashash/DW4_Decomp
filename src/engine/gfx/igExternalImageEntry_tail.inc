int igExternalImageEntry_LoadExternalFile(A *arg0) {
    igObject *temp_v0;
    temp_v0 = (igObject *)igImage_CreateInstance(((Gap::Core::igObject *)arg0)->getMemoryPool());
    if (FUN_001551f0((S_1551f0 *)arg0, (V_1551f0 *)temp_v0) == 0) {
        temp_v0->release();
        return 0;
    }
    arg0->vX(temp_v0);
    temp_v0->release();
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
    ((Gap::Core::igExternalDirEntry *)arg0)->setDirectoryName((char const *)(&text_igImageDirectory[0]));
}

