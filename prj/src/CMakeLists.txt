add_library(lacze_do_gnuplota lacze_do_gnuplota.cpp)
target_include_directories(lacze_do_gnuplota PUBLIC ${INC})

add_library(Sciezka Sciezka.cpp)
target_include_directories(Sciezka PUBLIC ${INC})
target_link_libraries(Sciezka LINK_PUBLIC lacze_do_gnuplota)

add_library(ElemPow ElemPow.cpp)
target_include_directories(ElemPow PUBLIC ${INC})

add_library(Gora_z_Ostr Gora_z_Ostr.cpp)
target_include_directories(Gora_z_Ostr PUBLIC ${INC})
target_link_libraries(Gora_z_Ostr LINK_PUBLIC ElemPow)

add_library(Gora_z_Dl_Grania Gora_z_Dl_Grania.cpp)
target_include_directories(Gora_z_Dl_Grania PUBLIC ${INC})
target_link_libraries(Gora_z_Dl_Grania LINK_PUBLIC ElemPow)

add_library(Plaskowyz Plaskowyz.cpp)
target_include_directories(Plaskowyz PUBLIC ${INC})
target_link_libraries(Plaskowyz LINK_PUBLIC ElemPow)

add_library(Dron Dron.cpp)
target_include_directories(Dron PUBLIC ${INC})
target_link_libraries(Dron LINK_PUBLIC Sciezka)

add_library(Scena Scena.cpp)
target_include_directories(Scena PUBLIC ${INC})
target_link_libraries(Scena LINK_PUBLIC Dron)
target_link_libraries(Scena LINK_PUBLIC Gora_z_Ostr)
target_link_libraries(Scena LINK_PUBLIC Gora_z_Dl_Grania)
target_link_libraries(Scena LINK_PUBLIC Plaskowyz)

add_executable(Dron_Dragonfly main.cpp)
target_include_directories(Dron_Dragonfly PUBLIC ${INC})
target_link_libraries(Dron_Dragonfly LINK_PUBLIC Scena)



