#
# Nome del progetto
TARGET = SGP_TEST

# Compilatore
CC = gcc

# Opzioni di compilazione
CFLAGS = -Wall -Wextra -std=c11 -g

# Librerie da collegare (vuoto perché linkiamo staticamente)
LDLIBS =

# File sorgenti
SRC = header_sorgenti/abbonamenti.c \
      header_sorgenti/Lezioni.c \
      header_sorgenti/Lista_Prenotazioni.c \
      header_sorgenti/Persistenza_Dati.c \
      header_sorgenti/Prenotazione.c \
      header_sorgenti/Utilities.c \
      header_sorgenti/report.c \
      cjson/cJSON.c \
      cjson/cJSON_Utils.c \
      test_clienti.c \
      test_main.c \
      test_prenotazioni.c \
      test_report.c \
      test_utilities.c

# File oggetto
OBJ = $(SRC:.c=.o)

# Includi directory per gli header file
INC = -I. -Icjson -Iheader_sorgenti

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

# Esecuzione test
.PHONY: test
test: all
	./$(EXEC)

# Pulizia
.PHONY: clean
clean:
	$(RM) $(OBJ) $(EXEC)