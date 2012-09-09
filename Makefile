EXE=inch
GCC=g++
FLAGS=-Wall --pedantic -ggdb -O2 -DLOCAL_PATH=\"${PWD}\"

date=`date +%Y%m%d`

CreateDir=@mkdir -p ${@D}

ObjectDir=obj/
SourceDir=src/
BinDir=bin/

Includes=${shell find ${SourceDir} -name '*.h'}
Sources=${shell find ${SourceDir} -name '*.cpp'}
Objects=${patsubst ${SourceDir}%.cpp,${ObjectDir}%.o,${Sources}}

Version=${shell grep version ${SourceDir}inputs.cpp | sed 's/version="\(.*\)";/\1/'}

all: ${BinDir}${EXE}

${BinDir}${EXE}: ${Objects}
	${CreateDir}
	@${GCC} ${FLAGS} $^ -o $@
	@echo Version =${Version}
	@echo Linking and building ./$@

${ObjectDir}%.o: ${SourceDir}%.cpp ${Includes}
	${CreateDir}
	@${GCC} ${FLAGS} -c $< -o $@
	@echo Compiling $@

.PHONY: clean veryclean dist

clean:
	rm -vf ${ObjectDir}*.o ${BinDir}${EXE}

veryclean: clean
	rm -vf *.*~ callgrind.out.*

#Create a tarball, in the directory above, to distribute
dist: clean
	mv -v ../${EXE}_*.tgz ../Old_versions_and_tests
	tar -cvzf ../${EXE}_${date}.tgz --exclude=".git*" --exclude='*~' --exclude='*.eps' --exclude='*.svg' ../${EXE}

#valgrind --tool=callgrind --dump-instr=yes --simulate-cache=yes --collect-jumps=yes
#valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes
