#############################################################
# cmake module for finding CfgParser
#
# FIXME this module should be DEPRECATED
#       CfgParserConfig.cmake should be used instead
#
# requires:
#   ZLIB
#
# returns:
#   CfgParser_FOUND        : set to TRUE or FALSE
#   CfgParser_INCLUDE_DIRS : paths to lcio includes
#   CfgParser_LIBRARY_DIRS : paths to lcio libraries
#   CfgParser_LIBRARIES    : list of lcio libraries
#
# @author Jan Engels, DESY
# Modified by Rémi Eté for CfgParser use
#############################################################



# ---------- includes ---------------------------------------------------------
SET( CfgParser_INCLUDE_DIRS CfgParser_INCLUDE_DIRS-NOTFOUND )
MARK_AS_ADVANCED( CfgParser_INCLUDE_DIRS )

FIND_PATH( CfgParser_INCLUDE_DIRS
    NAMES CfgParser.hh
    PATHS ${CfgParser_DIR}/source/include
    NO_DEFAULT_PATH
)
IF( NOT CfgParser_DIR )
    FIND_PATH( CfgParser_INCLUDE_DIRS NAMES CfgParser.h )
ENDIF()

IF( CfgParser_INCLUDE_DIRS )
    GET_FILENAME_COMPONENT( CfgParser_ROOT ${CfgParser_INCLUDE_DIRS} PATH )
ENDIF()


# ---------- libraries --------------------------------------------------------
SET( CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE )

MACRO( CHECK_PACKAGE_LIBS _pkgname )

    SET( _std_lib_missing FALSE )
    SET( _ext_lib_missing FALSE )

    SET( _std_libnames ${ARGN} )
    SET( _ext_libnames ${${_pkgname}_FIND_COMPONENTS} ${${_pkgname}_USE_COMPONENTS} )

    IF( _ext_libnames )
        SEPARATE_ARGUMENTS( _ext_libnames )
        LIST( REMOVE_DUPLICATES _ext_libnames )
    ENDIF()

    IF( NOT ${_pkgname}_FIND_QUIETLY )
        MESSAGE( STATUS "Check for ${_pkgname}_LIBRARIES: ${_std_libnames}" )
        IF( _ext_libnames )
            MESSAGE( STATUS "Check for ${_pkgname}_COMPONENT_LIBRARIES: ${_ext_libnames}" )
        ENDIF()
    ENDIF()

    SET( ${_pkgname}_LIBRARY_DIRS )
    MARK_AS_ADVANCED( ${_pkgname}_LIBRARY_DIRS )

    SET( ${_pkgname}_LIBRARIES )
    MARK_AS_ADVANCED( ${_pkgname}_LIBRARIES )
    
    SET( ${_pkgname}_COMPONENT_LIBRARIES )
    MARK_AS_ADVANCED( ${_pkgname}_COMPONENT_LIBRARIES )

    SET( ${_pkgname}_COMPONENT_VARIABLES )
    MARK_AS_ADVANCED( ${_pkgname}_COMPONENT_VARIABLES )

    FOREACH( _libname ${_std_libnames} ${_ext_libnames} )

        # flag to check if it is a standard or a component library
        LIST( FIND _std_libnames "${_libname}" _aux )
        IF( ${_aux} LESS 0 )
           SET( _is_std_lib FALSE )
        ELSE()
           SET( _is_std_lib TRUE )
        ENDIF()

        # libname in upper case
        STRING( TOUPPER ${_libname} _ulibname )

        SET( ${_pkgname}_${_ulibname}_LIBRARY ${_pkgname}_${_ulibname}_LIBRARY-NOTFOUND )
        MARK_AS_ADVANCED( ${_pkgname}_${_ulibname}_LIBRARY )

        # WARNING: using PATH_SUFFIXES may cause problems when using variable CMAKE_FIND_ROOT_PATH
        #           this problem does not occur if expanding PATHS
        #           look in FindMySQL.cmake for more info
        #FIND_LIBRARY( ${_pkgname}_${_ulibname}_LIBRARY NAMES ${_libname} PATHS
        #    ${${_pkgname}_ROOT} ${${_pkgname}_DIR} ${${_pkgname}_LIB_SEARCH_PATH}
        #    PATH_SUFFIXES lib64 lib
        #    NO_DEFAULT_PATH
        #)

        FIND_LIBRARY( ${_pkgname}_${_ulibname}_LIBRARY NAMES ${_libname} PATHS
            ${${_pkgname}_ROOT}/lib64 ${${_pkgname}_ROOT}/lib
            ${${_pkgname}_DIR}/lib64 ${${_pkgname}_DIR}/lib
            ${${_pkgname}_LIB_SEARCH_PATH} ${${_pkgname}_LIB_SEARCH_PATH}/lib64 ${${_pkgname}_LIB_SEARCH_PATH}/lib
            NO_DEFAULT_PATH
        )

        IF( NOT ${_pkgname}_DIR )
            FIND_LIBRARY( ${_pkgname}_${_ulibname}_LIBRARY NAMES ${_libname} )
        ENDIF()
        
        IF( ${_pkgname}_FIND_REQUIRED )
            LIST( APPEND ${_pkgname}_COMPONENT_VARIABLES ${_pkgname}_${_ulibname}_LIBRARY )
        ENDIF()

        IF( ${_pkgname}_${_ulibname}_LIBRARY ) # if library found

            SET( ${_pkgname}_${_ulibname}_FOUND TRUE )
            
            # split libraries in PKG_LIBRARIES and PKG_COMPONENT_LIBRARIES
            IF( _is_std_lib )
                LIST( APPEND ${_pkgname}_LIBRARIES ${${_pkgname}_${_ulibname}_LIBRARY} )
            ELSE()
                LIST( APPEND ${_pkgname}_COMPONENT_LIBRARIES ${${_pkgname}_${_ulibname}_LIBRARY} )
            ENDIF()

            GET_FILENAME_COMPONENT( _aux ${${_pkgname}_${_ulibname}_LIBRARY} PATH )
            LIST( APPEND ${_pkgname}_LIBRARY_DIRS ${_aux} )

            IF( NOT ${_pkgname}_FIND_QUIETLY )
                MESSAGE( STATUS "Check for ${_pkgname}_${_ulibname}_LIBRARY: ${${_pkgname}_${_ulibname}_LIBRARY} -- ok" )
            ENDIF()

        ELSE() # library not found

            SET( ${_pkgname}_${_ulibname}_FOUND FALSE )

            IF( _is_std_lib )
                SET( _std_lib_missing TRUE )
            ELSE()
                SET( _ext_lib_missing TRUE )
            ENDIF()

            IF( NOT ${_pkgname}_FIND_QUIETLY )
                MESSAGE( STATUS "Check for ${_pkgname}_${_ulibname}_LIBRARY: ${_libname} -- failed" )
            ENDIF()

        ENDIF()

    ENDFOREACH()

    # clear PKG_LIBRARIES if standard library is missing
    IF( _std_lib_missing )
        SET( ${_pkgname}_LIBRARIES )
    ENDIF()

    # clear PKG_COMPONENT_LIBRARIES if a component library is missing and
    # FIND_PACKAGE called with REQUIRED argument
    IF( _ext_lib_missing AND ${_pkgname}_FIND_REQUIRED )
        SET( ${_pkgname}_COMPONENT_LIBRARIES )
    ENDIF()

    # remove duplicate paths in PKG_LIBRARY_DIRS
    IF( ${_pkgname}_LIBRARY_DIRS )
        LIST( REMOVE_DUPLICATES ${_pkgname}_LIBRARY_DIRS )
    ENDIF()

    # debug
    #MESSAGE( STATUS "${_pkgname}_LIBRARIES: ${${_pkgname}_LIBRARIES}" )
    #MESSAGE( STATUS "${_pkgname}_COMPONENT_LIBRARIES: ${${_pkgname}_COMPONENT_LIBRARIES}" )
    #MESSAGE( STATUS "${_pkgname}_LIBRARY_DIRS: ${${_pkgname}_LIBRARY_DIRS}" )

