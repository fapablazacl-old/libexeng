
#ifndef __EXENG_SCENEGRAPH_GENERICSCENERENDERER_HPP__
#define __EXENG_SCENEGRAPH_GENERICSCENERENDERER_HPP__

#include <stack>
#include <functional>
#include <exeng/Exception.hpp>
#include <exeng/Matrix.hpp>
#include <exeng/graphics/GraphicsDriver.hpp>
#include <exeng/graphics/MeshSubset.hpp>
#include <exeng/graphics/Mesh.hpp>
#include <exeng/scenegraph/SceneRenderer.hpp>
#include <exeng/scenegraph/SceneNode.hpp>
#include <exeng/scenegraph/Camera.hpp>

namespace xe { namespace sg {

    /** 
     * @brief Renderer technology minimal interface
     */
	class EXENGAPI RenderWrapper {
	public:
        virtual ~RenderWrapper() {}

        virtual void prepareCamera(const xe::sg::Camera *camera) = 0;

		virtual void setTransform(const Matrix4f &transform) = 0;
		virtual void renderNodeData(const SceneNodeData *data) = 0;

        virtual void beginFrame(const Vector4f &clearColor) = 0;
        virtual void endFrame() = 0;

        virtual Matrix4f getViewMatrix(const Camera *camera);
        virtual Matrix4f getProjectionMatrix(const Camera *camera);
	};
    
    typedef std::unique_ptr<RenderWrapper> RenderWrapperPtr;

    /**
     * Scene renderer technology based on a rasterizer
     */
	class EXENGAPI RasterizerRenderWrapper : public RenderWrapper {
	public:
		explicit RasterizerRenderWrapper(xe::gfx::GraphicsDriver *driver);
		virtual ~RasterizerRenderWrapper();

        virtual void prepareCamera(const xe::sg::Camera *camera) {}

        virtual void beginFrame(const Vector4f &clearColor) override;
        virtual void endFrame() override;

        virtual void setTransform(const Matrix4f &transform) override;
		
		virtual void renderNodeData(const xe::sg::SceneNodeData *data) override;

        void setTransformName(const std::string &transformName);
        xe::gfx::GraphicsDriver* getGraphicsDriver();
		const xe::gfx::GraphicsDriver* getGraphicsDriver() const;

	private:
        struct Private;
        Private *impl = nullptr;
	};

    typedef std::unique_ptr<RasterizerRenderWrapper> RasterizerRenderWrapperPtr;

    /**
     *
     */
	class EXENGAPI GenericSceneRenderer : public SceneRenderer {
	public:
        explicit GenericSceneRenderer(RenderWrapperPtr renderWrapper);
        ~GenericSceneRenderer();

        RenderWrapper* getRenderWrapper();

        const RenderWrapper* getRenderWrapper() const;

		virtual void setScene(const Scene *scene) override;

		virtual const Scene* getScene() const override;

		virtual void render(const Camera *camera) override;

	private:
        struct Private;
        Private *impl = nullptr;
	};
}}

#endif  // __EXENG_SCENEGRAPH_GENERICSCENERENDERER_HPP__
