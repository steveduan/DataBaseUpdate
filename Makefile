PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OBJS = MyPro.o

BUILD_MODE = debug

Include  = C:\MinGW\include

Lib_dir = C:\MinGW\lib

libs = $(Lib_dir)\libwinmm.a

ifeq ($(BUILD_MODE),debug)
	CFLAGS += -g
else ifeq ($(BUILD_MODE),run)
	CFLAGS += -O2
else ifeq ($(BUILD_MODE),linuxtools)
	CFLAGS += -g -pg -fprofile-arcs -ftest-coverage
	LDFLAGS += -pg -fprofile-arcs -ftest-coverage
	EXTRA_CLEAN += MyPro.gcda MyPro.gcno $(PROJECT_ROOT)gmon.out
	EXTRA_CMDS = rm -rf MyPro.gcda
else
    $(error Build mode $(BUILD_MODE) not supported by this Makefile)
endif

all:	MyPro

MyPro:	$(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ -I $(Include) -L $(Lib_dir) $(libs)
	$(EXTRA_CMDS)

%.o:	$(PROJECT_ROOT)%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $< 

%.o:	$(PROJECT_ROOT)%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	del -fr MyPro $(OBJS) MyPro.exe
	
INFO:
	@echo "libs $(libs)" 
	@echo "include $(Include)"