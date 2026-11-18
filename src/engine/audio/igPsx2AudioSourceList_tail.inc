igMetaObject *igPsx2AudioSourceList_GetMeta(void)
{
    return g_igPsx2AudioSourceList_metaObject;
}

#define AUDIO_SOURCE_ENTRY_SIZE 0x24
int igPsx2AudioSourceList_GetElementSize(igPsx2AudioSourceList *self) {
    return AUDIO_SOURCE_ENTRY_SIZE;
}

void igPsx2AudioSourceList_TrimCapacity(igPsx2AudioSourceList *self) {
    int count;

    count = self->_count;
    if (count < self->_capacity) {
        List_Reserve((igDataList *)self, count, 0x24);
    }
}
}
