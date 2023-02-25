#pragma once
#include <memory>
#include <string>
#include <variant>
#include <vector>

#include "Formula.h"
#include "common.h"

namespace cell {

	class cellImpl {
	public:
		cellImpl() = default;

		cellImpl(std::string value);

		virtual Value getValue() const = 0;

		virtual const std::string& getText() const = 0;

		virtual ~cellImpl() {};

	protected:
		std::string value_;
	};

	class IntegerCell : public cellImpl {
	public:
		IntegerCell(std::string value);

		Value getValue() const override;

		const std::string& getText() const override;
	};


	class FormulaCell : public cellImpl {
	public:
		FormulaCell(std::string value, SheetInterface* sheet);

		Value getValue() const override;

		const std::string& getText() const override;

		std::vector<rawPosition>& GetReferencedPos();

	private:
		bool valid_ = true;
		SheetInterface* sheet_;
		std::shared_ptr<formula::formulaImpl> formula_ = nullptr;
		std::vector<rawPosition> ref_cells_;

		formula::Opearand getOperand(std::string::const_iterator first, std::string::const_iterator second) const;
	};

	class Cell : CellInterface {
	public:
		Cell() = default;

		Cell(SheetInterface* sheet, rawPosition& pos);

		Value getValue();

		const std::string& getText();

		void setText(const std::string& text);

		bool isFormula() const;

		std::vector<rawPosition> GetReferencedPos();

	private:
		SheetInterface* sheet_;
		rawPosition pos_;
		std::shared_ptr<cellImpl> Impl_ = nullptr;
	};

}  // namespace cell