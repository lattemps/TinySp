objs = main.o
flags = -Wall -Wextra -Wpedantic
ignore = -Wno-switch
exec = tsp

all: $(exec)

$(exec): $(objs)
	gcc	-o $(exec) $(objs)

%.o: %.c
	gcc	-c $< $(flags)

clean:
	rm	-rf $(objs) $(exec)
