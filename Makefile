CXX=g++
SRCDIR=src
OBJDIR=$(SRCDIR)/obj
EXE=$(OBJDIR)/main


libaes256.o:
	$(CXX) -c $(SRCDIR)/krypto/lib/aes256.c -o $(OBJDIR)/libaes256.o
aes256.o: libaes256.o
	$(CXX) -c $(SRCDIR)/krypto/aes256.cpp -o $(OBJDIR)/aes256.o
main.o: aes256.o
	$(CXX) -c $(SRCDIR)/main.cpp -o $(OBJDIR)/main.o
main:	main.o
	$(CXX) $(OBJDIR)/main.o $(OBJDIR)/aes256.o $(OBJDIR)/libaes256.o -o $(EXE)
clean:
	rm $(OBJDIR)/*.obj
