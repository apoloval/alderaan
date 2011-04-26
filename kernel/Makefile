CFLAGS = -I. -I../include -fno-builtin -nostdinc -O -g -Wall -m32
CXXFLAGS = $(CFLAGS) -nostdlib -fno-rtti -nostartfiles -fno-exceptions

LDFLAGS = -nostdlib -Wl,-N -Wl,-Ttext -Wl,100000 --format -m32
LXXFLAGS = -nostdlib -Wl,-N -Wl,-Ttext -Wl,100000 --format -m32

IMG = alderaan.img

OBJECTS = \
   i386/boot.o \
   i386/bootterm.o \
   i386/entry.o \
   cpp-runtime.o

all: $(IMG)

i386/boot.o: i386/boot.S i386/multiboot.h
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(IMG): $(OBJECTS)
	$(CXX) $(LXXFLAGS) $(OBJECTS) -o $(IMG)

install-floppy: floppy.img $(IMG)
	sudo mount -o loop floppy.img /mnt
	sudo cp $(IMG) /mnt
	sudo umount /mnt

.PHONY clean:
	rm -f $(OBJECTS) $(IMG)

