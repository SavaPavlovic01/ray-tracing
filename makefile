FILE_OUT = pic.ppm

OUTPUT = pic.exe

c_files = src/main.cpp \
src/vec3.cpp



h_files=$(addprefix inc/,$(notdir $(c_files:.cpp=.hpp)))


compiler_flags=-g -Wall -Wextra

all: $(c_files) $(h_files)
	g++ $(c_files)  $(compiler_flags) -o $(OUTPUT) 
	

run:
	./$(OUTPUT) > $(FILE_OUT)	

clean:
	rm -rf $(OUTPUT)

eval:
	gcc src/eval.c -mwindows -g -o eval.exe

gui:
	g++ $(c_files) src/gui.cpp src/Window.cpp $(compiler_flags) $(linker_flags) $(include_path) $(library_path) -o gui.exe 

.PHONY: all run