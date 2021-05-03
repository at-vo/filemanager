all:mymv mycp mycat myls mystat myrm mydiff
mymv: mymv.o filemanager.o
	g++ mymv.o filemanager.o -o mymv
mycp: mycp.o filemanager.o
	g++ mycp.o filemanager.o -o mycp
myls: myls.o filemanager.o
	g++ myls.o filemanager.o -o myls
mycat: mycat.o filemanager.o
	g++ mycat.o filemanager.o -o mycat
myrm: myrm.o filemanager.o
	g++ myrm.o filemanager.o -o myrm
mydiff: mydiff.o filemanager.o
	g++ mydiff.o filemanager.o -o mydiff
mystat: mystat.o filemanager.o
	g++ mystat.o filemanager.o -o mystat
mymv.o: mymv.cpp
	g++ -c mymv.cpp -o mymv.o
mycp.o: filemanager.cpp mycp.cpp 
	g++ -c mycp.cpp -o mycp.o
myls.o: filemanager.cpp myls.cpp
	g++ -c myls.cpp -o myls.o
mycat.o: filemanager.cpp mycat.cpp
	g++ -c mycat.cpp -o mycat.o
myrm.o: filemanager.cpp 	myrm.cpp
	g++ -c	myrm.cpp -o myrm.o
mydiff.o: filemanager.cpp mydiff.cpp
	g++ -c	mydiff.cpp 	-o mydiff.o
mystat.o: filemanager.cpp mystat.cpp
	g++ -c mystat.cpp -o mystat.o
filemanager.o: filemanager.cpp filemanager.h
	g++ -c filemanager.cpp
clean:
	rm *.o mymv mycp mycat myls mystat myrm mydiff
	