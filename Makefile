QMAKE = qmake-qt5
BUILD_DIR = build
PROJECTS = libblockdia test_bdviewblock


# these are the targets that can be triggered manually
# they will build in every case (not be skipped because up to date)
.PHONY: help all clean doc release debug


help:
	@echo "Targets:"
	@echo "all     - builds debug,release,doc (in that order)"
	@echo "doc     - build documentation"
	@echo "clean   - empties the build/ directory (does not touch the bin/ directory)"
	@echo "release - builds release version"
	@echo "debug   - builds debug version"


all: debug release doc
	echo "done"


clean:
	@rm -Rf build/*


doc:
	doxygen doxyconf


debug: $(PROJECTS:%=debug_%)
	# calls debug_<project> targets


release: $(PROJECTS:%=release_%)
	# calls release_<project> targets


debug_%: builddir_%
	# internal target
	# this target creates the Makefile with debug config
	${QMAKE} -o ${BUILD_DIR}/$*/Makefile src/$*/$*.pro CONFIG+=debug
	make -C ${BUILD_DIR}/$*


release_%: builddir_%
	# internal target
	# this target creates the Makefile with release config
	${QMAKE} -o ${BUILD_DIR}/$*/Makefile src/$*/$*.pro CONFIG+=release
	make -C ${BUILD_DIR}/$*


builddir_%:
	# internal target
	# this targets created the build directory
	mkdir -p ${BUILD_DIR}/$*/
