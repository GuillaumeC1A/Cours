.PHONY: 2.1 2.2 2.3

2.1: 2.1.o 2.1.main.cc
	g++ 2.1.o 2.1.main.cc -o 2.1
	@echo "2.1.main.cc compiled successfully! Running the program..."
	@./2.1 && echo "SUCCESS" || echo "FAILED"

2.1.o: 2.1.h 2.1.cc
	g++ -c 2.1.cc -o 2.1.o
	@echo "2.1.cc compiled successfully!"

2.2: 2.2.o 2.2.main.cc
	g++ 2.2.o 2.2.main.cc -o 2.2
	@echo "2.2.main.cc compiled successfully! Running the program..."
	@./2.2 && echo "SUCCESS" || echo "FAILED"
	@echo -n "Counting the number of 'const' in your .h: "
	@bash 2.2.count.sh

2.2.o: 2.2.h 2.2.cc
	g++ -c 2.2.cc -o 2.2.o
	@echo "2.2.cc compiled successfully!"

2.3: 2.2.o 2.3.o 2.3.main.cc
	@bash 2.3.compare.sh
	g++ 2.2.o 2.3.o 2.3.main.cc -o 2.3
	@echo "2.3.main.cc compiled! SUCCESS!"
	@echo -n "Counting the number of 'const' in your .h: "
	@bash 2.3.count.sh

2.3.o: 2.3.h 2.3.cc
	g++ -c 2.3.cc -o 2.3.o
	@echo "2.3.cc compiled successfully!"
