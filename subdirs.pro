TEMPLATE = subdirs

SUBDIRS = libblockdia \
          test_bdviewblock \
          blockeditor

libblockdia.subdir = src/libblockdia

test_bdviewblock.subdir = src/test_bdviewblock
test_bdviewblock.depend = libblockdia

blockeditor.subdir = src/blockeditor
blockeditor.depend = libblockdia
