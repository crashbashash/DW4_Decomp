void FUN_00208f20(int arg0) {
    int temp_a3;

    temp_a3 = *(int *)0x569330 * 2;
    *(int *)0x56B028 = (int) (*(int *)0x56B028 & ~(3 << temp_a3));
    *(int *)0x56B028 = (int) (*(int *)0x56B028 | ((arg0 & 3) << temp_a3));
}
