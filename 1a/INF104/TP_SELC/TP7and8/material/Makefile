##Commande intéressante - touch src/main.c permet d'actualiser la date
##de modification d'un fichier sans réellement devoir le modifier.
## Definifion of variables

CC=gcc ##C compiler
LD=gcc ##Editeur de liens qui est aussi gcc
AR=
RM=

SRC_DIR=src
LIB_DIR=lib
INCLUDE_DIR=include

CFLAGS= -Wall -I$(INCLUDE_DIR)
LDFLAGS= -g

LIB_FILES=

EXEC_NAME=main

## Target liblinked-list-utils.a
## archive linked-list.o into library liblinked-list-utils.a
liblinked-list-utils.a:


## Target main.o
## compile main.c to produce an object file (main.o)
main.o: src/main.c
	$(CC) $(CFLAGS) -c $<
##La variable $< est la première dépendance.
##$@ pour ..., $^ pour la liste des dépendances.

## Target linked-list.o
## compile linked-list.c to produce an object file (linked-list.o)
linked-list.o: src/linked-list.c
	$(CC) $(CFLAGS) -c $<
##On utilise à chaque fois src/... parce que le makefile est à la racine de src


##On se rend alors compte qu'on a écrit deux fois la ligne
##avec CC CFLAGS -c $<... on va donc écrire des lignes génériques :
## %.o: src/%.C un truc en .o à partir d'une dépendance du même nom .c
##	$(CC) $(CFLAGS) -c $< C'est ce qu'on appelle une commande générique.


## Target $(EXEC_NAME)
## link liblinked-list-utils.a and main.o to produce the executable (linked-list-exe)
$(EXEC_NAME): main.o linked-list.o
	$(CC) main.o linked-list.o -o main

## Target all: Useful? Where should be put in the makefile?
all: $(EXEC_NAME) liblinked-list-utils.a
##Oui utile, car elle permet de tout faire d'un coup. Ce pourquoi on la met souvent
##en tête de fichier Makefile afin de juste écrire make et donc de tout lancer !

## Target clean
clean:
	$(RM) *.o $(LIB_DIR)/*.a $(EXEC_NAME)
