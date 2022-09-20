CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		LoginManager.o

LIBS =

TARGET =	LoginManager

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
