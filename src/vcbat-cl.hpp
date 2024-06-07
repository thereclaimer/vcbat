#ifndef VCBAT_CL_HPP
#define VCBAT_CL_HPP

#include "vcbat-types.hpp"
#include "vcbat-cl-options.hpp"


struct VCBatClPreprocessor
{
    u32 args_count;
};

struct VCBatClLinker {
    u32 args_count;
};

struct VCBatClCompiler {
    u32 args_count;
};

struct VCBatCl {
    VCBatClPreprocessor preprocessor;
    VCBatClLinker       linker;
    VCBatClCompiler     compiler;
};

#endif //VCBAT_CL_HPP