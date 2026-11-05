extern int DAT_0058ca00[4];
extern int DAT_0058ca08[4];
extern int DAT_0058ca10[4];
extern int DAT_0058ca18[4];
extern int DAT_0058ca28[4];
extern int DAT_0058ca30[4];
extern int DAT_0058ca38[4];
extern int DAT_0058ca40[4];
extern int DAT_0058ca48[4];
extern int DAT_0058ca50[4];
extern int DAT_0058ca58[4];
extern int DAT_0058ca60[4];
extern int DAT_0058ca68[4];
extern int DAT_0058ca70[4];
extern int DAT_0058ca78[4];
extern int DAT_0058ca80[4];
extern int DAT_0058ca88[4];
extern int DAT_0058ca90[4];
extern int DAT_0058ca98[4];
extern int DAT_0058caa0[4];
extern int DAT_0058caa8[4];
extern int DAT_0058cab0[4];
extern int DAT_0058cab8[4];
extern int DAT_0058cac0[4];
extern int DAT_0058cac8[4];
extern int DAT_0058cad0[4];
extern int DAT_0058cad8[4];
extern int DAT_0058cae8[4];
extern int DAT_0058cb00[4];
extern int DAT_0058cb08[4];
extern int DAT_0058cb18[4];
int FUN_004601e0();
int FUN_00460260();
int FUN_004602c0();
int FUN_004608a0();
int FUN_00460ac0();
int FUN_004612a0();
int FUN_004629c0();
int FUN_00462a10();
int FUN_00462a20();
int FUN_00462a30();
int FUN_00462a40();
int FUN_00462fa0();
int FUN_00462fb0();
int FUN_00463400();
struct M { int f0; int p4; int f8; int f12; };
struct O { char p0[12]; int f12; int f16; };
void FUN_00460f90(struct O *arg0, struct M *arg1)
{
  int a0 = arg0->f12;
  int v1;
  if (a0 == 0) return;
  v1 = arg1->f8;
  if (v1 == DAT_0058ca30[0]) return;
  if (v1 == DAT_0058ca00[0] || v1 == DAT_0058ca08[0] || v1 == DAT_0058ca10[0] || v1 == DAT_0058ca18[0]) { FUN_004601e0(arg0->f16); return; }
  if (v1 == DAT_0058ca28[0]) { FUN_00460260(arg0->f16); return; }
  if (v1 == DAT_0058ca38[0] || v1 == DAT_0058ca40[0] || v1 == DAT_0058ca48[0] || v1 == DAT_0058ca50[0]) { FUN_004602c0(arg0->f16); return; }
  if (v1 == DAT_0058ca58[0] || v1 == DAT_0058ca60[0] || v1 == DAT_0058ca68[0]) { FUN_004608a0(arg0->f16); return; }
  if (v1 == DAT_0058ca70[0] || v1 == DAT_0058ca78[0] || v1 == DAT_0058ca80[0] || v1 == DAT_0058ca88[0] || v1 == DAT_0058ca90[0] || v1 == DAT_0058ca98[0] || v1 == DAT_0058caa0[0] || v1 == DAT_0058caa8[0]) { FUN_00460ac0(arg0->f16); return; }
  if (v1 == DAT_0058cab0[0]) { FUN_00462fa0(a0, arg1->f12); return; }
  if (v1 == DAT_0058cab8[0]) { FUN_004629c0(a0); return; }
  if (v1 == DAT_0058cac0[0]) { FUN_00462a20(a0); return; }
  if (v1 == DAT_0058cac8[0]) { FUN_00462a10(a0); return; }
  if (v1 == DAT_0058cad0[0]) { FUN_00462a30(a0); return; }
  if (v1 == DAT_0058cad8[0]) { FUN_00462fb0(a0); return; }
  if (v1 == DAT_0058cb18[0] || v1 == DAT_0058cb08[0]) { FUN_004612a0(a0); return; }
  if (v1 == DAT_0058cae8[0]) { FUN_00463400(a0); return; }
  if (arg1->f0 == 0) { FUN_00462fb0(a0); FUN_004612a0(arg0->f12); FUN_00463400(arg0->f12); return; }
  if (v1 == DAT_0058cb00[0]) { FUN_00462a40(a0); }
}
