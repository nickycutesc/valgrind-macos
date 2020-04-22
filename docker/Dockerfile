FROM alpine:latest

RUN apk add --no-cache valgrind gcc libc-dev

COPY pth_term_signal.c .
RUN gcc -o pth_term_signal pth_term_signal.c

ENTRYPOINT HISTFILE=.history /bin/sh
