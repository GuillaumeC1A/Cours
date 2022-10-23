.PHONY: 1.1 1.2 1.3 1.4 1.5 1.6 1.7

GCC=g++ -std=c++11 -Wall -Wextra -Wno-sign-compare  -O2

1.1: 1.1.o 1.1.test.cc
	$(GCC) 1.1.o 1.1.test.cc -o 1.1
	@echo "1.1.test.cc compiled successfully!"
	@echo "SUCCESS"

1.1.o: 1.1.h 1.1.cc
	$(GCC) -c 1.1.cc -o 1.1.o
	@echo "1.1.cc compiled successfully!"

1.2: 1.2.o 1.2.test.cc
	$(GCC) 1.2.o 1.2.test.cc -o 1.2
	@echo "1.2.test.cc compiled successfully! Running the program..."
	@./1.2 && echo "SUCCESS" || echo "FAILED"

1.2.o: 1.2.h 1.2.cc
	$(GCC) -c 1.2.cc -o 1.2.o
	@echo "1.2.cc compiled successfully!"

1.3: 1.3.o 1.3.test.cc
	$(GCC) 1.3.o 1.3.test.cc -o 1.3
	@echo "1.3.test.cc compiled successfully! Running the program..."
	@./1.3 && echo "SUCCESS" || echo "FAILED"

1.3.o: 1.3.h 1.3.cc
	$(GCC) -c 1.3.cc -o 1.3.o
	@echo "1.3.cc compiled successfully!"

1.4: 1.4.o 1.4.test.cc
	$(GCC) 1.4.o 1.4.test.cc -o 1.4
	@echo "1.4.test.cc compiled successfully! Running the program..."
	@./1.4 && echo "SUCCESS" || echo "FAILED"

1.4.o: 1.4.h 1.4.cc
	$(GCC) -c 1.4.cc -o 1.4.o
	@echo "1.4.cc compiled successfully!"

1.5: 1.5.o 1.5.test.cc
	$(GCC) 1.5.o 1.5.test.cc -o 1.5
	@echo "1.5.test.cc compiled successfully! Running the program..."
	@./1.5 && echo "SUCCESS" || echo "FAILED"

1.5.o: 1.5.h 1.5.cc
	$(GCC) -c 1.5.cc -o 1.5.o
	@echo "1.5.cc compiled successfully!"

1.6: 1.6.o 1.6.test.cc
	$(GCC) 1.6.o 1.6.test.cc -o 1.6
	@echo "1.6.test.cc compiled successfully! Running the program..."
	@./1.6 && echo "SUCCESS" || echo "FAILED"

1.6.o: 1.6.h 1.6.cc
	$(GCC) -c 1.6.cc -o 1.6.o
	@echo "1.6.cc compiled successfully!"

1.7: 1.7.o 1.7.test.cc
	$(GCC) 1.7.o 1.7.test.cc -o 1.7
	@echo "1.7.test.cc compiled successfully! Running the program..."
	@./1.7 && echo "SUCCESS" || echo "FAILED"

1.7.o: 1.7.h 1.7.cc
	$(GCC) -c 1.7.cc -o 1.7.o
	@echo "1.7.cc compiled successfully!"

