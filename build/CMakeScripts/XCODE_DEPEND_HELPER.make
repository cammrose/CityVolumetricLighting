# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.base.Debug:
PostBuild.glew.Debug: /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Debug/base
PostBuild.glfw.Debug: /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Debug/base
PostBuild.stb.Debug: /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Debug/base
PostBuild.imgui.Debug: /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Debug/base
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Debug/base:\
	/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Debug/libglew.a\
	/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Debug/libglfw3.a\
	/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Debug/libstb.a\
	/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Debug/libimgui.a
	/bin/rm -f /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Debug/base


PostBuild.glew.Debug:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Debug/libglew.a:
	/bin/rm -f /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Debug/libglew.a


PostBuild.glfw.Debug:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Debug/libglfw3.a:
	/bin/rm -f /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Debug/libglfw3.a


PostBuild.glm_dummy.Debug:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Debug/glm_dummy:
	/bin/rm -f /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Debug/glm_dummy


PostBuild.imgui.Debug:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Debug/libimgui.a:
	/bin/rm -f /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Debug/libimgui.a


PostBuild.stb.Debug:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Debug/libstb.a:
	/bin/rm -f /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Debug/libstb.a


PostBuild.base.Release:
PostBuild.glew.Release: /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Release/base
PostBuild.glfw.Release: /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Release/base
PostBuild.stb.Release: /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Release/base
PostBuild.imgui.Release: /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Release/base
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Release/base:\
	/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Release/libglew.a\
	/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Release/libglfw3.a\
	/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Release/libstb.a\
	/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Release/libimgui.a
	/bin/rm -f /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Release/base


PostBuild.glew.Release:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Release/libglew.a:
	/bin/rm -f /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Release/libglew.a


PostBuild.glfw.Release:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Release/libglfw3.a:
	/bin/rm -f /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Release/libglfw3.a


PostBuild.glm_dummy.Release:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Release/glm_dummy:
	/bin/rm -f /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Release/glm_dummy


PostBuild.imgui.Release:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Release/libimgui.a:
	/bin/rm -f /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Release/libimgui.a


PostBuild.stb.Release:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Release/libstb.a:
	/bin/rm -f /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Release/libstb.a


PostBuild.base.MinSizeRel:
PostBuild.glew.MinSizeRel: /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/MinSizeRel/base
PostBuild.glfw.MinSizeRel: /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/MinSizeRel/base
PostBuild.stb.MinSizeRel: /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/MinSizeRel/base
PostBuild.imgui.MinSizeRel: /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/MinSizeRel/base
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/MinSizeRel/base:\
	/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/MinSizeRel/libglew.a\
	/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/MinSizeRel/libglfw3.a\
	/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/MinSizeRel/libstb.a\
	/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/MinSizeRel/libimgui.a
	/bin/rm -f /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/MinSizeRel/base


PostBuild.glew.MinSizeRel:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/MinSizeRel/libglew.a:
	/bin/rm -f /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/MinSizeRel/libglew.a


PostBuild.glfw.MinSizeRel:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/MinSizeRel/libglfw3.a:
	/bin/rm -f /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/MinSizeRel/libglfw3.a


PostBuild.glm_dummy.MinSizeRel:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/MinSizeRel/glm_dummy:
	/bin/rm -f /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/MinSizeRel/glm_dummy


PostBuild.imgui.MinSizeRel:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/MinSizeRel/libimgui.a:
	/bin/rm -f /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/MinSizeRel/libimgui.a


PostBuild.stb.MinSizeRel:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/MinSizeRel/libstb.a:
	/bin/rm -f /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/MinSizeRel/libstb.a


PostBuild.base.RelWithDebInfo:
PostBuild.glew.RelWithDebInfo: /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/RelWithDebInfo/base
PostBuild.glfw.RelWithDebInfo: /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/RelWithDebInfo/base
PostBuild.stb.RelWithDebInfo: /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/RelWithDebInfo/base
PostBuild.imgui.RelWithDebInfo: /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/RelWithDebInfo/base
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/RelWithDebInfo/base:\
	/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/RelWithDebInfo/libglew.a\
	/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/RelWithDebInfo/libglfw3.a\
	/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/RelWithDebInfo/libstb.a\
	/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/RelWithDebInfo/libimgui.a
	/bin/rm -f /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/RelWithDebInfo/base


PostBuild.glew.RelWithDebInfo:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/RelWithDebInfo/libglew.a:
	/bin/rm -f /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/RelWithDebInfo/libglew.a


PostBuild.glfw.RelWithDebInfo:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/RelWithDebInfo/libglfw3.a:
	/bin/rm -f /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/RelWithDebInfo/libglfw3.a


PostBuild.glm_dummy.RelWithDebInfo:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/RelWithDebInfo/glm_dummy:
	/bin/rm -f /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/RelWithDebInfo/glm_dummy


PostBuild.imgui.RelWithDebInfo:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/RelWithDebInfo/libimgui.a:
	/bin/rm -f /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/RelWithDebInfo/libimgui.a


PostBuild.stb.RelWithDebInfo:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/RelWithDebInfo/libstb.a:
	/bin/rm -f /Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/RelWithDebInfo/libstb.a




# For each target create a dummy ruleso the target does not have to exist
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Debug/libglew.a:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Debug/libglfw3.a:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Debug/libimgui.a:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Debug/libstb.a:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/MinSizeRel/libglew.a:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/MinSizeRel/libglfw3.a:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/MinSizeRel/libimgui.a:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/MinSizeRel/libstb.a:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/RelWithDebInfo/libglew.a:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/RelWithDebInfo/libglfw3.a:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/RelWithDebInfo/libimgui.a:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/RelWithDebInfo/libstb.a:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Release/libglew.a:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Release/libglfw3.a:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Release/libimgui.a:
/Users/camm_rose/Documents/CGRA350/Cityscape/build/bin/Release/libstb.a:
