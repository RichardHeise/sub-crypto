# Dante Eleutério dos Santos (GRR20206686)
# Richard Fernando Heise Ferreira (GRR20191053)

CFLAGS  = -Wextra
CC = gcc

#-----------------------------------------------------------------------------#
all : bingchiling

encrypt: bingchiling
	./bingchiling -c

decrypt: bingchiling
	./bingchiling -d

bingchiling: bingchiling.o crypt.o


#-----------------------------------------------------------------------------#

clean :
	$(RM) *.o

#-----------------------------------------------------------------------------#

purge:
	$(RM) bingchiling *.o
