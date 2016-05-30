#ifndef SIM_RESULT_H
#define SIM_RESULT_H

/*
 * Copyright (c) 2016 CERN
 * @author Michele Castellana <michele.castellana@cern.ch>
 *
 * This source code is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This source code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "net.h"

struct SimResult {
   /*
    * CHANGED means that the input of a module that the simulator instance does not handle has changed and therefore the other simulator need to be adviced
    * OK the step went fine and the manager can decide what to do afterwards
    * ERROR something went terribly wrong. Need to exit.
    */
   enum outcome { OK, CHANGED, ERROR };
   SimResult()
      : changed_sigs(nullptr),
        result_(OK) {}
   SimResult( outcome res, std::vector<Net*>* changed = nullptr )
      : changed_sigs(changed),
        result_(res) {}
   virtual ~SimResult() {
      if( changed_sigs ) {
         for( auto elem = changed_sigs->begin();
               elem != changed_sigs->end(); /* nothing */ ) {
            delete *elem;
            elem = changed_sigs->erase(elem);
         }
         delete changed_sigs;
      }
   };
   outcome result() const {
      return result_;
   }

   std::vector<Net*>* changed_sigs;
   private:
   outcome result_;

};

#endif /* SIM_RESULT_H */
