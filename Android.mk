LOCAL_PATH:= $(call my-dir)

ifneq ($(BOARD_HAVE_GEN_GFX_SRC),true)

include $(CLEAR_VARS)
LOCAL_MODULE := ufo
LOCAL_MODULE_TAGS := optional
include $(BUILD_PHONY_PACKAGE)

# Always extract the tarball through a phony target
$(LOCAL_INSTALLED_MODULE): $(LOCAL_MODULE)_always_extract

.PHONY: $(LOCAL_MODULE)_always_extract
$(LOCAL_MODULE)_always_extract: PRIVATE_PATH := $(LOCAL_PATH)
$(LOCAL_MODULE)_always_extract: PRIVATE_MODULE := $(LOCAL_MODULE)
$(LOCAL_MODULE)_always_extract:
	$(hide) echo "GEN GFX: $@"
	$(hide) mkdir -p $(dir $@)
	$(hide) tar -xvf $(PRIVATE_PATH)/$(PRIVATE_MODULE).tgz -C $(PRODUCT_OUT)/

endif
