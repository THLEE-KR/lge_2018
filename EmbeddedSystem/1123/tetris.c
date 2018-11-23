#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <mcp3422.h>
#include <stdio.h>

#define SW1 4
#define SW2 5

typedef  unsigned char byte;

#define OLED_CONTROL	        	0x00 
#define OLED_ADDRESS	        	0x3C 
#define OLED_COMMAND	            0x80
#define OLED_DATA	                0x40
#define OLED_DISPLAY_OFF	        0xAE
#define OLED_DISPLAY_ON	            0xAF
#define OLED_NORMAL_DISPLAY	    	0xA6
#define OLED_INVERSE_DISPLAY     	0xA7
#define OLED_SET_BRIGHTNESS	        0x81
#define OLED_SET_ADDRESSING	        0x20
#define OLED_HORIZONTAL_ADDRESSING	0x00
#define OLED_VERTICAL_ADDRESSING	0x01
#define OLED_PAGE_ADDRESSING	    0x02
#define OLED_SET_COLUMN             0x21
#define OLED_SET_PAGE	            0x22

// the tetris blocks
const byte Blocks[7][2] = {
	{ 0B01000100, 0B01000100 },
	{ 0B11000000, 0B01000100 },
	{ 0B01100000, 0B01000100 },
	{ 0B01100000, 0B00000110 },
	{ 0B11000000, 0B00000110 },
	{ 0B01000000, 0B00001110 },
	{ 0B01100000, 0B00001100 }
};

const byte NumberFont[10][8]  = {
	{ 0x00, 0x1c, 0x22, 0x26, 0x2a, 0x32, 0x22, 0x1c },
	{ 0x00, 0x1c, 0x08, 0x08, 0x08, 0x08, 0x0c, 0x08 },
	{ 0x00, 0x3e, 0x02, 0x04, 0x18, 0x20, 0x22, 0x1c },
	{ 0x00, 0x1c, 0x22, 0x20, 0x18, 0x20, 0x22, 0x1c },
	{ 0x00, 0x10, 0x10, 0x3e, 0x12, 0x14, 0x18, 0x10 },
	{ 0x00, 0x1c, 0x22, 0x20, 0x20, 0x1e, 0x02, 0x3e },
	{ 0x00, 0x1c, 0x22, 0x22, 0x1e, 0x02, 0x04, 0x18 },
	{ 0x00, 0x04, 0x04, 0x04, 0x08, 0x10, 0x20, 0x3e },
	{ 0x00, 0x1c, 0x22, 0x22, 0x1c, 0x22, 0x22, 0x1c },
	{ 0x00, 0x0c, 0x10, 0x20, 0x3c, 0x22, 0x22, 0x1c }
};

const byte welcomeScreen[16][5]  = {
	0B01110011, 0B10100010, 0B00100011, 0B11100010, 0B00000000,
	0B10001001, 0B00100010, 0B00100000, 0B00100010, 0B00000000,
	0B10000001, 0B00100010, 0B00100000, 0B00100010, 0B00000000,
	0B01110001, 0B00011110, 0B00100001, 0B11100010, 0B00000000,
	0B00001001, 0B00100010, 0B00100000, 0B00100010, 0B00000000,
	0B10001001, 0B00100010, 0B00100000, 0B00100010, 0B00000000,
	0B01110011, 0B10011110, 0B11111011, 0B11101111, 0B10000000,
	0B00000000, 0B00000000, 0B00000000, 0B00000000, 0B00000000,
	0B00000000, 0B00000000, 0B00000000, 0B00000000, 0B00000000,
	0B00000000, 0B10001000, 0B10111000, 0B10000000, 0B00000000,
	0B00000000, 0B10001100, 0B10010000, 0B10000000, 0B00000000,
	0B00000000, 0B10001100, 0B10010000, 0B10000000, 0B00000000,
	0B00000001, 0B01001010, 0B10010000, 0B10000000, 0B00000000,
	0B00000010, 0B00101001, 0B10010000, 0B10000000, 0B00000000,
	0B00000010, 0B00101001, 0B10010000, 0B10000000, 0B00000000,
	0B00000010, 0B00101000, 0B10111011, 0B11100000, 0B00000000
};

