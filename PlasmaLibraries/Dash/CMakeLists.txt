################################################################################
# Generated using Joshua T. Fisher's 'CMake Builder'.
# Link: https://github.com/playmer/CmakeBuilder 
################################################################################
add_library(Dash "")

set_target_properties(Dash PROPERTIES FOLDER "PlasmaLibraries")

target_sources(Dash
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/BandwidthStats.hpp
    ${CMAKE_CURRENT_LIST_DIR}/DashStandard.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DashStandard.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Enums.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LinkInbox.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LinkInbox.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LinkOutbox.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LinkOutbox.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Message.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Message.hpp
    ${CMAKE_CURRENT_LIST_DIR}/MessageChannel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/MessageChannel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/MessageConfig.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Packet.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Packet.hpp
    ${CMAKE_CURRENT_LIST_DIR}/PacketConfig.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Peer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Peer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/PeerLink.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PeerLink.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Precompiled.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Precompiled.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ProtocolMessageData.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Replica.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Replica.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ReplicaChannel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ReplicaChannel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ReplicaConfig.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ReplicaProperty.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ReplicaProperty.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ReplicaStream.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ReplicaStream.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Replicator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Replicator.hpp
    ${CMAKE_CURRENT_LIST_DIR}/ReplicatorLink.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ReplicatorLink.hpp
    ${CMAKE_CURRENT_LIST_DIR}/Route.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Route.hpp
)

target_include_directories(Dash
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/../
)

target_link_libraries(Dash
                    PUBLIC
                    Common
                    Lightning                      
                    Geometry
)  

plasma_multitarget_output_settings(
    Dash
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

plasma_source_group(${CMAKE_CURRENT_LIST_DIR} Dash "")