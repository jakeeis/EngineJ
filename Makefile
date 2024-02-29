CC := emcc
CFLAGS := -Wall -Wextra -std=c++20 -fwasm-exceptions
EMFLAGS := -sALLOW_MEMORY_GROWTH=1 -sFULL_ES2=1 -sWASM=1 -sNO_EXIT_RUNTIME=1 --embed-file assets
TARGET := ./build/engine.js

LIBS := ./libs/JsonParser/libJsonParser.a
HEADERS := -I./include/headers -I./include/headers/renderer -I./include/headers/core -I./include/headers/core/objects -I./include/headers/core/entities -I./include/headers/core/entities/character -I./include/headers/core/components -I./include/headers/core/components/mesh -I./include/headers/math -I./include/headers/math/test -I./include/JsonParser 
CFLAGS_INCLUDE := $(CFLAGS) $(HEADERS)

.PHONY: all clean

all: $(TARGET)

clean:
	@rm -rf ./build/*

./build/renderer/Renderer.o: ./src/renderer/Renderer.cpp ./include/headers/renderer/Renderer.hpp ./include/headers/renderer/EngineJRenderer.hpp ./src/renderer/Renderer.cpp 
	@mkdir -p ./build/renderer
	$(CC) $(CFLAGS_INCLUDE) -c ./src/renderer/Renderer.cpp -o ./build/renderer/Renderer.o

./build/core/objects/GameObject.o: ./src/core/objects/GameObject.cpp ./include/headers/core/EngineJCore.hpp  ./include/headers/core/objects/GameObject.hpp ./src/core/objects/GameObject.cpp 
	@mkdir -p ./build/core/objects
	$(CC) $(CFLAGS_INCLUDE) -c ./src/core/objects/GameObject.cpp -o ./build/core/objects/GameObject.o

./build/core/entities/character/CharacterEntity.o: ./src/core/entities/character/CharacterEntity.cpp ./include/headers/core/entities/character/CharacterEntity.hpp ./src/core/entities/character/CharacterEntity.cpp ./include/headers/core/EngineJCore.hpp  
	@mkdir -p ./build/core/entities/character
	$(CC) $(CFLAGS_INCLUDE) -c ./src/core/entities/character/CharacterEntity.cpp -o ./build/core/entities/character/CharacterEntity.o

./build/core/entities/GameEntity.o: ./src/core/entities/GameEntity.cpp ./include/headers/core/entities/GameEntity.hpp ./src/core/entities/GameEntity.cpp ./include/headers/core/EngineJCore.hpp  
	@mkdir -p ./build/core/entities
	$(CC) $(CFLAGS_INCLUDE) -c ./src/core/entities/GameEntity.cpp -o ./build/core/entities/GameEntity.o

./build/core/components/GameComponent.o: ./src/core/components/GameComponent.cpp ./include/headers/core/components/GameComponent.hpp ./src/core/components/GameComponent.cpp ./include/headers/core/EngineJCore.hpp  
	@mkdir -p ./build/core/components
	$(CC) $(CFLAGS_INCLUDE) -c ./src/core/components/GameComponent.cpp -o ./build/core/components/GameComponent.o

./build/core/components/mesh/MeshElement.o: ./src/core/components/mesh/MeshElement.cpp ./include/headers/core/components/mesh/MeshElement.hpp ./src/core/components/mesh/MeshElement.cpp ./include/headers/renderer/EngineJRenderer.hpp  
	@mkdir -p ./build/core/components/mesh
	$(CC) $(CFLAGS_INCLUDE) -c ./src/core/components/mesh/MeshElement.cpp -o ./build/core/components/mesh/MeshElement.o

./build/core/components/mesh/MeshComponent.o: ./src/core/components/mesh/MeshComponent.cpp ./include/headers/core/components/mesh/MeshComponent.hpp ./src/core/components/mesh/MeshComponent.cpp ./include/headers/core/EngineJCore.hpp  
	@mkdir -p ./build/core/components/mesh
	$(CC) $(CFLAGS_INCLUDE) -c ./src/core/components/mesh/MeshComponent.cpp -o ./build/core/components/mesh/MeshComponent.o

./build/math/Matrix.o: ./src/math/Matrix.cpp ./include/headers/math/Matrix.hpp ./src/math/Matrix.cpp 
	@mkdir -p ./build/math
	$(CC) $(CFLAGS_INCLUDE) -c ./src/math/Matrix.cpp -o ./build/math/Matrix.o

./build/math/test/test.o: ./src/math/test/test.cpp ./include/headers/math/test/test.hpp ./src/math/test/test.cpp ./include/headers/math/Matrix.hpp ./src/math/Matrix.cpp ./include/headers/math/Vector.hpp ./src/math/Vector.cpp 
	@mkdir -p ./build/math/test
	$(CC) $(CFLAGS_INCLUDE) -c ./src/math/test/test.cpp -o ./build/math/test/test.o

./build/math/Vector.o: ./src/math/Vector.cpp ./include/headers/math/Vector.hpp ./src/math/Vector.cpp ./include/headers/core/EngineJCoreLibs.hpp  
	@mkdir -p ./build/math
	$(CC) $(CFLAGS_INCLUDE) -c ./src/math/Vector.cpp -o ./build/math/Vector.o

./build/engine.o: ./src/engine.cpp ./include/headers/core/EngineJCore.hpp  ./include/headers/math/EngineJMath.hpp  ./include/headers/math/test/test.hpp ./src/math/test/test.cpp 
	@mkdir -p ./build
	$(CC) $(CFLAGS_INCLUDE) -c ./src/engine.cpp -o ./build/engine.o

$(TARGET): ./build/renderer/Renderer.o ./build/core/objects/GameObject.o ./build/core/entities/character/CharacterEntity.o ./build/core/entities/GameEntity.o ./build/core/components/GameComponent.o ./build/core/components/mesh/MeshElement.o ./build/core/components/mesh/MeshComponent.o ./build/math/Matrix.o ./build/math/test/test.o ./build/math/Vector.o ./build/engine.o  $(LIBS)
	$(CC) $(CFLAGS_INCLUDE) $(EMFLAGS) $^ -o $@