// Tetris Illustration upside-down image binarized from http://www.dcode.fr/binary-image
const byte tetrisLogo[40][8]  =  {
	0B11111111, 0B11111111, 0B11111111, 0B11111111, 0B11111111, 0B11111111, 0B11111111, 0B11111111,
	0B11101101, 0B10111111, 0B11111111, 0B11111111, 0B11111111, 0B01111111, 0B11111001, 0B11100111,
	0B11101101, 0B00110100, 0B11111111, 0B11111111, 0B11111110, 0B01110011, 0B11110001, 0B11100111,
	0B10111000, 0B01010101, 0B11111111, 0B11111111, 0B11111000, 0B01110011, 0B11100001, 0B11100111,
	0B10011110, 0B10110011, 0B10110011, 0B11100011, 0B11100100, 0B00100011, 0B11100011, 0B11110011,
	0B10001111, 0B00010011, 0B00110001, 0B11110001, 0B11110100, 0B00100011, 0B11100011, 0B11110011,
	0B10001111, 0B00000111, 0B01110001, 0B11110000, 0B11110010, 0B00110011, 0B11100011, 0B11110001,
	0B10001111, 0B00000110, 0B01100001, 0B11111000, 0B11111010, 0B00000001, 0B11000001, 0B11100001,
	0B10000110, 0B00001110, 0B11100000, 0B11111000, 0B01111001, 0B00000001, 0B11000000, 0B11000001,
	0B10000110, 0B00001100, 0B11100000, 0B11111100, 0B01111001, 0B00000001, 0B11000000, 0B00000001,
	0B10000110, 0B00001100, 0B11110000, 0B11111100, 0B01111001, 0B00000000, 0B10000000, 0B00000001,
	0B10000110, 0B00001100, 0B11110000, 0B01111100, 0B01111001, 0B00000000, 0B10000000, 0B00000001,
	0B10000110, 0B00000110, 0B11110000, 0B01111100, 0B01111001, 0B00000000, 0B10000000, 0B00000001,
	0B10000110, 0B00000111, 0B01111000, 0B01111000, 0B01110010, 0B00000000, 0B10000000, 0B00000001,
	0B10001101, 0B00000011, 0B00111000, 0B01111000, 0B01110010, 0B00000000, 0B00000000, 0B00000001,
	0B10011001, 0B10000011, 0B10111000, 0B01111000, 0B11110100, 0B00000000, 0B00000000, 0B00000001,
	0B10011001, 0B10000001, 0B10011100, 0B01110001, 0B11101100, 0B00000000, 0B00000000, 0B00000001,
	0B10001001, 0B00000000, 0B11111100, 0B01110001, 0B11011000, 0B00000000, 0B00000000, 0B00000001,
	0B10001011, 0B00000000, 0B01111100, 0B01100011, 0B10110000, 0B00000000, 0B00000000, 0B00000001,
	0B10000110, 0B00000000, 0B00110100, 0B11100111, 0B01100000, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B00000000, 0B00011110, 0B11100110, 0B01000000, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B00000000, 0B00001110, 0B11001100, 0B10000000, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B00000000, 0B00000110, 0B11011011, 0B00000000, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B00000000, 0B00000111, 0B11010010, 0B00000000, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B00000000, 0B00000011, 0B10100100, 0B00000000, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B00000000, 0B00000001, 0B11111000, 0B00000000, 0B00000000, 0B00110000, 0B00000001,
	0B10000000, 0B00000000, 0B00000000, 0B11110000, 0B00000000, 0B00000000, 0B00110000, 0B00000001,
	0B10000000, 0B00000000, 0B00000000, 0B11010000, 0B00000000, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B00000000, 0B00000000, 0B01110000, 0B00000000, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B00000000, 0B10000000, 0B01100000, 0B00000000, 0B00000000, 0B00000000, 0B00000001,
	0B10000011, 0B00000000, 0B00000000, 0B01100000, 0B00000000, 0B00000000, 0B00000000, 0B00000001,
	0B10000011, 0B00000000, 0B00000000, 0B01100000, 0B00000000, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B00000000, 0B00000000, 0B01100000, 0B00000000, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B00000000, 0B00000000, 0B01100000, 0B00000000, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B00000000, 0B00000000, 0B11110000, 0B00000000, 0B00000000, 0B00000000, 0B00010001,
	0B10000000, 0B00000000, 0B00000000, 0B11001000, 0B00000000, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B00000000, 0B00000001, 0B10001000, 0B00000000, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B00000000, 0B00000001, 0B10001000, 0B00000000, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B00000000, 0B00000000, 0B10010000, 0B00000000, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B00000000, 0B00000000, 0B11110000, 0B00001000, 0B00000000, 0B00000000, 0B00000001
};

// Tetris Brick upside-down image binarized from http://www.dcode.fr/binary-image
const byte brickLogo[36][8] = {
	0B10000000, 0B00000000, 0B00000000, 0B00000000, 0B00000000, 0B11111111, 0B11111100, 0B00000001,
	0B10000000, 0B00000111, 0B11111100, 0B11111111, 0B11111110, 0B11111111, 0B11111100, 0B00000001,
	0B10000011, 0B11111111, 0B11111110, 0B11111111, 0B11111111, 0B01111111, 0B11111110, 0B00000001,
	0B10000011, 0B11111111, 0B11111110, 0B01111111, 0B11111111, 0B00111111, 0B11111111, 0B00000001,
	0B10000011, 0B11111111, 0B11111111, 0B01111111, 0B11111111, 0B10111111, 0B11111111, 0B10000001,
	0B10001001, 0B11111111, 0B11111111, 0B00111111, 0B11111111, 0B10011111, 0B11111111, 0B10000001,
	0B10001101, 0B11111111, 0B11111111, 0B10111111, 0B11111111, 0B11001111, 0B11111111, 0B11000001,
	0B10001101, 0B11111111, 0B11111111, 0B10011111, 0B11111111, 0B11101111, 0B11111111, 0B11100001,
	0B10001100, 0B11111111, 0B11111111, 0B11011111, 0B11111111, 0B11100111, 0B11111111, 0B11110001,
	0B10001110, 0B11111111, 0B11111111, 0B11001111, 0B11111111, 0B11110111, 0B11111111, 0B11110001,
	0B10001110, 0B11111111, 0B11111111, 0B11101111, 0B11111111, 0B11111011, 0B11111111, 0B00000001,
	0B10001110, 0B01111111, 0B11111111, 0B11101111, 0B11111111, 0B11100000, 0B00000000, 0B00010001,
	0B10001111, 0B01111111, 0B11111111, 0B11100100, 0B00000000, 0B00000001, 0B11111111, 0B11110001,
	0B10001111, 0B00111111, 0B10000000, 0B00000000, 0B00111111, 0B11111011, 0B11111111, 0B11110001,
	0B10011111, 0B00000000, 0B00000111, 0B11110111, 0B11111111, 0B11110011, 0B11111111, 0B11100001,
	0B10001111, 0B00111111, 0B11111111, 0B11100111, 0B11111111, 0B11110111, 0B11111111, 0B11000001,
	0B10001111, 0B00111111, 0B11111111, 0B11101111, 0B11111111, 0B11100111, 0B11111111, 0B11000001,
	0B10001111, 0B01111111, 0B11111111, 0B11101111, 0B11111111, 0B11101111, 0B11111111, 0B10000001,
	0B10001111, 0B01111111, 0B11111111, 0B11001111, 0B11111111, 0B11001111, 0B11111111, 0B10000001,
	0B10000111, 0B01111111, 0B11111111, 0B11011111, 0B11111111, 0B11011111, 0B11111111, 0B00000001,
	0B10000110, 0B01111111, 0B11111111, 0B11011111, 0B11111111, 0B11011111, 0B11111111, 0B00000001,
	0B10000110, 0B01111111, 0B11111111, 0B10011111, 0B11111111, 0B10111111, 0B11111110, 0B00000001,
	0B10000010, 0B11111111, 0B11111111, 0B10111111, 0B11111111, 0B10111111, 0B11111000, 0B00000001,
	0B10000010, 0B11111111, 0B11111111, 0B10111111, 0B11111111, 0B00110000, 0B00000000, 0B00000001,
	0B10000010, 0B11111111, 0B11111111, 0B00111111, 0B11100000, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B11111111, 0B11111111, 0B00000000, 0B00000110, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B11111111, 0B11000000, 0B00000111, 0B11111110, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B10000000, 0B00001110, 0B01111111, 0B11111100, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B00000000, 0B00111110, 0B11111111, 0B11111100, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B00000000, 0B00011110, 0B11111111, 0B11111100, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B00000000, 0B00011100, 0B11111111, 0B11111000, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B00000000, 0B00011101, 0B11111111, 0B11111000, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B00000000, 0B00001101, 0B11111111, 0B11110000, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B00000000, 0B00001001, 0B11111111, 0B11110000, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B00000000, 0B00000011, 0B11111111, 0B11100000, 0B00000000, 0B00000000, 0B00000001,
	0B10000000, 0B00000000, 0B00000011, 0B11110000, 0B00000000, 0B00000000, 0B00000000, 0B00000001
};


