"""Regression for LQ/SQ lane preservation, independently encoded instructions."""
import sys
from pathlib import Path
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'scripts'))
from ee_core import EE
class Memory(EE):
    def __init__(self): self.mem={};self.ee_reset()
    def read(self,p,n):return sum(self.mem.get(p+i,0)<<(i*8) for i in range(n))
    def write(self,p,n,v):
        for i in range(n):self.mem[p+i]=(v>>(i*8))&255
class Quadword(unittest.TestCase):
    def test_quadword_and_scalar_loads(self):
        cpu=Memory();cpu.r[4]=0x2000;cpu.r[5]=0x3000
        payload=0xfedcba98765432100123456789abcdef
        cpu.write(0x2000,16,payload)
        cpu.write(0x1000,4,0x78860000) # lq a2,0(a0)
        cpu.write(0x1004,4,0x7ca60000) # sq a2,0(a1)
        cpu.step(0x1000);cpu.step(0x1004)
        self.assertEqual(cpu.r[6],payload)
        self.assertEqual(cpu.read(0x3000,16),payload)
        cpu.write(0x1008,4,0xdc860000) # ld a2,0(a0)
        cpu.step(0x1008)
        self.assertEqual(cpu.r[6],payload&((1<<64)-1))
if __name__=='__main__':unittest.main()
