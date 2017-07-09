QMAKE = qmake-qt5
BUILD_DIR = build
PROJECTS = libblockdia

.PHONY: help all clean

help:
	@echo "Targets:"
	@echo "all     - builds debug,release,doc (in that order)"
	@echo "doc     - build documentation"
	@echo "clean   - empties the build/ directory (does not touch the bin/ directory)"
	@echo "release - builds release version"
	@echo "debug   - builds debug version"


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