#define KEY_MIDDLE  0
#define KEY_LEFT    68 
#define KEY_RIGHT   67 
#define KEY_DOWN    66 
#define KEY_ROTATE  65 

#define PIEZO_PIN   3
#define LED_PIN     13
#define KEYPAD_PIN  A0

//struct for pieces

typedef struct {
	byte umBlock[4][4];
	char Row;
	char Coloum;
} PieceSpace;

//Globals, is a mess. To do: tidy up and reduce glogal use if possible

byte pageArray[8] = { 0 };
byte scoreDisplayBuffer[8][6] = { { 0 }, { 0 } };
byte nextBlockBuffer[8][2] = { { 0 }, { 0 } };
int optomizePageArray[8] = { 0 };
byte blockColoum[10] = { 0 };
byte tetrisScreen[14][25] = { { 1 } , { 1 } };
PieceSpace currentPiece = { 0 };
PieceSpace oldPiece = { 0 };
byte nextPiece = 0;
//keyPress key = { 0 };
int gameOver = 0;
unsigned long moveTime = 0;
int pageStart = 0;
int pageEnd = 0;

int curr_pos;
int fd;
int score = 0;
int acceleration = 0;
int level = 0;
int levellineCount = 0;
int dropDelay = 1000;

int lastKey = 0;
int led = 1;

void OLEDCommand(byte command) ;
void OLEDData(byte data) ;
void setup() ;
void fillTetrisArray(byte value) ;
void fillTetrisScreen(byte value) ;
void drawTetrisScreen() ;
void drawTetrisTitle(int blank) ;
void drawTetrisLine(byte x) ;
void loadPiece(byte pieceNumber, byte row, byte coloum, int loadScreen) ;
void drawPiece() ;
void drawLandedPiece() ;
void RotatePiece() ;
int movePieceDown() ;
void movePieceLeft() ;
void movePieceRight() ;
int checkColloision() ;
void processCompletedLines() ;
void tetrisScreenToSerial() ;
int processKeys() ;
void setScore(long score, int blank);
void setNextBlock(byte pieceNumber) ;
void drawBottom() ;
void drawSides() ;
void initTermios(int echo);
void resetTermios(void); 
char getch_(void); 

int main() 
{
	setup();
	srand(time(0));
	gameOver = 0;
	score = 0;
	fillTetrisArray(1); //fill with 1's to make border
	fillTetrisScreen(2);
	drawTetrisScreen();
	delay(200);
	fillTetrisScreen(3);
	drawTetrisScreen();
	delay(200);
	drawSides();
	drawBottom();

	tetrisScreenToSerial();

	OLEDCommand(OLED_INVERSE_DISPLAY);
	delay(200);
	OLEDCommand(OLED_NORMAL_DISPLAY);

	loadPiece(rand()%7+1, 20, 5, 1);
	drawTetrisScreen();
	nextPiece = rand()%7+1;
	setNextBlock(nextPiece);

	setScore(0, 0);
	delay(300);
	setScore(0, 1);
	delay(300);
	setScore(0, 0);

	drawTetrisTitle(0);

	//TetrisTheme::start();
	//while(songOn) TetrisTheme::tetrisThemePlay();

	drawTetrisTitle(1);
	drawSides();
	drawBottom();
	setScore(0, 0);

	for(int i=1;i<10;i++) {
		nextPiece = rand()%7+1;
		setNextBlock(nextPiece);
		delay(100);
	}

	pinMode(4, INPUT);
	pinMode(5, INPUT);

	while (!gameOver) {
		movePieceDown();
		drawPiece();
		drawTetrisScreen();
		moveTime = millis();
		while (millis() - moveTime < (dropDelay - (level * 50))) {
			drawTetrisScreen();
			processKeys();
			delay(10);
		}
	}
	return 0;
}
// I2C

void OLEDCommand(byte command) {
	// write 8 bits data value to the given register
	int re;
	re = wiringPiI2CWriteReg8(fd, OLED_CONTROL, command);
	if (re == -1) {
		printf("I2C write operation failed with errno:%d\n", errno);
		exit(1);
	}
}


void OLEDData(byte data) {
	// write 8 bits data value to the given register
	int re;
	re = wiringPiI2CWriteReg8(fd, OLED_DATA, data);
	if (re == -1) {
		printf("I2C write operation failed with errno:%d\n", errno);
		exit(1);
	}
}


