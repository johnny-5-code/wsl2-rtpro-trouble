# wsl2-rtpro-trouble
Sample project showing troubles with using real time priorities in docker in wsl2

## Dependencies
* Windows 10
* WSL2
* ubuntu 20.04
* docker-compose
* docker (WSL2 integration enabled)

## Build instructions
### host
```bash
make
```

### Docker
```bash
docker-compose build
```

## Run instructions
### host
```bash
./test
```

### Docker
```bash
docker-compose up
```

## Output

### host
```bash
mklein@DESKTOP-UTVJ2AV:~/repos/wsl2-rtpro-trouble$ ./test
rlim                       =0
attr_init                  =0
inherit_sched              =0
policy                     =0
pthread_attr_setschedparam =0
pthread_create             =0
Succesfully created thread
```

### Docker
```bash
mklein@DESKTOP-UTVJ2AV:~/repos/wsl2-rtpro-trouble$ docker-compose up --build
Building test
[+] Building 1.4s (14/14) FINISHED
 => [internal] load build definition from Dockerfile                                                                                                                                                                             0.0s
 => => transferring dockerfile: 38B                                                                                                                                                                                              0.0s
 => [internal] load .dockerignore                                                                                                                                                                                                0.0s
 => => transferring context: 2B                                                                                                                                                                                                  0.0s
 => [internal] load metadata for docker.io/library/ubuntu:18.04                                                                                                                                                                  0.6s
 => [builder 1/5] FROM docker.io/library/ubuntu:18.04@sha256:67b730ece0d34429b455c08124ffd444f021b81e06fa2d9cd0adaf0d0b875182                                                                                                    0.0s
 => [internal] load build context                                                                                                                                                                                                0.0s
 => => transferring context: 1.53kB                                                                                                                                                                                              0.0s
 => CACHED [builder 2/5] RUN apt-get update && apt-get install -y build-essential gcc libpthread-stubs0-dev                                                                                                                      0.0s
 => CACHED [builder 3/5] WORKDIR /app                                                                                                                                                                                            0.0s
 => [builder 4/5] ADD main.c .                                                                                                                                                                                                   0.0s
 => [builder 5/5] RUN gcc main.c  -lpthread -o /app/test.exe                                                                                                                                                                     0.3s
 => CACHED [stage-1 2/5] WORKDIR /app                                                                                                                                                                                            0.0s
 => CACHED [stage-1 3/5] RUN apt update && apt install -y libcap2-bin rt-tests                                                                                                                                                   0.0s
 => [stage-1 4/5] COPY --from=builder /app/test.exe .                                                                                                                                                                            0.0s
 => [stage-1 5/5] RUN echo 'kernel.sched_rt_runtime_us=-1' > /etc/sysctl.conf                                                                                                                                                    0.4s
 => exporting to image                                                                                                                                                                                                           0.1s
 => => exporting layers                                                                                                                                                                                                          0.0s
 => => writing image sha256:a8ac6bef26e509288d470dd02fde2ae1da1dec7ddf4deb2d97bef95dd869eb73                                                                                                                                     0.0s
 => => naming to docker.io/library/test:latest                                                                                                                                                                                   0.0s

Use 'docker scan' to run Snyk tests against images to find vulnerabilities and learn how to fix them
Recreating wsl2-rtpro-trouble_test_1 ... done

test
Attaching to wsl2-rtpro-trouble_test_1
test_1  | rlim                       =0
test_1  | attr_init                  =0
test_1  | inherit_sched              =0
test_1  | policy                     =0
test_1  | pthread_attr_setschedparam =0
test_1  | pthread_create             =1
test_1  | pthread_create failed: Operation not permitted
wsl2-rtpro-trouble_test_1 exited with code 1
```
