#ifndef ELABORATOR_H
#define ELABORATOR_H

#include "module.h"

class Elaborator {
public:
    Elaborator();
    virtual ~Elaborator();

    /**
     * @brief Performs elaboration of the required entity/arch.
     * @param ent entity name.
     * @param arch architecture name.
     * @return unknown modules/architectures discovered during elaboration.
     */
    virtual ModuleInstance* elaborate(const std::string& ent, const std::string& arch) = 0;

    /**
     * @brief Complete the elaboration.
     * @param modules modules/architectures needed to complete the elaboration.
     * @return 0 in case of success.
     */
    virtual int elaborate(ModuleInstance* modules) = 0;

    /**
     * @brief Creates an instance with a given name.
     * This function is to be called by the Manager. It will also assign nets
     * to ports.
     */
    // TODO generic/parameters?
    ModuleInstance& instantiate(const ModuleInterface& iface);

protected:
    ///> Modules provided by this simulator instance. They can be instantiated
    ///> as required. The string key is the name of the module, as defined
    ///> in its interface.
    std::map<const std::string, ModuleInterface>;

    ///> Instances of modules handled by this simulator instance. The string key
    ///> is the name of an instance, not the name of the module.
    std::map<const std::string, ModuleInstance>;

};

#endif /* ELABORATOR_H */