void setup() {
	wiringPiSetup();
	mcp3422Setup (400, 0x6a, 0, 0) ;
	delay(200);
	curr_pos = analogRead(403);
	printf("curr_pos=%d\n", curr_pos);
	fd = wiringPiI2CSetup(OLED_ADDRESS);
	// if init failed
	if ( fd == -1) {
		printf("I2C interface init failed, with errno\n", errno);
		exit(1);
	}
	OLEDCommand(OLED_DISPLAY_OFF);
	delay(20);
	OLEDCommand(OLED_DISPLAY_ON);
	delay(20);
	OLEDCommand(OLED_NORMAL_DISPLAY);
	delay(20);
	OLEDCommand(0x8D);
	delay(20);
	OLEDCommand(0x14);
	delay(20);
	OLEDCommand(OLED_NORMAL_DISPLAY);
	fillTetrisScreen(0);
}


void fillTetrisArray(byte value) {
	for (char r = 0; r < 24; r++) {
		for (char c = 0; c < 14; c++) {
			tetrisScreen[c][r] = value;
		}
	}
	for (char r = 21; r < 24; r++) {
		for (char c = 0; c < 14; c++) {
			tetrisScreen[c][r] = 0;
		}
	}
}


void fillTetrisScreen(byte value) {
	for (int r = 1; r < 21; r++) {
		for (int c = 2; c < 12; c++) {
			tetrisScreen[c][r] = value;
		}
	}
}


void drawTetrisScreen() {
	for (byte r = 1; r < 21; r++) {
		//loop through rows to see if there is data to be sent
		for (byte c = 2; c < 12; c++) {
			if ((tetrisScreen[c][r] == 2) | (tetrisScreen[c][r] == 3)) 
			{
				//send line to screen
				for (byte i = 0; i < 10; i++) {
					blockColoum[i] = tetrisScreen[i + 2][r];
					//clear delete block
					if (tetrisScreen[i + 2][r] == 3) tetrisScreen[i + 2][r] = 0;
				}
				drawTetrisLine((r - 1) * 6);
				break;
			}
		}
	}
}


void drawTetrisTitle(int blank) {
	byte byteval;

	//set Vertical addressing mode and column - page start end
	OLEDCommand(OLED_SET_ADDRESSING);
	OLEDCommand(OLED_VERTICAL_ADDRESSING);

	OLEDCommand(OLED_SET_COLUMN);
	OLEDCommand( 50 );                //Set column start
	OLEDCommand( 66 );              //Set column end

	OLEDCommand(OLED_SET_PAGE);
	OLEDCommand( 1 );               //Set page start
	OLEDCommand( 5 );               //Set page end

	for (int r = 0; r <16; r++) {
		for (int c = 4; c >=0; c--) {
			if(blank) {
				OLEDData(0);
			}else {
				byteval = welcomeScreen[r][c];
				OLEDData(byteval);
			}
		}
	}

	OLEDCommand(OLED_SET_COLUMN);
	OLEDCommand( 1 );                //Set column start
	OLEDCommand( 42 );              //Set column end

	OLEDCommand(OLED_SET_PAGE);
	OLEDCommand( 0 );               //Set page start
	OLEDCommand( 7 );               //Set page end

	for (int r = 0; r <40; r++) {
		for (int c = 7; c >=0; c--) {
			if(blank) {
				OLEDData(0);
			}else {
				byteval = tetrisLogo[r][c];
				OLEDData(byteval);
			}
		}
	}

	OLEDCommand(OLED_SET_COLUMN);
	OLEDCommand( 75 );                //Set column start
	OLEDCommand( 116 );              //Set column end

	OLEDCommand(OLED_SET_PAGE);
	OLEDCommand( 0 );               //Set page start
	OLEDCommand( 7 );               //Set page end

	for (int r = 0; r <36; r++) {
		for (int c = 7; c >=0; c--) {
			if(blank) {
				OLEDData(0);
			}else {
				byteval = brickLogo[r][c];
				OLEDData(byteval);
			}
		}
	}
}


