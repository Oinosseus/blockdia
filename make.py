#!/usr/bin/python3
# -*- coding: utf8 -*-

"""
    This script supports the build process.
    It can generate debug, release and documentation.
    See "--help" for more details
"""

import subprocess
import argparse
import os
import shutil



# -----------------------------------------------------------------------------
#                                   CONSTANTS
# -----------------------------------------------------------------------------

# determine a save path to the project directoy
# this allows to call make.py from anywhere
PROJECTDIR = os.path.dirname(os.path.abspath(__file__))

# qmake command
QMAKE = "qmake-qt5"

# temporary output directories
TMPOUTDIRS = []
TMPOUTDIRS.append(os.path.join(PROJECTDIR, "build"))

# output directories (where target files are stored)
TGTOUTDIRS = []
TGTOUTDIRS.append(os.path.join(PROJECTDIR, "bin"))
TGTOUTDIRS.append(os.path.join(PROJECTDIR, "doc", "html"))



# -----------------------------------------------------------------------------
#                                  Sub-Commands
# -----------------------------------------------------------------------------

def make_doc(args):

    dir_dia_src = os.path.join(PROJECTDIR, "doc")
    dir_dia_dst = os.path.join(PROJECTDIR, "build", "dia_export")

    # dia export directory
    if not os.path.isdir(dir_dia_dst):
        os.makedirs(dir_dia_dst)

    # export all dia files
    for entry in os.listdir(dir_dia_src):

        if entry[-4:].lower() == ".dia":
            subprocess.run(["dia", "--export=" + os.path.join(dir_dia_dst, entry[:-4] + ".svg"), os.path.join(dir_dia_src, entry)])

    # run doxygen
    subprocess.run(["doxygen", os.path.join(PROJECTDIR, "doxyconf")])




def make_build(args):

    # call qmake
    if args.debug:
        subprocess.run([QMAKE, "subdirs.pro", "CONFIG+=debug"])
    else:
        subprocess.run([QMAKE, "subdirs.pro"])

    # make
    subprocess.run(["make"])


def make_all(args):
    raise NotImplementedError("To Be Done :-|")


def make_clean(args):

    # get list of directories to clean
    dirlist = TMPOUTDIRS
    if args.all:
        dirlist += TGTOUTDIRS

    # list of ignored files
    ignored_files = []
    ignored_files.append(".gitignore")

    # clear all directories
    for d in dirlist:
        for root, dirs, files in os.walk(d):
            for f in files:
                if f not in ignored_files:
                    os.unlink(os.path.join(root, f))
            for d in dirs:
                shutil.rmtree(os.path.join(root, d))

    # remove qt makefiles
    if os.path.isfile(os.path.join(PROJECTDIR, "Makefile")):
        os.unlink(os.path.join(PROJECTDIR, "Makefile"))
    for root, dirs, files in os.walk(os.path.join(PROJECTDIR, "src")):
        for d in dirs:
            if os.path.isfile(os.path.join(root, d, "Makefile")):
                os.unlink(os.path.join(root, d, "Makefile"))



# -----------------------------------------------------------------------------
#                                Parse Arguments
# -----------------------------------------------------------------------------

# create main parser
parser = argparse.ArgumentParser(description='Managing the project build.')
subparsers = parser.add_subparsers()

# make doc
parser_doc = subparsers.add_parser('doc', help='make documentation')
parser_doc.set_defaults(func=make_doc)

# make build
parser_build = subparsers.add_parser('build', help='build')
parser_build.add_argument('--debug', action='store_true', help='build debug instead of release version')
#parser_build.add_argument('--run',   action='store_true', help='run the application after build')
parser_build.set_defaults(func=make_build)

# make all
parser_all = subparsers.add_parser('all', help='build all versions and documentation')
parser_all.set_defaults(func=make_all)

# make clean
parser_clean = subparsers.add_parser('clean', help='remove temporary build files')
parser_clean.add_argument('--all', default=False, action='store_true', help='also removes build target files')
parser_clean.set_defaults(func=make_clean)

# parse arguments and call command
args = parser.parse_args()
args.func(args)
