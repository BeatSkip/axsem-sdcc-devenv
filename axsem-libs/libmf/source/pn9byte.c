/**
******************************************************************************
* @file
* @brief
* @internal
* @author Thomas Sailer
* $Rev: $
* $Date: $
******************************************************************************
* Copyright 2016 Semiconductor Components Industries LLC (d/b/a �ON Semiconductor�).
* All rights reserved.  This software and/or documentation is licensed by ON Semiconductor
* under limited terms and conditions.  The terms and conditions pertaining to the software
* and/or documentation are available at http://www.onsemi.com/site/pdf/ONSEMI_T&C.pdf
* (�ON Semiconductor Standard Terms and Conditions of Sale, Section 8 Software�) and
* if applicable the software license agreement.  Do not use this software and/or
* documentation unless you have carefully read and you agree to the limited terms and
* conditions.  By using this software and/or documentation, you agree to the limited
* terms and conditions.
*
* THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
* ON SEMICONDUCTOR SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL,
* INCIDENTAL, OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
* @endinternal
*
* @ingroup
*
* @details
*/

#include "libmfcrc.h"

#if defined(SDCC)

__reentrantb uint16_t pn9_advance_byte(uint16_t pn9) __reentrant __naked
{
	pn9;
	__asm
	mov	a,dph
	rrc	a
	mov	a,dpl
	rrc	a
	jnb	acc.4,00000$
	cpl	c
00000$:	rrc	a
	jnb	acc.4,00001$
	cpl	c
00001$:	rrc	a
	jnb	acc.4,00002$
	cpl	c
00002$:	rrc	a
	jnb	acc.4,00003$
	cpl	c
00003$:	rrc	a
	jnb	acc.4,00004$
	cpl	c
00004$:	rrc	a
	jnb	acc.4,00005$
	cpl	c
00005$:	rrc	a
	jnb	acc.4,00006$
	cpl	c
00006$:	rrc	a
	jnb	acc.4,00007$
	cpl	c
00007$:	mov	dpl,a
	clr	a
	rlc	a
	mov	dph,a
	ret
	__endasm;
}

#else

__reentrantb uint16_t pn9_advance_byte(uint16_t pn9) __reentrant
{
	uint8_t bits = 8;
	do {
		pn9 = (uint8_t)(pn9 >> 1) | (((pn9 << 3) ^ (pn9 << 8)) & 0x100);
	} while (--bits);
	return pn9;
}

#endif
