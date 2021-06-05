FROM ubuntu:18.04 AS builder
RUN apt-get update && apt-get install -y build-essential gcc libpthread-stubs0-dev
WORKDIR /app
ADD main.c .
RUN gcc main.c  -lpthread -o /app/test.exe 

FROM ubuntu:18.04
WORKDIR /app
RUN apt update && apt install -y libcap2-bin rt-tests
COPY --from=builder /app/test.exe .
RUN echo 'kernel.sched_rt_runtime_us=-1' > /etc/sysctl.conf
CMD ["/app/test.exe"]
