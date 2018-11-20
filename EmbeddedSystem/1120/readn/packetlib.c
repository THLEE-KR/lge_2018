#include "packetlib.h"

void construct(struct packet *packet, char *buf) {
	packet->current = buf;
	packet->base = buf;
}

char read_byte(struct packet *packet) {
	char ret = *(packet->current);
	packet->current += sizeof(ret);
	return ret;
}

int read_int32(struct packet *packet) {
	int ret = *((int*)(packet->current));
	packet->current += sizeof(ret);
	return ret;
}

void write_byte(struct packet *packet, char value) {
	*(packet->current) = value;
	packet->current += sizeof(value);
}

void write_int32(struct packet *packet, int value) {
	*((int*)(packet->current)) = value;
	packet->current += sizeof(value);
}

int packet_length(struct packet *packet) {
	return packet->current - packet->base;
}

