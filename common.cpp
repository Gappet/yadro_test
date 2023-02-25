#include "common.h"

#include <tuple>

Position::Position(const Position& pos) {
	column_ = pos.column_;
	row_ = pos.row_;
}

Position::Position(int row, int column) : column_(column), row_(row) {}

bool Position::operator<(const Position& pos) const {
	return std::tie(column_, row_) < std::tie(pos.column_, pos.row_);
}

bool Position::operator==(const Position& pos) const {
	return column_ == pos.column_ && row_ == pos.row_;
}

bool Position::isValid() const { return 0 <= column_ && 0 <= row_; }