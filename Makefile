all: server client

server:
	cd server_src/ && qmake server.pro && make all && mv server ../ && cd ../

client:
	cd client_src/ && qmake client.pro && make all && mv client ../ && cd ../

clean:
	cd server_src/ && make clean && rm Makefile && cd ../
	cd client_src/ && make clean && rm Makefile && cd ../

fclean: clean
	rm server client
