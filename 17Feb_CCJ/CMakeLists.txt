# ======================= ofxCMake =======================
#  PUT THIS FILE INTO YOUR OPENFRAMEWORKS PROJECT FOLDER

# ========================================================
# ===================== CMake Settings ===================
# ========================================================
cmake_minimum_required( VERSION 3.3 )
project( CCJamFeb17 )

# ========================================================
# ===================== User Settings ====================
# ========================================================
# ---------------------- App name  -----------------------
set( APP_NAME   songVisualizer )

# ------------------------ OF Path -----------------------
# --- If outside the OF structure, set an absolute OF path
set( OF_DIRECTORY_BY_USER "../../of" )

# --------------------- Source Files ---------------------
set( ${APP_NAME}_SOURCE_FILES
        cpp/main.cpp
        cpp/ofApp.cpp )


# ------------------------ AddOns  -----------------------
set( OFX_ADDONS_ACTIVE
                ofxOsc
        #        ofxXmlSettings
                ofxGui
        #        ofxNetwork
        #        ofxVectorGraphics
        #        ofxThreadedImageLoader
        #        ofxAssimpModelLoader
        #        ofxKinect
        #        ofxOpenCv
        #        ofxSvg
        #        ofxEmscripten (untested)
                )

# =========================================================================
# ============================== OpenFrameworks ===========================
# =========================================================================
include( ${OF_DIRECTORY_BY_USER}/addons/ofxCMake/modules/main.cmake )
# =========================================================================

