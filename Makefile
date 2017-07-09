QMAKE = qmake-qt5
BUILD_DIR = build
PROJECTS = libblockdia test_bdviewblock


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


debug: $(PROJECTS:%=debug_%)
	# calls debug_<project> targets


release: $(PROJECTS:%=release_%)
	# calls debug_<project> targets


debug_%: builddir_%
	${QMAKE} -o ${BUILD_DIR}/$*/Makefile src/$*/$*.pro CONFIG+=debug
	make -C ${BUILD_DIR}/$*


release_%: builddir_%
	${QMAKE} -o ${BUILD_DIR}/$*/Makefile src/$*/$*.pro CONFIG+=release
	make -C ${BUILD_DIR}/$*


builddir_%:
	mkdir -p ${BUILD_DIR}/$*/

doc: FORCE
	doxygen doxyconf


FORCE:

