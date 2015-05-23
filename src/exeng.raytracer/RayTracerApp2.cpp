
#include "RayTracerApp2.hpp"

#include <memory>
#include <exeng/StaticBuffer.hpp>
#include <exeng/system/PluginManager.hpp>
#include <exeng/graphics/GraphicsManager.hpp>
#include <exeng/graphics/TextureManager.hpp>
#include <exeng/scenegraph/MeshManager.hpp>
#include <exeng/scenegraph/GenericSceneRenderer.hpp>

#include "resources/Assets.xml.hpp"
#include "resources/VertexShader.glsl.hpp"
#include "resources/FragmentShader.glsl.hpp"
#include "resources/MultiHardwareTracer.cl.hpp"

#include "renderers/SoftwareRenderer.hpp"
#include "renderers/HardwareRenderer.hpp"

namespace exeng { namespace raytracer {
    using namespace exeng::graphics;
    using namespace exeng::scenegraph;
    using namespace exeng::input;
    using namespace exeng::framework;
    using namespace exeng::raytracer::renderers;

    class RotateAnimator : public SceneNodeAnimator {
    public:
        virtual void update(double seconds) override {
            this->angle += static_cast<float>(60.0 * seconds);

            Matrix4f transformation = rotatey<float>(rad(this->angle));

            this->getSceneNode()->setTransform(transformation);
        }

    private:
        float angle = 0.0f;
    };

    RayTracerApp2::RayTracerApp2() {}
    RayTracerApp2::~RayTracerApp2() {}

    BufferPtr RayTracerApp2::getAssetsXmlData() {
        return std::make_unique<StaticBuffer>((void*)assets_xml_data, assets_xml_size);
    }

    std::string RayTracerApp2::getPluginPath() {
#if defined(EXENG_UNIX)
        return "../../plugins/libexeng.graphics.gl3/";
#else
#  if defined (EXENG_DEBUG)
		return "../../bin/Debug/";
#  else 
		return "../../bin/Release/";
#  endif
#endif
	}

    GraphicsDriverPtr RayTracerApp2::createGraphicsDriver() {
        this->getPluginManager()->setPluginPath(this->getPluginPath());
        this->getPluginManager()->loadPlugin("exeng.graphics.gl3");
		
        GraphicsDriverPtr graphicsDriver = this->getGraphicsManager()->createDriver();
        graphicsDriver->addEventHandler(this);
        graphicsDriver->initialize();
	    
		return graphicsDriver;
    }

    AssetLibraryPtr RayTracerApp2::createAssetLibrary() {
        AssetLibraryPtr assetLibrary = std::make_unique<AssetLibrary>();
		assetLibrary->addAsset("Vertex.glsl", std::make_unique<StaticBuffer>((void*)vertexshader_glsl_data, vertexshader_glsl_size));
		assetLibrary->addAsset("Fragment.glsl", std::make_unique<StaticBuffer>((void*)fragmentshader_glsl_data, fragmentshader_glsl_size));
        assetLibrary->addAsset("MultiHardwareTracer.cl", std::make_unique<StaticBuffer>((void*)multihardwaretracer_cl_data, multihardwaretracer_cl_size));

		return assetLibrary;
    }

    SceneRendererPtr RayTracerApp2::createSceneRenderer(GraphicsDriver *graphicsDriver) {
        // Create the material for the rendering of the screen
        Size2i screenSize = graphicsDriver->getDisplayMode().size;
        Texture *renderTarget = this->getTextureManager()->create("renderTarget", screenSize, {0.2f, 0.2f, 0.8f, 1.0f});

        ShaderProgram *program = this->getShaderLibrary()->getProgram("shaderProgram");

        Material *screenMaterial = this->getMaterialLibrary()->createMaterial("screen", program);
        screenMaterial
            ->setAttribute(0, Vector4f(1.0f, 1.0f, 1.0f, 1.0f))
            ->setAttribute(1, Vector4f(0.0f, 0.0f, 0.0f, 1.0f))
            ->setAttribute(2, Vector4f(0.0f, 0.0f, 0.0f, 1.0f))
            ->setAttribute(3, 0.0f)
            ->getLayer(0)->setTexture(renderTarget);
        
        // Create the mesh for rendering
        Mesh *screenMesh = this->getMeshManager()->generateScreenMesh("screen");
        
        AssetLibrary *assets = this->getAssetLibrary();
        MaterialLibrary *materials = this->getMaterialLibrary();

        HardwareRendererPtr 
        renderWrapper = std::make_unique<HardwareRenderer>(renderTarget, assets, materials);
        
        SceneRendererPtr 
        sceneRenderer = std::make_unique<GenericSceneRenderer>(std::move(renderWrapper));
        sceneRenderer->setScene(this->getScene());

        return sceneRenderer;
    }

    bool RayTracerApp2::onInitialize() {
        this->screenMaterial = this->getMaterialLibrary()->getMaterial("screen");
        this->screenMesh = this->getMeshManager()->getMesh("screen");
        this->camera = this->getScene()->getCamera(0);

        this->animator = std::make_unique<RotateAnimator>();
        this->animator->setSceneNode(this->getScene()->getRootNode()->findNode("boxNode"));
        
        return true;
    }

    void RayTracerApp2::handleEvent(const EventData &data) {
        const InputEventData &inputData = data.cast<InputEventData>();
        
        if (inputData.check(ButtonStatus::Press, ButtonCode::KeyEsc)) {
            this->setApplicationStatus(ApplicationStatus::Terminated);
        }
    }

    void RayTracerApp2::update(float seconds) {
        this->animator->update(seconds);
    }

    void RayTracerApp2::render() {
        this->getGraphicsDriver()->beginFrame({0.2f, 0.2f, 0.8f, 1.0f}, ClearFlags::ColorDepth);

        // render the scene using ray tracing
        this->getSceneRenderer()->render(this->camera);

        // render the render target texture
        this->getGraphicsDriver()->setMaterial(this->screenMaterial);
        this->getGraphicsDriver()->getModernModule()->setProgramGlobal("WorldTransform", identity<float, 4>());
        this->renderMesh(this->screenMesh);

        this->getGraphicsDriver()->endFrame();
    }
}}

namespace exeng { namespace main {
    int main(int argc, char **argv) {
        using namespace exeng;
        using namespace exeng::framework;
        using namespace exeng::raytracer;

        return Application::execute<RayTracerApp2>(argc, argv);
    }
}}
