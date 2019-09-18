/*
 *	API of the "8bit-Unity" SDK for CC65
 *	All functions are cross-platform for the Apple IIe, Atari XL/XE, and C64/C128
 *	
 *	Last modified: 2019/07/12
 *	
 * Copyright (c) 2019 Anthony Beaucamp.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *   1. The origin of this software must not be misrepresented * you must not
 *   claim that you wrote the original software. If you use this software in a
 *   product, an acknowledgment in the product documentation would be
 *   appreciated but is not required.
 *
 *   2. Altered source versions must be plainly marked as such, and must not
 *   be misrepresented as being the original software.
 *
 *   3. This notice may not be removed or altered from any distribution.
 *
 *   4. The names of this software and/or it's copyright holders may not be
 *   used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 *	Credits: 
 *		* Oliver Schmidt for his IP65 network interface
 *		* Christian Groessler for helping optimize the memory maps on Commodore and Atari
 *		* Bill Buckels for his Apple II Double Hi-Res bitmap code
 */

// CC65 includes
#include <conio.h>
#include <peekpoke.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// Platform IDs
#if defined __CBM__
	#define PLATFORM   0	
    #include "C64/platform.h"		
#elif defined __ATARI__
	#define PLATFORM   1
    #include "Atari/platform.h"	
#elif defined __APPLE2__
	#define PLATFORM   2
    #include "Apple/platform.h"		
#elif defined __ATMOS__
	#define PLATFORM   3
    #include "Oric/platform.h"		
#elif defined __LYNX__
	#define PLATFORM   4
    #include "Lynx/platform.h"	
#endif

// Keyboard definitions
#if defined __LYNX__
	#define KEY_SP		49
#else
	#define KEY_SP		' '
#endif
#if defined __APPLE2__
	#define KEY_A		'A'
	#define KEY_B		'B'
	#define KEY_C		'C'
	#define KEY_D		'D'
	#define KEY_F		'F'
	#define KEY_G		'G'
	#define KEY_H		'H'
	#define KEY_I		'I'
	#define KEY_J		'J'
	#define KEY_L		'L'
	#define KEY_M		'M'
	#define KEY_O		'O'
	#define KEY_Q		'Q'	
	#define KEY_S		'S'	
	#define KEY_W		'W'
#else
	#define KEY_A		'a'	
	#define KEY_B		'b'	
	#define KEY_C		'c'	
	#define KEY_D		'd'	
	#define KEY_F		'f'
	#define KEY_G		'g'
	#define KEY_H		'h'
	#define KEY_I		'i'
	#define KEY_J		'j'
	#define KEY_L		'l'
	#define KEY_M		'm'
	#define KEY_O		'o'
	#define KEY_Q		'q'	
	#define KEY_S		's'	
	#define KEY_W		'w'
#endif

// Character data (see char.s)
extern const char charBlank[3];
extern const char charDigit[30];
extern const char charLetter[78];
extern const char charBracket[6];
extern const char charColon[3];
extern const char charComma[3];
extern const char charDot[3];
extern const char charExclaim[3];
extern const char charHyphen[3];
extern const char charQuestion[3];
extern const char charQuote[3];
extern const char charSlash[3];
extern const char charUnderbar[3];

// Colors for printing
extern unsigned char inkColor, paperColor;
#if defined __ATMOS__
  void SetInk(unsigned char col, unsigned char row);
#endif

// Bitmap functions (see bitmap.c)
void InitBitmap(void);
void EnterBitmapMode(void);
void ExitBitmapMode(void);
void ClearBitmap(void);
void LoadBitmap(char *filename);
void LocatePixel(unsigned int x, unsigned int y);
unsigned char GetPixel(void);
void SetPixel(unsigned char color);
void DrawPanel(unsigned char colBeg, unsigned char rowBeg, unsigned char colEnd, unsigned char rowEnd);
void PrintChr(unsigned char col, unsigned char row, const char *chr);
void PrintNum(unsigned char col, unsigned char row, unsigned char num);
void PrintStr(unsigned char col, unsigned char row, const char *buffer);
void PrintLogo(unsigned char col, unsigned char row, unsigned char index);
void PrintBuffer(char *buffer);
void InputStr(unsigned char col, unsigned char row, char *buffer, unsigned char len);
unsigned char InputUpdate(unsigned char col, unsigned char row, char *buffer, unsigned char len, unsigned char key);
const char *GetChr(unsigned char chr);

// Screen coordinates of current pixel (see LocatePixel())
extern unsigned char pixelX, pixelY;

// C64 specific functions (see C64/ROM.s)
#ifdef __CBM__
  void DisableRom();	// Disable ROM before using GetColor()
  void EnableRom();	// Enable ROM after using GetColor()
#endif

// Lynx specific functions (see Lynx/display.c)
#if defined __LYNX__
  void UpdateDisplay(void);
#endif

// Joystick definitions
#if defined __LYNX__
  #define JOY_UP    128
  #define JOY_DOWN  64
  #define JOY_LEFT  32
  #define JOY_RIGHT 16
  #define JOY_BTN1  2
  #define JOY_BTN2  1