ENDMACRO( CHECK_PACKAGE_LIBS _pkgname )

# only standard libraries should be passed as arguments to CHECK_PACKAGE_LIBS
# additional components are set by cmake in variable PKG_FIND_COMPONENTS
# first argument should be the package name
CHECK_PACKAGE_LIBS( CfgParser CfgParser )


# ---------- final checking ---------------------------------------------------
MACRO(FIND_PACKAGE_HANDLE_STANDARD_ARGS _NAME _FAIL_MSG _VAR1 )

  IF("${_FAIL_MSG}" STREQUAL "DEFAULT_MSG")
    IF (${_NAME}_FIND_REQUIRED)
      SET(_FAIL_MESSAGE "Could not find REQUIRED package ${_NAME}")
    ELSE (${_NAME}_FIND_REQUIRED)
      SET(_FAIL_MESSAGE "Could not find OPTIONAL package ${_NAME}")
    ENDIF (${_NAME}_FIND_REQUIRED)
  ELSE("${_FAIL_MSG}" STREQUAL "DEFAULT_MSG")
    SET(_FAIL_MESSAGE "${_FAIL_MSG}")
  ENDIF("${_FAIL_MSG}" STREQUAL "DEFAULT_MSG")

  STRING(TOUPPER ${_NAME} _NAME_UPPER)

  SET(${_NAME_UPPER}_FOUND TRUE)
  IF(NOT ${_VAR1})
    SET(${_NAME_UPPER}_FOUND FALSE)
  ENDIF(NOT ${_VAR1})

  FOREACH(_CURRENT_VAR ${ARGN})
    IF(NOT ${_CURRENT_VAR})
      SET(${_NAME_UPPER}_FOUND FALSE)
    ENDIF(NOT ${_CURRENT_VAR})
  ENDFOREACH(_CURRENT_VAR)

  IF (${_NAME_UPPER}_FOUND)
    IF (NOT ${_NAME}_FIND_QUIETLY)
        MESSAGE(STATUS "Found ${_NAME}: ${${_VAR1}}")
    ENDIF (NOT ${_NAME}_FIND_QUIETLY)
  ELSE (${_NAME_UPPER}_FOUND)
    IF (${_NAME}_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "${_FAIL_MESSAGE}")
    ELSE (${_NAME}_FIND_REQUIRED)
      IF (NOT ${_NAME}_FIND_QUIETLY)
        MESSAGE(STATUS "${_FAIL_MESSAGE}")
      ENDIF (NOT ${_NAME}_FIND_QUIETLY)
    ENDIF (${_NAME}_FIND_REQUIRED)
  ENDIF (${_NAME_UPPER}_FOUND)
  
ENDMACRO(FIND_PACKAGE_HANDLE_STANDARD_ARGS)

# set CfgParser_FOUND to TRUE if all listed variables are TRUE and not empty
FIND_PACKAGE_HANDLE_STANDARD_ARGS( CfgParser DEFAULT_MSG CfgParser_INCLUDE_DIRS CfgParser_LIBRARIES ${CfgParser_COMPONENT_VARIABLES} ZLIB_LIBRARIES )

