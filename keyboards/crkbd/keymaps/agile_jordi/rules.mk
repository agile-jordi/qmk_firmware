TAP_DANCE_ENABLE = yes

# If you want to change the display of OLED, you need to change here
# SRC +=  ./lib/glcdfont.c
# SRC +=  ./lib/rgb_state_reader.c 
# SRC +=  ./lib/layer_state_reader.c 
# SRC +=  ./lib/logo_reader.c 
# SRC +=  ./lib/keylogger.c
        # ./lib/mode_icon_reader.c \
        # ./lib/host_led_state_reader.c \
        # ./lib/timelogger.c \

SRC += oneshot.c