set(SOURCES
    rp2040/startup.cpp
    rp2040/vector_table.cpp
)

set(PUBLIC_HEADERS
    rp2040/registers/access_modifiers.hpp
    rp2040/registers/base_addresses.hpp
    rp2040/registers/field.hpp
    rp2040/registers/register.hpp
    rp2040/registers/registers.hpp
    rp2040/registers/types.hpp
    utility/concepts.hpp
)

list(TRANSFORM SOURCES PREPEND ${CMAKE_CURRENT_LIST_DIR}/)
list(TRANSFORM PUBLIC_HEADERS PREPEND ${CMAKE_CURRENT_LIST_DIR}/)

set(SOURCES ${SOURCES} ${PUBLIC_HEADERS} PARENT_SCOPE)
set(PUBLIC_HEADERS ${PUBLIC_HEADERS} PARENT_SCOPE)