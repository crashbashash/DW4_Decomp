extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
struct T { char p[44]; unsigned char f44; char p2[11]; char f56; };
void Gap__Core__igPsx2Thread__vfunc_56(int *arg0, struct T *arg1, int arg2) {
    if (arg1->f44 == 0) {
        arg1->f56 = (arg2 == 1);
        *arg0 = DAT_004fb410[0];
    } else {
        *arg0 = DAT_004fb418[0];
    }
}
