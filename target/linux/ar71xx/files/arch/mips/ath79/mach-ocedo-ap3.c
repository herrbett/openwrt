/*
 *  Ocedo AP3 board support
 *
 *  Copyright (C) 2018
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include <linux/gpio.h>

#include <asm/mach-ath79/ath79.h>
#include <asm/mach-ath79/ar71xx_regs.h>

#include "dev-m25p80.h"
#include "dev-wmac.h"
#include "machtypes.h"


static void __init ocedo_ap3_setup(void)
{
	ath79_register_m25p80(NULL);
	ath79_register_wmac_simple();
}

MIPS_MACHINE(ATH79_MACH_OCEDO_AP3, "OCEDO-AP3", "Ocedo AP3",
	     ocedo_ap3_setup);
