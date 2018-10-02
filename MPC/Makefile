all:  Stage

floathead := application/float/float.hpp application/float/circuits/float_add_circuit__3ac.cpp application/float/circuits/float_sub_circuit__3ac.cpp application/float/circuits/float_mul_circuit__3ac.cpp application/float/circuits/float_lt_circuit__3ac.cpp application/float/circuits/pool_test_circuit.hpp

STD :=c++11
CPPFLAGS :=-O3 -std=$(STD)  -msse4.2 -I src/Common -I src/Pool -I src/WRK -I src/Stage/ 
CXXFLAGS := -lstdc++ -maes -march=corei7-avx -lpthread -lm -lcrypto
File=Common/Network_IO Common/MOTE Common/OTE Common/util Common/Wiremap Pool/Pool WRK/Tuples WRK/Bits
StageFile=Stage/Stage
CppFiles=$(addprefix src/, $(File:=.cpp))
HppFiles=$(addprefix src/, $(File:=.hpp))
StageCpp=$(addprefix src/, $(StageFile:=.cpp))
StageHpp=$(addprefix src/, $(StageFile:=.hpp))

AES: bin/AES.out

bin/AES.out: obj/Backend application/AES/AES__3ac.cpp 
		gcc obj/*.o application/AES/AES__3ac.cpp -D B3 -D PartyNumber=$(NoP) $(CPPFLAGS) $(CXXFLAGS) -o bin/AES.out

ED: bin/ED.out

bin/ED.out: obj/Backend application/ED/ED_3ac.cpp  application/ApplicationExecution.cpp
		gcc obj/*.o application/ED/ED_3ac.cpp  application/ApplicationExecution.cpp -D B3 -D PartyNumber=$(NoP) $(CPPFLAGS) $(CXXFLAGS) -o bin/ED.out

Sort: bin/Sort.out

bin/Sort.out: obj/Backend application/Sort/Sort__3ac.cpp  application/ApplicationExecution.cpp
		gcc obj/*.o application/Sort/Sort__3ac.cpp  application/ApplicationExecution.cpp -D B3 -D PartyNumber=$(NoP) $(CPPFLAGS) $(CXXFLAGS) -o bin/Sort.out

LogReg: bin/LogReg.out

bin/LogReg.out: obj/Backend obj/*.o application/logreg/logreg.cpp $(floathead) application/ApplicationExecution.cpp
		gcc obj/*.o application/logreg/logreg.cpp  application/ApplicationExecution.cpp -D B3 -D PartyNumber=$(NoP) $(CPPFLAGS) $(CXXFLAGS) -I application/float -o bin/LogReg.out

LogRegFP: bin/LogRegFP.out

bin/LogRegFP.out: obj/Backend obj/*.o application/logreg/logreg_fixpoint.cpp application/fixpoint/FixPoint.cpp application/fixpoint/FixPoint.hpp application/ApplicationExecution.cpp
		gcc obj/*.o application/logreg/logreg_fixpoint.cpp application/fixpoint/FixPoint.cpp  application/ApplicationExecution.cpp -D B3 -D PartyNumber=$(NoP) $(CPPFLAGS) $(CXXFLAGS) -I application/fixpoint -o bin/LogRegFP.out

Install: obj/Backend

obj/Backend: obj/Bits.o obj/MOTE.o obj/Network_IO.o obj/OTE.o obj/Pool.o obj/Stage.o obj/Tuples.o obj/util.o obj/Wiremap.o 
	ar cr obj/Backend obj/Bits.o obj/MOTE.o obj/Network_IO.o obj/OTE.o obj/Pool.o obj/Stage.o obj/Tuples.o obj/util.o obj/Wiremap.o 

obj/Bits.o: src/WRK/Bits.cpp src/WRK/Bits.hpp
	gcc src/WRK/Bits.cpp $(CPPFLAGS) -D PartyNumber=$(NoP)  $(CPPFLAGS) -c -o obj/Bits.o

obj/MOTE.o: src/Common/MOTE.cpp src/Common/MOTE.hpp
	gcc src/Common/MOTE.cpp $(CPPFLAGS) -D PartyNumber=$(NoP)  $(CPPFLAGS) -c -o obj/MOTE.o

obj/Network_IO.o: src/Common/Network_IO.cpp src/Common/Network_IO.hpp
	gcc src/Common/Network_IO.cpp $(CPPFLAGS) -D PartyNumber=$(NoP)  $(CPPFLAGS) -c -o obj/Network_IO.o

obj/OTE.o: src/Common/OTE.cpp src/Common/OTE.hpp
	gcc src/Common/OTE.cpp $(CPPFLAGS) -D PartyNumber=$(NoP)  $(CPPFLAGS) -maes -msse4.2 -march=corei7-avx -c -o obj/OTE.o

obj/Pool.o: src/Pool/Pool.cpp src/Pool/Pool.hpp
	gcc src/Pool/Pool.cpp $(CPPFLAGS) -D PartyNumber=$(NoP)  $(CPPFLAGS)  -maes -msse4.2 -march=corei7-avx -c -o obj/Pool.o

obj/Stage.o: src/Stage/Stage.cpp src/Stage/Stage.hpp
	gcc src/Stage/Stage.cpp $(CPPFLAGS)  -D PartyNumber=$(NoP)  $(CPPFLAGS)  -maes -msse4.2 -march=corei7-avx  -c -o obj/Stage.o

obj/Tuples.o: src/WRK/Tuples.cpp src/WRK/Tuples.hpp
	gcc src/WRK/Tuples.cpp $(CPPFLAGS) -D PartyNumber=$(NoP)  $(CPPFLAGS)  -maes -msse4.2 -march=corei7-avx -c -o obj/Tuples.o

obj/util.o: src/Common/util.cpp src/Common/util.hpp
	gcc src/Common/util.cpp $(CPPFLAGS) -D PartyNumber=$(NoP)  $(CPPFLAGS) -c -o obj/util.o


obj/Wiremap.o: src/Common/Wiremap.cpp src/Common/Wiremap.hpp
	gcc src/Common/Wiremap.cpp $(CPPFLAGS) -D PartyNumber=$(NoP)  $(CPPFLAGS)  -c -o obj/Wiremap.o

Float: $(floathead) obj/Float.o obj/Add.o obj/Sub.o obj/Mul.o obj/Lt.o

obj/Float.o: application/float/float.cpp application/float/float.hpp
	 gcc application/float/float.cpp $(CPPFLAGS) -c -D PartyNumber=$(NoP)  $(CPPFLAGS) -o obj/Float.o

obj/Add.o: application/float/circuits/float_add_circuit__3ac.cpp application/float/circuits/float_add_circuit__3ac.hpp
	 gcc application/float/circuits/float_add_circuit__3ac.cpp $(CPPFLAGS) -c -D PartyNumber=$(NoP)  $(CPPFLAGS) -o obj/Add.o

obj/Mul.o: application/float/circuits/float_mul_circuit__3ac.cpp application/float/circuits/float_mul_circuit__3ac.hpp
	 gcc application/float/circuits/float_mul_circuit__3ac.cpp $(CPPFLAGS) -c -D PartyNumber=$(NoP)  $(CPPFLAGS) -o obj/Mul.o

obj/Sub.o: application/float/circuits/float_sub_circuit__3ac.cpp application/float/circuits/float_sub_circuit__3ac.hpp
	 gcc application/float/circuits/float_sub_circuit__3ac.cpp $(CPPFLAGS) -c -D PartyNumber=$(NoP)  $(CPPFLAGS) -o obj/Sub.o

obj/Lt.o: application/float/circuits/float_lt_circuit__3ac.cpp application/float/circuits/float_lt_circuit__3ac.hpp
	 gcc application/float/circuits/float_lt_circuit__3ac.cpp $(CPPFLAGS) -c -D PartyNumber=$(NoP)  $(CPPFLAGS) -o obj/Lt.o

Clean: 
	rm -f *.out 
	rm -rf bin/
	rm -rf obj/
	mkdir obj
	mkdir bin
clean:
	rm -rf *.out
	rm -rf bin/
	mkdir bin