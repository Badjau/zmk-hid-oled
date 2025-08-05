if(CONFIG_HID_OLED)
    zephyr_library()
    zephyr_library_sources(display.c)
endif()