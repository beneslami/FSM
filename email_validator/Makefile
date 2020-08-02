CC = gcc
CFLAGS = -g
FSMLIB = libfsm.a
APP = exe

TARGET:${APP} ${FSMLIB}

${APP}: main.o ${FSMLIB}
	@echo "Building "${APP}
	${CC} ${CFLAGS} main.o -o ${APP} -L . -lfsm

${FSMLIB}: fsm.o utils.o
	@echo "Building "${FSMLIB}
	ar rs ${FSMLIB} ../fsm.o utils.o

fsm.o:
	@echo "Building fsm.o"
	${CC} ${CFLAGS} -DENABLE_EMAIL_VALIDATOR -c ../fsm.c -o ../fsm.o

utils.o:
		${CC} ${CFLAGS} -c utils.c -o utils.o

clean:
	rm -rf main.o fsm.o utils.o libfsm.a ../fsm.o exe
