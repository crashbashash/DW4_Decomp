int igLongMetaField_ValueFromString(int self, int unused, int string) {
    int consumed;

    consumed = 0;
    sscanf(string, &text_ld_n[0], unused, &consumed);
    return consumed;
}

void igLongMetaField_ValueToString(int *out, int self, long long *value) {
    int text[256];
    int pool;
    int interned;

    sprintf(&text[0], &percent_ld[0], *value);
    if (&text[0] == 0) {
        interned = 0;
    } else {
        if (g_stringPool[0] == 0) {
            pool = ((int)StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool[0] = pool;
        }
        interned = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)&text[0]);
    }
    *out = interned;
}

/* igLongMetaField vtable slot +0x64 (GetSize): the byte size of one field value. A "long" field is
 * 8 bytes wide in the reflected layout. */
int igLongMetaField_GetSize(void) {
    return 8;
}

void igLongMetaField_SetDefault(void **self, long long value) {
    long long stored;

    stored = value;
    ((igMetaFieldView *)(self))->SetDefault(&stored);
}

int igLongMetaField_GetAlignment(void) {
    return 8;
}

igMediaView *igMediaFile_FindDeviceForPath(int path) {
    int colon;
    int len;
    int i;
    igMediaView *media;

    colon = ((int)strchr(path, 0x3A));
    if (colon != 0) {
        len = colon - path;
        for (i = g_fileDeviceList.p->_count - 1; i <= 0; i--) {
            media = ((igMediaView **)g_fileDeviceList.p->_data)[i];
            if (media->vfunc_32(path, len) != 0) {
                return media;
            }
        }
    }
    return g_defaultMedia[0];
}

void igMedia_CreateMediaList(void) {
    int pool;
    igObjectList *list;

    pool = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    list = g_fileDeviceList.p;
    if (list != 0) {
        list->_refCount = list->_refCount - 1;
        if ((list->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(list);
        }
    }
    g_fileDeviceList.p = (igObjectList *)(igMediaList_Create(pool));
}

void igMedia_AddMedia(int media) {
    ObjectList_AppendRetained(g_fileDeviceList.p, (igObject *)media);
}

void igMedia_ReleaseMediaList(void) {
    int *o;

    ((int *)g_defaultMedia)[0] = 0;
    o = (int *)g_fileDeviceList.p;
    if (o != 0) {
        o[1] = o[1] - 1;
        if ((o[1] & 0x7FFFFF) == 0) {
            igObject_Destroy(o);
        }
    }
    g_fileDeviceList.p = 0;
}

void igMedia_SetDefaultMedia(int media) {
    *(int *)0x586F28 = media;
}

