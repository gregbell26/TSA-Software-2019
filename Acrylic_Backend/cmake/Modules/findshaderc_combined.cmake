#Literally a direct clone of findglfw3 just for shaderc

set( _shaderc_combined_HEADER_SEARCH_DIRS
        "/usr/include"
        "/usr/local/include"
        "C:/SDKS/VulkanSDK/1.1.114.0/Include" )
set( _shaderc_combined_LIB_SEARCH_DIRS
        "/usr/lib"
        "/usr/local/lib"
        "C:/SDKS/VulkanSDK/1.1.114.0/Lib/" )

# Check environment for root search directory
set( _shaderc_combined_ENV_ROOT $ENV{shaderc_combined_ROOT} )
if( NOT shaderc_combined_ROOT AND _shaderc_combined_ENV_ROOT )
    set(shaderc_combined_ROOT ${_shaderc_combined_ENV_ROOT} )
endif()

# Put user specified location at beginning of search
if( shaderc_combined_ROOT )
    list( INSERT _shaderc_combined_HEADER_SEARCH_DIRS 0 "${shaderc_combined_ROOT}/include" )
    list( INSERT _shaderc_combined_LIB_SEARCH_DIRS 0 "${shaderc_combined_ROOT}/lib" )
endif()

# Search for the header
FIND_PATH(shaderc_combined_INCLUDE_DIR "shaderc/shaderc.hpp"
        PATHS ${_shaderc_combined_HEADER_SEARCH_DIRS} )

# Search for the library
FIND_LIBRARY(shaderc_combined_LIBRARY NAMES shaderc_combined
        PATHS ${_shaderc_combined_LIB_SEARCH_DIRS} )

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SHADERC_COMBINED DEFAULT_MSG
        SHADERC_COMBINED_LIBRARY SHADERC_COMBINED_INCLUDE_DIR)