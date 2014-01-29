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

#include "server.hpp"
#include "player.hpp"
#include "manager.hpp"
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>
#include <thread>
#include <atomic>
#include <string>
#include <chrono>
#include <list>
#include <algorithm>
#include <iomanip>

namespace nlp {
    namespace server {
        std::list<player> players;
        void run(bool);
        void run() {
            std::cout << "NoLifePony server." << std::endl;
            manager manage;
            manage.listen<player>(273);
            for (;;) {
                manage.update();
            }
        }
    }
}
