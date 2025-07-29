.POSIX:
.SUFFIXES:

CXX=m68k-apple-macos-g++
CXXFLAGS=-std=c++98 -Wpedantic -g
LDFLAGS = -g

TARGNM	= ika
TARGET  = $(TARGNM).code.bin

all: $(TARGET) $(TARGNM).dsk

$(TARGET): Boss.o Dialog.o Draw.o Editor.o Effect.o EventScript.o FakeRect.o Flags.o Game.o Generic.o Item.o Map.o NpChar.o Opening.o PixelScript.o PiyoPiyo.o Player.o Sound.o System.o
	$(CXX) -o $@ Boss.o Dialog.o Draw.o Editor.o Effect.o EventScript.o FakeRect.o Flags.o Game.o Generic.o Item.o Map.o NpChar.o Opening.o PixelScript.o PiyoPiyo.o Player.o Sound.o System.o $(LDFLAGS)

clean:
	rm -f Boss.o Dialog.o Draw.o Editor.o Effect.o EventScript.o FakeRect.o Flags.o Game.o Generic.o Item.o Map.o NpChar.o Opening.o PixelScript.o PiyoPiyo.o Player.o Sound.o System.o $(TARGET) $(TARGNM)

# generated with <g++ -MM *.cpp>
Boss.o: Boss.cpp Boss.h Map.h NpChar.h Effect.h EventScript.h Item.h \
 PiyoPiyo.h FakeRect.h Draw.h System.h Player.h Sound.h
Dialog.o: Dialog.cpp Dialog.h System.h
Draw.o: Draw.cpp Draw.h FakeRect.h System.h
Editor.o: Editor.cpp Editor.h NpChar.h Effect.h Map.h System.h Draw.h \
 FakeRect.h EventScript.h Item.h PiyoPiyo.h Sound.h
Effect.o: Effect.cpp Effect.h System.h Draw.h FakeRect.h Map.h NpChar.h
EventScript.o: EventScript.cpp EventScript.h Map.h NpChar.h Effect.h \
 Item.h PiyoPiyo.h Draw.h FakeRect.h System.h Sound.h Flags.h Player.h \
 Game.h Editor.h Boss.h
FakeRect.o: FakeRect.cpp FakeRect.h
Flags.o: Flags.cpp Flags.h
Game.o: Game.cpp Game.h FakeRect.h Generic.h Item.h Draw.h System.h \
 Flags.h PixelScript.h PiyoPiyo.h EventScript.h Map.h NpChar.h Effect.h \
 Opening.h Player.h Editor.h Boss.h
Generic.o: Generic.cpp Generic.h Draw.h FakeRect.h System.h Sound.h \
 PixelScript.h PiyoPiyo.h
Item.o: Item.cpp Item.h Draw.h FakeRect.h System.h Player.h Map.h \
 NpChar.h Effect.h EventScript.h PiyoPiyo.h Sound.h
Map.o: Map.cpp Map.h NpChar.h Effect.h Draw.h FakeRect.h System.h \
 Player.h Boss.h EventScript.h Item.h PiyoPiyo.h
NpChar.o: NpChar.cpp NpChar.h Effect.h Draw.h FakeRect.h System.h \
 EventScript.h Map.h Item.h PiyoPiyo.h Player.h Sound.h
Opening.o: Opening.cpp Opening.h Draw.h FakeRect.h System.h
PixelScript.o: PixelScript.cpp PixelScript.h Draw.h FakeRect.h System.h \
 PiyoPiyo.h EventScript.h Map.h NpChar.h Effect.h Item.h
PiyoPiyo.o: PiyoPiyo.cpp PiyoPiyo.h Sound.h System.h
Player.o: Player.cpp Player.h Map.h NpChar.h Effect.h Draw.h FakeRect.h \
 System.h Sound.h EventScript.h Item.h PiyoPiyo.h
Sound.o: Sound.cpp Sound.h System.h
System.o: System.cpp System.h Draw.h FakeRect.h Sound.h Generic.h \
 PiyoPiyo.h Dialog.h Game.h

.SUFFIXES: .cpp .o
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

# Lifted from ClassiCube
REZFLAGS=-I$(Retro68)/RIncludes
$(TARGNM).bin $(TARGNM).APPL $(TARGNM).dsk: $(TARGET)
	Rez $(REZFLAGS) \
		--copy "$(TARGNM).code.bin" \
		"Resource/IKA.R" \
		-t "APPL" -c "????" \
		-o $(TARGNM).bin --cc $(TARGNM).APPL --cc $(TARGNM).dsk