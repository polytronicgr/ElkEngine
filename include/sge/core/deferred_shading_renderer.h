#pragma once

#include "sge/core/object_3d.h"
#include "sge/core/camera.h"
#include "sge/core/shader_program.h"
#include "sge/core/renderer.h"
#include "sge/object_extensions/framebuffer_quad.h"

#include <memory>
#include <vector>

namespace sge { namespace core {

class Renderable;
class LightSource;

class DeferredShadingRenderer {
public:
  DeferredShadingRenderer(
    PerspectiveCamera& camera, int framebuffer_width, int framebuffer_height);
  ~DeferredShadingRenderer();
  
  void submitRenderable(Renderable& renderable);
  void submitLightSource(LightSource& light_source);

  void setWindowResolution(int width, int height);
  void render(Object3D& scene);
private:
  void checkForErrors();

  int _window_width, _window_height;

  std::shared_ptr<ShaderProgram> _gbuffer_program;
  std::shared_ptr<ShaderProgram> _shading_program_point_lights;
  std::shared_ptr<ShaderProgram> _shading_program_directional_light;

  std::unique_ptr<FrameBufferQuad> _fbo_quad;

  PerspectiveCamera& _camera;

  std::vector<Renderable*> _renderables_to_render;
  std::vector<LightSource*> _light_sources_to_render;
};

} }