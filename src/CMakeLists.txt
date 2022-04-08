set(SRC_FILES
        main.cpp
        GameEngine.cpp
        actors/Ship.cpp
        actors/AttackShip.cpp
        actors/Galaxian.cpp
        actors/Bullet.cpp
        actors/Escort.cpp
        actors/Galaxyip.cpp
        actors/Flagship.cpp
        actors/Actor.cpp
        actors/Drone.cpp
        actors/Emissary.cpp
        gui/MainMenuGui.cpp
        gui/PauseMenuGui.cpp
        gui/GameOverGui.cpp
        gui/GameplayGui.cpp
        gui/LoadScreenGui.cpp
        scene/Scene.cpp
        scene/MainMenuScene.cpp
        scene/PauseMenuScene.cpp
        scene/GameOverScene.cpp
        scene/GameplayScene.cpp
        scene/LoadScreenScene.cpp
        util/Utils.cpp)

# Resource script files
set(RES_FILES
        ${PROJECT_SOURCE_DIR}/icon.rc
        ${PROJECT_SOURCE_DIR}/version.rc)

# Set executables output folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Create executable project source files
add_executable(Galaxian ${SRC_FILES} ${RES_FILES})

# Find and link IME
list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/extlibs")
find_package(ime 3.1.0 REQUIRED)
target_link_libraries(Galaxian PRIVATE ime)

# Add <project>/ as include directory
include_directories(${PROJECT_SOURCE_DIR}/src)

# Copy runtime dependencies to the executable output folder
set(IME_BIN_DIR "${PROJECT_SOURCE_DIR}/extlibs/IME-${ime_VERSION}/bin")

add_custom_command(TARGET Galaxian PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${PROJECT_SOURCE_DIR}/bin
        COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_SOURCE_DIR}/bin
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${IME_BIN_DIR}/${CMAKE_BUILD_TYPE}/" $<TARGET_FILE_DIR:Galaxian>
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${IME_BIN_DIR}/Runtime/" $<TARGET_FILE_DIR:Galaxian>
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/res" $<TARGET_FILE_DIR:Galaxian>/res
        )