typedef struct T { int word0; int references; } T;
int FUN_002fd610(T **, int);
void igObject_Destroy(T *);
int FUN_002fe290(int, int);
extern int DAT_0055f468[4];
int Gap__Core__igGenericAttrDefaultManager__vfunc_24(T **arg0, int arg1, int arg2) {
    T *sp3C;
    T *temp_v1;

    FUN_002fe290(arg2, DAT_0055f468[0]);
    FUN_002fd610(&sp3C, arg2);
    *arg0 = sp3C;
    temp_v1 = *arg0;
    if (temp_v1 != 0) {
        temp_v1->references = temp_v1->references + 1;
    }
    if (sp3C != 0) {
        sp3C->references = sp3C->references - 1;
        if (((unsigned long long)(long long)sp3C->references & 0x7fffffULL) == 0) {
            igObject_Destroy(sp3C);
        }
    }
    return 0;
}
