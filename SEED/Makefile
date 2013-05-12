############################################
# 내  용 : 암호문 테스트용 바이너리 생성
#
# 생성일 : 2007-09-07 11:43오전
#
# 작성자 : Made by KimHoonCheol
############################################

#.SUFFIXES: .c

TARGET = testCipher
OBJECTS = testCipher.o
CC = cc
HOME = .. 
INCDIR = -I$(HOME)/
CIPHER_LIB = $(HOME)/libCipher.a

CFLAGS  = -xarch=v8 -I. -I/usr/include -lnsl
#CFLAGS  = -I. -I/usr/include -lnsl -DBIG_ENDIAN

all:$(TARGET)
$(TARGET):$(OBJECTS)
	$(CC) -o  $(TARGET) $(OBJECTS) $(CFLAGS) $(CIPHER_LIB)
	rm $@.o

.c.o:
	${CC} $(CFLAGS) -c $*.c $(INCDIR)

clean:
	@rm -f $@

