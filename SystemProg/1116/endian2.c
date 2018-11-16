
// Host Endian <-> Network Endian
// 4byte
// htonl, ntohl 

// 2byte
// htons, ntohs
#include <stdio.h>
#include <arpa/inet.h>

void printByOrder(void* value, int size) {
	int i;
	char* p = (char*)value;
	for (i = 0; i < size; ++i) {
		printf("%x ", p[i]);
	}
	putchar('\n');
}

// LGTM
int main()
{
	int value = 0x12345678;
	printByOrder(&value, sizeof value);

	value = htonl(value);
	// endian man page: 64bit 변환 하는 방법도 확인할 수 있습니다.
	
	printByOrder(&value, sizeof value);
}
























