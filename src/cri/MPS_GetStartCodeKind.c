/* Classifies an MPEG-1/2 system-layer start code (00 00 01 xx) at p:
 * 0x10000 pack header, 0x20000 system header, 0x80000 program end,
 * 0x40000 PES packet (stream id >= 0xBC), 0 otherwise. */
int MPS_GetStartCodeKind(unsigned char *p) {
    unsigned char code;

    if (p[0] == 0 && p[1] == 0 && p[2] == 1) {
        code = p[3];
        switch (code) {
        case 0xBA: return 0x10000; /* pack_start_code */
        case 0xBB: return 0x20000; /* system_header_start_code */
        case 0xB9: return 0x80000; /* MPEG_program_end_code */
        }
        if (code >= 0xBC) return 0x40000; /* PES packet */
    }
    return 0;
}
