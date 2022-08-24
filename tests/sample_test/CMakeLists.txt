if(TEST_NAME STREQUAL sample_test)

target_sources(app PRIVATE src/simple_test.cpp)

target_link_libraries(app PRIVATE robotics_lib)

endif()