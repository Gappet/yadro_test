#include "Sheet.h"
#include "Cell.h"
#include <algorithm>

void Sheet::SetCell(std::string column, int row, std::string text) {
	rawPosition raw_pos{ column, row };
	Position pos = convRawPos(raw_pos);
	std::shared_ptr<cell::Cell> new_cell =
		std::make_shared<cell::Cell>(this, raw_pos);
	new_cell->setText(text);
	if (!pos.isValid()) {
		return;
	}
	cells_[pos] = new_cell;

	if (new_cell->isFormula()) {
		std::vector<Position> vec;
		for (auto& elm : new_cell->GetReferencedPos()) {
			vec.push_back(convRawPos(elm));
		}
		used_cells_[pos] = { vec.begin(), vec.end() };
	}
}

Value Sheet::GetValue(const rawPosition& raw_pos) {
	auto pos = convRawPos(raw_pos);
	if (!cells_.count(pos)) {
		return std::string("InF");
	}
	auto cell = cells_[pos];
	if (cell->isFormula()) {
		try {
			auto vec = cell->GetReferencedPos();
			this->isCirced(raw_pos, vec);
			return cell->getValue();
		}
		catch (CircularDependencyException& cr) {
			return std::string("CR");
		}
	}
	return cell->getValue();
}

void Sheet::SetRows(std::vector<int> rows) {
	oreder_row_ = std::move(rows);
	for (auto& row : oreder_row_) {
		rows_[row] = next_row_++;
	}
}

void Sheet::SetColumns(std::vector<std::string> columns) {
	order_column_ = std::move(columns);
	for (std::string& column : order_column_) {
		columns_[column] = next_column_++;
	}
}

void Sheet::PrintValue(std::ostream& out) {
	//out.precision(2);
	for (auto& c : order_column_) {
		out << "," << c;
	}
	out << std::endl;
	for (auto& row : oreder_row_) {
		out << row;
		for (auto& column : order_column_) {
			out << ",";
			auto vl = cells_[convRawPos({ column, row })]->getValue();			
			if (std::get_if<double>(&vl)) {
				out << std::get<double>(vl);
			}
			else if (std::get_if<std::string>(&vl)) {
				out << std::get<std::string>(vl);
			}
		}
		out << std::endl;
	}
}

void Sheet::PrintText(std::ostream& out) {
	for (auto& row : oreder_row_) {
		for (auto& column : order_column_) {
			auto vl = cells_[convRawPos({ column, row })]->getText();

			out << vl << "\t";
		}
		out << std::endl;
	}
}

void Sheet::isCirced(const rawPosition& ps, const std::vector<rawPosition>& ref_pos) {
	auto pos = convRawPos(ps);
	std::vector<Position> poses;
	for (const auto& p : ref_pos) {
		poses.push_back(convRawPos(p));
	}

	if (std::find(poses.begin(), poses.end(), pos) != poses.end()) {
		throw CircularDependencyException("Circle dependency");
	}

	for (const Position& p : poses) {
		if (used_cells_.count(p)) {
			if (used_cells_[p].find(pos) != used_cells_[p].end()) {
				throw CircularDependencyException("Circle dependency");
			}
		}
	}

	std::set<Position> buffer{ poses.begin(), poses.end() };
	for (const Position& p : poses) {
		if (used_cells_.count(p)) {
			IsCicled(pos, used_cells_[p], buffer);
		}
	}
}

void Sheet::IsCicled(Position& pos, std::set<Position>& poses,
	std::set<Position>& buffer) {
	if (poses.find(pos) != poses.end()) {
		throw CircularDependencyException("Circle dependency");
	}

	for (const Position& ps : poses) {
		if (buffer.find(ps) == buffer.end()) {
			if (used_cells_.count(ps)) {
				if (used_cells_[ps].find(pos) != used_cells_.at(ps).end()) {
					throw CircularDependencyException("Circle dependency");
				}
			}
			buffer.insert(ps);
		}
	}

	for (const Position& ps : poses) {
		if (used_cells_.count(pos)) {
			IsCicled(pos, used_cells_[ps], buffer);
		}
	}
}

Position Sheet::convRawPos(const rawPosition& pos) {
	if (!rows_.count(pos.row) || !columns_.count(pos.column)) {
		return { -1, -1 };
	}

	return { rows_[pos.row], columns_[pos.column] };
}

Sheet::~Sheet() {}
