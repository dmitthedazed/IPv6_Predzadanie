<div align="center">

# IPv6_Predzadanie

**BSD sockets in C: from file I/O and UNIX sockets to TCP over IPv4 and IPv6**

Lab 10 of *IPv6 & IoT*. Echo client and server where the server sends back the message in uppercase.

[![Build](https://img.shields.io/github/actions/workflow/status/dmitthedazed/IPv6_Predzadanie/build.yml?style=flat-square&label=Build)](https://github.com/dmitthedazed/IPv6_Predzadanie/actions/workflows/build.yml)
![C](https://img.shields.io/badge/C-gcc-A8B9CC?logo=c&logoColor=white&style=flat-square)
![Linux](https://img.shields.io/badge/Linux-POSIX%20sockets-lightgrey?logo=linux&logoColor=white&style=flat-square)
[![License: MIT](https://img.shields.io/badge/License-MIT-lightgrey?style=flat-square)](LICENSE)

</div>

> [!NOTE]
> Archived. The course is over, so this repository is read-only and kept for reference.

## Programs

| Binary | Source | What it does |
|---|---|---|
| `fileWrite` | [`fileWrite.c`](fileWrite.c) | Writes a string to a file with `open`/`write`/`close` |
| `fileAppend` | [`fileAppend.c`](fileAppend.c) | Appends a string with a random prefix to a file |
| `server`, `client` | [`echoServer.c`](echoServer.c), [`echoClient.c`](echoClient.c) | Echo over a UNIX local socket |
| `serverIPv4`, `clientIPv4` | [`echoServerIPv4.c`](echoServerIPv4.c), [`echoClientIPv4.c`](echoClientIPv4.c) | Echo over TCP/IPv4, port 5000 |
| `serverIPv6`, `clientIPv6` | [`echoServerIPv6.c`](echoServerIPv6.c), [`echoClientIPv6.c`](echoClientIPv6.c) | Echo over TCP/IPv6, port 5000 |

[`settings.h`](settings.h) holds the shared constants and the `_runSafe` macro that checks every system call. The assignment text belongs to the course and isn't included.

## Build

Needs gcc on Linux.

```sh
for p in fileWrite fileAppend; do gcc -Wall -o $p $p.c; done
gcc -Wall -o server echoServer.c && gcc -Wall -o client echoClient.c
gcc -Wall -o serverIPv4 echoServerIPv4.c && gcc -Wall -o clientIPv4 echoClientIPv4.c
gcc -Wall -o serverIPv6 echoServerIPv6.c && gcc -Wall -o clientIPv6 echoClientIPv6.c
```

## Run

Start the server in one terminal and the client in another. The client sends a lowercase message and prints the uppercase reply.

```sh
./server /tmp/mysock        # UNIX socket
./client /tmp/mysock
```

```sh
./serverIPv4 127.0.0.1      # IPv4, port 5000
./clientIPv4 127.0.0.1
```

```sh
./serverIPv6 ::1            # IPv6, port 5000
./clientIPv6 ::1
```

The file programs take a file name and a message:

```sh
./fileWrite out.txt "hello"
./fileAppend out.txt "hello"
```

## License

[MIT](LICENSE) © Dmytrii Savin
