#!/usr/bin/env python3
"""Generates build.ninja and objdiff.json for one game version (the dtk-template workflow).

    python3 configure.py                       # USA, SLUS-20836 (default)
    ninja            # link: relink the merged image and compare it with config/<GAMEID>/build.sha1
    ninja check      # verify every unit byte-for-byte against retail (tools/check.py)
    ninja objdiff    # build the objdiff base/target objects (objdiff.json drives the GUI)
    ninja report     # build/<GAMEID>/report.json for decomp.dev (objdiff-cli report generate)
    python3 configure.py progress              # print the progress numbers (tools/progress.py)

Each version keeps its tables in config/<GAMEID>/ (config.yml, symbols.txt, the units.tsv
splits, build.sha1) and its private retail executable in orig/<GAMEID>/. The generator is
tools/project.py; docs/build-system.md describes the layout. `make check` / `make link`
remain as the same commands for the hooks and CI.
"""
import argparse
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent / "tools"))
import project  # noqa: E402

parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
parser.add_argument("mode", choices=["configure", "progress"], default="configure", nargs="?",
                    help="script mode (default: configure)")
parser.add_argument("-v", "--version", choices=project.VERSIONS, type=str.upper,
                    default=project.DEFAULT_VERSION, help="version to build")
parser.add_argument("--verbose", action="store_true", help="use this Python in the generated commands")
args = parser.parse_args()

if args.mode == "progress":
    sys.exit(subprocess.call([sys.executable, "tools/progress.py"]))
project.generate(args.version, verbose=args.verbose)
