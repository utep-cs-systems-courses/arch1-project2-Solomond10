#include "soundChange.h"

	.data
soundState:
	.word 0

	.text
JT:	
	.word caselow
	.word caselow_moderate
	.word casemoderate
	.word caselow_high
	.word casemoderate_high
	.word casevery_high

	.global sm_sound
	
sm_sound:
	.arch msp430g2553
	.p2align 1,0
	mov &soundState, r12
	add r12, r12
	mov JT(r12), r0
	
caselow:
	mov #200, r12
	call #buzzer_set_period
	mov #1, &soundState
	jmp esac
	
caselow_moderate:
	mov #400, r12
	call #buzzer_set_period
	mov #2, &soundState
	jmp esac
	
casemoderate:
	mov #575, r12
	call #buzzer_set_period
	mov #3, &soundState
	jmp esac

caselow_high:
	mov #750, r12
	call #buzzer_set_period
	mov #4, &soundState
	jmp esac
	

casemoderate_high:
	mov #900, r12
	call #buzzer_set_period
	mov #5, &soundState
	jmp esac
	

casevery_high:
	mov #1500, r12
	call #buzzer_set_period
	mov #0, &soundState
	jmp esac

esac:
	pop r0
