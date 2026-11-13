/* Whether the header lists the video stream (stream id 0xE0) and its info value is 3. */
#define SFD_STM_VIDEO 224

typedef struct SfdHdrHn SfdHdrHn;

int sfd_HdrHasStm(SfdHdrHn *hdr, int id, int *present);
int sfd_GetHdrStmInfo(SfdHdrHn *hdr, int id, int *value);

int mwply_IsPicItemType3(SfdHdrHn *hdr) {
    int v[2];

    if (sfd_HdrHasStm(hdr, SFD_STM_VIDEO, v) == 0 || v[0] == 0) {
        return 0;
    }
    if (sfd_GetHdrStmInfo(hdr, SFD_STM_VIDEO, &v[1]) == 0) {
        return 0;
    }
    return v[1] == 3;
}
