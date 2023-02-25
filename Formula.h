#pragma once

#include <memory>
#include <variant>
#include <stack>
#include "common.h"

namespace formula {

	using Opearand = std::variant<double, rawPosition>;

	class formulaImpl {
	public:
		formulaImpl(SheetInterface* sheet);

		void setOperands(const std::vector<Opearand>& operand);

		virtual Value compute() const = 0;

		virtual ~formulaImpl() {}

	protected:
		std::vector<Opearand> operands_;
		SheetInterface* sheet_;

		Value OperandToValue(const Opearand& op) const;

	};

	class AddFormula : public formulaImpl {
	public:
		AddFormula(SheetInterface* sheet);
		Value compute() const override;
	};

	class SubFormula : public formulaImpl {
	public:
		SubFormula(SheetInterface* sheet);
		Value compute() const override;
	};

	class MultFormula : public formulaImpl {
	public:
		MultFormula(SheetInterface* sheet);
		Value compute() const override;
	};

	class DivFormula : public formulaImpl {
	public:
		DivFormula(SheetInterface* sheet);
		Value compute() const override;
	};

	std::shared_ptr<formulaImpl> createFormula(char ch, SheetInterface* sheet);
}  // namespace formula