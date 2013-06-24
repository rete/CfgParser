#ifndef CfgParserConfig_h
#define CfgParserConfig_h 1

// version macros
#define CfgParser_MAJOR_VERSION 0
#define CfgParser_MINOR_VERSION 1
#define CfgParser_PATCH_LEVEL 0

#define CfgParser_VERSION_GE( MAJV , MINV , PLEV )  ( (CfgParser_MAJOR_VERSION > MAJV) || ( (CfgParser_MAJOR_VERSION == MAJV) && (CfgParser_MINOR_VERSION > MINV) ) || ( (CfgParser_MAJOR_VERSION == MAJV) && (CfgParser_MINOR_VERSION == MINV) && (CfgParser_PATCH_LEVEL >= PLEV) ) )

#endif // CfgParserConfig_h
