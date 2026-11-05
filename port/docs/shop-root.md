# Generic shop root (hub SUBWND modes 1..9)

Arena state ([#2728](../../docs/findings/findings-2501-2750.md#f2728)/#2729): this root owns a recovered
`beNDMWShopCtrl00` in the session arena. Its lifecycle uses `_isRun` and
`_st0..3`, entry/player use `_entCode`/`_playerNo`, and the service child-count
snapshot uses `_nowProcKazu`. `_subWindow` points to a typed
`beNDMWWindowList` of four-byte child handles; `_mother` holds a parent handle.
The native facade retains callbacks/resource owners, with no scalar/count mirror.
Failure before publication leaves child ownership unchanged, and teardown
releases the entire owned tree. Concrete service transaction/page/selection
adapters remain the next shop migration module; the root's arena ownership does not
mean those classes have been fully retargeted.

`src/shoproot.c` is the native `beNDMWShopCtrl00` update (`4267b0..426f94`, evidence in
[window tree and shop root](../../docs/engine/window-tree-and-shop-root.md)). It is the root window of the XDATA, BANK,
CNOS, DISK, WPU/APU/CHIP and JUNK services; the entry code is the SUBWND mode. LABO (mode 2) and CARD (mode 10) have their own
roots in retail ("the raw fallback does not establish that those services should use the generic shop root"). CARD keeps its
own native root (`cardshop.c`). The Digi-Lab is hosted here with entry code 2, which builds the widget set of its own root
(see below).

## Behaviour (all recovered from the retail instructions)

- **State 0**: the five common widgets, in this order: ShopTitle00, StatusTitle01, StatusTitle02, StatusTitle03, ShopTitle01.
  Their updates run in the same tick.
- **ShopTitle00** (`440fd0`): `MODELCTRL j_shback SQ_OPEN` (closed with `SQ_CLOSE`) and `i_bgclear SQ_OPEN`. `j_shback`
  is the green grid backdrop; it replaces the frozen hub frame.
- **StatusTitle01/02/03**: the existing native STATUS views: the player panel (name, species, HP/MP, the stats, X Data,
  refreshed from the same stat owner as the STATUS menu, so a chip quote's stat preview shows in it), the `i_messwn`
  message window (`SQ_STOPEN`) and the Select/Confirm/Cancel legend at the top right (`i_staccount`, `STWINFONT34`
  font000..002 filled by `txt_status.lua` call 0 with messages 10..12; the BITS and Next Level rows belong to the player
  panel, `STWINFONT06` font060/061 on `i_stbase`).
- **ShopTitle01** (`441040`): the `i_sttitle` header, tracks
  `STWINFONT12/font000` and runs `txt_shop.lua` call `1000 + 100 * entry code` for codes 1..10 (jump table `51cba0`):
  XDATA 1100 ("Data Keeper"), LABO 1200 ("Digi-Lab"), BANK 1300, CNOS 1400, DISK 1500, WPU/APU/CHIP 1600/1700/1800,
  JUNK 1900.
- **State 1**: waits while `i_messwn`'s `SQ_STOPEN` is the current sequence (the returned byte is exactly 1), then creates
  the service selected by the entry code and records the child count; **a change of the count** (the service finished and
  was removed) advances to state 2. Completion is never a result value.
- **State 2**: sends `MODELCTRL i_bgclear OFFREEZE`, then asks every child to close. Without that send `i_bgclear` never
  finishes closing under the STATUS scene freeze. **State 3** waits for the
  children to be gone and clears the active flag.

**Entry code 2 (the Digi-Lab)** follows its own root, `beNDMWShopCtrlDigilabo` (`431760` state 0): ShopTitle00,
StatusTitle03 (the legend) and ShopTitle01 (bound to the entry code, header call 1200), with no StatusTitle01/02 and no
`i_messwn` gate in state 1. The lab controller then presents `i_messwn SQ_OPEN` itself (`433290`) and creates
StatusTitle01 with context 1, the compact name/level/portrait base `j_shbase` (`433120`). State 2's `i_bgclear OFFREEZE`
matches Digilabo's own close (`431760` state 2). See [Digi-Lab](labo-shop.md).

The hub wires it in `status_prepare` (`src/hubruntime.c`); the service windows (`xdatashop.c`, `bankshop.c`, `cnosshop.c`,
`diskshop.c`, `equipshop.c`, `laboshop.c`) become its last child through the `shop_service` callback.

## Verification

`tools/hubtest.h` asserts on every drawn service frame that the header, the panel's name (and species, except in the
Digi-Lab's compact base) and the legend text are visible, and compares the frame with the GPU backend (`check-hubtalk`,
`-hubbank`, `-hubcnos`, `-hubdisk`, `-hubshops`, `-hublabo`). The
retail comparison is by eye against PCSX2 captures of the XDATA menu, stat list, chip list, quote and confirmation: the green
backdrop, left panel, "Data Keeper" header, legend, list/description windows and bottom prompt line agree in layout and text.
The Digi-Lab frames are compared in [Digi-Lab](labo-shop.md#retail-comparison).

## Boundaries

- Not pixel-compared with retail. The list cursor (`i_stcursor01`) pulses between a large green diamond and a small dot,
  so a single capture of either side shows whichever phase it caught; this is not a shape difference.
- The service windows still create their own content windows; the retail trees nest them under the service controller, which
  is not observable.
- GPU frames for these screens are compared with looser tolerances than the lobby world frames (MAE 3/255, 4%) because
  they are full-screen UI with many one-pixel window edges.
- CARD draws its own chrome from its own root (`cardshop.c`). LABO is hosted by this root rather than a separate
  `3b7750` root window; the observable widget set and order follow Digilabo's state 0.
