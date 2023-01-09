/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef _UTIL_H_
#define _UTIL_H_

#include <stddef.h>    
#include <stdint.h>

#include "hardware/structs/scb.h"

// works with negative index
static inline int wrap_ix(int index, int n)
{
    return ((index % n) + n) % n;
}

__attribute__((always_inline)) static inline uint32_t calculate_checksum(uint32_t const *p, size_t const size){
	uint32_t checksum = 0;
	for (uint32_t i = 0; i < (size/sizeof(uint32_t))-1; i++){
		checksum ^= *p;
		p++;
	}
	return checksum;
}


// from Google Chromium's codebase:
#ifndef COUNT_OF    
#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))
#endif

__attribute__((always_inline)) static inline void __DSB(void) {
    __asm volatile("dsb 0xF" ::: "memory");
}

// Patterned after CMSIS NVIC_SystemReset
__attribute__((__noreturn__)) static inline void system_reset() {
    __DSB(); /* Ensure all outstanding memory accesses included
         buffered write are completed before reset */
    scb_hw->aircr = ((0x5FAUL << 16U) | (1UL << 2U));
    __DSB(); /* Ensure completion of memory access */
    for (;;) {
        __asm volatile("nop");
    }
}

/**
  \brief   Disable IRQ Interrupts
  \details Disables IRQ interrupts by setting the I-bit in the CPSR.
           Can only be executed in Privileged modes.
 */
__attribute__((always_inline)) static inline void __disable_irq(void) {
    __asm volatile("cpsid i" : : : "memory");
}

#endif
/* [] END OF FILE */
