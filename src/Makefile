CXX=g++
LDLIBS=
LDFLAGS=-g
CXXINCLUDE=
CXXFLAGS=-g $(CXXINCLUDE) -Wall -std=c++17

SRCS=\
	main.cpp

OBJS=$(subst .cpp,.o,$(SRCS))


all: bank

bank: $(OBJS)
	$(CXX) $(LDFLAGS) -o bank $(OBJS) $(LDLIBS)

.PHONY: clean depend
depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
	rm -f $(OBJS) ./.depend

include .depend
