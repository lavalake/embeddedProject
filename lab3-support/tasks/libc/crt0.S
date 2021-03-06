/** @file crt0.S
 *
 * @brief Execution startup routine
 *
 * @author Mike Kasick <mkasick@andrew.cmu.edu>
 * @date   Sun, 07 Oct 2007 01:51:29 -0400
 *
 * @author Shan Gao <shang@andrew.cmu.edu>
 * @date 2014-10-30
 */

#include <asm.h>
#include <bits/swi.h>
#include <bits/errno.h>

	.file	"crt0.S"
	.text

	.global	_start
FUNC(_start)
_start:
	ldr	r0, [sp, #4]
	ldr	r1, [sp]
	bl	main
	swi	EXIT_SWI	
