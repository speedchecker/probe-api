//------------------------------------------------------
#ifndef _VERSION_H_UID00000347C85021AC
#define _VERSION_H_UID00000347C85021AC

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//------------------------------------------------------

#define VERSION_PRODUCT_NAME			"Probe API Utils"
#define VERSION_COMPANY_NAME			"Optimal Software s.r.o."
#define VERSION_COPYRIGHT				"Copyright \xA9 2015 Optimal Software s.r.o. All rights reserved."	// 0xA9 == '�' (c)
#define VERSION_COMMENT					"Probe API gives access to a set of network utilities for distributed network tests."

#define VERSION_PRODUCT_VER1			0
#define VERSION_PRODUCT_VER2			1
#define VERSION_PRODUCT_VER3			0

#define PRODUCT_BUILD_VER				3
#define VERSION_PRODUCT_COMMENT			""	// " [comment]"	// NOTE! string should be empty OR it should start from space (' ')!
//#define VERSION_SPECIAL_BUILD			VERSION_PRODUCT_COMMENT

//------------------------------------------------------

#ifdef DPING_PRJ
#define LOG_PREFIX						""
#define FILE_DESCRIPTION				VERSION_PRODUCT_NAME ": Distributed Ping"
#define FILE_INTERNAL_NAME				"dping"
#define VERSION_PRODUCT_VER4			PRODUCT_BUILD_VER
#define MODVERSION						0
#define MODREVISION						PRODUCT_BUILD_VER
#define MODSUBREVISION					1
#define MODRELEASE						0
#endif

//------------------------------------------------------

// Product version defines

#define TO_STR2(x)	#x
#define TO_STR(x)	TO_STR2(x)

#define MAIN_PRODUCT_VERSION_STR_A	TO_STR(VERSION_PRODUCT_VER1) "." TO_STR(VERSION_PRODUCT_VER2) "." TO_STR(VERSION_PRODUCT_VER3) "." TO_STR(PRODUCT_BUILD_VER)

#ifdef FILE_DESCRIPTION

#define APPVERSION					VERSION_PRODUCT_VER1
#define APPREVISION					VERSION_PRODUCT_VER2
#define APPSUBREVISION				VERSION_PRODUCT_VER3
#define APPRELEASE					VERSION_PRODUCT_VER4

#define	PRODUCTNAME					VERSION_PRODUCT_NAME

#define VERSIONCOPYRIGHT			VERSION_COPYRIGHT "\0"
#define VERSIONCOMPANY				VERSION_COMPANY_NAME "\0"
#define VERSIONCOMMENTS				VERSION_COMMENT "\0"
#define VERSIONPRODUCTNAME			PRODUCTNAME "\0"
#define VERSIONINTERNALNAME			FILE_INTERNAL_NAME "\0"
#ifdef VERSION_SPECIAL_BUILD
#define VERSIONSPECIALBUILD			VERSION_SPECIAL_BUILD "\0"
#endif

#define VERSIONDESCRIPTION			FILE_DESCRIPTION "\0"

#define VERSIONPRODUCTVERSIONSTR	TO_STR(APPVERSION) "." TO_STR(APPREVISION) "." TO_STR(APPSUBREVISION) "." TO_STR(APPRELEASE) VERSION_PRODUCT_COMMENT "\0"

// Module Info:
#define VERSIONFILEVERSIONSTR		TO_STR(MODVERSION) "." TO_STR(MODREVISION) "\0"

#ifdef _USRDLL
#define VERSIONORIGINALFILENAME		FILE_INTERNAL_NAME ".dll"
#else
#define VERSIONORIGINALFILENAME		FILE_INTERNAL_NAME ".exe"
#endif

//#define VERSIONCOMPANYNAME			"\0"
//#define VERSIONTRADEMARKS				"\0"
//#define VERSIONPRIVATEBUILD			"\0"
//#define VERSIONSPECIALBUILD			"\0"

#define _TO_W2(x)					L##x
#define _TO_W(x)					_TO_W2(x)
#define FILE_INTERNAL_NAME_W		_TO_W(FILE_INTERNAL_NAME)

#endif //ifdef FILE_DESCRIPTION

//------------------------------------------------------
#endif //ifndef _VERSION_H_UID00000347C85021AC