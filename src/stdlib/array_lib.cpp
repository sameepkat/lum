#include "lum/stdlib/array_lib.hpp"
#include "lum/error/error.hpp"
#include "lum/runtime/value.hpp"
#include "lum/visitors/interpreter.hpp"

namespace lum {
lum::Value __len(lum::Interpreter &interpreter, const std::vector<lum::Value> &args) {
  
    if(!(args.size() == 1 )) {
        lum::Error::throw_internal("expected 1 arguments. found " + std::to_string(args.size()) );
    }

    double size;

    if (args[0].isArray()) {
      size = args[0].asArray()->size();
    } else if (args[0].isString()) {
      size = args[0].asString().size();
    } else {
        lum::Error::throw_internal("can't determine size of the data ");
    }

    return lum::Value(size);
}

lum::Value __push(lum::Interpreter &interpreter, const std::vector<lum::Value> &args) {
    if(!(args.size() == 2 )) {
        lum::Error::throw_internal("expected 2 arguments. found " + std::to_string(args.size()) );
    }

    lum::Value array = args[0];
    lum::Value element = args[1];

    if (!array.isArray()) {
        lum::Error::throw_internal("can't push into non-array");
    }

    array.asArray()->push_back(element);
    return lum::Value(element);
    }

lum::Value __pop(lum::Interpreter &interpreter, const std::vector<lum::Value> &args) {
    if(!(args.size() == 1 )) {
        lum::Error::throw_internal("expected 1 arguments. found " + std::to_string(args.size()) );
    }


    if (!args[0].isArray()) {
        lum::Error::throw_internal("can't pop from non-array");
    }

    auto array = args[0].asArray();

    if(array->size() == 0) {
        lum::Error::throw_internal("no items to pop in the array ");
    }
    lum::Value popped_item;

    popped_item = (*array)[array->size()-1];
    array->pop_back();
    return lum::Value(popped_item);
    }
}
