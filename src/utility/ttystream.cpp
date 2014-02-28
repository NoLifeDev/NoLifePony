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

#include "ttystream.hpp"
#include "tty.hpp"

#pragma warning(push, 1)
#include <iostream>
#pragma warning(pop)

namespace nlp {
    class ttybuf : public std::streambuf {
    public:
        ttybuf() = delete;
        ttybuf(uv::loop const & p_loop) :
            m_tty{uv::tty::create(p_loop)},
            m_old{std::cout.rdbuf()} {
            std::cout.rdbuf(this);
        }
        ttybuf(ttybuf const &) = delete;
        ttybuf(ttybuf &&) = delete;
        ~ttybuf() {
            std::cout.rdbuf(m_old);
        }
        ttybuf & operator=(ttybuf const &) = delete;
        ttybuf & operator=(ttybuf &&) = delete;
        int_type overflow(int_type ch) override {
            m_buf.push_back(traits_type::to_char_type(ch));
            return{};
        }
        int sync() override {
            m_tty.write(m_buf);
            m_buf.clear();
            return{0};
        }
    private:
        uv::tty m_tty;
        std::vector<char_type> m_buf;
        std::streambuf * m_old;
    };
    class ttystream::impl {
    public:
        impl() = delete;
        impl(uv::loop const & p_loop) :
            m_out{p_loop} {}
        impl(impl const &) = delete;
        impl(impl &&) = delete;
        ~impl() = default;
        impl & operator=(impl const &) = delete;
        impl & operator=(impl &&) = delete;
    private:
        ttybuf m_out;
    };
    ttystream::ttystream(uv::loop const & p_loop) :
        m_impl{std::make_unique<impl>(p_loop)} {}
    ttystream::~ttystream() = default;
}
