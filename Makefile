CC       = gcc
CFLAGS   = -std=c99 -fstack-protector-all -Wall -Werror=implicit-function-declaration -g
LDFLAGS  = -lm

PROJECT  = ted
SRC      = src
TST      = tst
UNITY    = unity

# Objetos do programa principal
OBJS = $(SRC)/main.o      \
       $(SRC)/libs.o      \
       $(SRC)/list.o      \
       $(SRC)/hashtable.o \
       $(SRC)/paths.o     \
       $(SRC)/svg.o       \
       $(SRC)/system.o

# ─── Executavel principal ───────────────────────────────────────────────────

$(PROJECT): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(SRC)/$(PROJECT) $(LDFLAGS)

$(SRC)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# ─── Testes unitarios ────────────────────────────────────────────────────────

UNITY_OBJ = $(UNITY)/unity.o

$(UNITY)/unity.o: $(UNITY)/unity.c
	$(CC) $(CFLAGS) -c $< -o $@

# Cada modulo tem seu proprio binario de teste
t_list: $(UNITY_OBJ) $(SRC)/list.o $(TST)/t_list.o
	$(CC) $(CFLAGS) $^ -o $(TST)/t_list $(LDFLAGS)
	$(TST)/t_list

t_paths: $(UNITY_OBJ) $(SRC)/paths.o $(TST)/t_paths.o
	$(CC) $(CFLAGS) $^ -o $(TST)/t_paths $(LDFLAGS)
	$(TST)/t_paths

t_hashtable: $(UNITY_OBJ) $(SRC)/hashtable.o $(TST)/t_hashtable.o
	$(CC) $(CFLAGS) $^ -o $(TST)/t_hashtable $(LDFLAGS)
	$(TST)/t_hashtable

$(TST)/%.o: $(TST)/%.c
	$(CC) $(CFLAGS) -I$(SRC) -I$(UNITY) -c $< -o $@

# tstall: compila e roda todos os testes unitarios
tstall: t_list t_paths t_hashtable

# ─── Limpeza ─────────────────────────────────────────────────────────────────

clean:
	rm -f $(SRC)/*.o $(TST)/*.o $(UNITY)/*.o
	rm -f $(SRC)/$(PROJECT)
	rm -f $(TST)/t_list $(TST)/t_paths $(TST)/t_hashtable
