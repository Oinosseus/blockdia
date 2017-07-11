TEMPLATE = subdirs

SUBDIRS = libblockdia \
          test_bdviewblock


libblockdia.subdir = src/libblockdia

test_bdviewblock.subdir = src/test_bdviewblock
test_bdviewblock.depend = libblockdia
