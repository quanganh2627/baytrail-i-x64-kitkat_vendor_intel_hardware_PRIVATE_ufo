LOCAL_PATH:= $(call my-dir)

ifneq ($(BOARD_HAVE_GEN_GFX_SRC),true)

UFO_PROJECT_PATH := $(LOCAL_PATH)

include $(CLEAR_VARS)
LOCAL_MODULE := ufo
LOCAL_MODULE_TAGS := optional
include $(BUILD_PHONY_PACKAGE)

# Always extract the tarball through a phony target
$(LOCAL_INSTALLED_MODULE): $(LOCAL_MODULE)_always_extract

.PHONY: $(LOCAL_MODULE)_always_extract
$(LOCAL_MODULE)_always_extract: PRIVATE_PATH := $(LOCAL_PATH)
$(LOCAL_MODULE)_always_extract:
	$(hide) echo "$(UFO_PROJECT_PATH): GEN GFX: $@"
	$(hide) mkdir -p $(dir $@)
	$(hide) $(PRIVATE_PATH)/dist_install.sh $(PRIVATE_PATH)/dist $(PRODUCT_OUT)

endif
