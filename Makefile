# Dante Eleutério dos Santos (GRR)
# Richard Fernando Heise Ferreira (GRR20191053)

CFLAGS  = -g
CC = g++ 

#-----------------------------------------------------------------------------#
all : encrypt decrypt

rEncrypt: encrypt
	./encrypt

rDecrypt: decrypt
	./decrypt

encrypt: encrypt.o 

decrypt: decrypt.o utils.o

#-----------------------------------------------------------------------------#

clean :
	$(RM) *.o

#-----------------------------------------------------------------------------#

purge:
	$(RM) encrypt decrypt *.o
