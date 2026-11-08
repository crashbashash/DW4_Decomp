extern int DAT_00481e50;
int FUN_0010c6f0(void);
int FUN_0010c620(void *, int);
int FUN_0010b528(int fd, void *buf, int n) {
    if (fd == 0) {
        if (DAT_00481e50 == 0) {
            if (FUN_0010c6f0() == 0) goto err;
            DAT_00481e50 = 1;
        }
        return FUN_0010c620(buf, n);
    }
err:
    return -1;
}
