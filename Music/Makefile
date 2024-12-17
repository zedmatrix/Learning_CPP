CXX = g++ -std=c++20
CXXFLAGS = -lpulse-simple -lpulse -lm
INCLUDE = -I./include
BINDIR = ./bin
SRCDIR = ./src

.PHONY: default piano2 piano1 check clean

default:
	@echo "My Pulseaudio Programs"
	@echo "make		Show This Help Message"
	@echo "make check	Verify and Create Necessary Directories"
	@echo "make piano2	New Version with Flats and Inkey"
	@echo "make piano1	First Version prototype"
	@echo "make piano	Creates Both Versions"
	@echo "make music	An Experimental Version that is Automatic"
	@echo "make chord	An Experimental Version that is Automatic"

check:
	@echo "Checking directories..."
	@[ -d $(SRCDIR) ] || (echo "Creating $(SRCDIR)"; mkdir -p $(SRCDIR))
	@[ -d $(BINDIR) ] || (echo "Creating $(BINDIR)"; mkdir -p $(BINDIR))
	@echo "All directories are in place."

piano: $(BINDIR)/piano1 $(BINDIR)/piano2

$(BINDIR)/piano1: $(SRCDIR)/piano1.cpp
	mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $< -o $@

$(BINDIR)/piano2: $(SRCDIR)/piano2.cpp
	mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $< -o $@

music: $(BINDIR)/music

$(BINDIR)/music: $(SRCDIR)/music.cpp
	mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $< -o $@

chord: $(BINDIR)/chord

$(BINDIR)/chord: $(SRCDIR)/chord.cpp
	mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $< -o $@

clean:
	rm -f $(BINDIR)
