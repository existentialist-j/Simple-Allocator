cmake_minimum_required (VERSION 3.8)

project ("SimpleAllocator" LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC)

target_include_directories(${PROJECT_NAME}
    PRIVATE		
        ${PROJECT_SOURCE_DIR}/include
)
target_sources(${PROJECT_NAME}
	PRIVATE
		"src/SimpleAllocator.cpp"
)


