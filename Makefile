#       .-"""-.__
#      /      ' o'\    tiny spread sheet - makefile
#   ,-;  '.  :   _c    Oct 22 2024
#  :_."\._ ) ::-"
#         ""m "m
objs = main.o
flags = -Wall -Wextra -Wpedantic
avoid = -Wno-switch
exec = tsp

all: $(exec)

$(exec): $(objs)
	gcc	-o $(exec) $(objs)

%.o: %.c
	gcc	-c $< $(flags) $(avoid)

clean:
	rm	-f $(objs) "\\" $(exec)
