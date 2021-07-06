project(Impact LANGUAGES CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Impact
        src/mat4.cpp
        src/main.cpp
        src/particle_contact.cpp
        src/mat34.cpp
        src/mat3.cpp
        src/quaternion.cpp
        src/rigidbody.cpp
        src/impact.cpp
        src/rigidbody_contact.cpp
        src/particle.cpp)