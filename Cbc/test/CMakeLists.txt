
add_executable(CbcTest "CbcTest.cpp")
target_include_directories(Cbc PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include/coin>)
target_compile_definitions(CbcTest
  PUBLIC HAVE_CONFIG_H
  PRIVATE CLP_BUILD COIN_HAS_CLP)
if(CMAKE_VERSION VERSION_LESS "3.8.2")
  set_property(TARGET CbcTest PROPERTY CXX_STANDARD 11)
  set_property(TARGET CbcTest PROPERTY CXX_STANDARD_REQUIRED ON)
else()
  target_compile_features(CbcTest PUBLIC cxx_std_11)
endif()
target_link_libraries(CbcTest PRIVATE
  Coin::CoinUtils
  Coin::Osi
  Coin::Cbc)
set_target_properties(CbcTest PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR})
add_executable(Coin::CbcTest ALIAS CbcTest)

add_test(NAME CbcTest COMMAND CbcTest)
