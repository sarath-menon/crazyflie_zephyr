if(APP_NAME STREQUAL imu_read)

target_sources(app PRIVATE src/main.cpp)

target_include_directories(app PUBLIC include)

target_link_libraries(app PRIVATE robotics_lib)

endif()
