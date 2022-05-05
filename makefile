CC = C:/MinGW/bin/g++.exe

CPP_STANDARD = 17

CFLAGS = -Wall -Werror -Wextra -pedantic --std=c++$(CPP_STANDARD) -O3 \
         -Wl,-u,___mingw_vsnprintf -Wl,--defsym,___ms_vsnprintf=___mingw_vsnprintf

INCLUDES = -I./src/ -I./src/include/ -I./Dependencies/GLFW32/include/ \
		   -I./Dependencies/glm/ -I./Dependencies/glad/include/ -I./Dependencies/stb/ \
		   -I./Dependencies/ImGui/include

LIBS = -lglfw3 -limgui -lopengl32 -lgdi32 -luser32 -lshell32 -lkernel32
LIB_DIRS = -L./Dependencies/GLFW32/lib-mingw-w64/ -L./Dependencies/ImGui/lib

BASE_CMD = $(CC) $(CFLAGS) $(INCLUDES) $(LIB_DIRS)
ALL_OBJ_FILES = ./obj-files/glad.obj ./obj-files/stb_image.obj ./obj-files/glMessageCallback.obj \
			    ./obj-files/IndexBuffer.obj ./obj-files/Shader.obj ./obj-files/Texture2D.obj \
				./obj-files/VertexArray.obj ./obj-files/VertexBuffer.obj ./obj-files/main.obj \
				./obj-files/Renderer.obj

ALL_LABELS = ./obj-files/glad.obj ./obj-files/stb_image.obj ./obj-files/glMessageCallback.obj \
		     ./obj-files/IndexBuffer.obj ./obj-files/Shader.obj ./obj-files/Texture2D.obj  \
			 ./obj-files/VertexArray.obj ./obj-files/VertexBuffer.obj ./obj-files/main.obj \
			 ./Dependencies/ImGui/libimgui.a ./obj-files/Renderer.obj


main.exe: $(ALL_LABELS)
	$(BASE_CMD) -o main.exe $(ALL_OBJ_FILES) $(LIBS)

./obj-files/glad.obj: 
	$(BASE_CMD) -c -o ./obj-files/glad.obj Dependencies/glad/src/glad.cpp

./obj-files/stb_image.obj: Dependencies/stb/stb_image.cpp Dependencies/stb/stb_image.h
	$(BASE_CMD) -c -o ./obj-files/stb_image.obj Dependencies/stb/stb_image.cpp

./obj-files/main.obj: src/main.cpp
	$(BASE_CMD) -c -o ./obj-files/main.obj src/main.cpp

./obj-files/Renderer.obj: src/Renderer.cpp
	$(BASE_CMD) -c -o ./obj-files/Renderer.obj src/Renderer.cpp

./obj-files/glMessageCallback.obj: src/include/glMessageCallback.hpp src/glMessageCallback.cpp
	$(BASE_CMD) -c -o ./obj-files/glMessageCallback.obj src/glMessageCallback.cpp

./obj-files/IndexBuffer.obj: src/IndexBuffer.cpp src/include/IndexBuffer.hpp
	$(BASE_CMD) -c -o ./obj-files/IndexBuffer.obj src/IndexBuffer.cpp

./obj-files/Shader.obj: src/Shader.cpp src/include/Shader.hpp
	$(BASE_CMD) -c -o ./obj-files/Shader.obj src/Shader.cpp

./obj-files/Texture2D.obj: src/Texture2D.cpp src/include/Texture2D.hpp
	$(BASE_CMD) -c -o ./obj-files/Texture2D.obj src/Texture2D.cpp
	
./obj-files/VertexArray.obj: src/VertexBuffer.cpp src/include/VertexBuffer.hpp src/VertexArray.cpp src/include/VertexArray.hpp
	$(BASE_CMD) -c -o ./obj-files/VertexArray.obj src/VertexArray.cpp

./obj-files/VertexBuffer.obj: src/VertexBuffer.cpp src/include/VertexBuffer.hpp
	$(BASE_CMD) -c -o ./obj-files/VertexBuffer.obj src/VertexBuffer.cpp

include makefiles/imgui.in

clean:
	rm -rf ./obj-files/
	rm main.exe
	rm Dependencies/imgui.libimgui.a
