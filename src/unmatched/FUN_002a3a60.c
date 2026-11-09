typedef struct PicWaitWork {
    int handle;
    char pad4[272];
    int limit;
} PicWaitWork;

typedef struct PicWaitMsg {
    int busy;
    char pad4[120];
    int f124;
} PicWaitMsg;

typedef struct PicWaitObj {
    char pad[120];
    PicWaitMsg msg;
    char pad248[7872];
    PicWaitWork * work;
} PicWaitObj;

void FUN_0028eef0(int handle, int *value);
int FUN_0029e290(PicWaitObj *obj, int idx);
int FUN_0029e2d0(PicWaitObj *obj, int idx);
int FUN_002a4bb0(PicWaitObj *obj);
int FUN_002b03e8(PicWaitObj *obj, int idx);

int FUN_002a3a60(PicWaitObj *obj)
{
    PicWaitWork *work = (PicWaitWork *)obj->work;
    int handle = work->handle;
    PicWaitMsg *msg = &obj->msg;
    int value;
    int idx;

    if (FUN_002a4bb0(obj) == 1)
        return 1;
    if (msg->busy != 0 && msg->f124 == 0)
        return 1;
    FUN_0028eef0(handle, &value);
    if (value == 0x3FFFF)
        return 1;
    if (FUN_0029e2d0(obj, 1) >= work->limit)
        return 1;
    idx = FUN_002b03e8(obj, 1) == 0;
    if (FUN_0029e2d0(obj, idx) < FUN_0029e290(obj, idx))
        return 0;
    return 1;
}
