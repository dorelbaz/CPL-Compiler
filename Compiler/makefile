CC = gcc
CFLAGS = -c -Wall
obj = cpq.o First_Passage.o Error_Handler.o Symbol_Table_Manager.o Label_Manager.o Optimiser.o Operations.o Backpatch.o

all: cpq

cpq: $(obj) lex.yy.o Parser.tab.o
	$(CC) -g $^ -o $@

%.o: %.c Data_File.h
	$(CC) $(CFLAGS) $< -o $@

lex.yy.o: lex.yy.c Parser.tab.h Data_File.h
	$(CC) -c $< -o $@

lex.yy.c: Lexer.l Parser.tab.h
	flex Lexer.l

Parser.tab.o: Parser.tab.c Parser.tab.h Data_File.h
	$(CC) -c $< -o $@ 

Parser.tab.c Parser.tab.h: Parser.y Data_File.h
	bison -d Parser.y

clean:
	rm -f *.o Parser.tab.c Parser.tab.h lex.yy.c cpq