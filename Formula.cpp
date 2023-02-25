#include "Formula.h"
#include <iostream>

namespace formula {

	formulaImpl::formulaImpl(SheetInterface* sheet) : sheet_(sheet) {}

	void formulaImpl::setOperands(const std::vector<Opearand>& operands) {
		operands_ = operands;
	}

	Value formulaImpl::OperandToValue(const Opearand& op) const {
		if (std::get_if<rawPosition>(&op)) {
			rawPosition pos = std::get<rawPosition>(op);
			return sheet_->GetValue(pos);
		}
		return std::get<double>(op);

	}


	AddFormula::AddFormula(SheetInterface* sheet) : formulaImpl(sheet) {}

	Value AddFormula::compute() const {
		Value first = OperandToValue(operands_[0]);
		if (std::get_if<std::string>(&first)) {
			return std::get<std::string>(first);
		}
		Value second = OperandToValue(operands_[1]);
		if (std::get_if<std::string>(&second)) {
			return std::get<std::string>(second);
		}
		return std::get<double>(first) + std::get<double>(second);
	}

	SubFormula::SubFormula(SheetInterface* sheet) : formulaImpl(sheet) {}

	Value SubFormula::compute() const {
		Value first = OperandToValue(operands_[0]);
		if (std::get_if<std::string>(&first)) {
			return std::get<std::string>(first);
		}
		Value second = OperandToValue(operands_[1]);
		if (std::get_if<std::string>(&second)) {
			return std::get<std::string>(second);
		}

		return std::get<double>(first) - std::get<double>(second);
	}

	MultFormula::MultFormula(SheetInterface* sheet) : formulaImpl(sheet) {}

	Value MultFormula::compute() const {
		Value first = OperandToValue(operands_[0]);
		if (std::get_if<std::string>(&first)) {
			return std::get<std::string>(first);
		}
		Value second = OperandToValue(operands_[1]);
		if (std::get_if<std::string>(&second)) {
			return std::get<std::string>(second);
		}

		return std::get<double>(first) * std::get<double>(second);
	}

	DivFormula::DivFormula(SheetInterface* sheet) : formulaImpl(sheet) {}

	Value DivFormula::compute() const {
		Value first = OperandToValue(operands_[0]);
		if (std::get_if<std::string>(&first)) {
			return std::get<std::string>(first);
		}
		Value second = OperandToValue(operands_[1]);
		if (std::get_if<std::string>(&second)) {
			return std::get<std::string>(second);
		}

		if (std::get<double>(second) == 0) {
			return std::string("DiV0");
		}
		return std::get<double>(first) / std::get<double>(second);
	}

	std::shared_ptr<formulaImpl> createFormula(char ch, SheetInterface* sheet) {
		std::shared_ptr<formulaImpl> out;
		if (ch == '+') {
			out = std::make_shared<AddFormula>(sheet);
		}
		else if (ch == '-') {
			out = std::make_shared<SubFormula>(sheet);
		}
		else if (ch == '*') {
			out = std::make_shared<MultFormula>(sheet);
		}
		else if (ch == '/') {
			out = std::make_shared<DivFormula>(sheet);
		}
		else {
		}
		return out;
	}

}  // namespace formula