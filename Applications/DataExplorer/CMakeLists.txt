if(MSVC)
    add_definitions(-DVTKGUISUPPORTQT_STATIC_DEFINE)
endif()

if(VTKFBXCONVERTER_FOUND)
    add_definitions(-DVTKFBXCONVERTER_FOUND)
    include_directories(${VTKFBXCONVERTER_INCLUDE_DIRS})
endif()

set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTOUIC TRUE)
set(CMAKE_AUTORCC TRUE)

# Add subprojects
add_subdirectory(Base)
add_subdirectory(DataView/StratView)
add_subdirectory(DataView)
add_subdirectory(DataView/DiagramView)
add_subdirectory(VtkVis)
add_subdirectory(VtkAct)
include(DataExplorer.cmake)
