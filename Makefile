# Build path
BUILD_DIR = build/zephyr

TARGET = zephyr


OPENOCD           ?= openocd
OPENOCD_INTERFACE ?= interface/stlink.cfg
OPENOCD_TARGET    ?= target/stm32f4x.cfg
OPENOCD_CMDS      ?=
LOAD_ADDRESS		       = 0x8000000


#Flash the stm.

default:
	ninja -Cbuild

flash:
	ninja -Cbuild
	$(OPENOCD) -d2 -f $(OPENOCD_INTERFACE) $(OPENOCD_CMDS) -f $(OPENOCD_TARGET) -c init -c targets -c "reset halt" \
                 -c "flash write_image erase $(BUILD_DIR)/$(TARGET).hex" \
                 -c "verify_image $(BUILD_DIR)/$(TARGET).hex" -c "reset run" -c shutdown

reset:
	$(OPENOCD) -d0 -f $(OPENOCD_INTERFACE) $(OPENOCD_CMDS) -f $(OPENOCD_TARGET) -c init -c targets -c "reset" -c shutdown

erase:
	$(OPENOCD) -d2 -f $(OPENOCD_INTERFACE) -f $(OPENOCD_TARGET) -c init -c targets -c "halt" -c "stm32f4x mass_erase 0" -c shutdown


# name of the Kconfig file
KCONFIG_FILE = configs/Kconfig

# path to save and load the config file (do not change the name KCONFIG_CONFIG ! )
KCONFIG_CONFIG=configs/.config

# path to save the .h config file
CONFIG_HEADER_PATH = configs/config.h

KCONFIGLIB_SCRIPTS_PATH = robotics_lib/python_scripts/kconfiglib


menuconfig:
	$(kpython) $(KCONFIGLIB_SCRIPTS_PATH)/menuconfig.py $(KCONFIG_FILE)

guiconfig:
	$(kpython) $(KCONFIGLIB_SCRIPTS_PATH)/guiconfig.py $(KCONFIG_FILE)

genconfig:
	$(kpython) $(KCONFIGLIB_SCRIPTS_PATH)/genconfig.py $(KCONFIG_FILE) --header-path $(CONFIG_HEADER_PATH)






