typedef struct PicTypeWork {
    int handle;
    char pad4[112];
    int mode;
    char pad120[152];
    int enable;
} PicTypeWork;

typedef struct PicTypeObj {
    char pad[3648];
    int f3648;
    char pad3652[4468];
    PicTypeWork *work;
} PicTypeObj;

typedef struct PicTypeFrm {
    char pad[24];
    int type;
} PicTypeFrm;

int FUN_0028f018(int handle, int *a, int *b);
int FUN_002adc40(PicTypeObj *obj, int id);

void FUN_002a6368(PicTypeObj *obj, PicTypeFrm *frm, int kind)
{
    PicTypeWork *work = obj->work;
    int handle = work->handle;
    int mode = work->mode;
    int a, b;

    if (work->enable != 0) {
        FUN_0028f018(handle, &a, &b);
        if (a == 1)
            mode = 5;
        else {
            if (obj->f3648 == 0 && FUN_002adc40(obj, 73) == 1)
                b = 1;
            if (b == 1)
                mode = 2;
        }
    }
    if (kind == 1) {
        if (frm->type == 1 || frm->type == 2)
            mode = 2;
    } else if (mode == 2)
        mode = 3;
    else if (mode == 3)
        mode = 5;
    work->mode = mode;
}
