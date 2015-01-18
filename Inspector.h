#pragma once


#include <memory>
#ifdef MAGNUMINSPECTOR_BOOST
#include <boost/weak_ptr.hpp>
#endif

#include <Magnum/Magnum.h>
#include <Magnum/Math/Vector2.h>
#include <Magnum/Math/Vector3.h>
#include <Magnum/Math/Vector4.h>
#include <Magnum/Math/Quaternion.h>
#include <Magnum/Math/Matrix3.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/SceneGraph/AbstractFeature.h>
#include <Magnum/SceneGraph/AbstractObject.h>

#define INSPECT_EDITABLE(field) inspector.editable(#field, field);
#define INSPECT_READONLY(field) inspector.readonly(#field, field);

namespace MagnumInspector {
	
class Inspectable;

class Inspector
{
public:
	virtual void editable(const char* name, std::string& s) = 0;
	virtual void readonly(const char* name, const std::string& s) = 0;
	
	virtual void editable(const char* name, float& f) = 0;
	virtual void readonly(const char* name, const float& f) = 0;
	
	virtual void editable(const char* name, bool& f) = 0;
	virtual void readonly(const char* name, bool f) = 0;
	
	virtual void editable(const char* name, float* f, unsigned n, unsigned m) = 0;
	virtual void readonly(const char* name, const float* f, unsigned n, unsigned m) = 0;
	
	virtual void editable(const char* name, int& i) = 0;
	virtual void readonly(const char* name, const int& i) = 0;
	
	virtual void editable(const char* name, long& i) = 0;
	virtual void readonly(const char* name, const long& i) = 0;
	
	virtual void editable(const char* name, unsigned long& i) = 0;
	virtual void readonly(const char* name, const unsigned long& i) = 0;
	
	virtual void editable(const char* name, Magnum::Vector2& i) { editable(name, i.data(), 2u, 1u); }
	virtual void readonly(const char* name, const Magnum::Vector2& i) { readonly(name, i.data(), 2u, 1u); }
	
	virtual void editable(const char* name, Magnum::Vector3& i) { editable(name, i.data(), 3u, 1u); }
	virtual void readonly(const char* name, const Magnum::Vector3& i) { readonly(name, i.data(), 3u, 1u); }
	
	virtual void editable(const char* name, Magnum::Vector4& i) { editable(name, i.data(), 4u, 1u); }
	virtual void readonly(const char* name, const Magnum::Vector4& i) { readonly(name, i.data(), 4u, 1u); }
	
	virtual void editable(const char* name, Magnum::Matrix4& i) { editable(name, i.data(), 4u, 4u); }
	virtual void readonly(const char* name, const Magnum::Matrix4& i) { readonly(name, i.data(), 4u, 4u); }
	
	virtual void editable(const char* name, Magnum::Matrix3& i) { editable(name, i.data(), 3u, 3u); }
	virtual void readonly(const char* name, const Magnum::Matrix3& i) { readonly(name, i.data(), 3u, 3u); }
	
	
	virtual void editable(const char* name, Magnum::Quaternion& i) { editable(name, i.vector().data(), 4u, 1u); }
	virtual void readonly(const char* name, const Magnum::Quaternion& i) { readonly(name, i.vector().data(), 4u, 1u); }
	
	virtual void editable(Inspectable* i) = 0;
	virtual void readonly(Inspectable* i) = 0;
	
	virtual void editable(Magnum::SceneGraph::AbstractObject2D& i) = 0;
	virtual void readonly(Magnum::SceneGraph::AbstractObject2D& i) = 0;
	virtual void editable(Magnum::SceneGraph::AbstractObject3D& i) = 0;
	virtual void readonly(Magnum::SceneGraph::AbstractObject3D& i) = 0;
	virtual void editable(Magnum::SceneGraph::AbstractFeature2D& i) = 0;
	virtual void readonly(Magnum::SceneGraph::AbstractFeature2D& i) = 0;
	virtual void editable(Magnum::SceneGraph::AbstractFeature3D& i) = 0;
	virtual void readonly(Magnum::SceneGraph::AbstractFeature3D& i) = 0;
    
	static std::string demangle(const char* name);
 
#ifdef MAGNUMINSPECTOR_BOOST
    template<typename T>
    void editable(const char* name, boost::weak_ptr<T>& target) {
        if (auto actual = target.lock()) editable(actual.get());
    }
	
    template<typename T>
    void readonly(const char* name, boost::weak_ptr<T>& target) {
        if (auto actual = target.lock()) readonly(actual.get());
    }
#endif
};




}