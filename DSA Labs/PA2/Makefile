default: test

libpa2.so: pa2.c pa2.h
	gcc -g -Werror -shared -O3 -fPIC -o libpa2.so pa2.c
	@if nm -D libpa2.so |grep -q -e "U free" -e "U malloc" -e "U calloc" -e "U aligned"; then \
    echo "ERROR: Are you using malloc/calloc/free directly"; \
    echo "you are not supposed to do that"; \
    echo "deleting libpa2.so"; \
    rm -f libpa2.so; \
    fi
    

libdsa.so: ../lib/lib.c
	make -C ../lib
	cp ../lib/libdsa.so .


test: test1.c test2.c test3.c test4.c libpa2.so libdsa.so
	gcc -g -Werror -O3 -L. -Wl,-rpath=. -o test1 test1.c -ldsa -lpa2 -lm
	gcc -g -Werror -O3 -L. -Wl,-rpath=. -o test2 test2.c -ldsa -lpa2 -lm
	gcc -g -Werror -O3 -L. -Wl,-rpath=. -o test3 test3.c -ldsa -lpa2 -lm
	gcc -g -Werror -O3 -L. -Wl,-rpath=. -o test4 test4.c -ldsa -lpa2 -lm


submit1: test1.c libpa2.so libdsa.so
	@if nm -D libpa2.so |grep -q -e "U printf"; then \
		echo "ERROR: Are you using printf in your implementation"; \
    echo "you are not supposed to do that"; \
    echo "deleting libpa2.so"; \
    rm -f libpa2.so; \
    fi
	echo "Compiling test-case 1"
	gcc -g -Werror -O3 -L. -Wl,-rpath=. -o test1 test1.c -ldsa -lpa2 -lm
	./test1 100000
	./test1 1000000


submit2: test2.c libpa2.so libdsa.so
	@if nm -D libpa2.so |grep -q -e "U printf"; then \
		echo "ERROR: Are you using printf in your implementation"; \
    echo "you are not supposed to do that"; \
    echo "deleting libpa2.so"; \
    rm -f libpa2.so; \
    fi
	echo "Compiling test-case 2"
	gcc -g -Werror -O3 -L. -Wl,-rpath=. -o test2 test2.c -ldsa -lpa2 -lm
	./test2 100000
	./test2 1000000

submit3: test3.c libpa2.so libdsa.so
	@if nm -D libpa2.so |grep -q -e "U printf"; then \
		echo "ERROR: Are you using printf in your implementation"; \
    echo "you are not supposed to do that"; \
    echo "deleting libpa2.so"; \
    rm -f libpa2.so; \
    fi
	echo "Compiling test-case 3"
	gcc -g -Werror -O3 -L. -Wl,-rpath=. -o test3 test3.c -ldsa -lpa2 -lm
	./test3 100000
	./test3 1000000


submit4: test4.c libpa2.so libdsa.so
	@if nm -D libpa2.so |grep -q -e "U printf"; then \
		echo "ERROR: Are you using printf in your implementation"; \
    echo "you are not supposed to do that"; \
    echo "deleting libpa2.so"; \
    rm -f libpa2.so; \
    fi
	echo "Compiling test-case 4"
	gcc -g -Werror -O3 -L. -Wl,-rpath=. -o test4 test4.c -ldsa -lpa2 -lm
	./test4 100000
	./test4 1000000

clean:
	make -C ../lib clean
	rm -rf libpa2.so libdsa.so test1 test2 p 1 test3 test4
