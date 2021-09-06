//[]---------------------------------------------------------------[]
//|                                                                 |
//| Copyright (C) 2018 Orthrus Group.                               |
//|                                                                 |
//| This software is provided 'as-is', without any express or       |
//| implied warranty. In no event will the authors be held liable   |
//| for any damages arising from the use of this software.          |
//|                                                                 |
//| Permission is granted to anyone to use this software for any    |
//| purpose, including commercial applications, and to alter it and |
//| redistribute it freely, subject to the following restrictions:  |
//|                                                                 |
//| 1. The origin of this software must not be misrepresented; you  |
//| must not claim that you wrote the original software. If you use |
//| this software in a product, an acknowledgment in the product    |
//| documentation would be appreciated but is not required.         |
//|                                                                 |
//| 2. Altered source versions must be plainly marked as such, and  |
//| must not be misrepresented as being the original software.      |
//|                                                                 |
//| 3. This notice may not be removed or altered from any source    |
//| distribution.                                                   |
//|                                                                 |
//[]---------------------------------------------------------------[]
//
// OVERVIEW: SceneObject.h
// ========
// Class definition for scene object.
//
// Author(s): Paulo Pagliosa (and your name)
// Last revision: 25/08/2018

#ifndef __SceneObject_h
#define __SceneObject_h

#include "SceneNode.h"
#include "Transform.h"
#include "Component.h"
#include "Primitive.h"
#include <list>

namespace cg
{ // begin namespace cg

// Forward definition
class Scene;


/////////////////////////////////////////////////////////////////////
//
// SceneObject: scene object class
// ===========
class SceneObject: public SceneNode
{
public:
  bool visible{true};

  /// Constructs an empty scene object.
  SceneObject(const char* name, Scene* scene):
    SceneNode{name},
    _scene{scene},
    _parent{},
    _primitive{ nullptr }
  {
    makeUse(&_transform);
  }

  /// Returns the scene which this scene object belong to.
  auto scene() const
  {
    return _scene;
  }

  /// Returns the parent of this scene object.
  auto parent() const
  {
    return _parent;
  }
  //Adiciona um objeto de cena (filho) a coleção de objetos de cena de um objeto de cena
  void addSceneObjectChild(SceneObject* child);

  //remove um objeto de cena (filho) da coleção de objetos de cena de um objeto de cena
  void removeSceneObjectChild(SceneObject* child);

  //Adiciona um componente a coleção de componentes de um objeto de cena
  void addComponent(Component* component);

  //remove um componente a coleção de componentes de um objeto de cena
  void removeComponent(Component* component);

  /// Sets the parent of this scene object.
  void setParent(SceneObject* parent);

  /// Returns the transform of this scene object.
  auto transform()
  {
    return &_transform;
  }

  auto
      child()
  {
      return sceneObjectList;
  }

  int
      size()
  {
      return sceneObjectList.size();
  }

  //returns the componentList.
  auto
      getComponentList()
  {
      return componentList;
  }

  void setPrimitive(Primitive* _primitive) {
      this->_primitive = _primitive;
  }

  auto
      getPrimitive() {
      return _primitive;
  }

private:
  Scene* _scene;
  SceneObject* _parent;
  Transform _transform;
  Primitive* _primitive;
  std::list<SceneObject*> sceneObjectList;
  std::list<Component*> componentList;

  friend class Scene;

}; // SceneObject

/// Returns the transform of a component.
inline Transform*
Component::transform() // declared in Component.h
{
  return sceneObject()->transform();
}

/// Returns the parent of a transform.
inline Transform*
Transform::parent() const // declared in Transform.h
{
  if (auto p = sceneObject()->parent())
   return p->transform();
   return nullptr;
}

} // end namespace cg

#endif // __SceneObject_h
