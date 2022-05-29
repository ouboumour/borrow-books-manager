# build/run the program
run:
	@gcc main.c -ljson-c -o executable;
	@./executable

# install requirements
requirements:
	@apt-get install -y libjson-c-dev gcc