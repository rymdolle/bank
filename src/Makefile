CXX=g++
RM=rm -f
LDLIBS=
LDFLAGS=-g
CXXINCLUDE=
CXXFLAGS=-g $(CXXINCLUDE) -Wall -std=c++17

SRCS=\
	account.hpp \
	bank.hpp \
	login.hpp \
	main.cpp \
	navigation.hpp \
	transaction.hpp \
	user.hpp



OBJS=$(subst .cpp,.o,$(SRCS))


all: $(OBJS)
	$(CXX) $(LDFLAGS) -o bank $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

include .depend
