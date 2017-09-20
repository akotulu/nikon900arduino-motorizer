#!/usr/bin/python
# -*- coding: utf-8 -*-

"""
Folder merge tool for Blender Video Sequence Editor image importer.

Nikon P900 generates folders for stored images and resets sequence number after 9999 or 200 if intervalled, Blender sorts without folder index.
This tool will merge all ___NIKON folders and rename images starting from 0.ext to N.ext

Caution: if no arguments are specified, current script file directiory is merged
"""

import argparse
import os, shutil
import glob

from pathlib import Path

parser = argparse.ArgumentParser()
parser.add_argument('--src', nargs='?', type=str, default='./', help='merge source dir, default is "./"')
parser.add_argument('--dest', nargs='?', type=str, default='./merged', help='merge destination dir, if not specified --src/merged is used')
parser.add_argument('--ignore', nargs='+', type=str, action='append', help='folders to ignore', required=False)
parser.add_argument('--index', nargs='?', type=int, default=0, help='starting index for files, default is 0')
args = parser.parse_args()

if args.src != './' and args.dest == './merged':
  args.dest = args.src + '/merged'

if not os.path.exists(args.dest):
  print('makedirs: ' + args.dest)
  os.makedirs(args.dest)

src = Path(args.src)
dest = Path(args.dest)

folders = sorted([f for f in src.iterdir() if f.is_dir()])
folders.remove(dest)
if isinstance(args.ignore, list):
  folders = [f for f in folders if f.name not in args.ignore]

counter = args.index
for folder in folders:
  print('merging: ' + folder.name)
  for file in folder.iterdir():
    if not file.is_file(): continue
    new_file = dest / (str(counter) + file.suffix)

    print('  moving: ' + file.name + ' renaming to: ' + new_file.name)
    shutil.move(file, new_file)
    counter += 1

  shutil.rmtree(folder)