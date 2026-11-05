"""Build isolated native rule libraries with their arena/layout dependencies."""
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parents[1]


def build_shared(command, **kwargs):
    command = list(command)
    command[1:1] = ['-I' + str(ROOT.parent / 'include'), '-D_GNU_SOURCE=1', '-pthread']
    for name in ['arena.c', 'object.c', 'reflection_data.c']:
        source = str(ROOT / 'src' / name)
        if source not in command:
            command.append(source)
    command += ['-lm', '-pthread']
    return subprocess.run(command, **kwargs)
