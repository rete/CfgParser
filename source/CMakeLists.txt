#######################################################
# cmake file for building CfgParser package
# @author Eté Rémi 
#######################################################

# include directories
INCLUDE_DIRECTORIES( include )
#INCLUDE_DIRECTORIES( BEFORE "${PROJECT_BINARY_DIR}" ) # generated CfgParserConfig.h


# require proper c++
ADD_DEFINITIONS( "-pedantic -Wunused-value -O2" )
ADD_DEFINITIONS("-Wno-long-long")


# create library
FILE (
	GLOB_RECURSE
	CFGPARSER_LIBRARY_FILES
	include/*
	src/*
)

ADD_SHARED_LIBRARY( CfgParser ${CFGPARSER_LIBRARY_FILES} )

INSTALL(
	TARGETS CfgParser
	LIBRARY DESTINATION lib 
)


INCLUDE( MacroMakeExecutables )

OPTION( BUILD_EXAMPLE "Build examples" ON )

MAKE_DEV_TEST( devTest1 )

MAKE_EXECUTABLE( rawcfgparser_getvalue )
MAKE_EXECUTABLE( cfgparser_getvalue )

IF( BUILD_EXAMPLE )

	MAKE_EXAMPLE( example1 )

ENDIF()




#-------------------- install ----------------------- 
#INSTALL( 
#	TARGETS 
#	cfgparser
#	DESTINATION 
#	bin
#)

