#ifndef PLEXI_BUFFER_HPP
#define PLEXI_BUFFER_HPP

#include <string>
#include <memory>
#include <utility>
#include <vector>
namespace Plexi::Buffer {
//open GL Gen then bind buffers

    struct BufferElement {
        std::string parameterName;
        Shaders::DataType dataType;
        uint32_t size;
        size_t offset;
        bool normalized;

        BufferElement(Shaders::DataType type, std::string name, bool normal) :
            parameterName(std::move(name)), dataType(type), size(Shaders::getDataTypeSize(dataType)), offset(0), normalized(normal)
        {}

        BufferElement(Shaders::DataType type, std::string name) :
            parameterName(std::move(name)), dataType(type), size(Shaders::getDataTypeSize(dataType)), offset(0), normalized(false)
        {}

    };

    class BufferLayout {
    public:
        BufferLayout() = default;
        //Public Functions
        BufferLayout(const std::initializer_list<BufferElement>& elements) :
            bufferElements(elements), stride(0) //To make clang tidy shut up.
        {
            calcStrideAndOffset(bufferElements);
        }

        //Getters
        uint32_t getStride(){ return stride; }
        uint32_t getStride() const { return stride; }
        std::vector<BufferElement> getBufferElements() { return bufferElements; }

        //Stupid for loop bois to make the syntax slightly nicer
        std::vector<BufferElement>::iterator begin() { return bufferElements.begin();}
        std::vector<BufferElement>::iterator end() { return bufferElements.end(); }
        //Const version of above bc c++ is weird
        [[nodiscard]] std::vector<BufferElement>::const_iterator begin() const { return bufferElements.begin();}
        [[nodiscard]] std::vector<BufferElement>::const_iterator end() const  { return bufferElements.end(); }

    private:
        //Private Functions
        void calcStrideAndOffset(std::vector<BufferElement> &elements) { // Defined here bc other wise it would be one function in a cpp file
            size_t offset = 0;
            stride = 0;

            for(auto& element : elements){
                element.offset = offset;
                offset += element.size;
                stride += element.size;
            }

        }    private:
        //Private Vars
        std::vector<BufferElement> bufferElements;
        uint32_t stride;
    };


    //Default vertex arrays
    const float SQUARE_VERTICES_WITH_TEXTURE[20]{//4X5
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };
    const size_t SQUARE_VERTICES_WITH_TEXTURE_SIZE = 20;

    const float TRIANGLE_VERTICES_NO_TEXTURE[9] {//3X3
        -0.5f, -0.5f, 0.0f,
        0.25f, 0.25f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

    const size_t TRIANGLE_VERTICES_NO_TEXTURE_SIZE = 9;

    //Default index arrays
    const uint32_t SQUARE_INDICES[7] = {
            0, 1, 2, 2, 3, 0
    };

    const size_t SQUARE_INDICES_SIZE = 7;

    const uint32_t TRIANGLE_INDICES[4] = {//This one might be wrong
            0, 1, 2, 0
    };

    const size_t TRIANGLE_INDICES_SIZE = 4;

    struct BufferCreateInfo {
        std::string shaderName = "";
        size_t vertexArraySize = 0;
        size_t indexArraySize = 0;
        const float *vertexArray = nullptr;
        const uint32_t *indexArray = nullptr;
        void setLayout(const BufferLayout& layout){ bufferLayout = layout; }
        [[nodiscard]] Buffer::BufferLayout getLayout() const { return bufferLayout; }

    private:
        Buffer::BufferLayout bufferLayout;// = nullptr;

    };


}




#endif //PLEXI_BUFFER_HPP
