default: test1

libpa4.so: pa4.c pa4.h
	gcc -g -Werror -shared -O3 -fPIC -o libpa4.so pa4.c
	@if nm -D libpa4.so |grep -q -e "U free" -e "U malloc" -e "U calloc"; then \
    echo "ERROR: Are you using malloc/calloc/free directly"; \
    echo "you are not supposed to do that"; \
    echo "deleting libpa4.so"; \
    rm -f libpa4.so; \
    fi

libdsa.so: ../lib/lib.c
	make -C ../lib
	cp ../lib/libdsa.so .

test1: test1.c libpa4.so libdsa.so
	gcc -g -Werror -O3 -L. -Wl,-rpath=. -o test1 test1.c -ldsa -lpa4 -lm

submit1: test1.c libpa4.so libdsa.so
	@if nm -D libpa4.so |grep -q -e "U printf"; then \
		echo "ERROR: Are you using printf in your implementation"; \
    echo "you are not supposed to do that"; \
    echo "deleting libpa4.so"; \
    rm -f libpa4.so; \
    fi
	echo "Compiling test-case 1"
	gcc -g -Werror -O3 -L. -Wl,-rpath=. -o test1 test1.c -ldsa -lpa4 -lm
	./test1 1000
	./test1 5000

clean:
	make -C ../lib clean
	rm -rf libpa4.so libdsa.so test1 p
