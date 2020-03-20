#include "assembly.h"

		.data
soundState:	.byte,0	
		.arch msp430g2553
		.p2align 1,0
		.text

		.global sound_speed

sound_speed:	nop
		add #1, &soundState
		xor #3, &soundState
		ret

