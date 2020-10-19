LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)


LOCAL_SRC_FILES:= \
	spidev_fdx.c

LOCAL_MODULE:= spidev_fdx
LOCAL_C_FLAGS += -Wnosign-compare

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)


LOCAL_SRC_FILES:= \
	spidev_test.c

LOCAL_MODULE:= spidev_test
LOCAL_C_FLAGS += -Wnosign-compare

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)


LOCAL_SRC_FILES:= \
	spiRead_test.c

LOCAL_MODULE:= spiRead_test
LOCAL_C_FLAGS += -Wnosign-compare

include $(BUILD_EXECUTABLE)
