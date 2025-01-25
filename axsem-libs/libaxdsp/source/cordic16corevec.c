#include "libaxdsp.h"

#if STAGES==2
#define cordic16_core_vec cordic16_core_vec2
#elif STAGES==3
#define cordic16_core_vec cordic16_core_vec3
#elif STAGES==4
#define cordic16_core_vec cordic16_core_vec4
#elif STAGES==5
#define cordic16_core_vec cordic16_core_vec5
#elif STAGES==6
#define cordic16_core_vec cordic16_core_vec6
#elif STAGES==7
#define cordic16_core_vec cordic16_core_vec7
#elif STAGES==8
#define cordic16_core_vec cordic16_core_vec8
#elif STAGES==9
#define cordic16_core_vec cordic16_core_vec9
#elif STAGES==10
#define cordic16_core_vec cordic16_core_vec10
#elif STAGES==11
#define cordic16_core_vec cordic16_core_vec11
#elif STAGES==12
#define cordic16_core_vec cordic16_core_vec12
#elif STAGES==13
#define cordic16_core_vec cordic16_core_vec13
#elif STAGES==14
#define cordic16_core_vec cordic16_core_vec14
#elif STAGES==15
#define cordic16_core_vec cordic16_core_vec15
#else
#error "invalid STAGES value"
#endif

#if defined(SDCC)

// dec2hex(round(arg(1+i*2.^-(0:15))/2/pi*2^16))
// 0x2000, 0x12E4, 0x09FB, 0x0511, 0x028B, 0x0146, 0x00A3, 0x0051
// 0x0029, 0x0014, 0x000A, 0x0005, 0x0003, 0x0001, 0x0001, 0x0000

