CC   = gcc.exe 
OBJ  = demo.o 
LINKOBJ  = $(OBJ) $(RESOBJ)
DEFS =
CFLAGS = -Os -Wall
LDFLAGS = 
SRCS = demo.c zkey.c

OBJS    = $(ASRCS:.s=.o) $(SRCS:.c=.o) 
TARGET  = demo
CFLAGS += $(UINCS)  
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: $(OBJS) $(TARGET)

%.o: %.c
	$(CC) -c $(CFLAGS) -I. $< -o $@

clean: clean-custom
	${RM} $(LINKOBJ) $(TARGET) *~ .*.swp

$(TARGET): $(LINKOBJ)
	$(CC) $(OBJS) $(LDFLAGS) -o $@
