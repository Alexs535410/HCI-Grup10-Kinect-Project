# Microsoft nmake-compatible makefile

OUT = BodyBasics.exe
OBJ = BodyBasics.obj
RES = BodyBasics.res

KINECT_INC = "C:\Program Files\Microsoft SDKs\Kinect\v2.0_1409\inc"
KINECT_LIB = "C:\Program Files\Microsoft SDKs\Kinect\v2.0_1409\Lib\x64"
WINSDK_INC = "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\um"

CPPFLAGS = /c /EHsc /MD /DUNICODE /D_UNICODE /I $(KINECT_INC) /I $(WINSDK_INC)
RCFLAGS = /I $(KINECT_INC)
LDFLAGS = /SUBSYSTEM:WINDOWS /MACHINE:X64 /INCREMENTAL:YES /DEBUG /LIBPATH:$(KINECT_LIB)
LIBS = Kinect20.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib

all: $(OUT)

$(OUT): $(OBJ) $(RES)
  link $(OBJ) $(RES) /OUT:$(OUT) $(LDFLAGS) $(LIBS)

$(OBJ): BodyBasics.cpp
  cl $(CPPFLAGS) BodyBasics.cpp

$(RES): BodyBasics.rc
  rc $(RCFLAGS) BodyBasics.rc

clean:
  del $(OBJ) $(RES) $(OUT)