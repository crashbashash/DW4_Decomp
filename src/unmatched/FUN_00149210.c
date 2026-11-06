/* The field must be shifted as unsigned (srlv); (unsigned short) promotes to signed int, so the
 * (unsigned int) cast is needed or the compiler emits srav. */
int FUN_00149210(void *arg0, int arg1) {
    return (((unsigned int) * (unsigned short *)((char *)(arg0) + 68) >> arg1) & 1) == 0;
}
