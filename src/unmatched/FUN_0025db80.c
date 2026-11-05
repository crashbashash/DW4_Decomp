/* 0x0025db80 - FUN_0025db80. Indexed halfword: arg1 *= 2; arg1 += arg0 joins the web (retail sll a1 / addu a1,a1,a0). */
short FUN_0025db80(int arg0, int arg1) {
    arg1 *= 2;
    arg1 += arg0;
    return *(short *)((char *)arg1 + 226);
}
