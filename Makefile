CXX=g++
SRCDIR=src
OBJDIR=$(SRCDIR)/obj
EXE=$(OBJDIR)/main
all: main
libaes.o:
	$(CXX) -c $(SRCDIR)/krypto/lib/AES.cpp -o $(OBJDIR)/libaes.o
libaes256krypto.o: libaes.o
	$(CXX) -c $(SRCDIR)/krypto/aes256.cpp -o $(OBJDIR)/libaes256krypto.o
main.o:
	$(CXX) -c $(SRCDIR)/main.cpp -o $(OBJDIR)/main.o
main:	main.o libaes256krypto.o
	$(CXX) $(OBJDIR)/main.o $(OBJDIR)/libaes.o $(OBJDIR)/libaes256krypto.o -o $(EXE)
clean:
	rm $(OBJDIR)/*
run:
	$(EXE)

debug: all
	gdb $(EXE)
