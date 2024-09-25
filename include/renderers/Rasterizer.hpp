#include "cameras/Camera.hpp"
#include "math/Matrix3x3.hpp"
#include "primitives/Fragment.hpp"
#include "primitives/Mesh.hpp"
#include "primitives/RenderTarget.hpp"
#include "primitives/Scene.hpp"
#include <cmath>
#include <functional>
#include <set>
#include <stack>

#ifndef RASTERIZER_HPP
#define RASTERIZER_HPP

namespace t {

class Rasterizer {
public:
  template <class BufferType>
  void render(Scene &scene, Camera &camera,
              RenderTarget<BufferType> &renderTarget) {
    RenderTarget<double> depthTexture(renderTarget.texture.width,
                                      renderTarget.texture.height,
                                      TextureFormat::Depth);
    // Clear the depth texture and the render target

    for (int i = 0; i < renderTarget.width * renderTarget.height; ++i) {
      depthTexture.texture.image[i] = 2; // NDC Z ranges from -1 to 1
      renderTarget.texture.image[i * 3] = 0;
      renderTarget.texture.image[i * 3 + 1] = 0;
      renderTarget.texture.image[i * 3 + 2] = 0;
    }

    // Traverse the 3D scene tree and update the local and world matrices

    std::vector<std::reference_wrapper<Mesh>> meshes;
    std::vector<std::reference_wrapper<Light>> lights;
    std::stack<std::reference_wrapper<Object3D>> objects;

    objects.push(scene);

    while (!objects.empty()) {
      Object3D &parent = objects.top();
      objects.pop();

      parent.updateLocalMatrix();
      parent.updateModelMatrix();

      for (Object3D &child : parent.children) {
        if (child.isMesh()) {
          child.updateLocalMatrix();
          child.updateModelMatrix();
          meshes.push_back(static_cast<Mesh &>(child));
        } else {
          objects.push(child);

          if (child.isLight()) {
            lights.push_back(static_cast<Light &>(child));
          }
        }
      }
    }

    const auto cameraWorldPosHomo =
        camera.modelMatrix * Vector4(camera.localPosition, 1);
    auto cameraWorldPos = Vector3(cameraWorldPosHomo.x / cameraWorldPosHomo.w,
                                  cameraWorldPosHomo.y / cameraWorldPosHomo.w,
                                  cameraWorldPosHomo.z / cameraWorldPosHomo.w);

    // Compute the view matrix

    // FIXME: don't hardcode the lookat
    auto w = (cameraWorldPos - Vector3(0, 0, 0)).normalize();
    auto u = Vector3::cross(w, camera.up).normalize();
    auto v = Vector3::cross(w, u);

    // clang-format off
    auto viewMatrix = Matrix4x4(
      u.x, u.y, u.z, 0,
      v.x, v.y, v.z, 0,
      w.x, w.y, w.z, 0,
        0,   0,   0, 1
    ) * Matrix4x4(
      1, 0, 0, -cameraWorldPos.x,
      0, 1, 0, -cameraWorldPos.y,
      0, 0, 1, -cameraWorldPos.z,
      0, 0, 0,                 1
    );
    // clang-format on

    // Compute the viewport transform matrix‒used to transform from clip space
    // to viewport space

    // clang-format off
    auto viewportMatrix = Matrix4x4(
      renderTarget.width / 2.0, 0, 0, (renderTarget.width - 1) / 2.0,
      0, renderTarget.height / 2.0, 0, (renderTarget.height - 1) / 2.0,
      0, 0, 1, 0,
      0, 0, 0, 1
    );
    // clang-format on

    // Draw the meshes; one mesh per "draw call".

    for (Mesh &mesh : meshes) {
      auto geometry = mesh.geometry;
      auto modelViewMatrix = viewMatrix * mesh.modelMatrix;
      auto normalMatrix =
          Matrix3x3(mesh.modelMatrix.elements[0], mesh.modelMatrix.elements[1],
                    mesh.modelMatrix.elements[2], mesh.modelMatrix.elements[4],
                    mesh.modelMatrix.elements[5], mesh.modelMatrix.elements[6],
                    mesh.modelMatrix.elements[8], mesh.modelMatrix.elements[9],
                    mesh.modelMatrix.elements[10])
              .inverse()
              .transpose();

      if (geometry.faceIndices) {
        for (int i = 0; i < geometry.faceIndices.value().array.size(); i += 3) {
          const int vertexAIndex = geometry.faceIndices.value().array.at(i);
          const int vertexBIndex = geometry.faceIndices.value().array.at(i + 1);
          const int vertexCIndex = geometry.faceIndices.value().array.at(i + 2);

          processTriangle(vertexAIndex, vertexBIndex, vertexCIndex, geometry,
                          mesh, modelViewMatrix, camera, viewMatrix,
                          normalMatrix, cameraWorldPos, viewportMatrix, lights,
                          renderTarget, depthTexture);
        }
      } else {
        for (int i = 0; i < geometry.vertexPositions.array.size() / 3; i += 3) {
          processTriangle(i, i + 1, i + 2, geometry, mesh, modelViewMatrix,
                          camera, viewMatrix, normalMatrix, cameraWorldPos,
                          viewportMatrix, lights, renderTarget, depthTexture);
        }
      }
    }
  }

private:
  template <class BufferType>
  void processTriangle(int vertexAIndex, int vertexBIndex, int vertexCIndex,
                       Geometry &geometry, Mesh &mesh,
                       Matrix4x4 &modelViewMatrix, Camera &camera,
                       Matrix4x4 &viewMatrix, Matrix3x3 &normalMatrix,
                       Vector3 &cameraPosition, Matrix4x4 &viewportMatrix,
                       std::vector<std::reference_wrapper<Light>> &lights,
                       RenderTarget<BufferType> &renderTarget,
                       RenderTarget<double> &depthTexture) {
    auto localVertexA =
        Vector3::fromBufferAttribute(geometry.vertexPositions, vertexAIndex);
    auto localVertexB =
        Vector3::fromBufferAttribute(geometry.vertexPositions, vertexBIndex);
    auto localVertexC =
        Vector3::fromBufferAttribute(geometry.vertexPositions, vertexCIndex);

    auto vertexANormal =
        Vector3::fromBufferAttribute(geometry.vertexNormals, vertexAIndex);
    auto vertexBNormal =
        Vector3::fromBufferAttribute(geometry.vertexNormals, vertexBIndex);
    auto vertexCNormal =
        Vector3::fromBufferAttribute(geometry.vertexNormals, vertexCIndex);

    Uniforms uniforms{
        mesh.modelMatrix, modelViewMatrix, camera.projectionMatrix,
        viewMatrix,       normalMatrix,    cameraPosition};
    Attributes attributes{localVertexA, vertexANormal};
    Varyings varyingsVertexA = {localVertexA, vertexANormal};
    Varyings varyingsVertexB = {localVertexB, vertexBNormal};
    Varyings varyingsVertexC = {localVertexC, vertexCNormal};

    const auto transformedVertexA =
        mesh.material.vertexShader(uniforms, attributes);

    attributes.localPosition = localVertexB;
    attributes.localNormal = vertexBNormal;
    const auto transformedVertexB =
        mesh.material.vertexShader(uniforms, attributes);

    attributes.localPosition = localVertexC;
    attributes.localNormal = vertexCNormal;
    const auto transformedVertexC =
        mesh.material.vertexShader(uniforms, attributes);

    auto screenSpaceVertexA = viewportMatrix * transformedVertexA;
    auto screenSpaceVertexB = viewportMatrix * transformedVertexB;
    auto screenSpaceVertexC = viewportMatrix * transformedVertexC;

    screenSpaceVertexA /= screenSpaceVertexA.w;
    screenSpaceVertexA.w = 1.0 / transformedVertexA.w;
    screenSpaceVertexB /= screenSpaceVertexB.w;
    screenSpaceVertexB.w = 1.0 / transformedVertexB.w;
    screenSpaceVertexC /= screenSpaceVertexC.w;
    screenSpaceVertexC.w = 1.0 / transformedVertexC.w;

    const auto clockwiseMatrix = Matrix3x3(
        screenSpaceVertexA.x, screenSpaceVertexA.y, 1, screenSpaceVertexB.x,
        screenSpaceVertexB.y, 1, screenSpaceVertexC.x, screenSpaceVertexC.y, 1);

    if (clockwiseMatrix.determinant() *
            static_cast<int>(mesh.geometry.frontFace) *
            static_cast<int>(mesh.material.cullMode) <
        0) {
      return;
    }

    const auto maxY = static_cast<int>(std::round(
        std::max(std::max(screenSpaceVertexA.y, screenSpaceVertexB.y),
                 screenSpaceVertexC.y)));
    const auto minY = static_cast<int>(std::round(
        std::min(std::min(screenSpaceVertexA.y, screenSpaceVertexB.y),
                 screenSpaceVertexC.y)));
    const auto yDiff = maxY - minY;

    std::vector<std::set<Fragment>> fragments(yDiff + 1);

    const auto bresenhamAB =
        bresenham(static_cast<int>(std::round(screenSpaceVertexA.x)),
                  static_cast<int>(std::round(screenSpaceVertexA.y)),
                  static_cast<int>(std::round(screenSpaceVertexB.x)),
                  static_cast<int>(std::round(screenSpaceVertexB.y)));
    const auto bresenhamBC =
        bresenham(static_cast<int>(std::round(screenSpaceVertexB.x)),
                  static_cast<int>(std::round(screenSpaceVertexB.y)),
                  static_cast<int>(std::round(screenSpaceVertexC.x)),
                  static_cast<int>(std::round(screenSpaceVertexC.y)));
    const auto bresenhamCA =
        bresenham(static_cast<int>(std::round(screenSpaceVertexC.x)),
                  static_cast<int>(std::round(screenSpaceVertexC.y)),
                  static_cast<int>(std::round(screenSpaceVertexA.x)),
                  static_cast<int>(std::round(screenSpaceVertexA.y)));

    for (auto [x, y] : bresenhamAB) {
      fragments[y - minY].insert(Fragment{x, y});
    }

    for (auto [x, y] : bresenhamBC) {
      fragments[y - minY].insert(Fragment{x, y});
    }

    for (auto [x, y] : bresenhamCA) {
      fragments[y - minY].insert(Fragment{x, y});
    }

    for (auto &line : fragments) {
      auto startFragment = line.begin();
      auto endFragment = std::next(startFragment);

      const auto y = startFragment->y;

      while (endFragment != line.end()) {
        for (int x = startFragment->x; x <= endFragment->x; x++) {
          const auto bary = barycentric(
              Vector3(x, y, 0),
              Vector3(screenSpaceVertexA.x, screenSpaceVertexA.y, 0),
              Vector3(screenSpaceVertexB.x, screenSpaceVertexB.y, 0),
              Vector3(screenSpaceVertexC.x, screenSpaceVertexC.y, 0));

          const auto perspectiveBary =
              Vector3(bary.x * screenSpaceVertexA.w,
                      bary.y * screenSpaceVertexB.w,
                      bary.z * screenSpaceVertexC.w) /
              (bary.x * screenSpaceVertexA.w + bary.y * screenSpaceVertexB.w +
               bary.z * screenSpaceVertexC.w);

          Vector3 localPosition =
              varyingsVertexA.localPosition * perspectiveBary.x +
              varyingsVertexB.localPosition * perspectiveBary.y +
              varyingsVertexC.localPosition * perspectiveBary.z;
          Vector3 localNormal =
              varyingsVertexA.localNormal * perspectiveBary.x +
              varyingsVertexB.localNormal * perspectiveBary.y +
              varyingsVertexC.localNormal * perspectiveBary.z;

          Varyings varyings = {localPosition, localNormal};

          Color color =
              mesh.material.fragmentShader(uniforms, varyings, lights);

          // Clip vertices outside of the screen space

          if (x < 0 || x >= renderTarget.width || y < 0 ||
              y >= renderTarget.height) {
            continue;
          }

          const double z = bary.x * screenSpaceVertexA.z +
                           bary.y * screenSpaceVertexB.z +
                           bary.z * screenSpaceVertexC.z;

          const auto currentDepth = depthTexture.read(x, y).x;

          if (!(mesh.material.depthTest ^ (z <= currentDepth))) {
            renderTarget.write(x, y, color);
            if (mesh.material.depthWrite) {
              depthTexture.write(x, y, Color(z, 0.0, 0.0));
            }
          }
        }

        startFragment = std::next(startFragment);
        endFragment = std::next(endFragment);
      }
    }
  }
};

} // namespace t

#endif // RASTERIZER_HPP