void drawTetrisLine(byte x) {
	//fill array with blocks based on blockRow

	//clear page and Optimize array
	memset(optomizePageArray, 0, 8);   ///review this... declare them here? interesting question...
	memset(pageArray, 0, 8);

	x++; // up one
	//*********Column 0***********
	//draw block
	if (blockColoum[0] == 2 | blockColoum[0] == 1) {
		pageArray[0] = pageArray[0] | 0B11111001;
		optomizePageArray[0] = 1;
	}
	//delete block
	if (blockColoum[0] == 3) {
		pageArray[0] = pageArray[0] | 0B00000001; //create side wall
		pageArray[0] = pageArray[0] & 0B00000111;
		optomizePageArray[0] = 1;
	}
	//*********Column 1***********
	if (blockColoum[1] == 2 | blockColoum[1] == 1) {
		pageArray[1] = pageArray[1] | 0B00111110;
		optomizePageArray[1] = 1;
	}
	//delete block
	if (blockColoum[1] == 3) {
		pageArray[1] = pageArray[1] & 0B11000001;
		optomizePageArray[1] = 1;
	}
	//*********Column 2***********
	if (blockColoum[2] == 2 | blockColoum[2] == 1) {
		pageArray[1] = pageArray[1] | 0B10000000;
		optomizePageArray[1] = 1;
		pageArray[2] = pageArray[2] | 0B00001111;
		optomizePageArray[2] = 1;
	}
	//delete block
	if (blockColoum[2] == 3) {
		pageArray[1] = pageArray[1] & 0B01111111;
		optomizePageArray[1] = 1;
		pageArray[2] = pageArray[2] & 0B11110000;
		optomizePageArray[2] = 1;
	}
	//*********Column 3***********
	if (blockColoum[3] == 2 | blockColoum[3] == 1) {
		pageArray[2] = pageArray[2] | 0B11100000;
		optomizePageArray[2] = 1;
		pageArray[3] = pageArray[3] | 0B00000011;
		optomizePageArray[3] = 1;
	}
	//delete block
	if (blockColoum[3] == 3) {
		pageArray[2] = pageArray[2] & 0B00011111;
		optomizePageArray[2] = 1;
		pageArray[3] = pageArray[3] & 0B11111100;
		optomizePageArray[3] = 1;
	}
	//*********Column 4***********
	if (blockColoum[4] == 2 | blockColoum[4] == 1) {
		pageArray[3] = pageArray[3] | 0B11111000;
		optomizePageArray[3] = 1;
	}
	//delete block
	if (blockColoum[4] == 3) {
		pageArray[3] = pageArray[3] & 0B00000111;
		optomizePageArray[3] = 1;
	}
	//*********Column 5***********
	if (blockColoum[5] == 2 | blockColoum[5] == 1) {
		pageArray[4] = pageArray[4] | 0B00111110;
		optomizePageArray[4] = 1;
	}

	//delete block
	if (blockColoum[5] == 3) {
		pageArray[4] = pageArray[4] & 0B11000001;
		optomizePageArray[4] = 1;
	}
	//*********Column 6***********
	if (blockColoum[6] == 2 | blockColoum[6] == 1) {
		pageArray[4] = pageArray[4] | 0B10000000;
		optomizePageArray[4] = 1;
		pageArray[5] = pageArray[5] | 0B00001111;
		optomizePageArray[5] = 1;
	}
	//delete block
	if (blockColoum[6] == 3) {
		pageArray[4] = pageArray[4] & 0B01111111;
		optomizePageArray[4] = 1;
		pageArray[5] = pageArray[5] & 0B11110000;
		optomizePageArray[5] = 1;
	}
	//*********Column 7***********
	if (blockColoum[7] == 2 | blockColoum[7] == 1) {
		pageArray[5] = pageArray[5] | 0B11100000;
		optomizePageArray[5] = 1;
		pageArray[6] = pageArray[6] | 0B00000011;
		optomizePageArray[6] = 1;
	}
	if (blockColoum[7] == 3) {
		pageArray[5] = pageArray[5] & 0B00011111;
		optomizePageArray[5] = 1;
		pageArray[6] = pageArray[6] & 0B11111100;
		optomizePageArray[6] = 1;
	}
	//*********Column 8***********
	if (blockColoum[8] == 2 | blockColoum[8] == 1) {
		pageArray[6] = pageArray[6] | 0B11111000;
		optomizePageArray[6] = 1;
	}
	//delete block
	if (blockColoum[8] == 3) {
		pageArray[6] = pageArray[6] & 0B00000111;
		optomizePageArray[6] = 1;
	}
	//*********Column 9***********
	if (blockColoum[9] == 2 | blockColoum[9] == 1) {
		pageArray[7] = pageArray[7] | 0B10111110;
		optomizePageArray[7] = 1;
	}
	if (blockColoum[9] == 3) {
		pageArray[7] = pageArray[7] | 0B10000000;//create side wall
		pageArray[7] = pageArray[7] & 0B11000001;
		optomizePageArray[7] = 1;
	}
	//Optimize - figure out what page array has data
	for (int page = 0; page < 8; page++) {
		if (optomizePageArray[page]) {
			//block found set page start
			pageStart = page;
			break;
		}
	}
	for (int page = 7; page >= 0; page--) {
		if (optomizePageArray[page]) {
			//block found set page end
			pageEnd = page;
			break;
		}
	}

	//set Vertical addressing mode and column - page start end
	OLEDCommand(OLED_SET_ADDRESSING);
	OLEDCommand(OLED_VERTICAL_ADDRESSING);
	OLEDCommand(OLED_SET_COLUMN);
	OLEDCommand(x);
	OLEDCommand(x + 4);
	OLEDCommand(OLED_SET_PAGE);
	OLEDCommand(pageStart);
	OLEDCommand(pageEnd);

	//send the array 5 times
	for (int c = 0; c < 5; c++) {
		for (int p = pageStart; p <= pageEnd; p++) {
			OLEDData(pageArray[p]);
		}
	}
}


void loadPiece(byte pieceNumber, byte row, byte coloum, int loadScreen) {
	//load the piece from piece array to screen
	byte pieceRow = 0;
	byte pieceColoum = 0;
	byte c = 0;

	// load piece from progmem
	byte byte_in;
	byte piece_out[4][4];
	byte piece_bit[2] = {0,0};

	for(int i=0;i<2;i++) {

		byte_in = Blocks[pieceNumber-1][i];

		for( byte mask = 1; mask; mask <<=1) {
			if(mask & byte_in) {
				piece_out[piece_bit[0]][piece_bit[1]] = 1;
			} else {
				piece_out[piece_bit[0]][piece_bit[1]] = 0;
			}
			piece_bit[1]++;
			if(piece_bit[1]>=4) {
				piece_bit[1]=0;
				piece_bit[0]++;
			}
		}
	}

	memcpy(currentPiece.umBlock, piece_out, 16); 

	currentPiece.Row = row;
	currentPiece.Coloum = coloum;

	if (loadScreen) {
		oldPiece = currentPiece;

		for (c = coloum; c < coloum + 4; c++) {
			for (int r = row; r < row + 4; r++) {
				if (currentPiece.umBlock[pieceColoum][pieceRow]) tetrisScreen[c][r] = 2;
				pieceRow++;
			}
			pieceRow = 0;
			pieceColoum++;
		}
	}
}


void drawPiece() {
	char coloum;
	char row;
	byte pieceRow = 0;
	byte pieceColoum = 0;
	char c = 0;

	// delete blocks first

	coloum = oldPiece.Coloum;
	row = oldPiece.Row;

	for (c = coloum; c < coloum + 4; c++) {
		for (char r = row; r < row + 4; r++) {
			if (oldPiece.umBlock[pieceColoum][pieceRow]) tetrisScreen[c][r] = 3;
			pieceRow++;
		}
		pieceRow = 0;
		pieceColoum++;
	}

	//draw new blocks
	pieceRow = 0;
	pieceColoum = 0;
	c = 0;

	coloum = currentPiece.Coloum;
	row = currentPiece.Row;

	for (c = coloum; c < coloum + 4; c++) {
		for (char r = row; r < row + 4; r++) {
			if (currentPiece.umBlock[pieceColoum][pieceRow]) tetrisScreen[c][r] = 2;
			pieceRow++;
		}
		pieceRow = 0;
		pieceColoum++;
	}
}


