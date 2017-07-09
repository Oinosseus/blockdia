QMAKE = qmake-qt5
BUILD_DIR = build
PROJECTS = libblockdia

.PHONY: help all clean

help:
	echo "targets: all, clean, debug, doc, release"
	

all: debug release doc
	echo "done"

	
clean: FORCE
	@rm -Rf build/*
	
	
debug:
	mkdir -p ${BUILD_DIR}/${PROJECTS}/
	${QMAKE} -o ${BUILD_DIR}/${PROJECTS}/Makefile src/${PROJECTS}/${PROJECTS}.pro CONFIG+=debug
	make -C ${BUILD_DIR}/${PROJECTS}
	
	
doc: FORCE
	doxygen doxyconf


release:
	mkdir -p ${BUILD_DIR}/${PROJECTS}/
	${QMAKE} -o ${BUILD_DIR}/${PROJECTS}/Makefile src/${PROJECTS}/${PROJECTS}.pro
	make -C ${BUILD_DIR}/${PROJECTS}

FORCE:
	
