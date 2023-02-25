#include "Cell.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cctype>
#include <stdexcept>


namespace cell {

	cellImpl::cellImpl(std::string text) : value_(std::move(text)) {}

	IntegerCell::IntegerCell(std::string text) : cellImpl(text) {}

	Value IntegerCell::getValue() const {
		double out;
		try {
			for (auto& ch : value_) {
				if (!std::isdigit(ch)) {
					return std::string("InV");
				}
			}
			out = std::stod(value_);
		}
		catch (const std::invalid_argument& ex) {
			return std::string("InV");
		}
		return out;
	}

	const std::string& IntegerCell::getText() const {
		return value_;
	}


	FormulaCell::FormulaCell(std::string text, SheetInterface* sheet)
		: cellImpl(text), sheet_(sheet) {
		if (text.size() == 1) {
			valid_ = false;
			return;
		}

		auto op = std::find_if(value_.begin(), value_.end(), [](char ch) {
			return ch == '-' || ch == '+' || ch == '/' || ch == '*';
			});

		if (op == value_.end()) {
			valid_ = false;
			return;
		}

		formula_ = formula::createFormula(*op, sheet_);

		//first operand
		std::vector<formula::Opearand> operands;
		formula::Opearand first;
		try {
			first = getOperand(value_.begin() + 1, op);
			if (std::get_if<rawPosition>(&first)) {
				ref_cells_.push_back(std::get<rawPosition>(first));
			}
		}
		catch (...) {
			valid_ = false;
			return;
		}

		//second operand
		formula::Opearand second;
		try {
			second = getOperand(op + 1, value_.end());
			if (std::get_if<rawPosition>(&second)) {
				ref_cells_.push_back(std::get<rawPosition>(second));
			}
		}
		catch (...) {
			valid_ = false;
			return;
		}

		operands.push_back(first);
		operands.push_back(second);
		formula_->setOperands(operands);
	}

	formula::Opearand FormulaCell::getOperand(std::string::const_iterator first, std::string::const_iterator second) const {
		if (first == second) {
			throw std::invalid_argument("Can't extract operand");
		}

		if ('0' <= *first && *first <= '9') {
			return std::stod(std::string({ first, second }));
		}

		auto it = std::find_if(first, second,
			[](char ch) { return '0' <= ch && ch <= '9'; });
		std::string column_1 = { first, it };
		int row_1 = std::stoi(std::string({ it, second }));
		rawPosition pos = { column_1, row_1 };
		return pos;

	}

	Value FormulaCell::getValue() const {
		if (!valid_) {
			return std::string("InF");
		}
		return formula_.get()->compute();
	}

	const std::string& FormulaCell::getText() const {
		return value_;
	}

	std::vector<rawPosition>& FormulaCell::GetReferencedPos() {
		return ref_cells_;
	}

	Cell::Cell(SheetInterface* sheet, rawPosition& pos)
		: sheet_(sheet), pos_(pos) {}

	Value Cell::getValue() {
		return Impl_->getValue();
	}

	const std::string& Cell::getText() {
		return Impl_->getText();
	}

	void Cell::setText(const std::string& text) {
		if (text[0] == '=') {
			Impl_ = std::make_shared<cell::FormulaCell>(text, sheet_);
		}
		else {
			Impl_ = std::make_shared<cell::IntegerCell>(text);
		}
	}

	bool Cell::isFormula() const {
		return dynamic_cast<FormulaCell*>(Impl_.get()) != nullptr;
	}

	std::vector<rawPosition> Cell::GetReferencedPos() {
		FormulaCell* point = dynamic_cast<FormulaCell*>(Impl_.get());
		if (point) {
			return point->GetReferencedPos();
		}
		return {};
	}

}  // namespace cell