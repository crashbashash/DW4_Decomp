int sfd_GetStmVersion(void *arg0) {
    int r = 0;
    int t, m;
    arg0 = (char *)arg0 + 0x78;
    if (*(int *)arg0 != 0) {
        t = ((int *)arg0)[1];
        arg0 = (void *)((int *)arg0)[2];
        m = t * 3; m = m << 3; m = m + t; r = m << 2;
        r = r + (int)arg0;
    }
    return r;
}
