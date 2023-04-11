# Configure compiler.
CXX ?= g++

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Configure compile flags.
CXXFLAGS ?= -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ 				   \
			-Wc++14-compat 				   \
			-Wmissing-declarations -Wcast-align -Wcast-qual 			   \
			-Wchar-subscripts \
			-Wconversion -Wctor-dtor-privacy -Wempty-body 				   \
			-Wfloat-equal -Wformat-nonliteral -Wformat-security 		   \
			-Wformat=2 -Winline \
			-Wnon-virtual-dtor -Woverloaded-virtual 		   \
			-Wpacked -Wpointer-arith -Winit-self -Wredundant-decls		   \
			-Wshadow -Wsign-conversion -Wsign-promo \
			-Wstrict-overflow=2 \
			\
			-Wsuggest-override -Wswitch-default -Wswitch-enum \
			-Wundef -Wunreachable-code -Wunused \
			-Wvariadic-macros \
			-Wno-missing-field-initializers -Wno-narrowing 				   \
			-Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new \
			-fsized-deallocation -fstack-protector -fstrict-overflow 	   \
			-fno-omit-frame-pointer -fPIE 	   \

# Configure linker flags.
LINKFLAGS ?= 

# Configure program perfomance boost flags.
FASTFLAGS ?= 

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Configure directory flags.
DIRFLAGS ?= 

# Configure sources you need to compile.
SOURCES  ?= main.cpp 			\
            ./List/List.cpp             \
	    ./HashTable/HashTable.cpp 	\
	    ./Logs/Loglib.cpp

# Configure sources dependencies.
DEPENDS  ?= 				\
	    ./HashTable/HashTable.hpp   \
	    ./List/AltList.h 		\
	    ./Logs/LogLib.h

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Configure object directory name.
OBJDIR ?= ./Objects/

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Pick executable name.
EXECUTABLE ?= main

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# WARNING: Don't change values and commands below.

# Making objects names from sources names.
OBJECTS = $(patsubst %.cpp, $(OBJDIR)%.o, $(SOURCES)) 

# Adding directory flags to compiler flags.
CXXFLAGS += $(DIRFLAGS)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.PHONY: all
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(DEPENDS)
	@echo "Making executable from objects;"
	@$(CXX) $(OBJECTS) -o $@ $(LINKFLAGS)
	@echo "Done;"

$(OBJDIR)%.o: %.cpp
	@mkdir -p $(@D)
	@echo "Making object file from $<;"
	@$(CXX) -c $(CXXFLAGS) $(FASTFLAGS) $^ -o $@

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.PHONY: clear
clear:
	@echo "Clearing object files and executables;";
	@rm -rf $(OBJDIR) $(EXECUTABLE)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
