#ifndef ELAB_RESULT_H
#define ELAB_RESULT_H

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

#include "module.h"

struct ElabResult {
    enum outcome { NOT_FOUND, FOUND, NEED_ANOTHER };
    ElabResult( ModuleSpec* spec )
       : result_(NEED_ANOTHER){
          stored.spec_ = spec;
       }
    ElabResult( ModuleInstance* instance )
       : result_(FOUND) {
          stored.instance_ = instance;
       }
    ElabResult()
       : result_(NOT_FOUND) {}
    virtual ~ElabResult() {};
    ModuleSpec* get_spec() {
       assert(result_ == NEED_ANOTHER);
       return stored.spec_;
    }
    ModuleInstance* get_instance() {
       assert(result_ == FOUND);
       return stored.instance_;
    }
    outcome result() const {
       return result_;
    }

private:
    outcome result_; 
    union {
       ModuleSpec* spec_;
       ModuleInstance* instance_;
    } stored;

};

#endif /* ELAB_RESULT_H */
