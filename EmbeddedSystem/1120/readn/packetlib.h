
struct packet {
	char *current;
	char *base;
};

void construct(struct packet *packet, char *buf);
void write_byte(struct packet *packet, char value);
void write_int32(struct packet *packet, int value);
char read_byte(struct packet *packet);
int read_int32(struct packet *packet);
int packet_length(struct packet *packet);


