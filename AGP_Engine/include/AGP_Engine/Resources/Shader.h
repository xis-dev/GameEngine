#pragma once

#include "Resource.h"
#include "Utility/Utility.h"


namespace AGPEngine {
    // Shader descriptor
    struct ShaderDesc {

        const char* vertexShader{nullptr};
        const char* fragmentShader{nullptr};
        const char* geometryShader{nullptr};
    };

    struct ShaderStage {

        enum class Stage {
            VERTEX,
            FRAGMENT,
            GEOMETRY
        } stage;
    };

    class Shader: public GPUResource {

        using Error = Error<Shader>;
    public:
        Shader() = default;

        Shader(Shader&&) = default;
        Shader& operator=(Shader&&) = default;

        ~Shader() override;

        //std::expected<Shader, Error> Create(const ShaderDesc& desc);

        // TODO: Actual shaders as resources, this is a quick ver to get it up
        Shader(const std::string& vert, const std::string& frag);

        void use() const;

        void destroy() override;

    private:
        std::string getShaderSource(const std::string& file);
    };
}
