#!/usr/bin/env python3
"""GPU draws and composition measurements for fresh STATUS roots and submenus."""
import argparse
import os
import subprocess
import tempfile
from pathlib import Path

p = argparse.ArgumentParser()
p.add_argument('--roms', default='../../local/extracted')
p.add_argument('--tool', default='build/test_statusviews')
p.add_argument('--size', default='640x448')
a = p.parse_args()
with tempfile.TemporaryDirectory(prefix='dw4-status-gpu-') as tmp:
    env = dict(os.environ, DW4_STATUS_GPU_CHECK=a.size,
               DW4_STATUS_CAPTURE_MENUS='1')
    subprocess.run([a.tool, a.roms, str(Path(tmp) / 'root.png'), tmp,
                    '--root-only'], env=env, check=True)
