NPROC = $(shell nproc || shell sysctl -n hw.ncpu || echo 1)
SCONS = scons -C code -j$(NPROC)
SHELL = bash

all: sneezy

# quick build
sneezy:
	$(SCONS)

# debugging build with runtime checks
debug:
	$(SCONS) debug=1

# production-optimized build
prod:
	$(SCONS) shared=0 harden=1 optimize=1 lto=1

check:
	# can't use cppcheck -j with unusedfunction
	mkdir -p cppcheck
	cppcheck \
	    -Icode/code -rp=code/code --xml \
	    --enable=warning --enable=unusedFunction \
	    code/code/main.cc code/code/*/*.cc \
	    2> >( cppcheck-htmlreport \
		--source-dir=code/code --report-dir=cppcheck \
		--file=/dev/stdin )
	# no errors detected??
	#scan-build -v -o clang-analyzer $(SCONS)

test:
	# TODO: have a test suite...

clean:
	$(SCONS) -c
	rm -rf cppcheck clang-analyzer
	cd code && rm -rf config.log .sconf_temp .sconsign.dblite
	find -name '*.pyc' -o -name '__pycache__' -print0 -exec rm -r \{\} \;
	cd lib && rm -rf roomdata corpses immortals rent account player txt/stats

