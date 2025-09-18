# Nome del progetto
TARGET = SGP

# Compilatore
CC = gcc

# Opzioni di compilazione
CFLAGS = -Wall -Wextra -std=c11 -g

# Librerie da collegare
LDLIBS = `pkg-config --libs gtk+-3.0`

# File sorgenti
SRC = main.c abbonamenti.c Prenotazione.c Persistenza_Dati.c Lista_Prenotazioni.c Utilities.c Lezioni.c \
      cjson/cJSON.c cjson/cJSON_Utils.c report.c Descrittore.c gui/Gui_Home.c console/Main_Console.c

# File oggetto
OBJ = $(SRC:.c=.o)

# Includi directory per gli header file
INC = -I. -Icjson `pkg-config --cflags gtk+-3.0`

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

# Esecuzione del programma
.PHONY: run-console
run-console: all
	./$(EXEC) --console

# Esecuzione del programma(GUI)
.PHONY: run-gui
run-gui: all
	./$(EXEC) --gui     