typedef struct PicEntryGeom {
    int f0;
    int f4;
    int width;
    int height;
    int busy;
} PicEntryGeom;

typedef struct PicEntryWork {
    int handle;
    char pad4[272];
    int limit;
} PicEntryWork;

typedef struct PicEntryObj {
    char pad[2316];
    PicEntryGeom geom;
    char pad2336[5784];
    PicEntryWork *work;
} PicEntryObj;

typedef struct PicEntryChunk {
    char *addr;
    int size;
} PicEntryChunk;

int FUN_0028eef0(int sj, int *pts);
void FUN_0028ef50(int sj, int *x, int *y, int *z);
int FUN_0029e290(PicEntryObj *obj, int idx);
int FUN_002a0bb8(PicEntryObj *obj, int code);
void FUN_002a5ef0(PicEntryObj *obj, int pts, PicEntryChunk *chunk);
void FUN_002a6010(PicEntryGeom *geom, int pts, int a, int x);
int FUN_002a6048(PicEntryObj *obj, PicEntryGeom *geom);
int FUN_002adc40(PicEntryObj *obj, int id);

int FUN_002a5dc0(PicEntryObj *obj, int sj, int a, PicEntryChunk *chunk)
{
    PicEntryGeom *geom = &obj->geom;
    PicEntryWork *work = obj->work;
    int pts;
    int x, y, z;
    int n;

    if (geom->busy != 0)
        return 0;
    if (FUN_0028eef0(sj, &pts) != 0)
        return FUN_002a0bb8(obj, 0xFF000F16);
    FUN_0028ef50(sj, &x, &y, &z);
    if (FUN_002adc40(obj, 60) == 0)
        work->limit = 0;
    else {
        n = FUN_0029e290(obj, 1);
        if (z == -1)
            z = x;
        work->limit = z < n ? z : n;
    }
    FUN_002a5ef0(obj, pts, chunk);
    FUN_002a6010(geom, pts, a, x);
    return FUN_002a6048(obj, geom);
}
