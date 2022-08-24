if(APP_NAME STREQUAL sample_app)

target_sources(app PRIVATE src/main.cpp)

target_link_libraries(app PRIVATE robotics_lib)

endif()