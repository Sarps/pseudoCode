CCFLAGS = -O2 -std=c++11

OBJS = pseudoCode.o Token.o Tokenizer.o Parser.o Library.o Memory.o Input.o

pseudoCode: $(OBJS) libs
	$(CXX) -o pseudoCode $(OBJS) AST.a SYMTable.a $(LDFLAGS) $(LDLIBS)

pseudoCode.o: pseudoCode.cpp Parser.h
	$(CXX) $(CCFLAGS) -I. -c pseudoCode.cpp

Library.o: Library.cpp Library.h
	$(CXX) $(CCFLAGS) -I. -c Library.cpp

Token.o: Token.cpp Token.h
	$(CXX) $(CCFLAGS) -I. -c Token.cpp
	
Tokenizer.o: Tokenizer.cpp Tokenizer.h
	$(CXX) $(CCFLAGS) -I. -c Tokenizer.cpp
	
Parser.o: Parser.cpp Parser.h
	$(CXX) $(CCFLAGS) -I. -c Parser.cpp
	
Memory.o: Memory.cpp Memory.h
	$(CXX) $(CCFLAGS) -I. -c Memory.cpp

Input.o: Input.cpp Input.h
	$(CXX) $(CCFLAGS) -I. -c Input.cpp

.cpp.o:
	$(CXX) $(CCFLAGS) -c $<


libs: symtablea astnodesa

#move compiled libraries 
	mv -f AST/AST.a .
	mv -f SYMTable/SYMTable.a .

#Compile all libraries
astnodesa:
	cd AST; $(MAKE)

symtablea:
	cd SYMTable; $(MAKE)

clean:
	#rm -f pseudoCode $(OBJS)
	#rm -f AST.a
	#rm -f SYMTable.a
	#cd AST; $(MAKE) clean
	#cd SYMTable; $(MAKE) clean