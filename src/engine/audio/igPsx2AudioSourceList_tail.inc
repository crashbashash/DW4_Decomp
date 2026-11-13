igMetaObject *Gap__igPsx2AudioSourceList__vfunc_22(void)
{
    return g_igPsx2AudioSourceList_metaObject[0];
}

#define AUDIO_SOURCE_ENTRY_SIZE 0x24
int Gap__igPsx2AudioSourceList__vfunc_23(igPsx2AudioSourceList *self) {
    return AUDIO_SOURCE_ENTRY_SIZE;
}

void Gap__igPsx2AudioSourceList__vfunc_18(igPsx2AudioSourceList *self) {
    int count;

    count = self->_count;
    if (count < self->_capacity) {
        List_Reserve(self, count, 0x24);
    }
}
}
