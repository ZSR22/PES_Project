# Nome del progetto
TARGET = SGP

# Compilatore
CC = gcc

# Opzioni di compilazione
CFLAGS = -Wall -Wextra -std=c11 -g

# Librerie da collegare (vuoto perché linkiamo staticamente)
LDLIBS =

# File sorgenti
SRC = main.c abbonamenti.c Prenotazione.c Persistenza_Dati.c Lista_Prenotazioni.c Utilities.c Lezioni.c \
      cjson/cJSON.c cjson/cJSON_Utils.c report.c

# File oggetto
OBJ = $(SRC:.c=.o)

# Includi directory per gli header file
INC = -I. -Icjson

# Nome eseguibile differenziato per sistema operativo
ifeq ($(OS),Windows_NT)
    EXEC = $(TARGET).exe
    RM = del /Q
else
    EXEC = $(TARGET)
    RM = rm -f
endif

# Regola principale
all: $(EXEC)

# Link dell'eseguibile
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) $(LDLIBS)

# Compilazione dei file .c
%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Pulizia
.PHONY: clean
clean:
	$(RM) $(OBJ) $(EXEC)