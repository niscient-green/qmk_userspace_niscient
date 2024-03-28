OLED_ENABLE = yes					# Enable OLED displays
ENCODER_ENABLE = yes	       		# Enables the use of one or more encoders
LEADER_ENABLE = no         			# Enable the Leader Key feature
MOUSEKEY_ENABLE = no				# Enable the mouse key feature
KEY_OVERRIDE_ENABLE = yes  			# Enable key overrides for things like Shift + Bksp = Del
CONVERT_TO=liatris					# Output uf2 and liatris 2040 format

# lighting
WS2812_DRIVER = vendor 				# Use the RP2040's PIO interface
RGBLIGHT_ENABLE = no 				# Enables QMK's RGB code
RGB_MATRIX_ENABLE = yes				# enable rgb matrix lighting
RGB_MATRIX_DRIVER = ws2812			# matrix lighting uses ws2812 driver (note: driver must be lower case wtf)
SPLIT_KEYBOARD = yes				# notify qmk of split