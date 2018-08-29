# TCP_Server

For this project you need to have qmake!

## Compile a project:
```
> make all
```
Or open .pro files in server_src and client_src dirs by QtCreator

## Server usage:
```
> ./server (port)
```
## Client usage:
```
> ./client (port) (number_of_clients) (timeout_in_msec)
```
By default:
port = 2307,
numbers_of_clients = 8,
timeout_in_msec = 1000