__reentrantb uint16_t cordic16_core_vec(uint16_t phase) __reentrant
{
	// special calling conventions!
	// R3:R2: I
	// R5:R4: Q
	// DPTR: phase
	__asm
	;; unrolled
	;; pre stage
	mov	a,r3
	jnb	acc.7,00000$
	clr	c
	clr	a
	subb	a,r2
	mov	r2,a
	clr	a
	subb	a,r3
	mov	r3,a
	clr	c
	clr	a
	subb	a,r4
	mov	r4,a
	clr	a
	subb	a,r5
	mov	r5,a
	mov	a,dph
	xrl	a,#0x80
	mov	dph,a
00000$:
	__endasm;
#if STAGES >= 0
	__asm
	;; stage 0
	mov	a,r5
	jnb	acc.7,00004$
	clr	c
	mov	a,r2
	mov	r0,a
	subb	a,r4
	mov	r2,a
	mov	a,r3
	mov	r1,a
	subb	a,r5
	mov	r3,a
	mov	a,r4
	add	a,r0
	mov	r4,a
	mov	a,r5
	addc	a,r1
	mov	r5,a
	mov	a,dph
	add	a,#(-0x2000)>>8
	mov	dph,a
	sjmp	00005$
00004$:	mov	a,r2
	mov	r0,a
	add	a,r4
	mov	r2,a
	mov	a,r3
	mov	r1,a
	addc	a,r5
	mov	r3,a
	clr	c
	mov	a,r4
	subb	a,r0
	mov	r4,a
	mov	a,r5
	subb	a,r1
	mov	r5,a
	mov	a,dph
	add	a,#0x2000>>8
	mov	dph,a
00005$:
	__endasm;
#endif
#if STAGES >= 1
	__asm
	;; stage 1
	mov	a,r3
	mov	c,acc.7
	rrc	a
	mov	r1,a
	mov	a,r2
	rrc	a
	mov	r0,a
	mov	a,r5
	mov	c,acc.7
	rrc	a
	mov	r7,a
	mov	a,r4
	rrc	a
	mov	r6,a
	mov	a,r5
	jnb	acc.7,00008$
	clr	c
	mov	a,r2
	subb	a,r6
	mov	r2,a
	mov	a,r3
	subb	a,r7
	mov	r3,a
	mov	a,r4
	add	a,r0
	mov	r4,a
	mov	a,r5
	addc	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#-0x12E4
	mov	dpl,a
	mov	a,dph
	addc	a,#(-0x12E4)>>8
	mov	dph,a
	sjmp	00009$
00008$:	mov	a,r2
	add	a,r6
	mov	r2,a
	mov	a,r3
	addc	a,r7
	mov	r3,a
	clr	c
	mov	a,r4
	subb	a,r0
	mov	r4,a
	mov	a,r5
	subb	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#0x12E4
	mov	dpl,a
	mov	a,dph
	addc	a,#(0x12E4>>8)
	mov	dph,a
00009$:
	__endasm;
#endif
#if STAGES >= 2
	__asm
	;; stage 2
	mov	a,r2
	rr	a
	rr	a
	anl	a,#0x3f
	mov	r0,a
	mov	a,r3
	rr	a
	rr	a
	mov	r1,a
	anl	a,#0xc0
	orl	a,r0
	mov	r0,a
	mov	a,r1
	anl	a,#0x3f
	mov	r1,a
	mov	a,r3
	rlc	a
	subb	a,acc
	anl	a,#0xc0
	orl	a,r1
	mov	r1,a
	mov	a,r4
	rr	a
	rr	a
	anl	a,#0x3f
	mov	r6,a
	mov	a,r5
	rr	a
	rr	a
	mov	r7,a
	anl	a,#0xc0
	orl	a,r6
	mov	r6,a
	mov	a,r7
	anl	a,#0x3f
	mov	r7,a
	mov	a,r5
	rlc	a
	subb	a,acc
	anl	a,#0xc0
	orl	a,r7
	mov	r7,a
	mov	a,r5
	jnb	acc.7,00012$
	clr	c
	mov	a,r2
	subb	a,r6
	mov	r2,a
	mov	a,r3
	subb	a,r7
	mov	r3,a
	mov	a,r4
	add	a,r0
	mov	r4,a
	mov	a,r5
	addc	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#-0x09FB
	mov	dpl,a
	mov	a,dph
	addc	a,#(-0x09FB)>>8
	mov	dph,a
	sjmp	00013$
00012$:	mov	a,r2
	add	a,r6
	mov	r2,a
	mov	a,r3
	addc	a,r7
	mov	r3,a
	clr	c
	mov	a,r4
	subb	a,r0
	mov	r4,a
	mov	a,r5
	subb	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#0x09FB
	mov	dpl,a
	mov	a,dph
	addc	a,#(0x09FB>>8)
	mov	dph,a
00013$:
	__endasm;
#endif
#if STAGES >= 3
	__asm
	;; stage 3
	mov	a,r2
	swap	a
	rl	a
	anl	a,#0x1f
	mov	r0,a
	mov	a,r3
	swap	a
	rl	a
	mov	r1,a
	anl	a,#0xe0
	orl	a,r0
	mov	r0,a
	mov	a,r1
	anl	a,#0x1f
	mov	r1,a
	mov	a,r3
	rlc	a
	subb	a,acc
	anl	a,#0xe0
	orl	a,r1
	mov	r1,a
	mov	a,r4
	swap	a
	rl	a
	anl	a,#0x1f
	mov	r6,a
	mov	a,r5
	swap	a
	rl	a
	mov	r7,a
	anl	a,#0xe0
	orl	a,r6
	mov	r6,a
	mov	a,r7
	anl	a,#0x1f
	mov	r7,a
	mov	a,r5
	rlc	a
	subb	a,acc
	anl	a,#0xe0
	orl	a,r7
	mov	r7,a
	mov	a,r5
	jnb	acc.7,00016$
	clr	c
	mov	a,r2
	subb	a,r6
	mov	r2,a
	mov	a,r3
	subb	a,r7
	mov	r3,a
	mov	a,r4
	add	a,r0
	mov	r4,a
	mov	a,r5
	addc	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#-0x0511
	mov	dpl,a
	mov	a,dph
	addc	a,#(-0x0511)>>8
	mov	dph,a
	sjmp	00017$
00016$:	mov	a,r2
	add	a,r6
	mov	r2,a
	mov	a,r3
	addc	a,r7
	mov	r3,a
	clr	c
	mov	a,r4
	subb	a,r0
	mov	r4,a
	mov	a,r5
	subb	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#0x0511
	mov	dpl,a
	mov	a,dph
	addc	a,#(0x0511>>8)
	mov	dph,a
00017$:
	__endasm;
#endif
#if STAGES >= 4
	__asm
	;; stage 4
	mov	a,r2
	swap	a
	anl	a,#0x0f
	mov	r0,a
	mov	a,r3
	swap	a
	mov	r1,a
	anl	a,#0xf0
	orl	a,r0
	mov	r0,a
	mov	a,r1
	anl	a,#0x0f
	mov	r1,a
	mov	a,r3
	rlc	a
	subb	a,acc
	anl	a,#0xf0
	orl	a,r1
	mov	r1,a
	mov	a,r4
	swap	a
	anl	a,#0x0f
	mov	r6,a
	mov	a,r5
	swap	a
	mov	r7,a
	anl	a,#0xf0
	orl	a,r6
	mov	r6,a
	mov	a,r7
	anl	a,#0x0f
	mov	r7,a
	mov	a,r5
	rlc	a
	subb	a,acc
	anl	a,#0xf0
	orl	a,r7
	mov	r7,a
	mov	a,r5
	jnb	acc.7,00020$
	clr	c
	mov	a,r2
	subb	a,r6
	mov	r2,a
	mov	a,r3
	subb	a,r7
	mov	r3,a
	mov	a,r4
	add	a,r0
	mov	r4,a
	mov	a,r5
	addc	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#-0x028B
	mov	dpl,a
	mov	a,dph
	addc	a,#(-0x028B)>>8
	mov	dph,a
	sjmp	00021$
00020$:	mov	a,r2
	add	a,r6
	mov	r2,a
	mov	a,r3
	addc	a,r7
	mov	r3,a
	clr	c
	mov	a,r4
	subb	a,r0
	mov	r4,a
	mov	a,r5
	subb	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#0x028B
	mov	dpl,a
	mov	a,dph
	addc	a,#(0x028B>>8)
	mov	dph,a
00021$:
	__endasm;
#endif
#if STAGES >= 5
	__asm
	;; stage 5
	mov	a,r2
	swap	a
	rr	a
	anl	a,#0x07
	mov	r0,a
	mov	a,r3
	swap	a
	rr	a
	mov	r1,a
	anl	a,#0xf8
	orl	a,r0
	mov	r0,a
	mov	a,r1
	anl	a,#0x07
	mov	r1,a
	mov	a,r3
	rlc	a
	subb	a,acc
	anl	a,#0xf8
	orl	a,r1
	mov	r1,a
	mov	a,r4
	swap	a
	rr	a
	anl	a,#0x07
	mov	r6,a
	mov	a,r5
	swap	a
	rr	a
	mov	r7,a
	anl	a,#0xf8
	orl	a,r6
	mov	r6,a
	mov	a,r7
	anl	a,#0x07
	mov	r7,a
	mov	a,r5
	rlc	a
	subb	a,acc
	anl	a,#0xf8
	orl	a,r7
	mov	r7,a
	mov	a,r5
	jnb	acc.7,00024$
	clr	c
	mov	a,r2
	subb	a,r6
	mov	r2,a
	mov	a,r3
	subb	a,r7
	mov	r3,a
	mov	a,r4
	add	a,r0
	mov	r4,a
	mov	a,r5
	addc	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#-0x0146
	mov	dpl,a
	mov	a,dph
	addc	a,#(-0x0146)>>8
	mov	dph,a
	sjmp	00025$
00024$:	mov	a,r2
	add	a,r6
	mov	r2,a
	mov	a,r3
	addc	a,r7
	mov	r3,a
	clr	c
	mov	a,r4
	subb	a,r0
	mov	r4,a
	mov	a,r5
	subb	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#0x0146
	mov	dpl,a
	mov	a,dph
	addc	a,#(0x0146>>8)
	mov	dph,a
00025$:
	__endasm;
#endif
#if STAGES >= 6
	__asm
	;; stage 6
	mov	a,r2
	rl	a
	rl	a
	anl	a,#0x03
	mov	r0,a
	mov	a,r3
	rl	a
	rl	a
	mov	r1,a
	anl	a,#0xfc
	orl	a,r0
	mov	r0,a
	mov	a,r1
	anl	a,#0x03
	mov	r1,a
	mov	a,r3
	rlc	a
	subb	a,acc
	anl	a,#0xfc
	orl	a,r1
	mov	r1,a
	mov	a,r4
	rl	a
	rl	a
	anl	a,#0x03
	mov	r6,a
	mov	a,r5
	rl	a
	rl	a
	mov	r7,a
	anl	a,#0xfc
	orl	a,r6
	mov	r6,a
	mov	a,r7
	anl	a,#0x03
	mov	r7,a
	mov	a,r5
	rlc	a
	subb	a,acc
	anl	a,#0xfc
	orl	a,r7
	mov	r7,a
	mov	a,r5
	jnb	acc.7,00028$
	clr	c
	mov	a,r2
	subb	a,r6
	mov	r2,a
	mov	a,r3
	subb	a,r7
	mov	r3,a
	mov	a,r4
	add	a,r0
	mov	r4,a
	mov	a,r5
	addc	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#-0x00A3
	mov	dpl,a
	mov	a,dph
	addc	a,#(-0x00A3)>>8
	mov	dph,a
	sjmp	00029$
00028$:	mov	a,r2
	add	a,r6
	mov	r2,a
	mov	a,r3
	addc	a,r7
	mov	r3,a
	clr	c
	mov	a,r4
	subb	a,r0
	mov	r4,a
	mov	a,r5
	subb	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#0x00A3
	mov	dpl,a
	mov	a,dph
	addc	a,#(0x00A3>>8)
	mov	dph,a
00029$:
	__endasm;
#endif
#if STAGES >= 7
	__asm
	;; stage 7
	mov	a,r2
	rl	a
	anl	a,#0x01
	mov	r0,a
	mov	a,r3
	rl	a
	mov	r1,a
	anl	a,#0xfe
	orl	a,r0
	mov	r0,a
	mov	a,r1
	anl	a,#0x01
	mov	r1,a
	mov	a,r3
	rlc	a
	subb	a,acc
	anl	a,#0xfe
	orl	a,r1
	mov	r1,a
	mov	a,r4
	rl	a
	anl	a,#0x01
	mov	r6,a
	mov	a,r5
	rl	a
	mov	r7,a
	anl	a,#0xfe
	orl	a,r6
	mov	r6,a
	mov	a,r7
	anl	a,#0x01
	mov	r7,a
	mov	a,r5
	rlc	a
	subb	a,acc
	anl	a,#0xfe
	orl	a,r7
	mov	r7,a
	mov	a,r5
	jnb	acc.7,00032$
	clr	c
	mov	a,r2
	subb	a,r6
	mov	r2,a
	mov	a,r3
	subb	a,r7
	mov	r3,a
	mov	a,r4
	add	a,r0
	mov	r4,a
	mov	a,r5
	addc	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#-0x0051
	mov	dpl,a
	mov	a,dph
	addc	a,#(-0x0051)>>8
	mov	dph,a
	sjmp	00033$
00032$:	mov	a,r2
	add	a,r6
	mov	r2,a
	mov	a,r3
	addc	a,r7
	mov	r3,a
	clr	c
	mov	a,r4
	subb	a,r0
	mov	r4,a
	mov	a,r5
	subb	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#0x0051
	mov	dpl,a
	mov	a,dph
	addc	a,#(0x0051>>8)
	mov	dph,a
00033$:
	__endasm;
#endif
#if STAGES >= 8
	__asm
	;; stage 8
	mov	a,r3
	mov	r0,a
	rlc	a
	subb	a,acc
	mov	r1,a
	mov	a,r5
	mov	r6,a
	rlc	a
	subb	a,acc
	mov	r7,a
	mov	a,r5
	jnb	acc.7,00036$
	clr	c
	mov	a,r2
	subb	a,r6
	mov	r2,a
	mov	a,r3
	subb	a,r7
	mov	r3,a
	mov	a,r4
	add	a,r0
	mov	r4,a
	mov	a,r5
	addc	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#-0x0029
	mov	dpl,a
	mov	a,dph
	addc	a,#(-0x0029)>>8
	mov	dph,a
	sjmp	00037$
00036$:	mov	a,r2
	add	a,r6
	mov	r2,a
	mov	a,r3
	addc	a,r7
	mov	r3,a
	clr	c
	mov	a,r4
	subb	a,r0
	mov	r4,a
	mov	a,r5
	subb	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#0x0029
	mov	dpl,a
	mov	a,dph
	addc	a,#(0x0029>>8)
	mov	dph,a
00037$:
	__endasm;
#endif
#if STAGES >= 9
	__asm
	;; stage 9
	mov	a,r3
	rlc	a
	subb	a,acc
	mov	r1,a
	mov	a,r3
	mov	c,acc.7
	rrc	a
	mov	r0,a
	mov	a,r5
	rlc	a
	subb	a,acc
	mov	r7,a
	mov	a,r5
	mov	c,acc.7
	rrc	a
	mov	r6,a
	mov	a,r5
	jnb	acc.7,00040$
	clr	c
	mov	a,r2
	subb	a,r6
	mov	r2,a
	mov	a,r3
	subb	a,r7
	mov	r3,a
	mov	a,r4
	add	a,r0
	mov	r4,a
	mov	a,r5
	addc	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#-0x0014
	mov	dpl,a
	mov	a,dph
	addc	a,#(-0x0014)>>8
	mov	dph,a
	sjmp	00041$
00040$:	mov	a,r2
	add	a,r6
	mov	r2,a
	mov	a,r3
	addc	a,r7
	mov	r3,a
	clr	c
	mov	a,r4
	subb	a,r0
	mov	r4,a
	mov	a,r5
	subb	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#0x0014
	mov	dpl,a
	mov	a,dph
	addc	a,#(0x0014>>8)
	mov	dph,a
00041$:
	__endasm;
#endif
#if STAGES >= 10
	__asm
	;; stage 10
	mov	a,r3
	rlc	a
	subb	a,acc
	mov	r1,a
	anl	a,#0xc0
	mov	r0,a
	mov	a,r3
	rr	a
	rr	a
	anl	a,#0x3f
	orl	a,r0
	mov	r0,a
	mov	a,r5
	rlc	a
	subb	a,acc
	mov	r7,a
	anl	a,#0xc0
	mov	r6,a
	mov	a,r5
	rr	a
	rr	a
	anl	a,#0x3f
	orl	a,r6
	mov	r6,a
	mov	a,r5
	jnb	acc.7,00044$
	clr	c
	mov	a,r2
	subb	a,r6
	mov	r2,a
	mov	a,r3
	subb	a,r7
	mov	r3,a
	mov	a,r4
	add	a,r0
	mov	r4,a
	mov	a,r5
	addc	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#-0x000A
	mov	dpl,a
	mov	a,dph
	addc	a,#(-0x000A)>>8
	mov	dph,a
	sjmp	00045$
00044$:	mov	a,r2
	add	a,r6
	mov	r2,a
	mov	a,r3
	addc	a,r7
	mov	r3,a
	clr	c
	mov	a,r4
	subb	a,r0
	mov	r4,a
	mov	a,r5
	subb	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#0x000A
	mov	dpl,a
	mov	a,dph
	addc	a,#(0x000A>>8)
	mov	dph,a
00045$:
	__endasm;
#endif
#if STAGES >= 11
	__asm
	;; stage 12
	mov	a,r3
	rlc	a
	subb	a,acc
	mov	r1,a
	anl	a,#0xe0
	mov	r0,a
	mov	a,r3
	swap	a
	rl	a
	anl	a,#0x1f
	orl	a,r0
	mov	r0,a
	mov	a,r5
	rlc	a
	subb	a,acc
	mov	r7,a
	anl	a,#0xe0
	mov	r6,a
	mov	a,r5
	swap	a
	rl	a
	anl	a,#0x1f
	orl	a,r6
	mov	r6,a
	mov	a,r5
	jnb	acc.7,00048$
	clr	c
	mov	a,r2
	subb	a,r6
	mov	r2,a
	mov	a,r3
	subb	a,r7
	mov	r3,a
	mov	a,r4
	add	a,r0
	mov	r4,a
	mov	a,r5
	addc	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#-0x0005
	mov	dpl,a
	mov	a,dph
	addc	a,#(-0x0005)>>8
	mov	dph,a
	sjmp	00049$
00048$:	mov	a,r2
	add	a,r6
	mov	r2,a
	mov	a,r3
	addc	a,r7
	mov	r3,a
	clr	c
	mov	a,r4
	subb	a,r0
	mov	r4,a
	mov	a,r5
	subb	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#0x0005
	mov	dpl,a
	mov	a,dph
	addc	a,#(0x0005>>8)
	mov	dph,a
00049$:
	__endasm;
#endif
#if STAGES >= 12
	__asm
	;; stage 12
	mov	a,r3
	rlc	a
	subb	a,acc
	mov	r1,a
	anl	a,#0xf0
	mov	r0,a
	mov	a,r3
	swap	a
	anl	a,#0x0f
	orl	a,r0
	mov	r0,a
	mov	a,r5
	rlc	a
	subb	a,acc
	mov	r7,a
	anl	a,#0xf0
	mov	r6,a
	mov	a,r5
	swap	a
	anl	a,#0x0f
	orl	a,r6
	mov	r6,a
	mov	a,r5
	jnb	acc.7,00052$
	clr	c
	mov	a,r2
	subb	a,r6
	mov	r2,a
	mov	a,r3
	subb	a,r7
	mov	r3,a
	mov	a,r4
	add	a,r0
	mov	r4,a
	mov	a,r5
	addc	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#-0x0003
	mov	dpl,a
	mov	a,dph
	addc	a,#(-0x0003)>>8
	mov	dph,a
	sjmp	00053$
00052$:	mov	a,r2
	add	a,r6
	mov	r2,a
	mov	a,r3
	addc	a,r7
	mov	r3,a
	clr	c
	mov	a,r4
	subb	a,r0
	mov	r4,a
	mov	a,r5
	subb	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#0x0003
	mov	dpl,a
	mov	a,dph
	addc	a,#(0x0003>>8)
	mov	dph,a
00053$:
	__endasm;
#endif
#if STAGES >= 13
	__asm
	;; stage 13
	mov	a,r3
	rlc	a
	subb	a,acc
	mov	r1,a
	anl	a,#0xf8
	mov	r0,a
	mov	a,r3
	swap	a
	rr	a
	anl	a,#0x07
	orl	a,r0
	mov	r0,a
	mov	a,r5
	rlc	a
	subb	a,acc
	mov	r7,a
	anl	a,#0xf8
	mov	r6,a
	mov	a,r5
	swap	a
	rr	a
	anl	a,#0x07
	orl	a,r6
	mov	r6,a
	mov	a,r5
	jnb	acc.7,00056$
	clr	c
	mov	a,r2
	subb	a,r6
	mov	r2,a
	mov	a,r3
	subb	a,r7
	mov	r3,a
	mov	a,r4
	add	a,r0
	mov	r4,a
	mov	a,r5
	addc	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#-0x0001
	mov	dpl,a
	mov	a,dph
	addc	a,#(-0x0001)>>8
	mov	dph,a
	sjmp	00057$
00056$:	mov	a,r2
	add	a,r6
	mov	r2,a
	mov	a,r3
	addc	a,r7
	mov	r3,a
	clr	c
	mov	a,r4
	subb	a,r0
	mov	r4,a
	mov	a,r5
	subb	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#0x0001
	mov	dpl,a
	mov	a,dph
	addc	a,#(0x0001>>8)
	mov	dph,a
00057$:
	__endasm;
#endif
#if STAGES >= 14
	__asm
	;; stage 14
	mov	a,r3
	rlc	a
	subb	a,acc
	mov	r1,a
	anl	a,#0xfc
	mov	r0,a
	mov	a,r3
	rl	a
	rl	a
	anl	a,#0x03
	orl	a,r0
	mov	r0,a
	mov	a,r5
	rlc	a
	subb	a,acc
	mov	r7,a
	anl	a,#0xfc
	mov	r6,a
	mov	a,r5
	rl	a
	rl	a
	anl	a,#0x03
	orl	a,r6
	mov	r6,a
	mov	a,r5
	jnb	acc.7,00060$
	clr	c
	mov	a,r2
	subb	a,r6
	mov	r2,a
	mov	a,r3
	subb	a,r7
	mov	r3,a
	mov	a,r4
	add	a,r0
	mov	r4,a
	mov	a,r5
	addc	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#-0x0001
	mov	dpl,a
	mov	a,dph
	addc	a,#(-0x0001)>>8
	mov	dph,a
	sjmp	00061$
00060$:	mov	a,r2
	add	a,r6
	mov	r2,a
	mov	a,r3
	addc	a,r7
	mov	r3,a
	clr	c
	mov	a,r4
	subb	a,r0
	mov	r4,a
	mov	a,r5
	subb	a,r1
	mov	r5,a
	mov	a,dpl
	add	a,#0x0001
	mov	dpl,a
	mov	a,dph
	addc	a,#(0x0001>>8)
	mov	dph,a
00061$:
	__endasm;
#endif
#if STAGES >= 15
	__asm
	;; stage 15
	mov	a,r3
	rlc	a
	subb	a,acc
	mov	r1,a
	anl	a,#0xfe
	mov	r0,a
	mov	a,r3
	rl	a
	anl	a,#0x01
	orl	a,r0
	mov	r0,a
	mov	a,r5
	rlc	a
	subb	a,acc
	mov	r7,a
	anl	a,#0xfe
	mov	r6,a
	mov	a,r5
	rl	a
	anl	a,#0x01
	orl	a,r6
	mov	r6,a
	mov	a,r5
	jnb	acc.7,00064$
	clr	c
	mov	a,r2
	subb	a,r6
	mov	r2,a
	mov	a,r3
	subb	a,r7
	mov	r3,a
	mov	a,r4
	add	a,r0
	mov	r4,a
	mov	a,r5
	addc	a,r1
	mov	r5,a
	sjmp	00065$
00064$:	mov	a,r2
	add	a,r6
	mov	r2,a
	mov	a,r3
	addc	a,r7
	mov	r3,a
	clr	c
	mov	a,r4
	subb	a,r0
	mov	r4,a
	mov	a,r5
	subb	a,r1
	mov	r5,a
00065$:
	__endasm;
#endif
}

#endif
