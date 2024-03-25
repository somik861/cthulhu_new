#pragma once

#include <string>
#include <vector>

namespace builtin_structs {
class Instruction {
  public:
	Instruction(std::string domain,
	            std::string operation,
	            std::vector<std::string> operands,
	            std::size_t line_number)
	    : m_domain(std::move(domain)), m_operation(std::move(operation)),
	      m_operands(std::move(operands)), m_line_number(line_number) {}
	const std::string& domain() const { return m_domain; }
	const std::string& operation() const { return m_operation; }
	const std::vector<std::string>& operands() const { return m_operands; }
	std::size_t line_number() const { return m_line_number; }

  private:
	std::string m_domain;
	std::string m_operation;
	std::vector<std::string> m_operands;
	std::size_t m_line_number;
};
} // namespace builtin_structs