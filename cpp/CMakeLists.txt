# cmake_minimum_required(VERSION 3.15)

# project(LanguageLearningProgram)

# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# # set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17")
# set(CMAKE_CXX_STANDARD 11)

# # Turn on automatic invocation of the MOC, UIC & RCC
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTORCC ON)

# # Add a compiler flag
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# include_directories(inc)

# # Find the required Qt6 modules
# find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

# # Add the Qt6 libraries and modules
# add_executable(LanguageLearningProgram src/main.cpp 
#                                        src/mainwindow.cpp)

# set_target_properties(LanguageLearningProgram PROPERTIES AUTOMOC ON)

# target_link_libraries(LanguageLearningProgram PRIVATE Qt6::Core Qt6::Widgets)


cmake_minimum_required(VERSION 3.15)
project(HardWord)

set(CMAKE_CXX_STANDARD 11)

# Find the required Qt6 modules
find_package(Qt6 COMPONENTS Core Widgets Sql REQUIRED)
# find_package(Sqlite3 REQUIRED)

include_directories(inc)
# Add the Qt6 libraries and modules
add_executable(HardWord src/main.cpp 
                    inc/WordInfo.h
                    src/widgets/UploadWid.cpp inc/widgets/UploadWid.h 
                    src/TableModel.cpp inc/TableModel.h
                    src/DatabaseService.cpp inc/DatabaseService.h
                    src/StartWin.cpp inc/StartWin.h
                    src/widgets/StartWid.cpp inc/widgets/StartWid.h
                    src/widgets/GameWid.cpp inc/widgets/GameWid.h
                    src/widgets/GameSettingsWid.cpp inc/widgets/GameSettingsWid.h
                    src/widgets/LearnWordsWid.cpp inc/widgets/LearnWordsWid.h)

# Run MOC on the header file
set_target_properties(HardWord PROPERTIES AUTOMOC ON)

# Link against the required Qt modules
target_link_libraries(HardWord PRIVATE Qt6::Core Qt6::Widgets Qt6::Sql)