#else
  #define JOY_UP    1
  #define JOY_DOWN  2
  #define JOY_LEFT  4
  #define JOY_RIGHT 8
  #define JOY_BTN1  16
  #define JOY_BTN2  32
#endif

// Joystick functions
#if (defined __CBM__) || (defined __ATMOS__)
  #define JOY_MAX 4
  void InitJoy(void);
  unsigned char GetJoy(unsigned char);
#elif (defined __LYNX__)
  #define JOY_MAX 1
  #define InitJoy() (PEEK(0))
  #define GetJoy(i) (~PEEK(0xfcb0))
#else
  #define JOY_MAX 2
  #define InitJoy() (PEEK(0))
  #if defined __ATARI__
    #define GetJoy(i) (PEEK(0x0278+i)+(PEEK(0x0284+i)<<4))
  #else if defined __APPLE2__
    unsigned char GetJoy(unsigned char);		
    unsigned char GetPaddle(unsigned char);
    #define GetButton(i) (PEEK(0xC061+i)>127)
  #endif
#endif

// Math functions (see math.s)
#define DOT(a,b) (a[0]*b[0]+a[1]*b[1])
unsigned char atan2(unsigned char y, unsigned char x);

// Network functions (see network.c)
#define NETWORK_OK  0
#define ADAPTOR_ERR 1
#define DHCP_ERR    2
extern unsigned int  udp_packet;
unsigned char InitNetwork(void);							// Initialize network interface and get IP from DHCP
void InitUDP(unsigned char ip1, unsigned char ip2, unsigned char ip3, unsigned char ip4, unsigned int svPort, unsigned int clPort);	// Setup UDP connection
void SendUDP(unsigned char* buffer, unsigned char length);  // Send UDP packet (of specified length)
unsigned char RecvUDP(unsigned int timeOut);				// Fetch UDP packet (within time-out period)

// Music functions
// Apple: Electric Duet player (see Apple/DUET.s) 
// Atari: RMT/SFX player (see Atari/POKEY.s)
// C64:   SID music player (see C64/SID.s)
#if defined __APPLE2__
  extern unsigned char sfxOutput;	// 0 = Speaker, 1 = Mockingboard (Slot 4)
  void InitMocking(void);
#endif
void LoadMusic(const char* filename, unsigned int address);
void PlayMusic(unsigned int address);
void StopMusic(void);

// SFX functions (see sfx.c)
void InitSFX(void);
void StopSFX(void);
void EngineSFX(int channel, int vel);
void BleepSFX(unsigned char tone);
void BumpSFX(void);

// Sprite handling functions
#if defined __APPLE2__
  #define SPRITE_NUM 8
#elif defined __ATARI__
  #define SPRITE_NUM 10
#elif defined __ATMOS__
  #define SPRITE_NUM 8
#elif defined __CBM__
  #define SPRITE_NUM 8
#elif defined __LYNX__
  #define SPRITE_NUM 8  
#endif
void InitSprites(unsigned char frames, unsigned char rows, unsigned char *spriteColors);
void EnableSprite(signed char index);
void DisableSprite(signed char index);
void LocateSprite(unsigned int x, unsigned int y);
void SetSprite(unsigned char index, unsigned char frame);

// Screen coordinates of current sprite (see LocateSprite())
#if defined __CBM__
	extern unsigned int spriteX;
	extern unsigned char spriteY;	
#else
	extern unsigned char spriteX, spriteY;
#endif

// Hardware sprite collisions on Atari, C64, Lynx
#if defined __ATARI__	
  // On Atari, we need to reset collisions by poking 0 into 53278
  #define COLLISIONS(i) (PEEK(53260+i)+(1<<i)); POKE(53278,0)
  #define COLLIDING(collisions,i) ((collisions >> i) & 1) 
#elif defined __CBM__
  // On C64, all collisions are contained within a single register
  #define COLLISIONS(i) (PEEK(53278))
  #define COLLIDING(collisions,i) ((collisions >> i) & 1) 
#elif defined __LYNX__
  // On Lynx, collisions are checked in UpdateDisplay() 
  extern unsigned char spriteCols[SPRITE_NUM];
  #define COLLISIONS(i) (spriteCols[i])
  #define COLLIDING(collisions,i) ((collisions >> i) & 1) 
// Software sprite collisions on Apple, Oric
#else
  // Collisions are checked at draw time
  extern unsigned char sprCOL[SPRITE_NUM];
  #define COLLISIONS(i) (sprCOL[i])
  #define COLLIDING(collisions,i) ((collisions >> i) & 1) 
#endif

// 8bit-Hub support (see http://www.8bit-unity.com/8bit-Hub)
#if defined __ATMOS__	// see Oric/hub.c
	unsigned char InitHub();
	extern unsigned char hubMode;		// Detect Hub Operation Mode
	extern unsigned char hubNetwork;	// Detect Hub Networking
#else
	#define InitHub()  ( 0 )
	#define hubMode		 0
	#define hubNetwork	 0
#endif
