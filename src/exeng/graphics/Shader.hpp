/**
 * @file Shader.hpp
 * @brief Shader class definition.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_GRAPHICS_SHADER_HPP__
#define __EXENG_GRAPHICS_SHADER_HPP__

#include <exeng/Resource.hpp>
#include <exeng/graphics/ShaderType.hpp>

namespace exeng {
namespace graphics {

/**
 * @brief A shader subprogram, with source code included.
 */
class EXENGAPI Shader : public Resource {
public:
    Shader(ResourceFactory *factory);
    
    virtual ~Shader();
    
    /**
     * @brief Set the current source code for the shader.
     * @param sourceCode The source code
     */
    virtual void setSourceCode(const std::string &sourceCode) = 0;
    
    /**
     * @brief Get the current source of the shader subprogram
     * @return 
     */
    virtual std::string getSourceCode() const = 0;
    
    /**
     * @brief Check if the shader source has been modified.
     * @return 
     */
    virtual bool isSourceModified() const = 0;
    
    /**
     * @brief Compiles the shader source. If an error ocurred, a 
     * std::runtime_error exception is thrown.
     */
    virtual void compile() = 0;
    
    /**
     * @brief Check if the shader source has been compiled.
     */
    virtual bool isCompiled() const = 0;
    
    /**
     * @brief Get the type of shader.
     */
    virtual ShaderType getType() const = 0;
};
}
}

#endif // __EXENG_GRAPHICS_SHADER_HPP__