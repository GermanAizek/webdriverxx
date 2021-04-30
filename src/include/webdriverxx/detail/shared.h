#ifndef WEBDRIVERXX_DETAIL_SHARED_H
#define WEBDRIVERXX_DETAIL_SHARED_H

#include <cstdint>
#include <algorithm>

namespace webdriverxx {
namespace detail {

class SharedObjectBase { // noncopyable
public:
	SharedObjectBase() : ref_(0) {}
	virtual ~SharedObjectBase() {}

	inline
	virtual void AddRef() {
		++ref_;
	}

	inline
	virtual void Release() {
		if (--ref_ == 0)
			delete this;
	}

private:
	SharedObjectBase(SharedObjectBase&);
	SharedObjectBase& operator = (SharedObjectBase&);

private:
	uint32_t ref_;
};

// Copyable, not thread safe
template<typename T>
class Shared {
public:
	Shared()
		: ptr_(nullptr)
		, ref_(nullptr)
	{}

	template<typename T2>
	inline Shared(T2* ptr)
		: ptr_(ptr)
		, ref_(ptr)
	{
		if (ref_) ref_->AddRef();
	}

	inline
	Shared(const Shared& other)
		: ptr_(other.ptr_)
		, ref_(other.ref_)
	{
		if (ref_) ref_->AddRef();
	}

	template<typename T2>
	inline Shared(const Shared<T2>& other)
		: ptr_(other.ptr_)
		, ref_(other.ref_)
	{
		if (ref_) ref_->AddRef();
	}

	inline
	~Shared() {
		if (ref_) ref_->Release();
	}

	Shared& operator = (const Shared& other) {
		if (&other != this)
			Shared<T>(other).Swap(*this);
		return *this;
	}

	inline
	void Swap(Shared& other) {
		std::swap(ptr_, other.ptr_);
		std::swap(ref_, other.ref_);
	}

	T& operator * () const {
		return *ptr_;
	}

	T* operator -> () const {
		return ptr_;
	}

	inline
	T* Get() const {
		return ptr_;
	}

	operator T* () const {
		return ptr_;
	}

private:
	template<typename T2>
	friend class Shared;

	T* ptr_;
	SharedObjectBase* ref_;
};

} // namespace detail
} // namespace webdriverxx

#endif
