/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include <stdexcept>
#include <cstdint>
#include <boost/shared_array.hpp>

#include <xe/gfx/Image.hpp>

using namespace xe;
using namespace xe::gfx;

namespace xe {
    namespace gfx {
        struct Image::Private {
            Vector3i size;
            ColorFormat format;
            PixelType type;
            boost::shared_array<std::uint8_t> data;
                    
            Private() : size(0, 0, 0), type(PixelType::Unknown) {
            }
        };
    }
}


namespace xe {
    namespace gfx {
        Image::Image() : Data(nullptr) {
        }
        
        
        Image::Image(const Vector3i& size, ColorFormat format, PixelType type) : Data(nullptr) {
            this->initialize(size, format, type);
        }
        
        
        Image::~Image() {
            if (this->Data) {
                delete this->Data;
                this->Data = nullptr;    
            }
        }
        
        
        const void* Image::getPtr() const {
            assert(this->Data != nullptr);
            return (void*)this->Data->data.get();
        }
        
        
        void* Image::getPtr() {
            assert(this->Data != nullptr);
            return (void*)this->Data->data.get();
        }
        
        
        ColorFormat Image::getFormat() const {
            assert(this->Data != nullptr);
            return this->Data->format;
        }
        
        
        PixelType Image::getType() const {
            assert(this->Data != nullptr);
            return this->Data->type;
        }
        
        
        xe::Vector3i Image::geSize() const {
            assert(this->Data != nullptr);
            return this->Data->size;
        }
        
        
        void Image::initialize(const xe::Vector3i& size, ColorFormat format, PixelType type) {
            std::uint32_t imageSize;
            
            //Validar el formato y el tipo de datos
            /*
            if (format == ColorFormat::Unknown) {
                throw std::invalid_argument("'format' argument has an invalid value");
            }
            */
            
            if (type != PixelType::Integer ) {
                throw std::invalid_argument("Only integer image types supported by now");
            }
            
            if (size.x <= 0 || size.y <= 0 || size.z != 0) {
                throw std::invalid_argument("Only rectangular images supported");
            }

            //Continuar con el proceso de inicializacion
            if (this->Data) {
                delete this->Data;
            }
            
            this->Data = new Image::Private();
            
            // imageSize = ColorFormat::getPitch(format) * size.z * size.y;
            imageSize = 1;
            
            this->Data->format = format;
            this->Data->type = type;
            this->Data->size = size;
            
            this->Data->data.reset(new std::uint8_t[imageSize]);
        }
        
        
        std::uint32_t Image::getPixel(const Vector2i& position) const {
            assert( this->Data != nullptr );
            assert( position.x <  this->Data->size.x );
            assert( position.y <  this->Data->size.y );
            
            std::uint32_t *imagePointer = (std::uint32_t*)( this->Data->data.get() );
            
            return imagePointer[ this->getOffset(position) ];
        }
        
            
        void Image::setPixel(const Vector2i& position, std::uint32_t color) {
            assert( this->Data != nullptr );
            assert( position.x <  this->Data->size.x );
            assert( position.y <  this->Data->size.y );
            
            std::uint32_t *imagePointer = (std::uint32_t*)( this->Data->data.get() );

            imagePointer[ this->getOffset(position) ] = color;
        }


        int Image::getOffset(const Vector2i& position) const {
            assert(this->Data != nullptr);
            assert( position.x <  this->Data->size.x );
            assert( position.y <  this->Data->size.y );
            
            return position.y * this->Data->size.x + position.x;
        }
    }
}