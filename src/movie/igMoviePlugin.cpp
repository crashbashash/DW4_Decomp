
struct R { char pad[4]; int f4; char pad2[12]; char f20; };
struct S { char pad[8]; struct R *f8; };
extern "C" int igInsightCore_AddManager(int, struct R *);
extern "C" struct R *igMovieManager_CreateInstance(int);
extern "C" int Memory_GetAllocatorBySelector(int);
extern "C" int igObject_Destroy(struct R *);
extern "C" int igObject_GetAllocator(struct S *);
extern "C" int g_ndmwAllocatorSelector[4];
extern "C" unsigned char GPR_00554c14;
extern "C" void Gap__igMoviePlugin__vfunc_21(struct S *arg0, int arg1);
extern "C" int igInsightCore_RemoveManager(int, int);
extern "C" void Gap__igMoviePlugin__vfunc_22(void *arg0, int arg1);
extern "C" int g_igMoviePlugin_metaObject[4];
extern "C" int Gap__igMoviePlugin__vfunc_20(void);

void Gap__igMoviePlugin__vfunc_21(struct S *arg0, int arg1) {
    int var_v0;
    struct R *temp_a0;
    var_v0 = igObject_GetAllocator(arg0);
    var_v0 = GPR_00554c14 != 0 ? var_v0 : Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0]);
    temp_a0 = arg0->f8;
    if (temp_a0 != 0) {
        temp_a0->f4 = temp_a0->f4 - 1;
        if ((temp_a0->f4 & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->f8 = igMovieManager_CreateInstance(var_v0);
    arg0->f8->f20 = 1;
    igInsightCore_AddManager(arg1, arg0->f8);
}

void Gap__igMoviePlugin__vfunc_22(void *arg0, int arg1) {
    igInsightCore_RemoveManager(arg1, *(int *)((char *)(arg0) + 8));
}

int Gap__igMoviePlugin__vfunc_20(void)
{
    return g_igMoviePlugin_metaObject[0];
}

