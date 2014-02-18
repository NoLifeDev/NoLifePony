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
#include <string>
#include <cstdint>
#include <memory>
#pragma warning(pop)

namespace nlp {
    namespace uv {
        class ip {
        public:
            class impl;
            ip() = default;
            ip(ip const &) = default;
            ip(ip &&) = default;
            ~ip() = default;
            ip & operator=(ip const &) = default;
            ip & operator=(ip &&) = default;
            impl * operator->() const;
            static ip create(std::string const &, uint16_t);
        protected:
            std::shared_ptr<impl> m_impl;
        };
    }
}
