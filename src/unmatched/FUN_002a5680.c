typedef struct {
    int w[8];
} Pos2a5680;

void FUN_002af070(void *, int *, int *);
int FUN_002adc40(void *, int);

int FUN_002a5680(char *obj) {
    Pos2a5680 pos;
    int now;
    int rate;
    int start;
    int span;

    if (*(int *)(obj + 3472) == 0) {
        return 0;
    }
    pos = *(Pos2a5680 *)(obj + 3396);
    FUN_002af070(&pos, &now, &rate);
    FUN_002af070(obj + 3476, &start, &rate);
    span = FUN_002adc40(obj, 53) * rate;
    if (now <= start) {
        return 1;
    }
    if (now < start + span) {
        return 0;
    }
    return 1;
}
