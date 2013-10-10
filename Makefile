SHELL := /bin/bash

EXECUTABLE = HelloCpp

INCLUDES = -I.. 

SOURCES = $(shell ls *.cpp)

COCOS_ROOT = cocos2d-x-2.1.5
include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

SHAREDLIBS += -lcocos2d -lX11
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so $(LIB_DIR)/libglfw.so.3

$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c -g $< -o $@
