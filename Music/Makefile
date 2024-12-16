CXX = g++ -std=c++20
CXXFLAGS = -lpulse-simple -lpulse -lm
INCLUDE = -I./include
BINDIR = ./bin
SRCDIR = ./src

.PHONY: default piano check clean

default:
	@echo "My Pulseaudio Programs"
	@echo "make             will show this help message"
	@echo "make check       will verify and create necessary directories"
	@echo "make piano       will create the piano program"
	@echo "make music	will create the automatic music program"
	@echo "make noise	experimental version"


check:
	@echo "Checking directories..."
	@[ -d $(SRCDIR) ] || (echo "Creating $(SRCDIR)"; mkdir -p $(SRCDIR))
	@[ -d $(BINDIR) ] || (echo "Creating $(BINDIR)"; mkdir -p $(BINDIR))
	@echo "All directories are in place."

piano: $(BINDIR)/piano

$(BINDIR)/piano: $(SRCDIR)/piano.cpp
	mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $< -o $@

music: $(BINDIR)/music

$(BINDIR)/music: $(SRCDIR)/music.cpp
	mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $< -o $@

noise: $(BINDIR)/noise

$(BINDIR)/noise: $(SRCDIR)/noise.cpp
	mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $< -o $@

clean:
	rm -f $(BINDIR)
