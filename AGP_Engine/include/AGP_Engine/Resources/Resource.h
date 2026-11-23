    #pragma once

    #include <cstdint>
    #include <utility>

    // TODO: Not 100% sure on normal cpu based resources so just gpu for now

    using GPUResourceHandle = uint32_t;
    class GPUResource {
    public:

        static constexpr GPUResourceHandle InvalidHandle = UINT32_MAX;

        GPUResource() = default;
        virtual ~GPUResource() = default;

        // Resources are non copyable and only movable
        GPUResource(const GPUResource&) = delete;
        GPUResource& operator=(const GPUResource&) = delete;

        GPUResource(GPUResource&& r) noexcept: m_handle(std::exchange(r.m_handle, InvalidHandle)){}
        GPUResource& operator=(GPUResource&& r) noexcept {
            if (this != &r) {
                destroy();
                m_handle = std::exchange(r.m_handle, InvalidHandle);
            }
            return *this;
        }

        [[nodiscard]] GPUResourceHandle getHandle() const {return m_handle;}
        [[nodiscard]] bool isValid() const {return m_handle != InvalidHandle;}


        virtual void destroy() = 0;

    protected:
        uint32_t m_handle{InvalidHandle};
    };