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

#include "manager.hpp"
#include "connection.hpp"
#include "listener.hpp"
#include <utility/ptr.hpp>
#include <SFML/Network/SocketSelector.hpp>
#include <list>
#include <iostream>
#include <chrono>

namespace nlp {
    manager::manager() {}
    manager::~manager() {}
    void manager::add_listener(uint16_t port, recv_handler_creator && func) {
        if (auto listen = listener::create(port, std::move(func))) {
            select.add(listen->get_socket());
            listeners.emplace_back(std::move(listen));
        }
    }
    void manager::update() {
        std::vector<std::list<std::unique_ptr<connection>>::iterator> to_remove;
        if (select.wait(sf::seconds(1))) {
            for (auto & listen : listeners) {
                if (select.isReady(listen->get_socket())) {
                    for (auto && next : *listen) {
                        select.add(next->get_socket());
                        connections.emplace_back(std::move(next));
                    }
                }
            }
            for (auto it = connections.begin(); it != connections.end(); ++it) {
                auto & connect = **it;
                if (select.isReady(connect.get_socket())) {
                    if (!connect.update()) {
                        to_remove.push_back(it);
                        select.remove(connect.get_socket());
                    }
                }
            }
        }
        auto now = std::chrono::steady_clock::now();
        if (now - last_update > std::chrono::seconds(5)) {
            last_update = now;
            for (auto it = connections.begin(); it != connections.end(); ++it) {
                auto & connect = **it;
                if (!connect.recv_update()) {
                    to_remove.push_back(it);
                    select.remove(connect.get_socket());
                }
            }
        }
        for (auto & it : to_remove) {
            connections.erase(it);
        }
    }
}