void drawLandedPiece() {
	char coloum;
	char row;
	byte pieceRow = 0;
	byte pieceColoum = 0;
	char c = 0;

	// Landed pieces are 1
	coloum = currentPiece.Coloum;
	row = currentPiece.Row;

	for (c = coloum; c < coloum + 4; c++) {
		for (int r = row; r < row + 4; r++) {
			if (currentPiece.umBlock[pieceColoum][pieceRow]) tetrisScreen[c][r] = 1;
			pieceRow++;
		}
		pieceRow = 0;
		pieceColoum++;
	}
	processCompletedLines();
}


void RotatePiece() {
	byte i, j;

	byte umFig[4][4] = { 0 };

	memcpy(oldPiece.umBlock, currentPiece.umBlock, 16);
	oldPiece.Row = currentPiece.Row;
	oldPiece.Coloum = currentPiece.Coloum;

	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			umFig[j][i] = currentPiece.umBlock[4 - i - 1][j];
		}
	}

	oldPiece = currentPiece;
	memcpy(currentPiece.umBlock, umFig, 16);

	if (checkColloision()) currentPiece = oldPiece;

	// no need for this...
	/*
	   if (led) {
	   digitalWrite(LED_PIN, HIGH);
	   led = 0;
	   }
	   delay(1);
	   digitalWrite(LED_PIN, LOW);
	   if (led == 0) {
	   digitalWrite(LED_PIN, LOW);
	   led = 1;
	   }
	 */
}


int movePieceDown() {
	int pieceLanded = 0;
	char rndPiece = 0;

	oldPiece = currentPiece;
	currentPiece.Row = currentPiece.Row - 1;

	//check collision
	if (checkColloision()) {
		// its at the bottom make it a landed piece and start new piece
		currentPiece = oldPiece; // back to where it was
		drawLandedPiece();
		pieceLanded = 1;
	}

	if (pieceLanded) {
		loadPiece(nextPiece, 19, 4, 0);
		acceleration = 0;

		if (checkColloision()) {
			gameOver = 1;
		} else {
			loadPiece(nextPiece, 19, 4, 1);
			acceleration = 0;//reset acceleration as there is a new piece
		}

		nextPiece = rand()%7+1;
		setNextBlock(nextPiece);
	}
}


void movePieceLeft() {
	oldPiece = currentPiece;
	currentPiece.Coloum = currentPiece.Coloum - 1;
	//check collision
	if (checkColloision()) 	{
		currentPiece = oldPiece; // back to where it was
	}
}


void movePieceRight() {
	oldPiece = currentPiece;
	currentPiece.Coloum = currentPiece.Coloum + 1;
	//check collision
	if (checkColloision()) 	{
		currentPiece = oldPiece; // back to where it was
	}
}


int checkColloision() {

	byte pieceRow = 0;
	byte pieceColoum = 0;
	char c = 0;
	char coloum = currentPiece.Coloum;
	char row = currentPiece.Row;

	//scan across piece and translate to Tetris array and check Collisions.
	for (c = coloum; c < coloum + 4; c++) {
		for (char r = row; r < row + 4; r++) {
			if (currentPiece.umBlock[pieceColoum][pieceRow]) {
				if (tetrisScreen[c][r] == 1) return 1; //is it on landed blocks?
			}
			pieceRow++;
		}
		pieceRow = 0;
		pieceColoum++;
	}
	return 0;
}


void processCompletedLines() {

	char rowCheck = 0;
	char coloumCheck = 0;
	int fullLine = 0;
	int noLine = 1;
	char linesProcessed = 0;
	char clearedLines = 0;
	char topRow = 0;
	char bottomRow = 0;
	char currentRow = 0;
	int amountScored = 0;

	if (currentPiece.Row < 1)bottomRow = 1;
	else bottomRow = currentPiece.Row;

	for (int rowCheck = bottomRow; rowCheck < currentPiece.Row + 4; rowCheck++) {

		int fullLine = 1;
		for (coloumCheck = 2; coloumCheck < 12; coloumCheck++) {
			if (tetrisScreen[coloumCheck][rowCheck] == 0) {
				fullLine = 0;
				break;
			}
		}

		if (fullLine) {
			//make line values 3's and render
			for (char c = 2; c < 12; c++) {
				tetrisScreen[c][rowCheck] = 3;
			}

			bottomRow = rowCheck + 1;
			//line is now all 0's
			linesProcessed++;
			delay(77); // animation :)
		}

		drawTetrisScreen();
	}

	//******all lines are 0's and have been removed from the screen
	if (linesProcessed) {

		clearedLines = linesProcessed;

		while (clearedLines) {
			for (currentRow = 1; currentRow < 20; currentRow++) {
				noLine = 1;
				for (char c = 2; c < 12; c++) {
					if (tetrisScreen[c][currentRow])  noLine = 0;
				}
				if (noLine) {
					//move all lines down
					for (int r = currentRow + 1; r < 20; r++) {
						for (char c = 2; c < 12; c++) {
							if (tetrisScreen[c][r]) tetrisScreen[c][r - 1] = 2;
							else tetrisScreen[c][r - 1] = 3;
						}
					}
				}
			}

			//make the 2's 1's
			for (char r = 1; r < 24; r++) {
				for (char c = 2; c < 12; c++) {
					if (tetrisScreen[c][r] == 2)tetrisScreen[c][r] = 1;
				}
			}
			clearedLines--;
			drawTetrisScreen();

			/*
			   tone(PIEZO_PIN, 1000, 50);
			   delay(60);
			   tone(PIEZO_PIN, 2000, 50);
			   delay(50);
			   tone(PIEZO_PIN, 500, 50);
			   delay(60);
			 */
		}
	}

	// ************** process score *******************
	switch (linesProcessed) {
		case 1: 	amountScored = 40 * (level + 1); break;
		case 2: 	amountScored = 100 * (level + 1); break;
		case 3: 	amountScored = 300 * (level + 1); break;
		case 4: 	amountScored = 1200 * (level + 1);
					//do 4 line affect
					OLEDCommand(OLED_INVERSE_DISPLAY);
					delay(20);
					OLEDCommand(OLED_NORMAL_DISPLAY);
					break;
	}

	//score animation
	for (long s = score; s < score + amountScored; s = s + (5 * (level + 1))) {
		setScore(s, 0);
	}

	score = score + amountScored;
	setScore(score, 0);

	//****update level line count
	levellineCount = levellineCount + linesProcessed;
	if (levellineCount > 10) {
		level++;
		levellineCount = 0;
		//do level up affect
		OLEDCommand(OLED_INVERSE_DISPLAY);
		delay(100);
		OLEDCommand(OLED_NORMAL_DISPLAY);
		/*
		   for (int i = 250; i < 2500; i += 100) {
		   tone(PIEZO_PIN, i, 5);
		   delay(5);
		   tone(PIEZO_PIN, i / 2, 5);
		   delay(10);
		   }
		 */
		OLEDCommand(OLED_INVERSE_DISPLAY);
		delay(100);
		OLEDCommand(OLED_NORMAL_DISPLAY);
	}

	//make the 2's 1's
	for (char r = bottomRow; r <= topRow; r++) {
		for (char c = 2; c < 12; c++) {
			if (tetrisScreen[c][r]) {
				tetrisScreen[c][r] = 1;
			}
		}
	}
}

