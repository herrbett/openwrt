/*
 *  AVM FRITZ!WLAN Repeater 1750E board support
 *
 *  Copyright (C) 2017 Mathias Kresin <dev@kresin.me>
 *  Copyright (C) 2018 David Bauer <mail@david-bauer.net>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include <linux/gpio.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>

#include "dev-ap9x-pci.h"
#include "dev-eth.h"
#include "dev-gpio-buttons.h"
#include "dev-leds-gpio.h"
#include "dev-m25p80.h"
#include "machtypes.h"

#define FRITZ1750E_KEYS_POLL_INTERVAL	 	20 /* msecs */
#define FRITZ1750E_KEYS_DEBOUNCE_INTERVAL	(3 * FRITZ300E_KEYS_POLL_INTERVAL)

static struct mtd_partition fritz1750e_flash_partitions[] = {
	{
		.name	         	= "urloader",
		.offset	      	= 0,
		.size		        = 0x0020000,
		.mask_flags	    = MTD_WRITEABLE,
	}, {
		.name       		= "firmware",
		.offset		      = 0x0020000,
		.size		        = 0x0EE0000,
	}, {
		.name		        = "tffs (1)",
		.offset	      	= 0x0f00000,
		.size		        = 0x0080000,
		.mask_flags	    = MTD_WRITEABLE,
	}, {
		.name           = "tffs (2)",
		.offset         = 0x0f80000,
		.size           = 0x0080000,
		.mask_flags     = MTD_WRITEABLE,
	}
};

static struct flash_platform_data fritz1750e_flash_data = {
	.parts		= fritz1750e_flash_partitions,
	.nr_parts	= ARRAY_SIZE(fritz1750e_flash_partitions),
};

static void __init fritz1750e_setup(void) {
	u8 *mac = (u8 *) KSEG1ADDR(0x1f610008);
	u8 tmpmac[ETH_ALEN];

	ath79_register_m25p80(&fritz1750e_flash_data);

	ath79_init_mac(tmpmac, mac, -1);

	ath79_eth0_data.phy_if_mode = PHY_INTERFACE_MODE_SGMII;
	ath79_eth0_data.mii_bus_dev = &ath79_mdio0_device.dev;
	ath79_eth0_data.phy_mask = BIT(0);

	ath79_register_mdio(0, ~BIT(0));
	ath79_setup_qca955x_eth_cfg(QCA955X_ETH_CFG_RGMII_EN);
	ath79_register_eth(0);

	ath79_register_wmac_simple();

	ath79_register_pci();
}

MIPS_MACHINE(ATH79_MACH_FRITZ1750E, "FRITZ1750E",
	     "AVM FRITZ!WLAN Repeater 1750E", fritz1750e_setup);
