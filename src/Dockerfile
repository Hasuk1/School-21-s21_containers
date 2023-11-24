FROM debian:latest

RUN apt-get update; \
    apt-get upgrade; \
    apt-get install -y gcc g++ libgtest-dev valgrind make googletest build-essential
    
RUN mkdir /home/set
WORKDIR /home/set

COPY . /home/set

USER root

ENTRYPOINT ["make", "valgrind"]