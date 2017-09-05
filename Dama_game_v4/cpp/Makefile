all: $(TARGET)

#compiler settings                                                               
CXX           = g++
CXXFLAGS      = -O2 -W -fPIC -g -ansi
CXXFLAGS_DBG  = -fPIC -Wall -g3 -gdwarf-2
LD            = g++
LDFLAGS       = -O2
SOFLAGS       = -shared
#LIBS          = -lRooFit -lRooStats -lTMVA -lMLP -lTreePlayer -lGed
#EXTRALIBS     = -L /usr/lib64/libgsl.so  -L /usr/lib64/libgslcblas.so

OUTPUTLOG  = logfile.txt
EXE        = dama.exe
SHAREDLIB  = libFull.so

all: $(EXE) #$(#SHAREDLIB)  

$(EXE): $(HEADERS) $(OBJS) main.o
	$(LD) $(LDFLAGS) $(LIBS) $(OBJS) main.o -o $(EXE)

$(SHAREDLIB):   $(HEADERS) $(OBJS)
	$(LD) $(LDFLAGS) $(LIBS) $(OBJS) -$(SOFLAGS) -o $(SHAREDLIB)

.PHONY clean:
clean:
	@rm -f $(OBJS) rootdict.cpp main.o $(EXE) $(SHAREDLIB)


