/* CRI thunk: forwards the sub-object stored at +12 to the worker at 0x27a0e0. */
typedef struct CriObj {
    int pad[3];
    int inner;
} CriObj;

extern void FUN_0027a0e0(int inner);

void FUN_00265ba0(CriObj *obj)
{
    FUN_0027a0e0(obj->inner);
}
