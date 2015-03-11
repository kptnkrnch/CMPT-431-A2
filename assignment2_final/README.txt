Compiling:
	In order to compile to the decentralized queue version, you must use the flag Q_STEAL
	for example:

	g++ -ggdb3 -m64 -std=c++0x -pthread -lrt -Wall -O3 -D Q_STEAL ppp.C random.C TaskGroup.C driver-sort.C -o driver-sort
	g++ -ggdb3 -m64 -std=c++0x -pthread -lrt -Wall -O3 -D Q_STEAL ppp.C random.C TaskGroup.C driver-compute.C -o driver-compute
	g++ -ggdb3 -m64 -std=c++0x -pthread -lrt -Wall -O3 -D Q_STEAL ppp.C random.C TaskGroup.C driver-reduce.C -o driver-reduce

Who did what:
	the Who-Did-What.txt file contains information pertaining to which group member did what for the assignment.
	
Report:
	the master-report_final.pdf file contains an aggregate report by both group members.