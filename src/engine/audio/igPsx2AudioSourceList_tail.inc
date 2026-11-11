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

O *FUN_00145c60(O *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}
}
