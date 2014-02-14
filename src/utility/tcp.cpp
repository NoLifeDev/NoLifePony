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

#include "tcp.hpp"
#include "tcp_impl.hpp"
#include "handle_deleter.hpp"
#include "loop_impl.hpp"
#include "ip_impl.hpp"
#include "check.hpp"

#pragma warning(push, 1)
#include <iostream>
#pragma warning(pop)

namespace nlp {
    namespace uv {
        //tcp
        tcp tcp::listen(loop const & p_loop, ip const & p_ip, std::function<void(tcp)> p_callback) {
            auto && a = std::shared_ptr<impl>{new impl{p_loop.get()}, deleter{}};
            a->bind(p_ip.get());
            a->listen(0x100, [](uv_stream_t * p_stream, int p_status) {
                check(p_status);
                auto a = static_cast<tcp::impl *>(static_cast<handle::impl *>(p_stream->data));
                auto && b = std::shared_ptr<impl>{new impl{a->m_loop}, deleter{}};
                check(uv_accept(p_stream, b->get_stream()));
                a->m_listen_callback(std::move(b));
            });
            a->m_listen_callback = std::move(p_callback);
            return{a};
        }
        tcp::tcp(std::shared_ptr<impl> const & p_impl) :
            stream{std::static_pointer_cast<stream::impl>(p_impl)} {}
        //tcp::impl
        uv_stream_t * tcp::impl::get_stream() {
            return reinterpret_cast<uv_stream_t *>(&m_tcp);
        }
        void tcp::impl::bind(std::shared_ptr<ip::impl> const & p_ip) {
            check(uv_tcp_bind(&m_tcp, &p_ip->get(), 0));
        }
        tcp::impl::impl(std::shared_ptr<loop::impl> const & p_loop) :
            stream::impl{p_loop} {
            check(uv_tcp_init(p_loop->get(), &m_tcp));
            m_tcp.data = static_cast<handle::impl *>(this);
        }
    }
}
