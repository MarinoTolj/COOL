# flagovi za kompajliranje i linkanje
# -g je za debug
# -Wall pali sva upozorenja
# -Wno-unused da ne upozorava ako se ne koristi return value
# -Wno-write-strings miče upozorenje za konverziju string konst u char*
# -I dodaje putanju do headera
CFLAGS = -g -Wall -Wno-unused -Wno-deprecated -Wno-write-strings -Wno-nonnull-compare -Wno-register -DDEBUG -I. -DLLVM_DISABLE_ABI_BREAKING_CHECKS_ENFORCING

# LLVM configuration flags
LLVM_CFLAGS := $(shell llvm-config --cxxflags)
LLVM_LDFLAGS := $(shell llvm-config --ldflags)
LLVM_LIBS := $(shell llvm-config --libs)
LLVM_SYSTEM_LIBS := $(shell llvm-config --system-libs)

# Include LLVM flags
CFLAGS += $(LLVM_CFLAGS)
LDFLAGS = $(LLVM_LDFLAGS) $(LLVM_LIBS) $(LLVM_SYSTEM_LIBS)


.PHONY: codegen
.PHONY: codegen_test
.PHONY: test

FILE = ./hello_world.cl

# Define the test rule
test:
	./lexer $(FILE) && \
	./parser $(FILE) && \
	./semant $(FILE) && \
	./codegen $(FILE)
run:
	./lexer ./llvm/hello_world.cl | ./parser ./llvm/hello_world.cl | ./semant ./llvm/hello_world.cl | ./codegen ./llvm/hello_world.cl
run_llvm:
	lli ./test_files/res/hello_world.ll

#clang++ -S -emit-llvm ./llvm/x.cpp -o ./llvm/x.ll
#clang++ -o hello_world hello_world.ll; hello_world; echo $?
#llc ./test_files/res/hello_world.ll -o ./llvm/llvm_hello_world.s
#g++ -no-pie ./llvm/llvm_hello_world.s -o ./llvm/hello_world;./llvm/hello_world

full_test:
	make codegen; ./codegen_test
codegen:
# kompajlira pomocne datoteke bez linkanja
# -c samo kompajlira, ne linka	
	g++ ${CFLAGS} -c cgen.cc
	g++ ${CFLAGS} -c cgen_supp.cc
	g++ ${CFLAGS} -c cgen-phase.cc
	g++ ${CFLAGS} -c utilities.cc
	g++ ${CFLAGS} -c stringtab.cc
	g++ ${CFLAGS} -c dumptype.cc
	g++ ${CFLAGS} -c tree.cc
	g++ ${CFLAGS} -c cool-tree.cc
	g++ ${CFLAGS} -c ast-lex.cc
	g++ ${CFLAGS} -c ast-parse.cc
	g++ ${CFLAGS} -c handle_flags.cc
# na kraju linka sve kompajlirane datoteke skupa
# -lfl je uključivanje biblioteke libfl.a od flexa
# -o je ime izlazne datoteke	
	g++ ${CFLAGS} ast-lex.o ast-parse.o cgen.o cgen-phase.o cgen_supp.o cool-tree.o dumptype.o handle_flags.o stringtab.o tree.o utilities.o -lfl ${LDFLAGS} -o codegen

codegen_test:
	g++ ${CFLAGS} codegen_test.cpp ${LDFLAGS} -o codegen_test
