/*
 * LED Trigger for keyboard backlight control
 *
 * Copyright 2016, Hans de Goede <hdegoede@redhat.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/leds.h>
#include "../leds.h"

static struct led_trigger kbd_backlight_trigger = {
	.name     = "kbd-backlight",
	.activate = led_trigger_add_current_brightness,
	.deactivate = led_trigger_remove_current_brightness,
};

void ledtrig_kbd_backlight(bool set_brightness, enum led_brightness brightness)
{
	if (set_brightness)
		led_trigger_event(&kbd_backlight_trigger, brightness);

	led_trigger_notify_current_brightness_change(&kbd_backlight_trigger);
}
EXPORT_SYMBOL_GPL(ledtrig_kbd_backlight);

static int __init kbd_backlight_trig_init(void)
{
	return led_trigger_register(&kbd_backlight_trigger);
}
device_initcall(kbd_backlight_trig_init);
