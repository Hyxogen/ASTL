#pragma once

#include <memory>
#include <cuchar>
#include <concepts>

#define ASTL_VECTOR_DEFAULT_RESERVE 50

namespace astl {

	template<class T, class Allocator = std::allocator<T>>
	requires std::is_copy_assignable<T>::value
	class vector {
		using value_type		= T;
		using reference			= T&;
		using const_referenc	= const T&;
		using size_type			= std::size_t;

		T			*m_Pointer = nullptr;
		size_type	m_Capacity = 0;
		size_type	m_Size = 0;
		Allocator	*m_Allocator = nullptr;
	public:
		vector() {

		}

		~vector() {

		}

		constexpr void push_back(const T& t) {
			if (m_Size == m_Capacity)
				reserve(ASTL_VECTOR_DEFAULT_RESERVE * sizeof(T));
			m_Pointer[m_Size++] = t;
		}

		constexpr void reserve(size_type new_cap) {
			if (m_Allocator == nullptr)
				m_Allocator = new Allocator;

			T* newPtr = m_Allocator->allocate(new_cap);
			if (m_Pointer != nullptr) {
				std::memcpy(newPtr, m_Pointer, new_cap);
				m_Allocator->deallocate(m_Pointer, m_Size * sizeof(T));
			}
			m_Pointer = newPtr;
		}

		constexpr size_type capacity() const noexcept {
			return m_Capacity;
		}
	};
}