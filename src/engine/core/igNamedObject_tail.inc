void igNamedObject_SetName(struct N_2fecb0 *arg0, int arg1) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    char *temp_a0;
    void *temp_s0;
    if (g_stringPool[0] == 0) {
        var_v0 = ((int)StringPool_Allocate(0x10));
        if (var_v0 != 0) {
            var_v0 = ((int)StringPool_Construct((S_2eadf0 *)var_v0));
        }
        g_stringPool[0] = var_v0;
    }
    temp_s0 = (void *)(((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)arg1)));
    temp_a0 = arg0->f8;
    if (temp_a0 != 0) {
        temp_a1 = (int *)(temp_a0 - 8);
        temp_v1 = *(int *)((char *)temp_a0 - 4) - 1;
        *(int *)((char *)temp_a0 - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
        }
    }
    arg0->f8 = (char *)temp_s0;
}

