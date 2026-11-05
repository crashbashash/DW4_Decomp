extern "C" bool FUN_003a0d40(void *self, float *a, float *p) {
 bool res = false;
 float r = a[37];
 float y = p[1];
 float ax = a[26];
 float x1 = ax + (a[32] + r);
 float x2 = ax + (a[29] - r);
 float z1 = (a[28]) + (a[34] + r);
 float z2 = (a[28]) + (a[31] - r);
 if ((!((a[27]) + a[15] < y) && ((a[27]) + a[16] < y)) || (!((a[27]) + a[18] < y) && ((a[27]) + a[19] < y))) {
  if (x1 <= (p[0]) && !(x2 < (p[0]))) {
   if (z1 <= (p[2]) && !(z2 < (p[2]))) res = true;
  }
 }
 return res;
}
