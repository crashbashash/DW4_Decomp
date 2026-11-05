#!/usr/bin/env python3
"""Naming batches preserve explicit aliases and rewrite both C/C++ source halves."""
from pathlib import Path
import subprocess
import tempfile
import unittest
ROOT=Path(__file__).resolve().parents[1]

class ApplyNames(unittest.TestCase):
    def test_explicit_thunk_and_same_basename_sources(self):
        with tempfile.TemporaryDirectory(prefix='dw4-name-batch-') as td:
            base=Path(td);src=base/'src';asm=base/'asm';names=base/'names'
            src.mkdir();asm.mkdir();names.mkdir()
            (base/'symbols.txt').write_text('00100000 000008 FUN_00100000\n00100010 000008 thunk_FUN_00100000\n')
            (names/'Test.tsv').write_text('0x00100000\tBuffer_Free\tengine\n0x00100010\tBuffer_FreeAlias\tengine\n')
            (src/'FUN_00100000.c').write_text('int FUN_00100000(){return 0;}\n')
            (src/'thunk_FUN_00100000.c').write_text('int thunk_FUN_00100000(){return FUN_00100000();}\n')
            for ext in ('c','cpp'):
                (src/f'merged.{ext}').write_text('int caller(){return thunk_FUN_00100000()+FUN_00100000();}\n')
            subprocess.run(['python3',str(ROOT/'tools/apply_names.py'),'--src',str(src),
                            '--asm',str(asm),'--names',str(names),'--symbols',str(base/'symbols.txt'),
                            '--apply','--no-regen'],check=True,capture_output=True,text=True)
            self.assertEqual((src/'engine/Buffer_FreeAlias.c').read_text(),
                             'int Buffer_FreeAlias(){return Buffer_Free();}\n')
            for ext in ('c','cpp'):
                self.assertEqual((src/f'merged.{ext}').read_text(),
                                 'int caller(){return Buffer_FreeAlias()+Buffer_Free();}\n')
            self.assertFalse((src/'thunk_FUN_00100000.c').exists())
if __name__=='__main__':unittest.main()
