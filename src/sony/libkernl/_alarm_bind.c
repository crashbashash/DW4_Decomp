int isceSifSendCmd();

int _alarm_bind(int arg0, int arg1, int arg2, int arg3) {
    return (isceSifSendCmd(0x80000008, arg3, 0x40, 0, 0, 0) != 0) ? 0 : 0x800;
}
