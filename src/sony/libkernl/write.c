extern int DAT_00481e50;
int sceTtyInit(void);
int sceTtyWrite(void *, int);
int write(int fd, void *buf, int n) {
    if ((unsigned int)(fd - 1) < 2) {
        if (DAT_00481e50 == 0) {
            if (sceTtyInit() == 0) goto err;
            DAT_00481e50 = 1;
        }
        return sceTtyWrite(buf, n);
    }
err:
    return -1;
}
