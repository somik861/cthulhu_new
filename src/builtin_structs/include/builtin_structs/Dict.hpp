#pragma once

#include "builtin_structs/forward_defs.hpp"
#include "common/InterpreterException.hpp"
#include <format>
#include <map>
#include <memory>

namespace builtin_structs {
class DictException : public common::InterpreterException {
  public:
	using common::InterpreterException::InterpreterException;
};

template <bool enable_checks>
class Dict {
  public:
	constexpr static bool checks_enabled = enable_checks;
	using key_type = uint32_t;
	using stack_type = Stack<checks_enabled>;
	using backend_type = std::map<key_type, std::unique_ptr<stack_type>>;

	Dict() = default;
	Dict(const Dict& d) {
		for (const auto& [k, v] : d.m_storage)
			set(k, std::make_unique<stack_type>(*v));
	}
	Dict(Dict&& d) = default;
	Dict& operator=(const Dict& d) {
		Dict cpy = d;
		std::swap(*this, cpy);
		return *this;
	}
	Dict& operator=(Dict&& d) = default;
	~Dict() = default;

	bool contains(key_type key) const { return m_storage.contains(key); }
	stack_type* at(key_type key) const {
		if constexpr (checks_enabled)
			if (!contains(key))
				throw DictException(
				    std::format("Key '{}' not in dictionary", key));

		auto it = m_storage.find(key);
		return it->second.get();
	}
	std::unique_ptr<stack_type> pop(key_type key) {
		if constexpr (checks_enabled)
			if (!contains(key))
				throw DictException(
				    std::format("Key '{}' not in dictionary", key));

		auto it = m_storage.find(key);
		auto rv = std::move(it->second);
		m_storage.erase(it);
		return rv;
	}
	void set(key_type key, std::unique_ptr<stack_type> stack) {
		m_storage.insert_or_assign(key, std::move(stack));
	}
	std::size_t size() const noexcept { return m_storage.size(); }
	void clear() { m_storage.clear(); }

  private:
	backend_type m_storage;
};

} // namespace builtin_structs

#include "builtin_structs/builtin_structs.hpp"
