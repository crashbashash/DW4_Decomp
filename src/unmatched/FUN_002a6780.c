typedef struct PicDecodePic {
    char pad[24];
    int id;
    char pad28[60];
    signed char skip;
} PicDecodePic;

typedef struct PicDecodeWork {
    int handle;
    char pad4[136];
    PicDecodePic pic;
    char pad232[132];
    int flag;
} PicDecodeWork;

typedef struct PicDecodeObj {
    char pad[8120];
    PicDecodeWork *work;
} PicDecodeObj;

int FUN_0027c760(int sj, int id, int mode);
int FUN_0028ed30(int handle, int sj);
void FUN_002a4b20(PicDecodeObj *obj, int size);
int FUN_002a4bc8(PicDecodeObj *obj, int status, int n, int code);
void FUN_002a6870(PicDecodeObj *obj);
void FUN_002abc98(PicDecodeObj *obj, int a, int b);

int FUN_002a6780(PicDecodeObj *obj, int sj)
{
    PicDecodeWork *work = obj->work;
    int handle = work->handle;
    PicDecodePic *pic;
    int before;
    int status;
    int used;
    int ret;

    FUN_002a6870(obj);
    before = FUN_0027c760(sj, 0, 1);
    pic = &work->pic;
    status = FUN_0028ed30(handle, sj);
    used = FUN_0027c760(sj, 0, 1) - before;
    ret = FUN_002a4bc8(obj, status, used, 0xFF000F07);
    FUN_002a4b20(obj, used);
    if (ret != 0)
        return ret;
    if (pic->skip == 0)
        work->flag = 1;
    FUN_002abc98(obj, 1, pic->id);
    return 0;
}
