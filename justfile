default: build

build:
    avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega164p -c src/*.c
    avr-gcc -mmcu=atmega164p *.o -o morse.elf 
    avr-objcopy -j .text -j .data -O ihex morse.elf morse.hex

clean:
    rm -rf *.o *.elf *.hex *.bin

test: build clean 
