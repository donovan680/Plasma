################################################################################
# Generated using Joshua T. Fisher's 'CMake Builder'.
# Link: https://github.com/playmer/CmakeBuilder 
################################################################################

add_library(Networking "")

set_target_properties(Networking PROPERTIES FOLDER "Systems")

target_sources(Networking
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/NetProperty.hpp
    ${CMAKE_CURRENT_LIST_DIR}/NetProperty.cpp
    ${CMAKE_CURRENT_LIST_DIR}/BitStreamExtended.cpp
    ${CMAKE_CURRENT_LIST_DIR}/EventBundle.cpp
    ${CMAKE_CURRENT_LIST_DIR}/InternetHostDiscovery.cpp
    ${CMAKE_CURRENT_LIST_DIR}/IrcClient.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LanHostDiscovery.cpp
    ${CMAKE_CURRENT_LIST_DIR}/NetChannel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/NetDiscoveryInterface.cpp
    ${CMAKE_CURRENT_LIST_DIR}/NetEvents.cpp
    ${CMAKE_CURRENT_LIST_DIR}/NetHost.cpp
    ${CMAKE_CURRENT_LIST_DIR}/NetHostRecord.cpp
    ${CMAKE_CURRENT_LIST_DIR}/NetObject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/NetPeer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/NetPeerConnectionInterface.cpp
    ${CMAKE_CURRENT_LIST_DIR}/NetSpace.cpp
    ${CMAKE_CURRENT_LIST_DIR}/NetTypes.cpp
    ${CMAKE_CURRENT_LIST_DIR}/NetUser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/NetworkingBindingExtensions.cpp
    ${CMAKE_CURRENT_LIST_DIR}/NetworkingStandard.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PendingHostPing.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PingManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Precompiled.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SendableEvent.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SimpleSocket.cpp
    ${CMAKE_CURRENT_LIST_DIR}/TcpSocket.cpp
    ${CMAKE_CURRENT_LIST_DIR}/WebRequester.cpp
    ${CMAKE_CURRENT_LIST_DIR}/WebServer.cpp
#  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/BitStreamExtended.hpp
    ${CMAKE_CURRENT_LIST_DIR}/EventBundle.hpp
    ${CMAKE_CURRENT_LIST_DIR}/InternetHostDiscovery.hpp
    ${CMAKE_CURRENT_LIST_DIR}/IrcClient.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LanHostDiscovery.hpp
    ${CMAKE_CURRENT_LIST_DIR}/NetChannel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/NetDiscoveryInterface.hpp
    ${CMAKE_CURRENT_LIST_DIR}/NetEvents.hpp
    ${CMAKE_CURRENT_LIST_DIR}/NetHost.hpp
    ${CMAKE_CURRENT_LIST_DIR}/NetHostRecord.hpp
    ${CMAKE_CURRENT_LIST_DIR}/NetObject.hpp
    ${CMAKE_CURRENT_LIST_DIR}/NetPeer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/NetPeerConnectionInterface.hpp
    ${CMAKE_CURRENT_LIST_DIR}/NetPeerMessageInterface.hpp
    ${CMAKE_CURRENT_LIST_DIR}/NetSpace.hpp
    ${CMAKE_CURRENT_LIST_DIR}/NetTypes.hpp
    ${CMAKE_CURRENT_LIST_DIR}/NetUser.hpp
    ${CMAKE_CURRENT_LIST_DIR}/NetworkingBindingExtensions.hpp
    ${CMAKE_CURRENT_LIST_DIR}/NetworkingStandard.hpp
    ${CMAKE_CURRENT_LIST_DIR}/PendingHostPing.hpp
    ${CMAKE_CURRENT_LIST_DIR}/PingManager.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Precompiled.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SendableEvent.hpp
    ${CMAKE_CURRENT_LIST_DIR}/SimpleSocket.hpp
    ${CMAKE_CURRENT_LIST_DIR}/TcpSocket.hpp
    ${CMAKE_CURRENT_LIST_DIR}/WebRequester.hpp
    ${CMAKE_CURRENT_LIST_DIR}/WebServer.hpp
)

target_include_directories(Networking 
    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/../Networking
        ${CMAKE_CURRENT_LIST_DIR}/../
)

target_link_libraries(Networking
    PUBLIC
    Common
    Geometry
) 

plasma_multitarget_output_settings(
    Networking
    CONFIGS ${supported_configs}
    BASEPATH ${plasma_build_out}
    PLATFORM ${platform}
    CONFIG ${configuration}
    BITS ${bit}
    TOOLSET ${CMAKE_VS_PLATFORM_TOOLSET}
    PRECOMPILED_HEADER_NAME "Precompiled.hpp"
    PRECOMPILED_SOURCE_NAME "Precompiled.cpp"
    TARGET_SUBFOLDER
)

plasma_source_group(${CMAKE_CURRENT_LIST_DIR} Networking "")