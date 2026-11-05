int DeleteSema();
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
void Gap__Core__igPsx2Semaphore__vfunc_24(int *arg0, int *arg1) {
    int id = arg1[3];
    int *p;
    if (id == -1) {
        *arg0 = DAT_004fb418[0];
        return;
    }
    id = DeleteSema(id);
    arg1[3] = -1;
    p = id >= 0 ? DAT_004fb410 : DAT_004fb418;
    *arg0 = *p;
}
