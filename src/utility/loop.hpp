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
#include "fwd.hpp"

namespace nlp {
    class loop {
    public:
        loop() = default;
        loop(loop const &) = default;
        loop(loop &&) = default;
        ~loop() = default;
        loop & operator=(loop const &) = default;
        loop & operator=(loop &&) = default;
        uv_loop_s * get() const;
        void run_default() const;
        void run_once() const;
        void run_nowait() const;
        static loop create();
        static loop get_default();
    private:
        loop(uv_loop_s *);
        uv_loop_s * m_loop = nullptr;
    };
}
