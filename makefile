CXX = g++
CXXFLAGS = -Wall $(LFLAGS) -std=c++11 -I $(IDIR)
LFLAGS = -F/Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf -framework SDL2_mixer
EXE = game

SDIR = src
RDIR = rel
DDIR = dbg
IDIR = include

SRCS = main.cpp renderer.cpp texture.cpp Entity.cpp Player.cpp level.cpp monster.cpp bullet.cpp poof.cpp
OBJS = $(SRCS:%.cpp=%.o)
RLS = $(addprefix $(RDIR)/, $(OBJS))
DBG = $(addprefix $(DDIR)/, $(OBJS))

.PHONY: all clean

all: $(EXE)

$(EXE): $(RLS)
	$(CXX) $^ -o $@ $(CXXFLAGS)

$(RDIR)/%.o : $(SDIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(DDIR)/%.o : $(SDIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $< -o $@ $(CXXFLAGS) -g -O0

clean:
	rm -f $(RLS) $(DBG) $(EXE)

debug: $(DBG)
	$(CXX) -g -O0 $^ -o $(EXE) $(CXXFLAGS)
