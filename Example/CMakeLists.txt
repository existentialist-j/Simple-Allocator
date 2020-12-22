cmake_minimum_required (VERSION 3.8)

project ("exampleApp" VERSION "0.1" LANGUAGES CXX)

add_executable(${PROJECT_NAME} "")

target_sources(${PROJECT_NAME}
	PRIVATE
		"src/main.cpp"
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		SimpleAllocator
)

include_directories(${PROJECT_NAME}
    PRIVATE		
        ${PROJECT_SOURCE_DIR}/../SimpleAllocator/include
)