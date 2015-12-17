
#ifndef __EXENG_RAYTRACER_RENDERERS_HARDWARERENDERERPRIVATE_HPP__
#define __EXENG_RAYTRACER_RENDERERS_HARDWARERENDERERPRIVATE_HPP__

#define NOMINMAX

#include <CL/cl.h>
#include <CL/cl_gl.h>

#include <CL/cl.hpp>
#include <GLFW/glfw3.h>

#include <list>
#include <stack>

#include <exeng/Matrix.hpp>
#include <exeng/graphics/Texture.hpp>
#include <exeng/graphics/MaterialLibrary.hpp>
#include <exeng/scenegraph/Ray.hpp>
#include <exeng/scenegraph/Camera.hpp>
#include <exeng/scenegraph/SceneNodeData.hpp>
#include <exeng/scenegraph/AssetsLibrary.hpp>

#include "exeng.raytracer/samplers/Sampler.hpp"

namespace exeng { namespace raytracer { namespace renderers {

	using namespace exeng::graphics;
	using namespace exeng::scenegraph;
	using namespace ::raytracer::samplers;

	// ClearSynthesisData
	typedef cl::make_kernel<cl::Buffer> ClearSynthesisDataFunctor;

	// GenerateRays
	typedef cl::make_kernel <
		cl::Buffer,				// [out]
		float, float, float,	// camera_position
		float, float, float,	// camera_lookat
		float, float, float		// camera_up
	> GenerateRaysFunctor;
		
	// ComputeSynthesisData
	typedef cl::make_kernel <
		cl::Buffer,	// [out] synthesis_buffer
		cl::Buffer,	// rays
		cl::Buffer,	// vertices
		cl::Buffer,	// indices
		int,		// index_count
		int,		// material_index
		cl::Buffer,	// transform
		cl::Buffer,	// samples
		int			// sample_count
	> ComputeSynthesisDataFunctor;

	// SynthetizeImage
	typedef cl::make_kernel <
		cl::Image2DGL,	// [out] image
		cl::Buffer,		// synthesisBuffer
		cl::Buffer,		// rays
		int,			// materialSize
		cl::Buffer		// materialData
	> SynthetizeImageFunctor;

	struct FunctorPack {
		FunctorPack(cl::Kernel clear, cl::Kernel generate, cl::Kernel compute, cl::Kernel synthetize) : 
			clearSynthesisDataFunctor(clear),
			generateRaysFunctor			(generate),
			computeSynthesisDataFunctor	(compute),
			synthetizeImageFunctor		(synthetize) 
		{}

		ClearSynthesisDataFunctor	clearSynthesisDataFunctor;
		GenerateRaysFunctor			generateRaysFunctor;
		ComputeSynthesisDataFunctor	computeSynthesisDataFunctor;
		SynthetizeImageFunctor		synthetizeImageFunctor;
	};

    class HardwareRendererPrivate {
	public:
		HardwareRendererPrivate (
			Texture *renderTarget, 
			const AssetLibrary *assets, 
			const MaterialLibrary *materialLibrary, 
			Sampler *sampler
		);

        exeng::graphics::Texture *renderTarget = nullptr;
        const exeng::graphics::MaterialLibrary *materialLibrary = nullptr;

        Matrix4f modelView = identity<float, 4>();

        cl::Platform platform;
		cl::Device device;
		cl::Context context;

		cl::Program program;
		cl::Image2DGL image;

		std::unique_ptr<FunctorPack> functors;

        std::vector<exeng::scenegraph::Ray> raysData;
        
		cl::Buffer raysBuffer;
		cl::Buffer synthesisBuffer;

		cl::Buffer samplesBuffer;
		cl::CommandQueue queue;
        cl::Buffer materialBuffer;

		cl_int samplesCount = 0;

		cl_int synthesisElementSize = 0;
		cl_int raySize = 0;
		
		// TODO: Determine the appropiate range at run-time
		// cl::NDRange localSize = cl::NDRange(16, 8);	
        cl::NDRange localSize = cl::NDRange(4, 4);
        
        cl::Buffer localTransformBuffer;

		float clearSynthesisBufferTime = 0.0f;
		float generateRaysTime = 0.0f;
		float computeSynthesisBufferTime = 0.0f;
		float computeImageTime = 0.0f;

    public:
		~HardwareRendererPrivate();

        static std::string clErrorToString(cl_int errCode);
        static Vector2i indexToCoord(int index, int width, int height);
        static cl::Buffer createBuffer(cl::Context &context, const exeng::graphics::MaterialLibrary *library);

        void setRenderTarget(exeng::graphics::Texture *renderTarget);

        void generateRays(const exeng::scenegraph::Camera *camera);

        void clearSynthesisBuffer();

	    void computeSynthesisBuffer(const exeng::scenegraph::SceneNodeData *nodeData);

	    void computeImage();

        void updateStructSizes();

        void setTransform(const Matrix4f &localTransform);
    };
}}}

#endif  // __EXENG_RAYTRACER_RENDERERS_HARDWARERENDERER_HPP__
