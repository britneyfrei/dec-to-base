#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void other_base(unsigned, unsigned);
void power2_base(unsigned, unsigned);
void base_256(unsigned, unsigned);

const char *ascii = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/";
char buffer[32];
int bindex = 30;

int main(int argc, char *argv[]) {
	int i;
	if (argc != 3) {
		printf("Usage: ./conv <decimal> <base>\n");
		return 1;
	}
	for (i = 0; argv[1][i] != 0; i++) {
		if (argv[1][i] > '9' || argv[1][i] < '0') {
			printf("INVALID NUMBER\n");
			return 1;
		}
	}
	for (i = 0; argv[2][i] != 0; i++) {
		if (argv[2][i] > '9' || argv[2][i] < '0') {
			printf("INVALID NUMBER\n");
			return 1;
		}
	}
	buffer[31] = 0;
	unsigned decimal = atoi(argv[1]);
	unsigned base    = atoi(argv[2]);
	if (base < 2 || (base > 64 && base != 256)) {
		printf("INVALID BASE\n");
		return 1;
	}
	float b = base;
	float f = 1.0;
	if (base == 256) {
		base_256(decimal, base);
	}
	else {
		if (pow(b, (1.0/f)) == 2.0) {
			power2_base(decimal, base);
		}
		else {
			other_base(decimal, base);
		}
	}
	printf("%s\n", &buffer[bindex + 1]);
	return 0;
}

void other_base(unsigned decimal, unsigned base) {
	int dgt;
	for (; decimal != 0; decimal /= base) {
		if (dgt > base) {
			printf("INVALID BASE\n");
			return;
		}
		buffer[bindex] = ascii[dgt];
		bindex--;
	}
	return;
}

void power2_base(unsigned decimal, unsigned base) {
	float f = 1.0;
	float b = base;
	while (pow(b, (1.0/f)) != 2.0) {
		f++;
	}
	int n = (int)f;
	int dgt;
	while (decimal != 0) {
		dgt = decimal & (base - 1);
		if (dgt > base) {
			printf("INVALID BASE\n");
			return;
		}
		buffer[bindex] = ascii[dgt];
		bindex--;
		decimal = decimal >> n;
	}
	return;
}

void base_256(unsigned decimal, unsigned base) {
	int mask;
	int dgt;
	while (decimal != 0) {
		mask = decimal & 255;
		for (; mask != 0; mask /= 10) {
			dgt = mask % 10;
			if (dgt > base) {
				printf("INVALID BASE\n");
				return;
			}
			buffer[bindex] = ascii[dgt];
			bindex--;
		}
		decimal = decimal >> 8;
		if (decimal != 0) {
			buffer[bindex] = '.';
			bindex--;
		}
	}
	return;
}
