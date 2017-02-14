CC 				:= g++
SRCDIR 		:= .
BUILDDIR 	:= .
BIN 			:= bin
TARGET 		:= bin/jvm.exe
TARGET2 	:= ./bin/jvm.exe

SRCEXT    := cpp
SOURCES   := $(wildcard $(SRCDIR)/operands/*.$(SRCEXT)) $(wildcard $(SRCDIR)/*.$(SRCEXT)) 
OBJECTS   := $(subst $(SRCDIR),$(BUILDDIR),$(SOURCES:.cpp=.o))

CFLAGS := -g -std=c++11

$(TARGET): $(OBJECTS) | $(BIN)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET)"; $(CC) $^ -o $(TARGET) 

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR) $(BUILDDIR)/operands
	@echo " $(CC) $(CFLAGS) -c -o $@ $<"; $(CC) $(CFLAGS) -c -o $@ $<

$(BIN):
	mkdir $@

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(TARGET2)"; $(RM) -r $(TARGET2)

.PHONY: clean


