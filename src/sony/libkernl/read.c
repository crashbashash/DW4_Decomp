extern int DAT_00481e50;
int sceTtyInit(void);
int sceTtyRead(void *, int);
int read(int fd, void *buf, int n) {
    if (fd == 0) {
        if (DAT_00481e50 == 0) {
            if (sceTtyInit() == 0) goto err;
            DAT_00481e50 = 1;
        }
        return sceTtyRead(buf, n);
    }
err:
    return -1;
}
