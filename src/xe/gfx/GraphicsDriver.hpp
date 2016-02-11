/**
 * @file GraphicsDriver.hpp
 * @brief GraphicsDriver class API and support structures and enumerations.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_GRAPHICS_GRAPHICSDRIVER_HPP__
#define __EXENG_GRAPHICS_GRAPHICSDRIVER_HPP__

#include <string>
#include <vector>
#include <memory>
#include <xe/Enum.hpp>
#include <xe/TFlags.hpp>
#include <xe/Boundary.hpp>
#include <xe/Vector.hpp>
#include <xe/Matrix.hpp>
#include <xe/Buffer.hpp>
#include <xe/input2/IInputManager.hpp>
#include <xe/gfx/Image.hpp>
#include <xe/gfx/Material.hpp>
#include <xe/gfx/PixelFormat.hpp>
#include <xe/gfx/Texture.hpp>
#include <xe/gfx/Primitive.hpp>
#include <xe/gfx/Shader.hpp>
#include <xe/gfx/ShaderProgram.hpp>
#include <xe/gfx/MeshSubset.hpp>
#include <xe/gfx/ModernModule.hpp>
#include <xe/gfx/LegacyModule.hpp>
#include <xe/gfx/Material2.hpp>
#include <xe/cm/Forward.hpp>

namespace xe { namespace gfx {

    /**
     * @brief Framebuffer clearing flags
     */
    struct ClearFlags : public Enum {
        enum Enum {
            Color = 1,
            Depth = 2,
            Stencil = 4,
			ColorDepth = Color | Depth
        };
        
        typedef TFlags<Enum> Flags;
    };
    
    struct DisplayStatus : public Enum {
        enum Enum { Window, Fullscreen };
    };

    /**
     * @brief The used graphics API backend.
     */
    struct GraphicsBackend : public Enum {
        enum Enum {
            Unknown,
            OpenGL_Legacy,
            OpenGL_Core,
            OpenGL_ES_1,
            OpenGL_ES_2,
            OpenGL_ES_3,
            Direct3D_9,
            Direct3D_10,
            Software
        };
    };
    
    /**
    * @brief Encapsulate a display mode.
    */
    struct DisplayMode {
		//! Width and height, in pixels.
        Size2i size = Size2i(640, 480);

		//! Frame buffer colors.
		Vector<std::uint8_t, 4> colorFormat = Vector<std::uint8_t, 4>(8, 8, 8, 8);

		//! Other frame buffer 
        int depthBits = 16;
		int stencilBits = 0;

		//! Fullscreen or window?
        DisplayStatus::Enum status = DisplayStatus::Window;        
        
        //! Enable compute module?
        bool enableCompute = false;
        
		DisplayMode() {}

        DisplayMode(const Size2i &size, const Vector<std::uint8_t, 4> &colorFormat) {
			this->size = size;
			this->colorFormat = colorFormat;
		}

        DisplayMode(const Size2i &size, const Vector<std::uint8_t, 4> &colorFormat, int depthBits, int stencilBits, DisplayStatus::Enum status) {
			this->size = size;
			this->colorFormat = colorFormat;
			this->depthBits = depthBits;
			this->stencilBits = stencilBits;
			this->status = status;
		}
    };
    
    /**
     * @brief Software interface to graphics hardware
     */
	class EXENGAPI GraphicsDriver {
    public:
        virtual ~GraphicsDriver();
        
		virtual DisplayMode getDisplayMode() const = 0;

        /**
         * @brief Initializes the graphics driver, with the settings included. 
         * Throws exception if the graphics drives can't be initialized with the
         * supplied settings.
         * @param displayMode The settings requested.
         */
        virtual void initialize(const DisplayMode &displayMode) = 0;
        
        /**
         * @brief Initializes the graphics driver, with the states specified by default
         * on the DisplayMode structure.
         * Throws exception if the graphics drives can't be initialized with the supplied settings.
         * @param displayMode The settings requested.
         */
        virtual void initialize() = 0;
        
        /**
         * @brief Terminate the use of the graphics drivers, killing all resources 
         * created.
         */
        virtual void terminate() = 0;
        
        /**
         * @brief Checks if the GraphicsDriver has been initialized.
         * @return true if the graphics drivers has been correctly initialized, 
         * and false in other case.
         */
        virtual bool isInitialized() const = 0;
		
        /**
         * @brief Start the rendering of a new frame, clearing the previous one
         */
        virtual void beginFrame(const Vector4f &color, ClearFlags::Flags flags=ClearFlags::ColorDepth) = 0;
        
        /**
         * @brief Flip the backbuffer and the front buffer
         */
        virtual void endFrame() = 0;
        
        /**
         * @brief Set the currently used material
         */
        virtual void setMaterial(const Material* material) = 0;
        
        /**
         * @brief Get the currently used material
         */
        virtual const Material* getMaterial() const = 0;
        
        /**
         * @brief Create a new hardware-based vertex buffer. 
         */
        virtual BufferPtr createVertexBuffer(const std::int32_t size, const void* data) = 0;
        
		template<typename Type>
		BufferPtr createVertexBuffer(const std::vector<Type> &vertices) 
		{
			const int bufferSize = sizeof(Type) * vertices.size();
			const void *bufferData = vertices.data();

			return this->createVertexBuffer(bufferSize, bufferData);
		}

		BufferPtr createVertexBuffer(Buffer *buffer) {
			BufferLocker<void> locker(buffer, BufferUsage::Read);
            
			return this->createVertexBuffer(buffer->getSize(), locker.getPointer());
		}

        /**
         * @brief Like CreateVertexBuffer, create a new hardware based index buffer.
         */
        virtual BufferPtr createIndexBuffer(const std::int32_t size, const void* data) = 0;

		BufferPtr createIndexBuffer(Buffer *buffer) {
            BufferLocker<void> locker(buffer, BufferUsage::Read);
            
			return this->createIndexBuffer(buffer->getSize(), locker.getPointer());
		}
        
		template<typename Type>
		BufferPtr createIndexBuffer(const std::vector<Type> &indices) 
		{
			const int bufferSize = sizeof(Type) * indices.size();
			const void *bufferData = indices.data();

			return this->createIndexBuffer(bufferSize, bufferData);
		}

        MeshSubsetPtr createMeshSubset(BufferPtr vertexBuffer, const VertexFormat &format);

		MeshSubsetPtr createMeshSubset(BufferPtr vertexBuffer, const VertexFormat &format, BufferPtr ibuffer, IndexFormat::Enum iformat);

		MeshSubsetPtr createMeshSubset(std::vector<BufferPtr> vbuffers, const VertexFormat &vformat);

        /**
         * @brief Create a new mesh subset object.
         */
        virtual MeshSubsetPtr createMeshSubset(std::vector<BufferPtr> vbuffers, const VertexFormat &vformat, BufferPtr ibuffer, IndexFormat::Enum iformat) = 0;

        /**
         * @brief Bound the specified MeshSubset object.
         */
        virtual void setMeshSubset(const MeshSubset *meshSubset) = 0;
        
        /**
         * @brief Gets the currently bound MeshSubset.
         */
        virtual const MeshSubset* getMeshSubset() const = 0;

        /**
         * @brief Create a new texture object.
         */
		virtual TexturePtr createTexture(const Vector2i& size, PixelFormat::Enum format, const void *data = nullptr) = 0;
		virtual TexturePtr createTexture(const Vector3i& size, PixelFormat::Enum format, const void *data = nullptr) = 0;
		virtual TexturePtr createTextureCube(const Vector2i& size, PixelFormat::Enum format, const void *data = nullptr) = 0;
        
		virtual TexturePtr createTexture(const Image *image) {
			if (image->getType() == ImageType::Img2D) {
				Vector2i size = image->getSize();
                
                auto locker = image->getBuffer()->getLocker();
                
				return this->createTexture (
					size, 
					image->getFormat(), 
					locker.getPointer()
				);
			} else {
				return nullptr;
			}
		}

        /**
         * @brief Set the area of the screen that can be rendered
         */
        virtual void setViewport(const Rectf& viewport) = 0;
        
        /**
         * @brief Return the currently setted viewport.
         */
        virtual Rectf getViewport() const = 0;
        
        /**
         * @brief Render a primitive using the supplied parameter values and the current state of the graphics driver
		 * (current material and meshsubset).
         * @param primitive The primitive type.
         * @param count The vertex count to utilize from the currently setter meshsubset.
         */
        virtual void render(Primitive::Enum primitive, int count) = 0;
		
		/**
		 * @brief Get an interface to a fixed-function pipeline functionality.
		 */
		virtual LegacyModule* getLegacyModule() = 0;

		/**
		 * @brief Get an interface to a fully-programmable pipeline functionality.
		 */
		virtual ModernModule* getModernModule() = 0;

		virtual xe::input2::IInputManager* getInputManager() = 0;
		
		/**
		 * @brief Create a GPU dependent material.
		 * 
		 * This material *may be* stored in GPU memory.
		 */
		virtual Material2Ptr createMaterial(const MaterialFormat2 *format);
        
        /** 
         * @brief Get the underlying graphics backend identification
         */
        virtual GraphicsBackend::Enum getBackend() const = 0;

        /**
         * @brief Get the graphics backend dependent,
         * @return 
         */        
        virtual std::uint64_t getHandle() const = 0;
    };

	typedef std::unique_ptr<GraphicsDriver> GraphicsDriverPtr;
}}

#endif
