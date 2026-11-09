typedef struct VidCreateWork {
    int dec;
} VidCreateWork;

typedef struct VidCreateObj {
    char pad[56];
    int mode;
    char pad60[8060];
    VidCreateWork *work;
    char pad8124[996];
    VidCreateWork workbuf;
} VidCreateObj;

typedef struct VidCreateBuf3 {
    char *base;
    int count;
    int size;
} VidCreateBuf3;

extern char *DAT_00585620;
extern int DAT_00585624;
extern int DAT_00585628;
int FUN_0028ea48(int dec, int (*cb)(), VidCreateObj *obj);
int FUN_00291048(void);
int FUN_00291250(int dec, int id, int value);
int FUN_002a0bb8(int obj, int code);
int FUN_002a3558(VidCreateObj *obj, char *base, int count, int size);
int FUN_002a7770(VidCreateObj *obj, VidCreateWork *work);
int FUN_002a7b48();
void FUN_002a7d18(int dec);
void FUN_002a97a0(VidCreateObj *obj);
int FUN_002abf68(void);
int FUN_002adc40(VidCreateObj *obj, int id);

int FUN_002a7610(VidCreateObj *obj)
{
    VidCreateWork *work = &obj->workbuf;
    int dec;
    int ret;

    ret = FUN_002adc40(obj, 5);
    if (ret == 0)
        return ret;
    obj->work = work;
    ret = FUN_002a7770(obj, work);
    if (ret != 0)
        return ret;
    FUN_002a97a0(obj);
    dec = FUN_00291048();
    if (dec == 0)
        return FUN_002a0bb8(0, 0xFF000F0A);
    if (FUN_0028ea48(dec, FUN_002a7b48, obj) != 0) {
        FUN_002a7d18(dec);
        return FUN_002a0bb8(0, 0xFF000F0B);
    }
    FUN_00291250(dec, 1, FUN_002adc40(obj, 0));
    FUN_00291250(dec, 2, FUN_002adc40(obj, 1));
    FUN_00291250(dec, 6, obj->mode);
    work->dec = dec;
    if (FUN_002abf68() != 0)
        FUN_002a3558(obj, DAT_00585620, DAT_00585624, DAT_00585628);
    return 0;
}
