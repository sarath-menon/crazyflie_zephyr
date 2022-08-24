
if(TEST_NAME STREQUAL imu_test)

target_sources(app PRIVATE 
src/main.cpp 
src/tests.cpp
)

target_link_libraries(app PRIVATE robotics_lib)

target_include_directories(app PUBLIC include)

endif()