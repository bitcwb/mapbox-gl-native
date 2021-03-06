#pragma once

#include <mbgl/tile/tile_data.hpp>
#include <mbgl/renderer/raster_bucket.hpp>

namespace mbgl {

class FileSource;
class AsyncRequest;

namespace gl { class TexturePool; }

namespace style {
class Layer;
}

class RasterTileData : public TileData {
public:
    RasterTileData(const OverscaledTileID&,
                   float pixelRatio,
                   const std::string& urlTemplate,
                   gl::TexturePool&,
                   Worker&,
                   FileSource&,
                   const std::function<void(std::exception_ptr)>& callback);
    ~RasterTileData();

    void cancel() override;
    Bucket* getBucket(const style::Layer&) override;

private:
    gl::TexturePool& texturePool;
    Worker& worker;
    std::unique_ptr<AsyncRequest> req;
    std::unique_ptr<Bucket> bucket;
    std::unique_ptr<AsyncRequest> workRequest;
};

} // namespace mbgl
