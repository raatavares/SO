all: frontend backend 

frontend:
	gcc -c frontend.c
	gcc header.h frontend.c -o frontend

backend:
	gcc -c backend.c
	gcc header.h backend.c -o backend

clean:
	rm frontend
	rm backend
	rm frontend.o
	rm backend.o
