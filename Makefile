all:	main

main:	main.o
	g++ main.o -o submission

main.o:	main.cpp
	g++ -g -c main.cpp

clean:
	rm -f *.o submission output.txt

