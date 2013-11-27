USE_BOX2D = 1
SHELL := /bin/bash

EXECUTABLE = Game

INCLUDES = -Iinclude -Icocos2d-x-2.1.5/external -Icocos2d-x-2.1.5/external/Box2D -Icocos2d-x-2.1.5/extensions -Icocos2d-x-2.1.5/external/chipmunk/include/chipmunk

SOURCES = $(shell ls src/*.cpp)

COCOS_ROOT = cocos2d-x-2.1.5
include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

CXXFLAGS+= -g

STATICLIBS += \
	$(STATICLIBS_DIR)/libcurl.a \
	$(LIB_DIR)/libextension.a \
	$(LIB_DIR)/libbox2d.a \
	$(LIB_DIR)/libchipmunk.a

SHAREDLIBS += -lcocos2d -lX11 -lXrandr
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so $(LIB_DIR)/libglfw.so.3

$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c -g $< -o $@
