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

#pragma once

#pragma warning(push, 1)
#include <vector>
#include <iostream>
#pragma warning(pop)

namespace nlp {
    class packet {
    public:
        packet() = default;
        packet(packet const &) = default;
        packet(packet &&) = default;
        packet(std::vector<char>::const_iterator, std::vector<char>::const_iterator);
        ~packet() = default;
        packet & operator=(packet const &) = default;
        packet & operator=(packet &&) = default;
        void compute_size();
        std::vector<char> & get();
    protected:
        std::vector<char> m_data{4};
        size_t m_read_pos{0};
    };
}
