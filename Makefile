run: json-lib
	@gcc main.c -ljson-c -o executable;
	@./executable

json-lib:
	@sudo apt install libjson-c-dev