void tetrisScreenToSerial() {
	//for debug
	for (int r = 0; r < 24; r++) {
		for (int c = 0; c < 14; c++) {
			printf("%d", tetrisScreen[c][r]);
		}
		printf("\n");
	}
	printf("\n");
}


int processKeys() {
	int	processKey; 
	int keypressed = 1;
	int rotate = 700;
	int dpadpos;
	int reading = analogRead(403);  // 센서로 부터 자료값을 받는다.

	if( curr_pos+20 < reading)
	{
		dpadpos = KEY_RIGHT;
		printf("KEY_RIGHT\n");
	}
	else if( curr_pos-20 > reading)
	{
		dpadpos = KEY_LEFT;
		printf("KEY_LEFT\n");
	}
	else
	{
		dpadpos = 0;
	}
	curr_pos = reading;

	if (digitalRead(SW1) == LOW) {
		RotatePiece();
	} 

	if (digitalRead(SW2) == LOW) {
		movePieceDown();
	}

	switch(dpadpos) {
		case KEY_LEFT:
			movePieceLeft();
			break;
		case KEY_RIGHT:
			movePieceRight();
			break;
		case KEY_DOWN:
			movePieceDown();
			break;
		case KEY_ROTATE:
			RotatePiece();
			break;
		default:
			acceleration = 0; 
			processKey = 1; 
			keypressed = 0;
			break;
	}

	if (keypressed) {
		drawPiece();
		drawTetrisScreen();
	}
}


void setScore(long score, int blank)

{
	// this is a kludge. To do: create a proper system for rendering numbers and letters.


	long ones = (score % 10);
	long tens = ((score / 10) % 10);
	long hundreds = ((score / 100) % 10);
	long thousands = ((score / 1000) % 10);
	long tenthousands = ((score / 10000) % 10);
	long hunderedthousands = ((score / 100000) % 10);


	//create the score in upper left part of the screen
	byte font = 0;
	char bytes_out[8];
	memset(scoreDisplayBuffer, 0, sizeof scoreDisplayBuffer);

	//****************score digit 6****************

	for (int v = 0; v<8; v++) bytes_out[v] = NumberFont[hunderedthousands][v];

	//write the number to the Score buffer
	for (int i = 0; i < 8; i++)
	{
		scoreDisplayBuffer[i][0] = scoreDisplayBuffer[i][0] | bytes_out[i] >> 1;
	}

	//****************score digit 5****************

	for (int v = 0; v<8; v++) bytes_out[v] = NumberFont[tenthousands][v];

	//write the number to the Score buffer
	for (int i = 0; i < 8; i++)
	{
		scoreDisplayBuffer[i][0] = scoreDisplayBuffer[i][0] | (bytes_out[i] << 6);
	}

	//write the number to the Score buffer
	for (int i = 0; i < 8; i++)
	{
		scoreDisplayBuffer[i][1] = scoreDisplayBuffer[i][1] | bytes_out[i] >> 1;
	}

	//****************score digit 4****************

	for (int v = 0; v<8; v++) bytes_out[v] = NumberFont[thousands][v];


	//write the number to the Score buffer
	for (int i = 0; i < 8; i++)
	{
		scoreDisplayBuffer[i][1] = scoreDisplayBuffer[i][1] | (bytes_out[i] << 6);
	}

	//write the number to the Score buffer
	for (int i = 0; i < 8; i++)
	{
		scoreDisplayBuffer[i][2] = scoreDisplayBuffer[i][2] | bytes_out[i] >> 1;
	}

	//****************score digit 3****************

	for (int v = 0; v<8; v++) bytes_out[v] = NumberFont[hundreds][v];

	//write the number to the Score buffer
	for (int i = 0; i < 8; i++)
	{
		scoreDisplayBuffer[i][2] = scoreDisplayBuffer[i][2] | (bytes_out[i] << 6);
	}

	//write the number to the Score buffer
	for (int i = 0; i < 8; i++)
	{
		scoreDisplayBuffer[i][3] = scoreDisplayBuffer[i][3] | bytes_out[i] >> 1;
	}


	//****************score digit 2****************

	for (int v = 0; v<8; v++) bytes_out[v] = NumberFont[tens][v];

	//write the number to the Score buffer
	for (int i = 0; i < 8; i++)
	{
		scoreDisplayBuffer[i][3] = scoreDisplayBuffer[i][3] | (bytes_out[i] << 6);
	}

	//write the number to the Score buffer
	for (int i = 0; i < 8; i++)
	{
		scoreDisplayBuffer[i][4] = scoreDisplayBuffer[i][4] | bytes_out[i] >> 1;
	}


	//****************score digit 1****************

	for (int v = 0; v<8; v++) bytes_out[v] = NumberFont[ones][v];

	//write the number to the Score buffer
	for (int i = 0; i < 8; i++)
	{
		scoreDisplayBuffer[i][4] = scoreDisplayBuffer[i][4] | (bytes_out[i] << 6);
	}

	//write the number to the Score buffer
	for (int i = 0; i < 8; i++)
	{
		scoreDisplayBuffer[i][5] = scoreDisplayBuffer[i][5] | bytes_out[i] >> 1;

	}

	//set Vertical addressing mode and column - page start end
	OLEDCommand(OLED_SET_ADDRESSING);
	OLEDCommand(OLED_VERTICAL_ADDRESSING);

	OLEDCommand(OLED_SET_COLUMN);
	OLEDCommand(120);                 //Set column start
	OLEDCommand(127);                 //Set column end

	OLEDCommand(OLED_SET_PAGE);
	OLEDCommand(0);                  //Set page start
	OLEDCommand(5);                  //Set page end

	for (int p = 0; p < 8; p++)
	{
		for (int c = 0; c <6; c++)
		{
			if (blank) OLEDData(0);
			else OLEDData(scoreDisplayBuffer[p][c]);
		}

	}
}


