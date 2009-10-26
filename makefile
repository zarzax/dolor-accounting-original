BINS = bin/set_of_books.o bin/Accounts.o bin/Transaction.o bin/Category.o bin/main.o \
	bin/tinystr.o bin/tinyxml.o bin/tinyxmlerror.o bin/tinyxmlparser.o \

OBJS = set_of_books.o Accounts.o Transaction.o Category.o main.o \
	tinystr.o tinyxml.o tinyxmlerror.o tinyxmlparser.o \
	
SRCS = src/inc/set_of_books.cpp src/inc/Accounts.cpp src/inc/Transaction.cpp src/inc/Category.cpp src/main.cpp \
	src/inc/lib/tinyxml/tinystr.cpp src/inc/lib/tinyxml/tinyxml.cpp src/inc/lib/tinyxml/tinyxmlerror.cpp src/inc/lib/tinyxml/tinyxmlparser.cpp \
	

all: dolor

clean:
	-rm bin/* dolor

dolor: $(OBJS)
	g++ -g -o dolor $(BINS)	
			
set_of_books.o: src/inc/lib/strextra/Strextra.h
	g++ -c -g src/inc/set_of_books.cpp -o bin/set_of_books.o			
	
Accounts.o: src/inc/lib/strextra/Strextra.h
	g++ -c -g src/inc/Accounts.cpp -o bin/Accounts.o	
	
Transaction.o: src/inc/lib/strextra/Strextra.h
	g++ -c -g src/inc/Transaction.cpp -o bin/Transaction.o
	
Category.o:
	g++ -c -g src/inc/Category.cpp -o bin/Category.o

main.o:
	g++ -c -g src/main.cpp -o bin/main.o



	
tinystr.o:
	g++ -c -g src/inc/lib/tinyxml/tinystr.cpp -o bin/tinystr.o
	
tinyxml.o:
	g++ -c -g src/inc/lib/tinyxml/tinyxml.cpp -o bin/tinyxml.o	
	
tinyxmlerror.o:
	g++ -c -g src/inc/lib/tinyxml/tinyxmlerror.cpp -o bin/tinyxmlerror.o		
	
tinyxmlparser.o:
	g++ -c -g src/inc/lib/tinyxml/tinyxmlparser.cpp -o bin/tinyxmlparser.o


