
ADD_DEFINITIONS(-DEXENG_BUILD)

set (BaseFiles_hpp 
	Forward.hpp
    Exeng.hpp DetectEnv.hpp Config.hpp Enum.hpp DataType.hpp 
    Object.hpp Version.hpp Core.hpp
    TypeInfo.hpp TFlags.hpp Buffer.hpp
    HeapBuffer.hpp StaticBuffer.hpp 
	Resource.hpp ResourceLoader.hpp ResourceManager.hpp 
	# Product.hpp ProductLoader.hpp 
	ProductManager.hpp ProductManagerImpl.hpp
	ISerializable.hpp Timer.hpp
    Common.hpp Boundary.hpp Matrix.hpp Size.hpp Vector.hpp Exception.hpp
)

set (BaseFiles_cpp Enum.cpp Object.cpp 
    Version.cpp  Core.cpp TypeInfo.cpp
    Buffer.cpp HeapBuffer.cpp StaticBuffer.cpp
    Resource.cpp ResourceLoader.cpp ResourceManager.cpp 
    ISerializable.cpp Timer_Win.cpp Timer_Unix.cpp Exception.cpp
)
set (BaseFiles ${BaseFiles_hpp} ${BaseFiles_cpp})

set (IoFiles_cpp io/Stream.cpp io/Stream.inl io/StreamBuffer.cpp)
set (IoFiles_hpp io/Stream.hpp               io/StreamBuffer.hpp)
set (IoFiles ${IoFiles_hpp} ${IoFiles_hpp})

set (AudioFiles_cpp sfx/AudioBuffer.cpp sfx/Listener.cpp sfx/Source.cpp)
set (AudioFiles_hpp sfx/AudioBuffer.hpp sfx/Listener.hpp sfx/Source.hpp)
set (AudioFiles ${AudioFiles_hpp} ${AudioFiles_cpp})

set (FrameworkFiles_cpp
	fw/Application.cpp fw/GraphicsApplication.cpp
)
set (FrameworkFiles_hpp 
	fw/Main.hpp                fw/Main.inl
	fw/Application.hpp         fw/GraphicsApplication.hpp 
)
set (FrameworkFiles ${FrameworkFiles_hpp} ${FrameworkFiles_cpp})

set (ComputeFiles_hpp
    compute/ComputeBuffer.hpp compute/ComputeDevice.hpp compute/ComputeManager.hpp compute/Kernel.hpp 
)
set (ComputeFiles_cpp
    compute/ComputeBuffer.cpp compute/ComputeDevice.cpp compute/ComputeManager.cpp compute/Kernel.cpp            
)
set (ComputeFiles ${ComputeFiles_hpp} ${ComputeFiles_cpp})

set (GraphicsFiles_hpp
    gfx/Primitive.hpp
    gfx/ShaderType.hpp           
    gfx/TextureType.hpp			
    gfx/GraphicsDriver.hpp       
    gfx/GraphicsDriverBase.hpp   
    gfx/GraphicsManager.hpp      
    gfx/Image.hpp                
    gfx/Material.hpp             
    gfx/PixelFormat.hpp          
	gfx/VertexFormat.hpp 
	gfx/VertexArray.hpp 
    gfx/Vertex.hpp
    gfx/IndexFormat.hpp          
    gfx/Texture.hpp              
    gfx/ColorFormat.hpp          
    gfx/Shader.hpp               
    gfx/ShaderProgram.hpp        

	gfx/Forward.hpp        

    gfx/MeshSubset.hpp			
    gfx/MeshSubsetBase.hpp	
	gfx/MeshSubsetTransformer.hpp	
	gfx/MeshSubsetGenerator.hpp	
	gfx/Mesh.hpp
    gfx/MeshManager.hpp
    gfx/MeshLoader.hpp

	gfx/PixelType.hpp		

	gfx/TextureManager.hpp
	gfx/TextureLoader.hpp
	gfx/ModernModule.hpp
	gfx/LegacyModule.hpp
	gfx/TextureLoader.hpp
	gfx/MaterialLibrary.hpp
	gfx/ShaderLibrary.hpp 
)

set (GraphicsFiles_cpp
    gfx/TextureType.cpp 
    gfx/GraphicsDriver.cpp 
    gfx/GraphicsManager.cpp 
    gfx/Image.cpp 
    gfx/Material.cpp 
    gfx/PixelFormat.cpp 
    gfx/Vertex.cpp
    gfx/VertexFormat.cpp
	gfx/VertexArray.cpp
    gfx/IndexFormat.cpp
    gfx/Texture.cpp
    gfx/ColorFormat.cpp
    gfx/Shader.cpp
    gfx/ShaderProgram.cpp
    gfx/MeshSubset.cpp
	gfx/MeshSubsetTransformer.cpp
	gfx/MeshSubsetGenerator.cpp
	gfx/Mesh.cpp
    gfx/MeshManager.cpp
    gfx/MeshLoader.cpp
	gfx/TextureManager.cpp
	gfx/TextureLoader.cpp
	gfx/LegacyModule.cpp
	gfx/ModernModule.cpp
	gfx/MaterialLibrary.cpp
	gfx/ShaderLibrary.cpp
)
set (GraphicsFiles ${GraphicsFiles_hpp} ${GraphicsFiles_cpp})

set (InputFiles_cpp
    input/IEventRaiser.cpp
    input/IEventHandler.cpp
    input/InputData.cpp 
    input/EventData.cpp 
)
set (InputFiles_hpp
    input/IEventRaiser.hpp    
    input/IEventHandler.hpp   
    input/InputData.hpp       
    input/EventData.hpp       
)
set (InputFiles ${InputFiles_hpp} ${InputFiles_cpp})

