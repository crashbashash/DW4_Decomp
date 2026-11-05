# Card album (`stagIS11`, SUBWND mode 10 `CARD`)

Central's `n_digilff[2]` (the card Digi-Elf) asks `STAGECTL NEXTSTAGE stagIS11`. The scene is hosted natively by the interface-scene
host ([Save Keeper](save-keeper.md), `src/savescene.c`, kind `DW4_SCENE_CARD`): original pack 808, whose `first` chunk sends
`SUBWND GENERATE CARD/I<0>`, and the native window tree in `src/cardshop.c`. No save controller and no memory card are involved.
Exercised headless by `make -C port check-hubcard` (real NPC, scripted pad), `check-hubnpcs`, `check-hubstages`,
`check-playerinit` (the transaction).

## The window tree (recovered from `42c810`, `42d450`, `42eb80`)

| Retail | Native | Role |
| --- | --- | --- |
| `ShopCtrlA0` update `42c810` (root) | `root_*` | Opens `j_shback SQ_OPENCARD` and `i_bgclear`; creates `ShopTitle03` (`i_messwn`), `StatusTitle03` (the Select/Confirm/Cancel legend, model `i_staccount`), `ShopTitle01` (`i_sttitle`, text 2000) and `StatusTitle01` (player panel, `j_shbase` variant); menu `2003` ("Select a Digimon." / "Return to Main Lobby."); then the player chooser and a per-player `A1`. |
| `ShopSelect02` case -1 (`43dc10`) | `DW4_STATUS_TALKSELECT02`, call `-1` | The chooser: each joined player's name (`TALKFONT01`) and species (`TALKFONT04`). |
| `ShopCtrlA1` update `42d450` | `a1_*` | Menu `2005` ("Open Booster Pack." / "View Album."), the pack opening (or notice `0x7D7` with `CURSOR_NG` when no pack is held) and the album viewer. |
| `ShopSelectA0` (`440670`) + `42df70`/`42e330`/`42e9e0` | `DW4_STATUS_CARDPAGE`, `album_*` | The nine-page album over `j_shcardwin` with the `j_shcardcursor` cursor: six card positions per page (owned cards as their `CARDINFO` model, others as the `j_shcard00` back), page counter `n/9` in `STWINFONT33`. |
| `ShopCtrlA2` update `42eb80` | `a2_*` | Booster Pack opening: `j_shbooster SQ_OPEN0n`, notice `0x7DD`, confirmation `2008`, the draw, the three cards and a rarity notice. |

Completion is a change in the child count, exactly as in the other shop controllers. The SUBWND `end` hook is the CARD exit (`STAGECTL ISRESETSTART`
answers zero here): the scene requests `PLAYERPOINT SETGENERATEPOS 4` and `NEXTSTAGE stagML12`.

## The Booster Pack draw

`dw4_playertransactions_booster_open` (`src/inventorydetail.c`): the disk entry with record 10 loses one pack (a count of zero stays zero, as in
retail, because the window checks first). Three draws take one engine random value each: `r = (roll % 1000) * 1000`; the first `card`
database row whose running `KAKURITSU * 1000` sum exceeds `r` wins, the last row when none does; its `CARDLIST` byte is set to 1 (ids beyond the 50
stored bytes are not stored). The highest `RARE` picks the notice (`0x7DA` rare, `0x7DB` uncommon, `0x7DC` common) and each name is
coloured by its own `RARE`. Pack and cards are published together. `check-hubcard` predicts the three cards from a copy of the engine's
random stream and the database and compares names, models and `CARDLIST`.

## Boundaries

- Window code comes from m2c drafts and the decoded tables, not matched source. Retail pixel-level comparison was not done.
- Retail run (PCSX2, a fresh level-1 save from `warp_test/fresh_save_before_enter_world_1.p2s`): the Central Card
  Keeper (`n_digilff` slot 2) says "Hey, do you collect Trading Cards?" and then offers "View Card Keeper Menu." / "Exit Card
  Keeper."; choosing the first loads `stagIS11`, whose root screen shows the "Card Keeper" header, the player panel and the
  Select/Confirm/Cancel legend over the menu "Select a Digimon." / "Return to Main Lobby."; leaving it loads `stagML12` and
  returns to the Card Keeper station. The port's flow, texts and Central arrival (position 4, the port reports
  (-240, 40, -160), ten units from the NPC) match these observations frame for frame in layout; the exact retail coordinate
  was not read.
- A far-progressed retail save (level 99, story flag 1 set) instead gets a plain conversation from this NPC
  ("Hey, do you want to start collecting Trading Cards with me?" / "If you find a Booster Pack bring it to me. I'll check
  it out for you.") and no menu, independent of owning Booster Packs: chunk 47 of the Central pack branches on story flag 1
  (`FLGisOn(1)`) and on flag 29. That branch reproduces under the port only when the flags match; the exact retail
  flag state of that save was not read.
- Only player 0 is wired (co-op out of scope): the chooser lists one player, the second-player panel retarget fails with a named error, and player
  names outside ASCII show as `?`.
- Title windows `ShopTitle03/01` are tracked content windows; the `StatusTitle01` panel's refresh uses the scene's own stat owner.
- Scene sound is not examined; the scene runs on the headless CPU path (no GPU or windowed run).
Findings [#975](../../docs/findings/findings-0751-1000.md#f975)-[#978](../../docs/findings/findings-0751-1000.md#f978).

## Arena control state

ShopCtrlA0/A1/A2 retain counters, selections and count snapshots in concrete arena instances. Player identity is `_playerNo`, Booster Pack count is A2 `_entCode`, and album page retention is A1 `_st3`. A0 owns an igIntList player list; `_account` holds the borrowed StatusTitle01 panel handle. Child selectors publish into the parent arena return code.
Host contexts still own services, resource tracking and derived presentation
values. See [arena scope and remaining references](arena-object-model.md#concrete-shop-and-status-records).

## Arena album resources

A1's `_cardInfoList` and `_cardRamNoList` own the six model-name/slot entries.
Names are owned arena strings; page replacement and closing release old entries,
and construction failure releases partial lists. Booster-draw presentation
arguments remain native view context over the already committed CARDLIST result;
the pack draw, rarity, RNG and progression rules do not depend on these lists.
