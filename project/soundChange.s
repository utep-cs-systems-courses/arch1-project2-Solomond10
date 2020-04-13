#include "soundChange.h"

	.arch msp430g2553
	.p2align 1,0
	
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
	mov &soundState, r12	;moves soundState into r12
	cmp #6, r12	 	;range check
	jc esac			
	add r12, r12		;add r12 into r12 because its a word
	mov JT(r12), r0		;moves the jumps table into the program counter so that the counter 				   ;begins at the beginning of the jump table
	
caselow:
	mov #200, r12		;set buzzer's period 200
	call #buzzer_set_period	;calls buzzer_set_period method(200)
	mov #1, &soundState	;Sets soundState = 1 so it can transition to the next case
	jmp esac		;break
	
caselow_moderate:
	mov #400, r12		;set buzzer's period 400
	call #buzzer_set_period	;calls buzzer_set_period method(400)
	mov #2, &soundState	;Sets soundState = 2 so it can transition to the next case
	jmp esac		;break
	
casemoderate:
	mov #575, r12		;set buzzer's period 575
	call #buzzer_set_period	;calls buzzer_set_period method(575)
	mov #3, &soundState	;Sets soundState = 3 so it can transition to the next case
	jmp esac		;break

caselow_high:
	mov #750, r12		;set buzzer's period 750
	call #buzzer_set_period	;calls buzzer_set_period method(750)
	mov #4, &soundState	;Sets soundState = 4 so it can transition to the next case
	jmp esac		;break
	

casemoderate_high:
	mov #900, r12		;set buzzer's period 900
	call #buzzer_set_period	;calls buzzer_set_period method(900)
	mov #5, &soundState	;Sets soundState = 5 so it can transition to the next case
	jmp esac		;break
	

casevery_high:
	mov #1500, r12		;set buzzer's period 1500
	call #buzzer_set_period	;calls buzzer_set_period method(1500)
	mov #0, &soundState	;Sets soundState = 0 so it can transition to the next case
	jmp esac		;break

esac:
	pop r0
