
// Endian: CPU가 메모리에 데이터를 저장하고 읽어오는 순서
// Big Endian: 시작 주소에 상위 바이트부터 기록하는 방법
// Little Endian: 시작 주소에 하위 바이트부터 기록하는 방법

// 0x12345678

// 0x0     0x4
//  [12][34][56][78] -> Big
//  [78][56][34][12] -> Little

// 타입의 크기가 1바이트면 고려할 필요가 없다.
// char a[] = { 'A', 'B' }
//  [65][66]
//  [65][66]

// x86/x64: Little Endian
// ARM: Little or Big
// Java: Big
// => 네트워크로 데이터를 전송할 때는 네트워크 엔디안으로
//    전환해야 한다.
//  Network Endian: Big Endian

#include <stdio.h>


// 매크로를 이용해서 엔디안을 확인하는 방법
int main() 
{
#if __BYTE_ORDER == __LITTLE_ENDIAN 
	printf("Little endian\n");
#elif __BYTE_ORDER == __BIG_ENDIAN
	printf("Big endian\n");
#endif
}

#if 0
void printByOrder(void* value, int size) {
	int i;
	char* p = (char*)value;
	for (i = 0; i < size; ++i) {
		printf("%x ", p[i]);
	}
	putchar('\n');
}

int main()
{
	int value = 0x12345678;
	printByOrder(&value, sizeof value);
}
#endif
