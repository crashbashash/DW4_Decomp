/* 0x00109378 — 12 bytes. Mirror of FUN_00109368 (+0x08 <- +0x0c), same v0 return trick. */
int FUN_00109378(void *arg0) {
    return *(int *)((char *)(arg0) + 8) = *(int *)((char *)(arg0) + 12);
}
