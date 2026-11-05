"""Permuter targets stay private; explicit project roots are honored."""
import os
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch
import permuter_one as p
class Paths(unittest.TestCase):
    def test_default_is_under_build(self):
        expected=Path(p.ROOT)/'build/permuter'
        self.assertEqual(Path(p.project_root()),expected)
    def test_relative_and_absolute_overrides(self):
        with tempfile.TemporaryDirectory() as td:
            self.assertEqual(p.project_root(td),os.path.abspath(td))
        self.assertEqual(p.project_root('../custom'),os.path.abspath('../custom'))
    def test_main_build_uses_override(self):
        with tempfile.TemporaryDirectory() as td:
            seen=[]
            def build(va,path,*args):seen.append(path);return 'target',None
            with patch.object(p.am,'load_symbols',return_value=[(0x100000,8,'target')]), \
                 patch.object(p.am,'disassemble',return_value={}), \
                 patch.object(p,'build',side_effect=build):
                self.assertEqual(p.main(['0x100000','--outdir',td,'--build-only']),0)
            self.assertEqual(seen,[os.path.join(td,'target')])
    def test_pilot_uses_override(self):
        with tempfile.TemporaryDirectory() as td:
            seen=[]
            def build(va,path,*args):seen.append(path);return 'target',None
            with patch.object(p,'build',side_effect=build),patch.object(p,'run',return_value=(None,None)):
                result=p.pilot([(0x100000,8,'tiny')],{}, {0x100000:'target'},
                               {0x100000:(8,'target')},parallel=1,outdir=td)
            self.assertEqual(seen,[os.path.join(td,'target')])
            self.assertEqual(len(result),1)
if __name__=='__main__':unittest.main()
