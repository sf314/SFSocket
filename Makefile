## Make SFSocket's static library to link against (C++)
## Use this lib by providing the path to INLCUDE and libsfsocket.a

INCLUDES = \
-Iinclude

SOURCES = \
src/sfsocketserver.cpp \
src/sfsocketclient.cpp

OBJECTS = \
sfsocketserver.o \
sfsocketclient.o

all:
	g++ -c -fPIC $(INCLUDES) $(SOURCES)
	ar rcs libsfsocket.a $(OBJECTS)

clean:
	rm *.a *.o

