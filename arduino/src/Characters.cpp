#include <Arduino.h>
#include "Characters.h"

void Characters::draw(byte * canvas, byte * patterns, byte patternHeight, byte patternWidth, short characterCode, short targetX, short targetY) {
	if (targetX <= -patternWidth || targetY <= -patternHeight || targetX >= 32 || targetY >= 8)
		return; // basic bounds check
	byte * patternOffset = patterns + characterCode * patternHeight;
	for (int y = 0; y < patternHeight; y ++) {
		short destRow = targetY + y;
		if (destRow < 0 || destRow >= 8)
			continue;
		for (int x = 0; x < patternWidth; x ++) {
			short destColumn = x + targetX;
			if (destColumn < 0 || destColumn >= 32)
				continue;
			byte * destByte = canvas + destRow * 4 + (destColumn >> 3);
			byte destBit = 1 << (destColumn & 7);
			byte patternTestBit = 1 << (patternWidth - x - 1);
			if (*patternOffset & patternTestBit) {
				*destByte |= destBit;
			}
		}
		patternOffset ++;
	}
}