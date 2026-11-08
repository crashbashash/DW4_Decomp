typedef struct B { char pad[8]; char *f8; } B;
typedef struct A { char pad[228]; int f228; } A;
extern "C" {
int FUN_0039a130(int, int, int);
int FUN_0039a500(int, B *);
int strcmp(char *, char *);
extern char DAT_004e0858[];
extern char DAT_0050f178[];
extern char DAT_0050f188[];
extern int DAT_005887c8[4];
int FUN_00394fa0(int arg0, int arg1, A *arg2, B *arg3);
}
int FUN_00394fa0(int arg0, int arg1, A *arg2, B *arg3) {
    char *var_a0;
    char *var_a0_2;
    char *t;

    t = arg3->f8;
    if (t != 0) {
        var_a0 = t;
    } else {
        var_a0 = DAT_004e0858;
    }
    if (strcmp(var_a0, DAT_0050f178) == 0) {
        FUN_0039a130(arg2->f228, arg1, DAT_005887c8[0]);
    } else {
        t = arg3->f8;
        if (t != 0) {
            var_a0_2 = t;
        } else {
            var_a0_2 = DAT_004e0858;
        }
        if (strcmp(var_a0_2, DAT_0050f188) == 0) {
            FUN_0039a500(arg2->f228, arg3);
        }
    }
    return 1;
}
