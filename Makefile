FILES := $(shell ls | grep ".c")
X = -lX11
LIBS = $(X)
all:
	cc $(LIBS) $(FILES) -o waterwm
