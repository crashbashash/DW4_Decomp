typedef struct MwsfdInputCbTbl MwsfdInputCbTbl;

extern MwsfdInputCbTbl *mwsfd_input_cb_tbl;

void mwsfd_SetInputCbTbl(MwsfdInputCbTbl *tbl) {
    mwsfd_input_cb_tbl = tbl;
}
