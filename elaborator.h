#ifndef ELABORATOR_H
#define ELABORATOR_H

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
#include "handler.h"

class Elaborator : public virtual FileParamHandler {
public:
    Elaborator() :
       spec_to_find_(nullptr),
       instance_found_(nullptr) {};
    virtual ~Elaborator() {};

    enum status { NOT_FOUND, FOUND, NEED_ANOTHER };

    /**
     * @brief Complete the elaboration.
     * @param module module/architecture needed to continue the elaboration.
     * @return unknown module/architecture discovered during elaboration.
     *         NULL in any other case.
     */
    virtual ModuleSpec* elaborate(ModuleInstance* module = nullptr) = 0;

   /**
     * @brief To be used after the call of the method "instantiate".
     * @return A new instance if the compiler status after the "instantiate"
     *         method is FOUND. Nullptr otherwise.
     * @warning only the first call will actually return the spec.
     *          Subsequent call will return nullptr
     */
    ModuleInstance* get_instance() {
       ModuleInstance* tmp = instance_found_;
       if( instance_found_ ) {
          instance_found_ = nullptr;
       }
       return tmp;
    };

    /**
     * @brief To be used after the call of the method "instantiate".
     * @return The new required spec if the compiler status after the
     *         "instantiate" method is NEED_ANOTHER. Nullptr otherwise.
     * @warning only the first call will actually return the spec.
     *          Subsequent call will return nullptr
     */
    ModuleSpec* get_spec() {
       ModuleSpec* tmp = spec_to_find_;
       if( spec_to_find_ ) {
          spec_to_find_ = nullptr;
       }
       return tmp;
    };

    /**
     * @brief Answer the question: Is possible to continue with the emit_code?
     * @return True if there are no internal problems. False otherwise.
     */
    virtual bool can_continue() = 0;

    /**
     * @brief Emit code for the simulation.
     * If something went wrong in the elaboration phase, do nothing.
     * @return 0 if success. Non zero value in case of failure.
     */
    virtual int emit_code() = 0;

    /**
     * @brief Given a spec returns the compiler status after the request.
     * @param result the status of the compiler.
     * @return the status of the compiler.
     */
    virtual status instantiate(ModuleSpec& iface) = 0;

protected:
    ModuleSpec* spec_to_find_;
    ModuleInstance* instance_found_;

};

#endif /* ELABORATOR_H */
