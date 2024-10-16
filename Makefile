#
#       .-"""-.__
#      /      ' o'\    tiny spread sheet - Makefile
#   ,-;  '.  :   _c    Oct 15 2024
#  :_."\._ ) ::-"
#         ""m "m
#
objs = tinysp.o
cxx = gcc
flags = -Wall -Wextra -Wpedantic
avoid = -Wno-switch
exec = TinySp

all: $(exec)

$(exec): $(objs)
	$(cxx)	-o $(exec) $(objs)

%.o: %.c
	$(cxx)	$(flags) -c $<

clean:
	rm	-rf $(objs) $(exec) '\\'
