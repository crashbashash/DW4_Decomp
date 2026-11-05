#!/usr/bin/env python3
"""Score ordered-diagnostic images against reference screenshots (PCSX2 replay or F8 sidecar).

Both images are resampled to 640x448 and blurred (Gaussian 1.5 px) so that resampling noise does
not dominate.  Reports mean absolute RGB error and the share of pixels differing by more than 48
grey levels, plus an all-black baseline for the same reference.

Usage: python3 gs_ordered_score.py <reference.png> <candidate.png> [<candidate.png> ...]
"""
import sys
from PIL import Image, ImageChops, ImageFilter, ImageStat


def load(path):
    return Image.open(path).convert('RGB').resize((640, 448), Image.LANCZOS).filter(ImageFilter.GaussianBlur(1.5))


def score(a, b):
    d = ImageChops.difference(a, b)
    mae = sum(ImageStat.Stat(d).mean) / 3
    big = sum(1 for p in d.convert('L').tobytes() if p > 48) / (640 * 448)
    return mae, big * 100


def main():
    ref = load(sys.argv[1])
    for name, img in [('all-black', Image.new('RGB', (640, 448)))] + [(p, load(p)) for p in sys.argv[2:]]:
        mae, big = score(ref, img)
        print('%-60s MAE %6.2f  px>48 %5.2f%%' % (name, mae, big))


if __name__ == '__main__':
    main()
