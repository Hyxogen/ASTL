#pragma once

#include <memory>
#include <cuchar>
#include <concepts>

#define ASTL_VECTOR_DEFAULT_RESERVE 50

namespace astl {

	template<class T>
	class vector_iterator_base {
	public:
		using iterator_concept		= std::contiguous_iterator_tag;
		using iterator_tag			= std::contiguous_iterator_tag;
		using difference_type		= std::ptrdiff_t;
		using value_type			= T;
		using pointer				= T*;
		using reference				= T&;

	protected:
		pointer m_Pointer;

		vector_iterator_base(pointer data) : m_Pointer(data) {
		
		}

	public:
		vector_iterator_base operator++() {
			m_Pointer++; return *this;
		}

		vector_iterator_base operator++(T) {
			vector_iterator_base ret = *this;
			++(*this);
			return ret;
		}

		friend bool operator==(const vector_iterator_base& a, const vector_iterator_base& b) {
			return a.m_Pointer == b.m_Pointer;
		
		}
		friend bool operator!=(const vector_iterator_base& a, const vector_iterator_base& b) {
			return a.m_Pointer != b.m_Pointer;
		}
	};

	template<class T>
	class vector_const_iterator : public vector_iterator_base<const T> {
		using _base = vector_iterator_base<const T>;

	public:
		using value_type = T;
		using pointer = const T*;
		using reference = const T&;

		vector_const_iterator(_base::pointer data) : _base(data) {

		}

		reference operator*() const {
			return *this->m_Pointer;
		}

		pointer operator->() {
			return this->m_Pointer;
		}
	};

	template<class T>
	class vector_iterator : public vector_iterator_base<T> {
		using _base = vector_iterator_base<T>;

	public:
		vector_iterator(_base::pointer data) : _base(data) {

		}

		_base::reference operator*() const {
			return *this->m_Pointer;
		}

		_base::pointer operator->() {
			return this->m_Pointer;
		}
	};

	template<class T, class Allocator = std::allocator<T>>
	requires std::is_copy_assignable<T>::value
	class vector {
		using _alloc_traits = std::allocator_traits<Allocator>;
	public:
		using value_type		= T;
		using reference			= T&;
		using pointer			= _alloc_traits::pointer;
		using const_pointer		= _alloc_traits::const_pointer;
		using const_reference	= const T&;
		using size_type			= std::size_t;
		using iterator			= vector_iterator<T>;
		using const_iterator	= vector_const_iterator<T>;

	private:
		size_type		m_Capacity = 0;
		Allocator		m_Allocator;

		//Pointer to first element
		pointer m_Begin	= nullptr;
		//Pointer to last element (not null)
		pointer m_Last	= nullptr;
		//Pointer to end of array
		pointer m_End	= nullptr;
	public:
		constexpr vector() noexcept(noexcept(Allocator())) {
			m_Allocator = Allocator();
		}

		constexpr explicit vector(const Allocator& alloc) noexcept : m_Allocator(alloc) {

		}

		constexpr ~vector() {
			if (m_Begin != nullptr)
				m_Allocator.deallocate(m_Begin, size() * sizeof(T));
		}

		constexpr void push_back(const T& t) {
			if (size() == m_Capacity)
				reserve(ASTL_VECTOR_DEFAULT_RESERVE + size());
			*m_Last = t;
			m_Last++;
		}

		constexpr void reserve(size_type new_cap) {
			/*if (m_Allocator == nullptr)
				m_Allocator = new Allocator;*/

			size_type vec_size = size();

			T* newPtr = m_Allocator.allocate(new_cap * sizeof(T));
			if (m_Begin != nullptr) {
				std::memcpy(newPtr, m_Begin, vec_size);
				m_Allocator.deallocate(m_Begin, vec_size * sizeof(T));
			}
			m_Begin = newPtr;
			m_Last = m_Begin + vec_size;
			m_End = m_Begin + new_cap;
		}

		constexpr size_type capacity() const noexcept {
			return m_Capacity;
		}

		constexpr size_type size() const noexcept {
			return m_Begin == nullptr ? 0 : (m_End - m_Begin);
		}

		constexpr iterator begin() noexcept {
			return iterator(m_Begin);
		}

		constexpr iterator end() noexcept {
			return iterator(m_Last);
		}

		constexpr const_iterator cbegin() noexcept {
			return const_iterator(m_Begin);
		}

		constexpr const_iterator cend() noexcept {
			return const_iterator(m_Last);
		}

		constexpr reference operator[](size_type pos) {
			return m_Begin[pos];
		}
		constexpr const_reference operator[](size_type pos) const {
			return m_Begin[pos];
		}

	};
}