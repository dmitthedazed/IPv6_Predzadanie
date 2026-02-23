# IPv6 & IoT — Lab 10: TCP Sockets

Lab assignment implementing BSD sockets in C — from UNIX local sockets up to TCP/IPv6.

## Programs

| Executable | Source | Description |
|---|---|---|
| `fileWrite` | `fileWrite.c` | Write string to file (low-level `open/write/close`) |
| `fileAppend` | `fileAppend.c` | Append string with random prefix to file |
| `client` | `echoClient.c` | Echo client via UNIX local socket |
| `server` | `echoServer.c` | Echo server via UNIX local socket |
| `clientIPv4` | `echoClientIPv4.c` | Echo client via TCP/IPv4 (port 5000) |
| `serverIPv4` | `echoServerIPv4.c` | Echo server via TCP/IPv4 (port 5000) |
| `clientIPv6` | `echoClientIPv6.c` | Echo client via TCP/IPv6 (port 5000) |
| `serverIPv6` | `echoServerIPv6.c` | Echo server via TCP/IPv6 (port 5000) |

## Build

```bash
gcc -Wall -o fileWrite fileWrite.c
gcc -Wall -o fileAppend fileAppend.c
gcc -Wall -o client echoClient.c
gcc -Wall -o server echoServer.c
gcc -Wall -o clientIPv4 echoClientIPv4.c
gcc -Wall -o serverIPv4 echoServerIPv4.c
gcc -Wall -o clientIPv6 echoClientIPv6.c
gcc -Wall -o serverIPv6 echoServerIPv6.c
```

## Usage

**UNIX local socket** (two terminals):
```bash
./server /tmp/mysock       # terminal 1
./client /tmp/mysock       # terminal 2
```

**IPv4** (two terminals):
```bash
./serverIPv4 127.0.0.1    # terminal 1
./clientIPv4 127.0.0.1    # terminal 2
```

**IPv6** (two terminals):
```bash
./serverIPv6 ::1          # terminal 1
./clientIPv6 ::1          # terminal 2
```

The server converts the client's lowercase message to uppercase and sends it back.
