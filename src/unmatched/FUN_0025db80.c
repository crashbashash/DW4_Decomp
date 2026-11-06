/* arg1 is scaled and added to arg0 in place so the index stays one web. */
short FUN_0025db80(int arg0, int arg1) {
    arg1 *= 2;
    arg1 += arg0;
    return *(short *)((char *)arg1 + 226);
}
