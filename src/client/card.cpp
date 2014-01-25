//////////////////////////////////////////////////////////////////////////////
// NoLifePony - Pony Card Game                                              //
// Copyright © 2014 Peter Atashian                                          //
//                                                                          //
// This program is free software: you can redistribute it and/or modify     //
// it under the terms of the GNU Affero General Public License as           //
// published by the Free Software Foundation, either version 3 of the       //
// License, or (at your option) any later version.                          //
//                                                                          //
// This program is distributed in the hope that it will be useful,          //
// but WITHOUT ANY WARRANTY; without even the implied warranty of           //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            //
// GNU Affero General Public License for more details.                      //
//                                                                          //
// You should have received a copy of the GNU Affero General Public License //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.    //
//////////////////////////////////////////////////////////////////////////////

#include "card.hpp"

namespace nlp {
    class card::data {
    public:
        virtual type get_type() const = 0;
        virtual bool is_mane() const {
            return false;
        }
        virtual bool is_problem() const {
            return false;
        }
        virtual bool is_regular() const {
            return false;
        }
    private:
    };
    class card_mane final : public card::data {
    public:
        card::type get_type() const override {
            return card::type::mane;
        }
        bool is_mane() const override {
            return true;
        }
    private:
    };
    card::operator bool() const {
        return !!m_data;
    }
    bool card::operator==(card const & o) const {
        return m_data == o.m_data;
    }
    card::type card::get_type() const {
        return m_data->get_type();
    }
    bool card::is_mane() const {
        return m_data->is_mane();
    }
    bool card::is_problem() const {
        return m_data->is_problem();
    }
    //Returns whether the card is a regular card, aka a card that goes directly in the deck, and not separately as a problem or mane.
    bool card::is_regular() const {
        return m_data->is_regular();
    }
}
