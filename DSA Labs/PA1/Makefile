default: test

libpa1.so: pa1.c pa1.h
	gcc -g -Werror -shared -O3 -fPIC -o libpa1.so pa1.c
	@if nm -D libpa1.so |grep -q -e "U free" -e "U malloc" -e "U calloc" -e "U aligned"; then \
    echo "ERROR: Are you using malloc/calloc/free directly"; \
    echo "you are not supposed to do that"; \
    echo "deleting libpa1.so"; \
    rm -f libpa1.so; \
    fi

libdsa.so: ../lib/lib.c
	make -C ../lib
	cp ../lib/libdsa.so .

test: test1.c test2.c test3.c libpa1.so libdsa.so
	gcc -g -Werror -O3 -L. -Wl,-rpath=. -o test1 test1.c -ldsa -lpa1 -lm
	gcc -g -Werror -O3 -L. -Wl,-rpath=. -o test2 test2.c -ldsa -lpa1 -lm
	gcc -g -Werror -O3 -L. -Wl,-rpath=. -o test3 test3.c -ldsa -lpa1 -lm

submit1: test1.c libpa1.so libdsa.so
	@if nm -D libpa1.so |grep -q -e "U printf"; then \
		echo "ERROR: Are you using printf in your implementation"; \
    echo "you are not supposed to do that"; \
    echo "deleting libpa1.so"; \
    rm -f libpa1.so; \
    fi
	echo "Compiling test-case 1"
	gcc -g -Werror -O3 -L. -Wl,-rpath=. -o test1 test1.c -ldsa -lpa1 -lm
	./test1 10000
	./test1 100000

submit2: test2.c libpa1.so libdsa.so
	@if nm -D libpa1.so |grep -q -e "U printf"; then \
		echo "ERROR: Are you using printf in your implementation"; \
    echo "you are not supposed to do that"; \
    echo "deleting libpa1.so"; \
    rm -f libpa1.so; \
    fi
	echo "Compiling test-case 2"
	gcc -g -Werror -O3 -L. -Wl,-rpath=. -o test2 test2.c -ldsa -lpa1 -lm
	./test2 100000
	./test2 1000000

submit3: test3.c libpa1.so libdsa.so
	@if nm -D libpa1.so |grep -q -e "U printf"; then \
		echo "ERROR: Are you using printf in your implementation"; \
    echo "you are not supposed to do that"; \
    echo "deleting libpa1.so"; \
    rm -f libpa1.so; \
    fi
	echo "Compiling test-case 3"
	gcc -g -Werror -O3 -L. -Wl,-rpath=. -o test3 test3.c -ldsa -lpa1 -lm
	./test3 100000
	./test3 1000000

clean:
	make -C ../lib clean
	rm -rf libpa1.so libdsa.so test1 test2 test3 p
