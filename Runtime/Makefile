CC 				:= g++
SRCDIR 		:= .
BUILDDIR 	:= .
BIN 			:= bin
TARGET 		:= bin/jvm.exe

SRCEXT    := cpp
SOURCES   := $(wildcard $(SRCDIR)/*.$(SRCEXT))
OBJECTS   := $(subst $(SRCDIR),$(BUILDDIR),$(SOURCES:.cpp=.o))

CFLAGS := -g -std=c++11

$(TARGET): $(OBJECTS) | $(BIN)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET)"; $(CC) $^ -o $(TARGET) 

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@echo " $(CC) $(CFLAGS) -c -o $@ $<"; $(CC) $(CFLAGS) -c -o $@ $<

$(BIN):
	mkdir $@

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Tests
#tester:
#	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

.PHONY: clean


