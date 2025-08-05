#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/init.h>
#include <zmk/display.h>
#include <zmk/widgets/battery_status.h>
#include <zmk/widgets/output_status.h>
#include <zmk/widgets/layer_status.h>

static lv_obj_t *battery_widget;
static lv_obj_t *output_widget;
static lv_obj_t *layer_widget;

static int display_app_init(void)
{
    const struct device *display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
    if (!device_is_ready(display_dev)) {
        return -ENODEV;
    }

    lv_obj_t *screen = lv_scr_act();

    // Battery widget
    battery_widget = zmk_widget_battery_status_create(screen);
    lv_obj_align(battery_widget, LV_ALIGN_TOP_RIGHT, -2, 2);

    // Output (connection) status widget
    output_widget = zmk_widget_output_status_create(screen);
    lv_obj_align(output_widget, LV_ALIGN_TOP_LEFT, 2, 2);

    // Layer widget
    layer_widget = zmk_widget_layer_status_create(screen);
    lv_obj_align(layer_widget, LV_ALIGN_BOTTOM_MID, 0, -2);

    return 0;
}

SYS_INIT(display_app_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
