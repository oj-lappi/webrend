#The WebRend library
add_library(WebRend)

target_compile_options(WebRend
	PUBLIC
		$<$<CXX_COMPILER_ID:GNU>:-fconcepts>
	PRIVATE
		-Wall
		$<$<CONFIG:Debug>:-g>
	)


target_include_directories(WebRend
    PUBLIC
      ../include
    PRIVATE
     ${CMAKE_CURRENT_LIST_DIR}
     ../3rd_party
)

###################
#  Build options  #
###################

if (ENABLE_ADDRESS_SANITIZER)
	target_compile_options(WebRend
		INTERFACE
			$<$<CXX_COMPILER_ID:GNU>:-fsanitize=address>
			$<$<CXX_COMPILER_ID:Clang>:-fsanitize=address>
	)

	target_link_options(WebRend
		INTERFACE
			$<$<CXX_COMPILER_ID:GNU>:-fsanitize=address>
			$<$<CXX_COMPILER_ID:Clang>:-fsanitize=address>
	)
endif()

if (ENABLE_PERFORMANCE_TRACES)
	target_compile_options(WebRend
		INTERFACE
                    -fno-omit-frame-pointer
	)
endif()

if(INTRUSIVE_PROFILING)
	target_compile_definitions(WebRend PUBLIC WEBREND_PROFILE)
endif()

##################
#  Dependencies  #
##################

find_package(Boost REQUIRED)
target_link_libraries(WebRend PRIVATE Boost::boost)

find_package(fmt REQUIRED CONFIG)
target_link_libraries(WebRend PRIVATE fmt::fmt)

find_package(Threads REQUIRED)
target_link_libraries(WebRend PRIVATE Threads::Threads)

#TODO: add generator expressions to separate BUILD and INSTALL concerns

add_subdirectory(utils)
