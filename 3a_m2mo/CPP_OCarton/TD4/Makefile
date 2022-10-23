CC=g++
CPPFLAGS= -g -Wall

main : main.o io.o class.o student.o 
	$(CC) $(CPPFLAGS) -o main main.o io.o class.o student.o

io : io.o class.o student.o
	$(CC) $(CPPFLAGS) -o io io.o class.o student.o

class : class.o student.o
	$(CC) $(CPPFLAGS) -o class class.o student.o

student : student.o
	$(CC) $(CPPFLAGS) -o student student.o
