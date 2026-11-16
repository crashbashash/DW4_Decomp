/* libsdr.h - what Sony libsdr's two files share: the IOP interrupt callbacks sceSdSetTransIntrHandler
 * and sceSdSetSpu2IntrHandler install, with their arguments and the caller's $gp; sdr_cb.c holds
 * them for its callback thread. */
#ifndef DW4_SONY_LIBSDR_H
#define DW4_SONY_LIBSDR_H

extern void *_sce_sdr_transIntr0Hdr, *_sce_sdr_transIntr1Hdr, *_sce_sdr_spu2IntrHdr;
extern void *_sce_sdr_transIntr0Arg, *_sce_sdr_transIntr1Arg, *_sce_sdr_spu2IntrArg;
extern void *_sce_sdr_transIntr0Gp, *_sce_sdr_transIntr1Gp, *_sce_sdr_spu2IntrGp;

#endif
