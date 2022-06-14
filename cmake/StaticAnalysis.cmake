option(ENABLE_CLANG_TIDY "Do static analysis with clang-tidy" OFF)
if(ENABLE_CLANG_TIDY)
    find_program(CLANGTIDY clang-tidy)
    if(CLANGTIDY)
	message(STATUS "Using clang-tidy")
        set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY})
    else()
        message(SEND_ERROR "clang-tidy not found")
    endif()
endif()