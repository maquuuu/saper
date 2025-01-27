# Nazwa pliku wynikowego
TARGET = saper

# Kompilator
CC = gcc

# Opcje kompilacji
CFLAGS = -Wall -Wextra -std=c11 -g

# Pliki źródłowe
SRCS = main.c mapa.c wynik.c ruch.c interak.c zapis.c

# Pliki nagłówkowe
HEADERS = mapa.h wynik.h ruch.h interak.h zapis.h common.h

# Pliki obiektowe
OBJS = $(SRCS:.c=.o)

# Reguła główna
all: $(TARGET)

# Kompilacja pliku wykonywalnego
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Kompilacja plików źródłowych
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Usuwanie plików wynikowych
clean:
	rm -f $(OBJS) $(TARGET)

# Uruchomienie programu
run: $(TARGET)
	./$(TARGET)
