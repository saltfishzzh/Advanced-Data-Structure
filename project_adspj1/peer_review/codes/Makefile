CC       = gcc.exe
BIN      = project1.exe
CFLAGS   = -std=c99

.PHONY: clean

${BIN}: AVLTree.o SplayTree.o project1.o UBTree.o
		${CC} -o $@ AVLTree.o SplayTree.o project1.o UBTree.o ${CFLAGS}
project1.o: project1.c AVLTree.h SplayTree.h
		${CC} -c project1.c -o project1.o ${CFLAGS}
AVLTree.o: AVLTree.c AVLTree.h
		${CC} -c AVLTree.c -o AVLTree.o ${CFLAGS}
SplayTree.o: SplayTree.c SplayTree.h
		${CC} -c SplayTree.c -o SplayTree.o ${CFLAGS}
UBTree.o: UBTree.c UBTree.h
		${CC} -c UBTree.c -o UBTree.o ${CFLAGS}
clean:
		rm -f *.o ${BIN}