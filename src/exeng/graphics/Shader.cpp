/**
 * @file Shader.cpp
 * @brief Shader class implementation.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#include <exeng/graphics/Shader.hpp>


namespace exeng {
namespace graphics {

Shader::Shader(ResourceFactory *factory) : Resource(factory) {
}

Shader::~Shader()
{
}

}
}