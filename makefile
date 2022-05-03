CC = C:/MinGW/bin/g++.exe

CPP_STANDARD = 17

CFLAGS = -Wall -Werror -Wextra -pedantic --std=c++$(CPP_STANDARD) -O3 \
         -Wl,-u,___mingw_vsnprintf -Wl,--defsym,___ms_vsnprintf=___mingw_vsnprintf

INCLUDES = -I./src/ -I./src/include/ -I./Dependencies/GLFW32/include/ \
		   -I./Dependencies/glm/ -I./Dependencies/glad/include/ -I./Dependencies/stb/ \
		   -I./Dependencies/ImGui

LIBS = -lglfw3 -limgui -lopengl32 -lgdi32 -luser32 -lshell32 -lkernel32
LIB_DIRS = -L./Dependencies/GLFW32/lib-mingw-w64/ -L./Dependencies/ImGui

BASE_CMD = $(CC) $(CFLAGS) $(INCLUDES) $(LIB_DIRS)
ALL_OBJ_FILES = ./obj-files/glad.obj ./obj-files/stb_image.obj ./obj-files/glMessageCallback.obj \
			    ./obj-files/IndexBuffer.obj ./obj-files/Shader.obj ./obj-files/Texture.obj \
				./obj-files/VertexArray.obj ./obj-files/VertexBuffer.obj ./obj-files/main.obj \
				./Dependencies/ImGui/libimgui.a

ALL_LABELS = ./obj-files/glad.obj ./obj-files/stb_image.obj ./obj-files/glMessageCallback.obj \
		     ./obj-files/IndexBuffer.obj ./obj-files/Shader.obj ./obj-files/Texture.obj  \
			 ./obj-files/VertexArray.obj ./obj-files/VertexBuffer.obj ./obj-files/main.obj \
			 ./Dependencies/ImGui/libimgui.a


main.exe: $(ALL_LABELS)
	$(BASE_CMD) -o main.exe $(ALL_OBJ_FILES) $(LIBS)

./obj-files/glad.obj: 
	$(BASE_CMD) -c -o ./obj-files/glad.obj Dependencies/glad/src/glad.cpp

./obj-files/stb_image.obj: Dependencies/stb/stb_image.cpp Dependencies/stb/stb_image.h
	$(BASE_CMD) -c -o ./obj-files/stb_image.obj Dependencies/stb/stb_image.cpp

./obj-files/main.obj: src/main.cpp
	$(BASE_CMD) -c -o ./obj-files/main.obj src/main.cpp

./obj-files/glMessageCallback.obj: src/include/glMessageCallback.hpp src/glMessageCallback.cpp
	$(BASE_CMD) -c -o ./obj-files/glMessageCallback.obj src/glMessageCallback.cpp

./obj-files/IndexBuffer.obj: src/IndexBuffer.cpp src/include/IndexBuffer.hpp
	$(BASE_CMD) -c -o ./obj-files/IndexBuffer.obj src/IndexBuffer.cpp

./obj-files/Shader.obj: src/Shader.cpp src/include/Shader.hpp
	$(BASE_CMD) -c -o ./obj-files/Shader.obj src/Shader.cpp

./obj-files/Texture.obj: src/Texture.cpp src/include/Texture.hpp
	$(BASE_CMD) -c -o ./obj-files/Texture.obj src/Texture.cpp
	
./obj-files/VertexArray.obj: src/VertexBuffer.cpp src/include/VertexBuffer.hpp src/VertexArray.cpp src/include/VertexArray.hpp
	$(BASE_CMD) -c -o ./obj-files/VertexArray.obj src/VertexArray.cpp

./obj-files/VertexBuffer.obj: src/VertexBuffer.cpp src/include/VertexBuffer.hpp
	$(BASE_CMD) -c -o ./obj-files/VertexBuffer.obj src/VertexBuffer.cpp


./obj-files/imgui.obj:
	$(BASE_CMD) -c -o ./obj-files/imgui.obj ./Dependencies/ImGui/imgui.cpp

./obj-files/imgui_impl_glfw.obj:
	$(BASE_CMD) -c -o ./obj-files/imgui_impl_glfw.obj ./dependencies/ImGui/imgui_impl_glfw.cpp

./obj-files/imgui_impl_opengl3.obj:
	$(BASE_CMD) -c -o ./obj-files/imgui_impl_opengl3.obj ./dependencies/ImGui/imgui_impl_opengl3.cpp

./obj-files/imgui_tables.obj:
	$(BASE_CMD) -c -o ./obj-files/imgui_tables.obj ./dependencies/ImGui/imgui_tables.cpp

./obj-files/imgui_widgets.obj:
	$(BASE_CMD) -c -o ./obj-files/imgui_widgets.obj ./dependencies/ImGui/imgui_widgets.cpp

./obj-files/imgui_draw.obj: 
	$(BASE_CMD) -c -o ./obj-files/imgui_draw.obj ./dependencies/ImGui/imgui_draw.cpp


./Dependencies/ImGui/libimgui.a:    ./Dependencies/ImGui/imconfig.h \
									./Dependencies/ImGui/imgui.cpp \
									./Dependencies/ImGui/imgui.h \
									./Dependencies/ImGui/imgui_internal.h \
									./Dependencies/ImGui/imgui_demo.cpp \
									./Dependencies/ImGui/imgui_draw.cpp \
									./Dependencies/ImGui/imgui_impl_glfw.cpp \
									./Dependencies/ImGui/imgui_impl_glfw.h \
									./Dependencies/ImGui/imgui_impl_opengl3.cpp \
									./Dependencies/ImGui/imgui_impl_opengl3.h \
									./Dependencies/ImGui/imgui_impl_opengl3_loader.h \
									./Dependencies/ImGui/imgui_tables.cpp \
									./Dependencies/ImGui/imgui_widgets.cpp \
									./Dependencies/ImGui/imstb_rectpack.h \
									./Dependencies/ImGui/imstb_textedit.h \
									./Dependencies/ImGui/imstb_truetype.h \
									./obj-files/imgui.obj \
									./obj-files/imgui_impl_glfw.obj \
									./obj-files/imgui_impl_opengl3.obj \
									./obj-files/imgui_tables.obj \
									./obj-files/imgui_widgets.obj \
									./obj-files/imgui_draw.obj 

	ar cr ./Dependencies/ImGui/libimgui.a ./obj-files/imgui.obj ./obj-files/imgui_impl_glfw.obj ./obj-files/imgui_impl_opengl3.obj ./obj-files/imgui_tables.obj ./obj-files/imgui_widgets.obj ./obj-files/imgui_draw.obj

#   $(BASE_CMD) -c -o ./obj-files/imgui_demo.obj ./dependencies/ImGui/imgui_demo.cpp
#   $(BASE_CMD) -c -o ./obj-files/imgui_draw.obj ./dependencies/ImGui/imgui_draw.cpp

clean:
	rm -rf ./obj-files/
	rm main.exe
