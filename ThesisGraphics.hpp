#ifndef THESIS_GRAPHICS_H
#define THESIS_GRAPHICS_H

#include <iostream>
#include <Corrade/Containers/Array.h>
#include <Corrade/Containers/Optional.h>
#include <Corrade/PluginManager/Manager.h>
#include <Corrade/Utility/Arguments.h>
#include <Corrade/Utility/Directory.h>
#include <Corrade/Utility/DebugStl.h>
#include <Magnum/ImageView.h>
#include <Magnum/Mesh.h>
#include <Magnum/PixelFormat.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/GL/Texture.h>
#include <Magnum/GL/TextureFormat.h>
#include <Magnum/Math/Color.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/SceneGraph/Scene.h>
#include <Magnum/Shaders/Phong.h>
#include <Magnum/Trade/AbstractImporter.h>
#include <Magnum/Trade/ImageData.h>
#include <Magnum/Trade/MeshData.h>
#include <Magnum/Trade/CameraData.h>
#include <Magnum/Trade/MeshObjectData3D.h>
#include <Magnum/Trade/PhongMaterialData.h>
#include <Magnum/Trade/SceneData.h>
#include <Magnum/Trade/TextureData.h>
#include "Serial.hpp"

using namespace Magnum;

using namespace Math::Literals;

typedef SceneGraph::Object<SceneGraph::MatrixTransformation3D> Object3D;
typedef SceneGraph::Scene<SceneGraph::MatrixTransformation3D> Scene3D;

class ThesisGraphics : public Platform::Application {
public:
    explicit ThesisGraphics(const Arguments& arguments, const Configuration& configuration);

private:
    void drawEvent() override;
    void viewportEvent(ViewportEvent& event) override;
    void mousePressEvent(MouseEvent& event) override;
    void mouseReleaseEvent(MouseEvent& event) override;
    void mouseMoveEvent(MouseMoveEvent& event) override;
    void mouseScrollEvent(MouseScrollEvent& event) override;
    void tickEvent() override;

    Vector3 positionOnSphere(const Vector2i& position) const;

    void addObject(Trade::AbstractImporter& importer, Containers::ArrayView<const Containers::Optional<Trade::PhongMaterialData>> materials, Object3D& parent, UnsignedInt i);

    Shaders::Phong _coloredShader,
        _texturedShader{ Shaders::Phong::Flag::DiffuseTexture };
    Containers::Array<Containers::Optional<GL::Mesh>> _meshes;
    Containers::Array<Containers::Optional<GL::Texture2D>> _textures;

    Scene3D _scene;
    Object3D _manipulator, _cameraObject, _endEffector, _ball;
    SceneGraph::Camera3D* _camera;
    SceneGraph::DrawableGroup3D _drawables;
    Vector3 _previousPosition;
   
    Vector2 _previousEffectorPosition;
    Vector2 _previousBallPosition;

    Serial _serial;
};

#endif