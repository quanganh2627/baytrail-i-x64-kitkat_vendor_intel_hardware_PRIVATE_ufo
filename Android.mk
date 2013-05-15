ifneq ($(BOARD_HAVE_GEN_GFX_SRC),true)

LOCAL_PATH:= $(call my-dir)

UFO_PROJECT_PATH := $(LOCAL_PATH)

include $(CLEAR_VARS)

LOCAL_MODULE := ufo
LOCAL_MODULE_TAGS := optional

# libastl - From external/asti, required for building these packages.
LOCAL_STATIC_LIBRARIES := libastl

# Replace $(BUILD_PHONY_PACKAGE) with a kludge that will generate
# pre-requisites for the package, particularly $(LOCAL_STATIC_LIBRARIES).
# Note: Variable "all_libraries" is a build system internal variable.

## include $(BUILD_PHONY_PACKAGE)

# ------------------------------------------------------------------------
LOCAL_MODULE_CLASS := FAKE
LOCAL_MODULE_SUFFIX := -timestamp

include $(BUILD_SYSTEM)/binary.mk

$(LOCAL_BUILT_MODULE): $(all_libraries)

$(LOCAL_BUILT_MODULE):
	$(hide) echo "Fake: $@"
	$(hide) mkdir -p $(dir $@)
	$(hide) touch $@

# ------------------------------------------------------------------------

$(LOCAL_INSTALLED_MODULE): $(LOCAL_MODULE)_always_extract

.PHONY: $(LOCAL_MODULE)_always_extract

$(LOCAL_MODULE)_always_extract: PRIVATE_PATH := $(LOCAL_PATH)

$(LOCAL_MODULE)_always_extract:
	@ echo "$(UFO_PROJECT_PATH): GEN GFX: $@"
	$(hide) mkdir -p $(dir $@)
	$(hide) $(PRIVATE_PATH)/dist_install.sh $(PRIVATE_PATH)/dist $(PRODUCT_OUT)

endif
