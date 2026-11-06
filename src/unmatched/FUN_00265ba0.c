typedef struct CriObj {
    int pad[3];
    int inner;
} CriObj;

extern void FUN_0027a0e0(int inner);

void FUN_00265ba0(CriObj *obj)
{
    FUN_0027a0e0(obj->inner);
}
