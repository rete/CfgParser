
# helper macro for generating project configuration file
MACRO( GENERATE_PACKAGE_CONFIGURATION_FILES )

    FOREACH( arg ${ARGN} )
        IF( ${arg} MATCHES "Config.cmake" )
            IF( EXISTS "${PROJECT_SOURCE_DIR}/cmake/${arg}.in" )
                CONFIGURE_FILE( "${PROJECT_SOURCE_DIR}/cmake/${arg}.in"
                                "${arg}" @ONLY
                )
                INSTALL( FILES "${PROJECT_BINARY_DIR}/${arg}" DESTINATION ${PROJECT_SOURCE_DIR} )
            ENDIF()
        ENDIF()


        IF( ${arg} MATCHES "ConfigVersion.cmake" )
            # version configuration file
            IF( EXISTS "${PROJECT_SOURCE_DIR}/cmake/${arg}.in" )
                CONFIGURE_FILE( "${PROJECT_SOURCE_DIR}/cmake/${arg}.in"
                                "${arg}" @ONLY
                )
                INSTALL( FILES "${PROJECT_BINARY_DIR}/${arg}" DESTINATION ${PROJECT_SOURCE_DIR} )
            ENDIF( EXISTS "${PROJECT_SOURCE_DIR}/cmake/${arg}.in" )
        ENDIF()

        IF( ${arg} MATCHES "LibDeps.cmake" )
            EXPORT_LIBRARY_DEPENDENCIES( "${arg}" )
            INSTALL( FILES "${PROJECT_BINARY_DIR}/${arg}" DESTINATION ${PROJECT_SOURCE_DIR}/lib/cmake )
        ENDIF()

    ENDFOREACH()

ENDMACRO( GENERATE_PACKAGE_CONFIGURATION_FILES )

