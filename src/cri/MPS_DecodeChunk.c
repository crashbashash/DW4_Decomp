/* Parses one chunk of a system stream through the handle's parser entry (+212),
 * or reports error 0xFF020301 when the handle is invalid. */
typedef struct MpsHn MpsHn;
typedef int (*MpsParseFunc)(MpsHn *mps, unsigned char *pos, int n, int *len, int *flags);
struct MpsHn {
    char pad0[212];
    MpsParseFunc parse; /* +212 */
};

int mps_CheckHn(MpsHn *mps);
int mps_ReportError(MpsHn *mps, int error);

int MPS_DecodeChunk(MpsHn *mps, unsigned char *pos, int n, int *len, int *flags) {
    *len = 0;
    *flags = 0;
    if (mps_CheckHn(mps) != 0) {
        return mps_ReportError(0, 0xFF020301);
    }
    return mps->parse(mps, pos, n, len, flags);
}
