СС := gcc
CFLAGS := -std=c99 -Wall -Werror -Wextra -Wpedantic -I../lab_03_01_01/inc
UTFLAGS := -lcheck

# Получение переменных с файлами

FUNC_DIR := func_tests
FUNCFILES = ./all_test.sh

SRC_DIR := ./src
CFILES := $(wildcard $(SRC_DIR)/*.c)

INC_DIR := ./inc
INCLUDEFILES := $(wildcard $(INC_DIR)/*.h)

UNIT_DIR := ./unit_tests
UNITFILES := $(wildcard $(UNIT_DIR)/*.c)

OUT_DIR := ./out
OBJFILES := $(CFILES:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)

UNIT_OBJ := $(UNITFILES:$(UNIT_DIR)/%.c=$(OUT_DIR)/%.o)
UNIT_OBJ += $(filter $(OUT_DIR)/my_%.o,$(OBJFILES))

# Функции

app.exe : $(OBJFILES)
	$(CC) $^ -o $@

$(OUT_DIR):
	@mkdir -p $@

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c $(INCLUDEFILES) $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

unit_tests.exe: $(UNIT_OBJ)
	$(CC) $^ -o $@ $(UTFLAGS)

$(OUT_DIR)/%.o: $(UNIT_DIR)/%.c $(INCLUDEFILES) $(OUT_DIR)
	$(CC) $(CFLAGS) $(UTFLAGS) -c $< -o $@

.PHONY : clean func

func: $(OBJFILES)
	$(CC) $^ -o app.exe
	cd $(FUNC_DIR) && $(FUNCFILES)

clean:
	$(RM) *.o *.exe