void setNextBlock(byte pieceNumber) {
	memset(nextBlockBuffer, 0, sizeof nextBlockBuffer); //clear buffer
	switch (pieceNumber) {
		case 1:
			//************l piece - 1 *************
			for (int k = 2; k < 6; k++) {
				nextBlockBuffer[k][0] = 0B01110111;
				nextBlockBuffer[k][1] = 0B01110111;
			}
			break;
		case 2:
			//************J piece - 2 *************
			for (int k = 0; k < 3; k++) {
				nextBlockBuffer[k][0] = 0B01110000;
				nextBlockBuffer[k][1] = 0B01110111;
			}
			for (int k = 4; k < 7; k++) {
				nextBlockBuffer[k][0] = 0B01110000;
			}
			break;
		case 3:
			//************L piece - 3 *************
			for (int k = 0; k < 3; k++) {
				nextBlockBuffer[k][0] = 0B01110000;
			}
			for (int k = 4; k < 7; k++) {
				nextBlockBuffer[k][0] = 0B01110000;
				nextBlockBuffer[k][1] = 0B01110111;
			}
			break;
		case 4:
			//************O piece - 4 *************
			for (int k = 0; k < 3; k++) {
				nextBlockBuffer[k][0] = 0B01110000;
				nextBlockBuffer[k][1] = 0B00000111;
			}
			for (int k = 4; k < 7; k++) {
				nextBlockBuffer[k][0] = 0B01110000;
				nextBlockBuffer[k][1] = 0B00000111;
			}
			break;
		case 5:
			//************S piece - 5 *************
			for (int k = 0; k < 3; k++) {
				nextBlockBuffer[k][0] = 0B01110000;
				nextBlockBuffer[k][1] = 0B00000111;
			}
			for (int k = 4; k < 7; k++) {
				nextBlockBuffer[k][0] = 0B00000000;
				nextBlockBuffer[k][1] = 0B11101110;
			}
			break;
		case 6:
			//************T piece - 6 *************
			for (int k = 0; k < 3; k++) {
				nextBlockBuffer[k][0] = 0B01110000;
				nextBlockBuffer[k][1] = 0B01110111;
			}
			for (int k = 4; k < 7; k++) {
				nextBlockBuffer[k][0] = 0B00000000;
				nextBlockBuffer[k][1] = 0B00001110;
			}
			break;
		case 7:
			//************Z piece - 7 *************
			for (int k = 0; k < 3; k++) {
				nextBlockBuffer[k][0] = 0B01110000;
				nextBlockBuffer[k][1] = 0B00000111;
			}
			for (int k = 4; k < 7; k++) {
				nextBlockBuffer[k][0] = 0B11101110;
				nextBlockBuffer[k][1] = 0B00000000;
			}
			break;
	}

	//set Vertical addressing mode and column - page start end
	OLEDCommand(OLED_SET_ADDRESSING);
	OLEDCommand(OLED_VERTICAL_ADDRESSING);

	OLEDCommand(OLED_SET_COLUMN);
	OLEDCommand(120);                 //Set column start
	OLEDCommand(127);                 //Set column end

	OLEDCommand(OLED_SET_PAGE);
	OLEDCommand(6);                  //Set page start
	OLEDCommand(7);                  //Set page end

	for (int p = 0; p < 8; p++) {
		for (int c = 0; c < 2; c++) {
			OLEDData(nextBlockBuffer[p][c]);
		}
	}
}


void drawBottom() {

	//set Vertical addressing mode and column - page start end
	OLEDCommand(OLED_SET_ADDRESSING);
	OLEDCommand(OLED_VERTICAL_ADDRESSING);

	OLEDCommand(OLED_SET_COLUMN);
	OLEDCommand(0);              //Set column start
	OLEDCommand(0);              //Set column end

	OLEDCommand(OLED_SET_PAGE);
	OLEDCommand(0);              //Set page start
	OLEDCommand(7);              //Set page end

	for (int c = 0; c < 8; c++) {
		OLEDData(255);
	}
}


void drawSides() {

	//set Vertical addressing mode and column - page start end
	OLEDCommand(OLED_SET_ADDRESSING);
	OLEDCommand(OLED_VERTICAL_ADDRESSING);

	OLEDCommand(OLED_SET_COLUMN);
	OLEDCommand(0);                //Set column start
	OLEDCommand(127);              //Set column end

	OLEDCommand(OLED_SET_PAGE);
	OLEDCommand(0);               //Set page start
	OLEDCommand(7);               //Set page end

	for (int r = 0; r < 128; r++) {
		for (int c = 0; c < 8; c++) {
			if (c == 0) OLEDData(1);
			else if (c == 7) OLEDData(128);
			else OLEDData(0);
		}
	}
}




