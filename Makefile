#
#       .-"""-.__
#      /      ' o'\    tiny spread sheet - makefile.
#   ,-;  '.  :   _c    Oct 21 2024
#  :_."\._ ) ::-"
#         ""m "m
objs = main.o lexer.o
flags = -Wall -Wextra -Wpedantic
ignore = -Wno-switch
exec = tsp

all: $(exec)

$(exec): $(objs)
	gcc	-o $(exec) $(objs)

%.o: %.c
	gcc	-c $< $(flags) $(ignore)

clean:
	rm	-rf $(objs) $(exec)
