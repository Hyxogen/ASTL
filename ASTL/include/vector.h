#pragma once

#include <memory>
#include <cuchar>
#include <concepts>

#define ASTL_VECTOR_DEFAULT_RESERVE 50

namespace astl {

	//TODO add iterator

	template<class T, class Allocator = std::allocator<T>>
	requires std::is_copy_assignable<T>::value
	class vector {

		struct iterator {
			using iterator_category = std::forward_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = T*;
			using reference = T&;

			iterator(pointer ptr) : m_Pointer(ptr) {}

		private:
			pointer m_Pointer;

		public:
			reference operator*() const { return *m_Pointer; }
			pointer operator->() { return m_Pointer; }

			iterator operator++() { m_Pointer++; return *this; }

			iterator operator++(T) { iterator ret = *this; ++(*this); return ret; }

			friend bool operator==(const iterator& a, const iterator& b) { return a.m_Pointer == b.m_Pointer; }
			friend bool operator!=(const iterator& a, const iterator& b) { return a.m_Pointer != b.m_Pointer; }
		};

		using value_type		= T;
		using reference			= T&;
		using pointer			= std::allocator_traits<Allocator>::pointer;
		using const_referenc	= const T&;
		using size_type			= std::size_t;

		size_type	m_Capacity = 0;
		Allocator	*m_Allocator = nullptr;

		//Pointer to first element
		pointer m_Begin	= nullptr;
		//Pointer to last element (not null)
		pointer m_Last	= nullptr;
		//Pointer to end of array
		pointer m_End	= nullptr;
	public:
		vector() {

		}

		~vector() {

		}

		constexpr void push_back(const T& t) {
			if (size() == m_Capacity)
				reserve(ASTL_VECTOR_DEFAULT_RESERVE * sizeof(T));
			*m_Last = t;
			m_Last++;
		}

		constexpr void reserve(size_type new_cap) {
			if (m_Allocator == nullptr)
				m_Allocator = new Allocator;

			size_type vec_size = size();

			T* newPtr = m_Allocator->allocate(new_cap);
			if (m_Begin != nullptr) {
				std::memcpy(newPtr, m_Begin, vec_size);
				m_Allocator->deallocate(m_Begin, vec_size * sizeof(T));
			}
			m_Begin = newPtr;
			m_Last = m_Begin + vec_size;
			m_End = m_Begin + new_cap;
		}

		constexpr size_type capacity() const noexcept {
			return m_Capacity;
		}

		constexpr size_type size() const noexcept {
			//TODO check if this works without static_cast
			return m_Begin == nullptr ? 0 : static_cast<size_type>(m_End - m_Begin);
		}

		constexpr iterator begin() noexcept {
			return iterator(m_Begin);
		}

		constexpr iterator end() noexcept {
			return iterator(m_Last);
		}
	};
}