set (Input2Files_hpp
	input2/IEvent.hpp 
	input2/IEventHandler.hpp 
	input2/IInputDevice.hpp 
	input2/IInputManager.hpp 
	input2/IKeyboard.hpp 
	input2/IMouse.hpp 
	input2/KeyboardStatus.hpp 
	input2/KeyCode.hpp 
	input2/KeyStatus.hpp 
	input2/KeyStroke.hpp 
)
set (Input2Files ${Input2Files_hpp})

set (ScenegraphFiles_cpp
	sg/ISceneRenderer.cpp
    sg/SceneNode.cpp 
    sg/Scene.cpp
	sg/SceneNodeAnimator.cpp
	sg/SceneLoader.cpp
	sg/SceneManager.cpp
	sg/SceneRenderer.cpp
	sg/SceneRendererBase.cpp
	sg/SceneRendererGeneric.cpp
	sg/SceneLoader.cpp
    sg/Camera.cpp 
    sg/Light.cpp
    sg/Geometry.cpp
	sg/AssetsLibrary.cpp
	sg/GeometryLibrary.cpp
)

set (ScenegraphFiles_hpp
	sg/Forward.hpp 
	sg/ISceneRenderer.hpp
    sg/SceneNode.hpp      
    sg/Scene.hpp          
    sg/Camera.hpp         
    sg/Light.hpp          
    sg/Geometry.hpp       
    sg/TSolidGeometry.hpp 
    sg/Segment.hpp 
    sg/Box.hpp            
    sg/Ray.hpp            
    sg/Plane.hpp          
    sg/Intersect.hpp      
    sg/IntersectInfo.hpp  
    sg/Sphere.hpp
    sg/Triangle.hpp
	sg/SceneRenderer.hpp
	sg/SceneRendererBase.hpp
    sg/SceneRendererGeneric.hpp
	sg/SceneLoader.hpp
	sg/SceneManager.hpp
	sg/SceneNodeAnimator.hpp
	sg/AssetsLibrary.hpp
	sg/GeometryLibrary.hpp
)
set (ScenegraphFiles ${ScenegraphFiles_hpp} ${ScenegraphFiles_cpp})

set (SystemFiles_cpp
    sys/Library.cpp 
    sys/Plugin.cpp 
    sys/PluginManager.cpp 
    sys/LibraryPrivatePosix.cpp sys/LibraryPrivateWin32.cpp
)
set (SystemFiles_hpp
	sys/Forward.hpp        
    sys/Library.hpp        
    sys/Plugin.hpp         
    sys/PluginLibrary.hpp  
    sys/PluginManager.hpp  
    sys/LibraryPrivate.hpp 
)
set (SystemFiles ${SystemFiles_hpp} ${SystemFiles_cpp})

set (UtilFiles_cpp 
	util/FrameCounter.cpp 
	util/MessageBox.cpp)

set (UtilFiles_hpp 
	util/FrameCounter.hpp 
	util/MessageBox.hpp)

set (UtilFiles ${UtilFiles_hpp} ${UtilFiles_cpp})

add_library (xe SHARED
    ${BaseFiles}
    ${IoFiles}
    ${AudioFiles}
    ${FrameworkFiles}
    ${ComputeFiles}
    ${GraphicsFiles}
    ${InputFiles}
	${Input2Files}
    ${ScenegraphFiles}
    ${SystemFiles}
    ${UtilFiles}
)

SET_PROPERTY (TARGET xe PROPERTY CXX_STANDARD 14)

SOURCE_GROUP(\\			FILES ${BaseFiles})
SOURCE_GROUP(io         FILES ${IoFiles})
SOURCE_GROUP(sfx      	FILES ${AudioFiles})
SOURCE_GROUP(fw  		FILES ${FrameworkFiles})
SOURCE_GROUP(compute    FILES ${ComputeFiles})
SOURCE_GROUP(gfx   		FILES ${GraphicsFiles})
SOURCE_GROUP(input      FILES ${InputFiles})
SOURCE_GROUP(input2     FILES ${Input2Files})
SOURCE_GROUP(sg 		FILES ${ScenegraphFiles})
SOURCE_GROUP(sys	    FILES ${SystemFiles})
SOURCE_GROUP(util		FILES ${UtilFiles})

TARGET_LINK_LIBRARIES(xe ${UNIX_LIBRARIES} lwobject xmlpp ${Boost_LIBRARIES} ${LIBXML2_LIBRARIES})

INSTALL (
	TARGETS xe 
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
)

INSTALL (FILES ExengConfig.cmake		DESTINATION lib/cmake/xe/)
INSTALL (FILES ${BaseFiles_hpp}			DESTINATION include/xe)
INSTALL (FILES ${IoFiles_hpp}			DESTINATION include/xe/io)
INSTALL (FILES ${AudioFiles_hpp}		DESTINATION include/xe/sfx)
INSTALL (FILES ${FrameworkFiles_hpp}	DESTINATION include/xe/fw)
INSTALL (FILES ${ComputeFiles_hpp}		DESTINATION include/xe/compute)
INSTALL (FILES ${GraphicsFiles_hpp}		DESTINATION include/xe/gfx)
INSTALL (FILES ${InputFiles_hpp}		DESTINATION include/xe/input)
INSTALL (FILES ${Input2Files_hpp}		DESTINATION include/xe/input2)
INSTALL (FILES ${ScenegraphFiles_hpp}	DESTINATION include/xe/sg)
INSTALL (FILES ${SystemFiles_hpp}		DESTINATION include/xe/sys)
INSTALL (FILES ${UtilFiles_hpp}			DESTINATION include/xe/util)