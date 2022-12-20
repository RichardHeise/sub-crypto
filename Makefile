# Dante Eleutério dos Santos (GRR)
# Richard Fernando Heise Ferreira (GRR20191053)

CFLAGS  = -g
CC = gcc

#-----------------------------------------------------------------------------#
all : crypto 

rEncrypt: crypto
	./crypto -c

rDecrypt: crypto
	./crypto -d

crypto: crypto.o 

#-----------------------------------------------------------------------------#

clean :
	$(RM) *.o

#-----------------------------------------------------------------------------#

purge:
	$(RM) encrypt *.o
