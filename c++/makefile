Astar:main.o chrome.o
	g++ -o Astar main.o chrome.o
main.o:main.cpp chrome.h
	g++ -c main.cpp
chrome.o:chrome.cpp chrome.h
	gcc -c chrome.cpp
clean:
	rm *.o