/* The game links none of this file's functions (the callback thread's sceSdRemoteCallbackInit and
   sceSdRemoteCallbackQuit, _sdrCBThread, _sdrCB), only its data. */
void *_sce_sdr_transIntr0Hdr = 0;
void *_sce_sdr_transIntr1Hdr = 0;
void *_sce_sdr_spu2IntrHdr = 0;
void *_sce_sdr_transIntr0Arg = 0;
void *_sce_sdr_transIntr1Arg = 0;
void *_sce_sdr_spu2IntrArg = 0;
void *_sce_sdr_transIntr0Gp = 0;
void *_sce_sdr_transIntr1Gp = 0;
void *_sce_sdr_spu2IntrGp = 0;
static int _sce_sdr_cb_thid = -1;
