extern "C" {
void FloatingNumber_Spawn(int, int);
void MDLdspDamage(int, int);
}
void MDLdspDamage(int p0, int p1)
{
    FloatingNumber_Spawn(p0, 0);
}
