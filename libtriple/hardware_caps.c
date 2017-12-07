/*
 * determine the capabilities of the hardware.
 * part of libstb-hal
 *
 * (C) 2010-2012,2016 Stefan Seyfried
 *
 * License: GPL v2 or later
 */

#include "hardware_caps.h"

static hw_caps_t caps = {
	.has_fan = 0,
	.has_SCART = 1,
	.has_SCART_input = 1,
	.has_HDMI = 0,
	.has_YUV_cinch = 0,
	.can_shutdown = 0,
	.can_cec = 0,
	.can_ar_14_9 = 0,
	.can_ps_14_9 = 1,
	.force_tuner_2G = 0,
	.display_type = HW_DISPLAY_GFX,
	.display_xres = 128,
	.display_yres = 64,
	.display_has_statusline = 0,
	.display_can_deepstandby = 0;
	.display_can_set_brightness = 0;
	.boxvendor = "Armas",
	.boxname = "TripleDragon",
	.boxarch = "ppc405"
};

hw_caps_t *get_hwcaps(void)
{
	return &caps;
}
