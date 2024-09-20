add_executable(${PROJECT_NAME} Cavern.cpp Pos.cpp Enemy.cpp Player.cpp Room.cpp nums.cpp animations.cpp)

enable_testing()

add_executable(Test Test.cpp Pos.cpp Enemy.cpp Player.cpp Room.cpp animations.cpp)
target_link_libraries(Cavern winmm)
add_test(NAME RunCavernTests COMMAND Test)