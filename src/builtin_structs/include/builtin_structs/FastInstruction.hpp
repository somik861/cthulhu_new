#pragma once

#include "common/InterpreterException.hpp"
#include <cstdint>

namespace builtin_structs {
class FastInstructionException : public common::InterpreterException {
  public:
	using common::InterpreterException::InterpreterException;
};

template <bool enable_checks>
class FastInstruction {
  public:
	constexpr static bool checks_enabled = enable_checks;
	FastInstruction() = default;
	FastInstruction(uint8_t domain, uint8_t operation) {
		data.domain = domain;
		data.operation = operation;
	}
	FastInstruction(uint8_t domain, uint8_t operation, uint8_t operand_1) {
		if constexpr (checks_enabled)
			if (!fitsIn(operand_1, 4))
				throw FastInstructionException(
				    "Operand does not fit into its number of bits");

		data.domain = domain;
		data.operation = operation;
		data.operand_1 = operand_1;
	}
	FastInstruction(uint8_t domain,
	                uint8_t operation,
	                uint8_t operand_1,
	                uint8_t operand_2) {
		if constexpr (checks_enabled)
			if (!fitsIn(operand_1, 4) || !fitsIn(operand_2, 4))
				throw FastInstructionException(
				    "Operand does not fit into its number of bits");

		data.domain = domain;
		data.operation = operation;
		data.operand_1 = operand_1;
		data.operand_2 = operand_2;
	}
	FastInstruction(uint8_t domain,
	                uint8_t operation,
	                uint8_t operand_1,
	                uint8_t operand_2,
	                uint8_t operand_3) {
		if constexpr (checks_enabled)
			if (!fitsIn(operand_1, 4) || !fitsIn(operand_2, 4) ||
			    !fitsIn(operand_3, 4))
				throw FastInstructionException(
				    "Operand does not fit into its number of bits");

		data.domain = domain;
		data.operation = operation;
		data.operand_1 = operand_1;
		data.operand_2 = operand_2;
		data.operand_3 = operand_3;
	}
	FastInstruction(uint8_t domain,
	                uint8_t operation,
	                uint8_t operand_1,
	                uint8_t operand_2,
	                uint8_t operand_3,
	                uint8_t operand_4) {
		if constexpr (checks_enabled)
			if (!fitsIn(operand_1, 4) || !fitsIn(operand_2, 4) ||
			    !fitsIn(operand_3, 4) || !fitsIn(operand_4, 4))
				throw FastInstructionException(
				    "Operand does not fit into its number of bits");

		data.domain = domain;
		data.operation = operation;
		data.operand_1 = operand_1;
		data.operand_2 = operand_2;
		data.operand_3 = operand_3;
		data.operand_4 = operand_4;
	}
	FastInstruction(uint8_t domain,
	                uint8_t operation,
	                uint8_t operand_1,
	                uint8_t operand_2,
	                uint8_t operand_3,
	                uint8_t operand_4,
	                uint8_t operand_5) {
		if constexpr (checks_enabled)
			if (!fitsIn(operand_1, 4) || !fitsIn(operand_2, 4) ||
			    !fitsIn(operand_3, 4) || !fitsIn(operand_4, 4) ||
			    !fitsIn(operand_5, 4))
				throw FastInstructionException(
				    "Operand does not fit into its number of bits");

		data.domain = domain;
		data.operation = operation;
		data.operand_1 = operand_1;
		data.operand_2 = operand_2;
		data.operand_3 = operand_3;
		data.operand_4 = operand_4;
		data.operand_5 = operand_5;
	}
	FastInstruction(uint8_t domain,
	                uint8_t operation,
	                uint8_t operand_1,
	                uint8_t operand_2,
	                uint8_t operand_3,
	                uint8_t operand_4,
	                uint8_t operand_5,
	                uint8_t operand_6) {
		if constexpr (checks_enabled)
			if (!fitsIn(operand_1, 4) || !fitsIn(operand_2, 4) ||
			    !fitsIn(operand_3, 4) || !fitsIn(operand_4, 4) ||
			    !fitsIn(operand_5, 4) || !fitsIn(operand_6, 4))
				throw FastInstructionException(
				    "Operand does not fit into its number of bits");

		data.domain = domain;
		data.operation = operation;
		data.operand_1 = operand_1;
		data.operand_2 = operand_2;
		data.operand_3 = operand_3;
		data.operand_4 = operand_4;
		data.operand_5 = operand_5;
		data.operand_6 = operand_6;
	}

	void setCustom(uint32_t value) {
		if constexpr (checks_enabled)
			if (!fitsIn(value, 24))
				throw FastInstructionException(
				    "Custom bytcode part does not fit into its number of bits");
		data.custom = value;
	}

	/**
	 * Standard layout:
	 * domain (8) | operation (8) | operands (6 * 4) | custom (24) -> 64
	 */
	struct {
		uint32_t domain : 8;
		uint32_t operation : 8;
		uint32_t operand_1 : 4;
		uint32_t operand_2 : 4;
		uint32_t operand_3 : 4;
		uint32_t operand_4 : 4;
		uint32_t operand_5 : 4;
		uint32_t operand_6 : 4;
		uint32_t custom : 24;
	} data{};

  private:
	template <typename T>
	bool fitsIn(T value, uint8_t bits) {
		return (value >> bits) == 0;
	}
};

static_assert(sizeof(FastInstruction<true>) <= 8);
} // namespace builtin_structs