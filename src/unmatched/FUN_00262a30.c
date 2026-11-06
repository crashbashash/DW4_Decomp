/* Stores a 16-bit value big-endian at bytes. */
void FUN_00262a30(unsigned char *bytes, short value) {
    bytes[1] = value;
    bytes[0] = (unsigned short)value >> 8;
}
