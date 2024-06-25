#ifndef VCBAT_CL_OPTIONS_HPP
#define VCBAT_CL_OPTIONS_HPP

#include "vcbat-types.hpp"

/***************************************
 * 
 * These are all the C/C++ options, including flag values and descriptions
 * for cl.exe, the MSVC compiler
 * 
 * All of the flags and descriptions appear here exactly as they do on the MSDN
 * https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category?view=msvc-170
 *
 **************************************/

enum VcBatClOptionsCategory {
    VcBatClOptionsCategory_Optimization   = 0x00,
    VcBatClOptionsCategory_CodeGeneration = 0x01,
    VcBatClOptionsCategory_OutputFiles    = 0x02,
    VcBatClOptionsCategory_Preprocessor   = 0x03,
    VcBatClOptionsCategory_HeaderModules  = 0x04,
    VcBatClOptionsCategory_Language       = 0x05,
    VcBatClOptionsCategory_Linking        = 0x06,
    VcBatClOptionsCategory_Miscellaneous  = 0x07,
    VcBatClOptionsCategory_Diagnostics    = 0x08,
    VcBatClOptionsCategory_Experimental   = 0x09,
    VcBatClOptionsCategory_Deprecated     = 0x0A,
};

const u32 VCBAT_CL_OPTIONS_COUNT_OPTIMIZATIONS   = 11; 
const u32 VCBAT_CL_OPTIONS_COUNT_CODE_GENERATION = 66;
const u32 VCBAT_CL_OPTIONS_COUNT_OUTPUT_FILES    = 11;
const u32 VCBAT_CL_OPTIONS_COUNT_PREPROCESSOR    = 15;
const u32 VCBAT_CL_OPTIONS_COUNT_HEADER_MODULES  = 11;
const u32 VCBAT_CL_OPTIONS_COUNT_LANGUAGE        = 64;
const u32 VCBAT_CL_OPTIONS_COUNT_LINKING         = 9;
const u32 VCBAT_CL_OPTIONS_COUNT_MISCELLANEOUS   = 35;
const u32 VCBAT_CL_OPTIONS_COUNT_DIAGNOSTICS     = 20;
const u32 VCBAT_CL_OPTIONS_COUNT_EXPERIMENTAL    = 2;
const u32 VCBAT_CL_OPTIONS_COUNT_DEPRECATED      = 17;

enum VcBatClOptions {
    VcBatClOptions_Optimization_favor                          = 0x0000,//    /favor:<blend|AMD64|INTEL64|ATOM>	    Produces code that is optimized for a specified architecture, or for a range of architectures.
    VcBatClOptions_Optimization_O1                             = 0x0001,//    /O1	                                Creates small code.
    VcBatClOptions_Optimization_O2                             = 0x0002,//    /O2	                                Creates fast code.
    VcBatClOptions_Optimization_Ob                             = 0x0003,//    /Ob<n>	                            Controls inline expansion.
    VcBatClOptions_Optimization_Od                             = 0x0004,//    /Od	                                Disables optimization.
    VcBatClOptions_Optimization_Og                             = 0x0005,//    /Og	                                Deprecated. Uses global optimizations.
    VcBatClOptions_Optimization_Oi                             = 0x0006,//    /Oi[-]	                            Generates intrinsic functions.
    VcBatClOptions_Optimization_Os                             = 0x0007,//    /Os	                                Favors small code.
    VcBatClOptions_Optimization_Ot                             = 0x0008,//    /Ot	                                Favors fast code.
    VcBatClOptions_Optimization_Ox                             = 0x0009,//    /Ox	                                A subset of /O2 that doesn't include /GF or /Gy.
    VcBatClOptions_Optimization_Oy                             = 0x000A,//    /Oy	                                Omits frame pointer. (x86 only)
    
    VcBatClOptions_CodeGeneration_arch                         = 0x0100,//    /arch	                                Minimum CPU architecture requirements.
    VcBatClOptions_CodeGeneration_clr                          = 0x0101,//    /clr	                                Produces an output file to run on the common language runtime.
    VcBatClOptions_CodeGeneration_clr_implicitKeepAlive        = 0x0102,//    /clr:implicitKeepAlive-	            Turn off implicit emission of System::GC::KeepAlive(this).
    VcBatClOptions_CodeGeneration_clr_initialAppDomain         = 0x0103,//    /clr:initialAppDomain	                Enable initial AppDomain behavior of Visual C++ 2002.
    VcBatClOptions_CodeGeneration_clr_netCore                  = 0x0104,//    /clr:netcore	                        Produce assemblies targeting .NET Core runtime.
    VcBatClOptions_CodeGeneration_clr_noAssembly               = 0x0105,//    /clr:noAssembly	                    Don't produce an assembly.
    VcBatClOptions_CodeGeneration_clr_nostdimport              = 0x0106,//    /clr:nostdimport	                    Don't import any required assemblies implicitly.
    VcBatClOptions_CodeGeneration_clr_nostdlib                 = 0x0107,//    /clr:nostdlib	                        Ignore the system .NET framework directory when searching for assemblies.
    VcBatClOptions_CodeGeneration_clr_pure                     = 0x0108,//    /clr:pure	                            Produce an IL-only output file (no native executable code).
    VcBatClOptions_CodeGeneration_clr_safe                     = 0x0109,//    /clr:safe	                            Produce an IL-only verifiable output file.
    VcBatClOptions_CodeGeneration_EHa                          = 0x010A,//    /EHa	                                Enable C++ exception handling (with SEH exceptions).
    VcBatClOptions_CodeGeneration_EHc                          = 0x010B,//    /EHc	                                extern "C" defaults to nothrow.
    VcBatClOptions_CodeGeneration_EHr                          = 0x010C,//    /EHr	                                Always generate noexcept runtime termination checks.
    VcBatClOptions_CodeGeneration_EHs                          = 0x010D,//    /EHs	                                Enable C++ exception handling (no SEH exceptions).
    VcBatClOptions_CodeGeneration_feature                      = 0x010E,//    /feature	                            Enable architecture features.17.10
    VcBatClOptions_CodeGeneration_fp_contract                  = 0x010F,//    /fp:contract	                        Consider floating-point contractions when generating code.
    VcBatClOptions_CodeGeneration_fp_except                    = 0x0110,//    /fp:except[-]	                        Consider floating-point exceptions when generating code.
    VcBatClOptions_CodeGeneration_fp_fast                      = 0x0111,//    /fp:fast	                            "fast" floating-point model; results are less predictable.
    VcBatClOptions_CodeGeneration_fp_precise                   = 0x0112,//    /fp:precise	                        "precise" floating-point model; results are predictable.
    VcBatClOptions_CodeGeneration_fp_strict                    = 0x0113,//    /fp:strict	                        "strict" floating-point model (implies /fp:except).
    VcBatClOptions_CodeGeneration_fpcvt_BC                     = 0x0114,//    /fpcvt:BC	                            Backward-compatible floating-point to unsigned integer conversions.
    VcBatClOptions_CodeGeneration_fpcvt_IA                     = 0x0115,//    /fpcvt:IA	                            Intel native floating-point to unsigned integer conversion behavior.
    VcBatClOptions_CodeGeneration_fsanitize                    = 0x0116,//    /fsanitize	                        Enables compilation of sanitizer instrumentation such as AddressSanitizer.
    VcBatClOptions_CodeGeneration_fsanitize_coverage           = 0x0117,//    /fsanitize-coverage	                Enables compilation of code coverage instrumentation for libraries such as LibFuzzer.
    VcBatClOptions_CodeGeneration_GA                           = 0x0118,//    /GA	                                Optimizes for Windows applications.
    VcBatClOptions_CodeGeneration_Gd                           = 0x0119,//    /Gd	                                Uses the __cdecl calling convention. (x86 only)
    VcBatClOptions_CodeGeneration_Ge                           = 0x011A,//    /Ge	                                Deprecated. Activates stack probes.
    VcBatClOptions_CodeGeneration_GF                           = 0x011B,//    /GF	                                Enables string pooling.
    VcBatClOptions_CodeGeneration_Gh                           = 0x011C,//    /Gh	                                Calls hook function _penter.
    VcBatClOptions_CodeGeneration_GH                           = 0x011D,//    /GH	                                Calls hook function _pexit.
    VcBatClOptions_CodeGeneration_GL                           = 0x011E,//    /GL[-]	                            Enables whole program optimization.
    VcBatClOptions_CodeGeneration_Gm                           = 0x011F,//    /Gm[-]	                            Deprecated. Enables minimal rebuild.
    VcBatClOptions_CodeGeneration_Gr                           = 0x0120,//    /Gr	                                Uses the __fastcall calling convention. (x86 only)
    VcBatClOptions_CodeGeneration_GR                           = 0x0121,//    /GR[-]	                            Enables run-time type information (RTTI).
    VcBatClOptions_CodeGeneration_GS                           = 0x0122,//    /GS[-]	                            Checks buffer security.
    VcBatClOptions_CodeGeneration_Gs                           = 0x0123,//    /Gs[n]	                            Controls stack probes.
    VcBatClOptions_CodeGeneration_GT                           = 0x0124,//    /GT	                                Supports fiber safety for data allocated by using static thread-local storage.
    VcBatClOptions_CodeGeneration_Gu                           = 0x0125,//    /Gu[-]	                            Ensure distinct functions have distinct addresses.
    VcBatClOptions_CodeGeneration_guard_cf                     = 0x0126,//    /guard:cf[-]	                        Adds control flow guard security checks.
    VcBatClOptions_CodeGeneration_guard_ehcont                 = 0x0127,//    /guard:ehcont[-]	                    Enables EH continuation metadata.
    VcBatClOptions_CodeGeneration_Gv                           = 0x0128,//    /Gv	                                Uses the __vectorcall calling convention. (x86 and x64 only)
    VcBatClOptions_CodeGeneration_Gw                           = 0x0129,//    /Gw[-]	                            Enables whole-program global data optimization.
    VcBatClOptions_CodeGeneration_GX                           = 0x012A,//    /GX[-]	                            Deprecated. Enables synchronous exception handling. Use /EH instead.
    VcBatClOptions_CodeGeneration_Gy                           = 0x012B,//    /Gy[-]	                            Enables function-level linking.
    VcBatClOptions_CodeGeneration_Gz                           = 0x012C,//    /Gz	                                Uses the __stdcall calling convention. (x86 only)
    VcBatClOptions_CodeGeneration_GZ                           = 0x012D,//    /GZ	                                Deprecated. Enables fast checks. (Same as /RTC1)
    VcBatClOptions_CodeGeneration_homeparams                   = 0x012E,//    /homeparams	                        Forces parameters passed in registers to be written to their locations on the stack upon function entry. This compiler option is only for the x64 compilers (native and cross compile).
    VcBatClOptions_CodeGeneration_hotpatch                     = 0x012F,//    /hotpatch	                            Creates a hotpatchable image.
    VcBatClOptions_CodeGeneration_jumptablerdata               = 0x0130,//    /jumptablerdata	                    Put switch case statement jump tables in the .rdata section.
    VcBatClOptions_CodeGeneration_Qfast_transcendentals        = 0x0131,//    /Qfast_transcendentals	            Generates fast transcendentals.
    VcBatClOptions_CodeGeneration_QIfist                       = 0x0132,//    /QIfist	                            Deprecated. Suppresses the call of the helper function _ftol when a conversion from a floating-point type to an integral type is required. (x86 only)
    VcBatClOptions_CodeGeneration_Qimprecise_fwaits            = 0x0133,//    /Qimprecise_fwaits	                Removes fwait commands inside try blocks.
    VcBatClOptions_CodeGeneration_QIntel_jcc_erratum           = 0x0134,//    /QIntel-jcc-erratum	                Mitigates the performance impact of the Intel JCC erratum microcode update.
    VcBatClOptions_CodeGeneration_Qpar                         = 0x0135,//    /Qpar	                                Enables automatic parallelization of loops.
    VcBatClOptions_CodeGeneration_Qpar_report_n                = 0x0136,//    /Qpar-report:n	                    Enables reporting levels for automatic parallelization.
    VcBatClOptions_CodeGeneration_Qsafe_fp_loads               = 0x0137,//    /Qsafe_fp_loads	                    Uses integer move instructions for floating-point values and disables certain floating point load optimizations.
    VcBatClOptions_CodeGeneration_Qspectre                     = 0x0138,//    /Qspectre[-]	                        Enable mitigations for CVE 2017-5753, for a class of Spectre attacks.
    VcBatClOptions_CodeGeneration_Qspectre_load                = 0x0139,//    /Qspectre-load	                    Generate serializing instructions for every load instruction.
    VcBatClOptions_CodeGeneration_Qspectre_load_cf             = 0x013A,//    /Qspectre-load-cf	                    Generate serializing instructions for every control flow instruction that loads memory.
    VcBatClOptions_CodeGeneration_Qvec_report_n                = 0x013B,//    /Qvec-report:n	                    Enables reporting levels for automatic vectorization.
    VcBatClOptions_CodeGeneration_RTC1                         = 0x013C,//    /RTC1	                                Enable fast runtime checks (equivalent to /RTCsu).
    VcBatClOptions_CodeGeneration_RTCc                         = 0x013D,//    /RTCc	                                Convert to smaller type checks at run-time.
    VcBatClOptions_CodeGeneration_RTCs                         = 0x013E,//    /RTCs	                                Enable stack frame runtime checks.
    VcBatClOptions_CodeGeneration_RTCu                         = 0x013F,//    /RTCu	                                Enables uninitialized local usage checks.
    VcBatClOptions_CodeGeneration_volatile_iso                 = 0x0140,//    /volatile:iso	                        Acquire/release semantics not guaranteed on volatile accesses.
    VcBatClOptions_CodeGeneration_volatile_ms                  = 0x0141,//    /volatile:ms	                        Acquire/release semantics guaranteed on volatile accesses.
    
    VcBatClOptions_OutputFiles_doc                             = 0x0200,//    /doc	                                Processes documentation comments to an XML file. 
    VcBatClOptions_OutputFiles_FA                              = 0x0201,//    /FA	                                Configures an assembly listing file. 
    VcBatClOptions_OutputFiles_Fa                              = 0x0202,//    /Fa	                                Creates an assembly listing file. 
    VcBatClOptions_OutputFiles_Fd                              = 0x0203,//    /Fd	                                Renames program database file. 
    VcBatClOptions_OutputFiles_Fe                              = 0x0204,//    /Fe	                                Renames the executable file. 
    VcBatClOptions_OutputFiles_Fi                              = 0x0205,//    /Fi	                                Specifies the preprocessed output file name. 
    VcBatClOptions_OutputFiles_Fm                              = 0x0206,//    /Fm	                                Creates a mapfile. 
    VcBatClOptions_OutputFiles_Fo                              = 0x0207,//    /Fo	                                Creates an object file. 
    VcBatClOptions_OutputFiles_Fp                              = 0x0208,//    /Fp	                                Specifies a precompiled header file name. 
    VcBatClOptions_OutputFiles_FR                              = 0x0209,//    /FR, /Fr	                            Name generated .sbr browser files. /Fr is deprecated. 
    VcBatClOptions_OutputFiles_Ft                              = 0x020A,//    /Ft<dir>	                            Location of the header files generated for #import.
    
    VcBatClOptions_Preprocessor_AI                             = 0x0300,//    /AI<dir>	                            Specifies a directory to search to resolve file references passed to the #using directive.
    VcBatClOptions_Preprocessor_C                              = 0x0301,//    /C	                                Preserves comments during preprocessing.
    VcBatClOptions_Preprocessor_D                              = 0x0302,//    /D<name>{=|#}<text>                   Defines constants and macros.
    VcBatClOptions_Preprocessor_E                              = 0x0303,//    /E	                                Copies preprocessor output to standard output.
    VcBatClOptions_Preprocessor_EP                             = 0x0304,//    /EP	                                Copies preprocessor output to standard output.
    VcBatClOptions_Preprocessor_FI                             = 0x0305,//    /FI<file>	                            Preprocesses the specified include file.
    VcBatClOptions_Preprocessor_FU                             = 0x0306,//    /FU<file>	                            Forces the use of a file name, as if it had been passed to the #using directive.
    VcBatClOptions_Preprocessor_Fx                             = 0x0307,//    /Fx	                                Merges injected code with the source file.
    VcBatClOptions_Preprocessor_I                              = 0x0308,//    /I<dir>	                            Searches a directory for include files.
    VcBatClOptions_Preprocessor_P                              = 0x0309,//    /P	                                Writes preprocessor output to a file.
    VcBatClOptions_Preprocessor_PD                             = 0x031A,//    /PD	                                Print all macro definitions.
    VcBatClOptions_Preprocessor_PH                             = 0x031B,//    /PH	                                Generate #pragma file_hash when preprocessing.
    VcBatClOptions_Preprocessor_U                              = 0x031C,//    /U<name>	                            Removes a predefined macro.
    VcBatClOptions_Preprocessor_u                              = 0x031D,//    /u	                                Removes all predefined macros.
    VcBatClOptions_Preprocessor_X                              = 0x031E,//    /X	                                Ignores the standard include directory.
    
    VcBatClOptions_HeaderModules_exportHeader                  = 0x0400,//    /exportHeader	                        Create the header units files (.ifc) specified by the input arguments.
    VcBatClOptions_HeaderModules_headerUnit                    = 0x0401,//    /headerUnit	                        Specify where to find the header unit file (.ifc) for the specified header.
    VcBatClOptions_HeaderModules_headerName                    = 0x0402,//    /headerName	                        Build a header unit from the specified header.
    VcBatClOptions_HeaderModules_ifcOutput                     = 0x0403,//    /ifcOutput	                        Specify the output file name or directory for built .ifc files.
    VcBatClOptions_HeaderModules_interface                     = 0x0404,//    /interface	                        Treat the input file as a module interface unit.
    VcBatClOptions_HeaderModules_internalPartition             = 0x0405,//    /internalPartition	                Treat the input file as an internal partition unit.
    VcBatClOptions_HeaderModules_reference                     = 0x0406,//    /reference	                        Use named module IFC.
    VcBatClOptions_HeaderModules_scanDependencies              = 0x0407,//    /scanDependencies	                    List module and header unit dependencies in C++ Standard JSON form.
    VcBatClOptions_HeaderModules_sourceDependencies            = 0x0408,//    /sourceDependencies	                List all source-level dependencies.
    VcBatClOptions_HeaderModules_sourceDependencies_directives = 0x0409,//    /sourceDependencies:directives	    List module and header unit dependencies.
    VcBatClOptions_HeaderModules_translateInclude              = 0x040A,//    /translateInclude	                    Treat #include as import.
    
    VcBatClOptions_Language_await                              = 0x0500,//    /await	                            Enable coroutines (resumable functions) extensions.
    VcBatClOptions_Language_await_strict                       = 0x0501,//    /await:strict	                        Enable standard C++20 coroutine support with earlier language versions.
    VcBatClOptions_Language_constexpr_backtrace                = 0x0502,//    /constexpr:backtrace<N>	            Show N constexpr evaluations in diagnostics (default: 10).
    VcBatClOptions_Language_constexpr_depth                    = 0x0503,//    /constexpr:depth<N>	                Recursion depth limit for constexpr evaluation (default: 512).
    VcBatClOptions_Language_constexpr_steps                    = 0x0504,//    /constexpr:steps<N>	                Terminate constexpr evaluation after N steps (default: 100000)
    VcBatClOptions_Language_openmp                             = 0x0505,//    /openmp	                            Enables #pragma omp in source code.
    VcBatClOptions_Language_openmp_experimental                = 0x0506,//    /openmp:experimental	                Enable OpenMP 2.0 language extensions plus select OpenMP 3.0+ language extensions.
    VcBatClOptions_Language_openmp_llvm                        = 0x0507,//    /openmp:llvm	                        OpenMP language extensions using LLVM runtime.
    VcBatClOptions_Language_permissive                         = 0x0508,//    /permissive[-]	                    Set standard-conformance mode.
    VcBatClOptions_Language_std_cpp_14                         = 0x0509,//    /std:c++14	                        C++14 standard ISO/IEC 14882:2014 (default).
    VcBatClOptions_Language_std_cpp_17                         = 0x0500,//    /std:c++17	                        C++17 standard ISO/IEC 14882:2017.
    VcBatClOptions_Language_std_cpp_20                         = 0x050A,//    /std:c++20	                        C++20 standard ISO/IEC 14882:2020.
    VcBatClOptions_Language_std_cpp_latest                     = 0x050B,//    /std:c++latest	                    The latest draft C++ standard preview features.
    VcBatClOptions_Language_std_c_11                           = 0x050C,//    /std:c11	                            C11 standard ISO/IEC 9899:2011.
    VcBatClOptions_Language_std_c_17                           = 0x050D,//    /std:c17	                            C17 standard ISO/IEC 9899:2018.
    VcBatClOptions_Language_std_c_latest                       = 0x050E,//    /std:clatest	                        The latest draft C standard preview features.
    VcBatClOptions_Language_vd                                 = 0x050F,//    /vd{0|1|2}	                        Suppresses or enables hidden vtordisp class members.
    VcBatClOptions_Language_vmb                                = 0x0510,//    /vmb	                                Uses best base for pointers to members.
    VcBatClOptions_Language_vmg                                = 0x0511,//    /vmg	                                Uses full generality for pointers to members.
    VcBatClOptions_Language_vmm                                = 0x0512,//    /vmm	                                Declares multiple inheritance.
    VcBatClOptions_Language_vms                                = 0x0513,//    /vms	                                Declares single inheritance.
    VcBatClOptions_Language_vmv                                = 0x0514,//    /vmv	                                Declares virtual inheritance.
    VcBatClOptions_Language_Z7                                 = 0x0515,//    /Z7	                                Generates C 7.0-compatible debugging information.
    VcBatClOptions_Language_Za                                 = 0x0516,//    /Za	                                Disables some C89 language extensions in C code.
    VcBatClOptions_Language_Zc___cplusplus                     = 0x0517,//    /Zc:__cplusplus[-]	                Enable the __cplusplus macro to report the supported standard (off by default).
    VcBatClOptions_Language_Zc___STDC__                        = 0x0518,//    /Zc:__STDC__	                        Enable the __STDC__ macro to report the C standard is supported (off by default).
    VcBatClOptions_Language_Zc_alignedNew                      = 0x0519,//    /Zc:alignedNew[-]	                    Enable C++17 over-aligned dynamic allocation (on by default in C++17).
    VcBatClOptions_Language_Zc_auto                            = 0x0510,//    /Zc:auto[-]	                        Enforce the new Standard C++ meaning for auto (on by default).
    VcBatClOptions_Language_Zc_char8_t                         = 0x051A,//    /Zc:char8_t[-]	                    Enable or disable C++20 native u8 literal support as const char8_t (off by default, except under /std:c++20).
    VcBatClOptions_Language_Zc_enumTypes                       = 0x051B,//    /Zc:enumTypes[-]	                    Enable Standard C++ rules for inferred enum base types (Off b y default, not implied by /permissive-).
    VcBatClOptions_Language_Zc_externC                         = 0x051C,//    /Zc:externC[-]	                    Enforce Standard C++ rules for extern "C" functions (implied by /permissive-).
    VcBatClOptions_Language_Zc_externConstexpr                 = 0x051D,//    /Zc:externConstexpr[-]	            Enable external linkage for constexpr variables (off by default).
    VcBatClOptions_Language_Zc_forScope                        = 0x051E,//    /Zc:forScope[-]	                    Enforce Standard C++ for scoping rules (on by default).
    VcBatClOptions_Language_Zc_gotoScope                       = 0x051F,//    /Zc:gotoScope	                        Enforce Standard C++ goto rules around local variable initialization (implied by /permissive-).
    VcBatClOptions_Language_Zc_hiddenFriend                    = 0x0520,//    /Zc:hiddenFriend[-]	                Enforce Standard C++ hidden friend rules (implied by /permissive-)
    VcBatClOptions_Language_Zc_implicitNoexcept                = 0x0521,//    /Zc:implicitNoexcept[-]	            Enable implicit noexcept on required functions (on by default).
    VcBatClOptions_Language_Zc_inline                          = 0x0522,//    /Zc:inline[-]	                        Remove unreferenced functions or data if they're COMDAT or have internal linkage only (off by default).
    VcBatClOptions_Language_Zc_lambda                          = 0x0523,//    /Zc:lambda[-]	                        Enable new lambda processor for conformance-mode syntactic checks in generic lambdas.
    VcBatClOptions_Language_Zc_noexceptTypes                   = 0x0524,//    /Zc:noexceptTypes[-]	                Enforce C++17 noexcept rules (on by default in C++17 or later).
    VcBatClOptions_Language_Zc_nrvo                            = 0x0525,//    /Zc:nrvo[-]	                        Enable optional copy and move elisions (on by default under /O2, /permissive-, or /std:c++20 or later).
    VcBatClOptions_Language_Zc_preprocessor                    = 0x0526,//    /Zc:preprocessor[-]	                Use the new conforming preprocessor (off by default, except in C11/C17).
    VcBatClOptions_Language_Zc_referenceBinding                = 0x0527,//    /Zc:referenceBinding[-]	            A UDT temporary won't bind to a non-const lvalue reference (off by default).
    VcBatClOptions_Language_Zc_rvalueCast                      = 0x0528,//    /Zc:rvalueCast[-]	                    Enforce Standard C++ explicit type conversion rules (off by default).
    VcBatClOptions_Language_Zc_sizedDealloc                    = 0x0529,//    /Zc:sizedDealloc[-]	                Enable C++14 global sized deallocation functions (on by default).
    VcBatClOptions_Language_Zc_strictStrings                   = 0x0520,//    /Zc:strictStrings[-]	                Disable string-literal to char* or wchar_t* conversion (off by default).
    VcBatClOptions_Language_Zc_templateScope                   = 0x052A,//    /Zc:templateScope[-]	                Enforce Standard C++ template parameter shadowing rules (off by default).
    VcBatClOptions_Language_Zc_ternary                         = 0x052B,//    /Zc:ternary[-]	                    Enforce conditional operator rules on operand types (off by default).
    VcBatClOptions_Language_Zc_threadSafeInit                  = 0x052C,//    /Zc:threadSafeInit[-]	                Enable thread-safe local static initialization (on by default).
    VcBatClOptions_Language_Zc_throwingNew                     = 0x052D,//    /Zc:throwingNew[-]	                Assume operator new throws on failure (off by default).
    VcBatClOptions_Language_Zc_tlsGuards                       = 0x052E,//    /Zc:tlsGuards[-]	                    Generate runtime checks for TLS variable initialization (on by default).
    VcBatClOptions_Language_Zc_trigraphs                       = 0x052F,//    /Zc:trigraphs	                        Enable trigraphs (obsolete, off by default).
    VcBatClOptions_Language_Zc_twoPhase                        = 0x0530,//    /Zc:twoPhase[-]	                    Use nonconforming template parsing behavior (conforming by default).
    VcBatClOptions_Language_Zc_wchar_t                         = 0x0531,//    /Zc:wchar_t[-]	                    wchar_t is a native type, not a typedef (on by default).
    VcBatClOptions_Language_Zc_zeroSizeArrayNew                = 0x0532,//    /Zc:zeroSizeArrayNew[-]	            Call member new/delete for 0-size arrays of objects (on by default).
    VcBatClOptions_Language_Ze                                 = 0x0533,//    /Ze	                                Deprecated. Enables C89 language extensions.
    VcBatClOptions_Language_Zf                                 = 0x0534,//    /Zf	                                Improves PDB generation time in parallel builds.
    VcBatClOptions_Language_ZH                                 = 0x0535,//    /ZH:[MD5|SHA1|SHA_256]	            Specifies MD5, SHA-1, or SHA-256 for checksums in debug info.
    VcBatClOptions_Language_ZI                                 = 0x0536,//    /ZI	                                Includes debug information in a program database compatible with Edit and Continue. (x86 only)
    VcBatClOptions_Language_Zi                                 = 0x0537,//    /Zi	                                Generates complete debugging information.
    VcBatClOptions_Language_Zl                                 = 0x0538,//    /Zl	                                Removes the default library name from the .obj file.
    VcBatClOptions_Language_Zo                                 = 0x0539,//    /Zo[-]	                            Generate richer debugging information for optimized code.
    VcBatClOptions_Language_Zp                                 = 0x0530,//    /Zp[n]	                            Packs structure members.
    VcBatClOptions_Language_Zs                                 = 0x053A,//    /Zs	                                Checks syntax only.
    VcBatClOptions_Language_ZW                                 = 0x053B,//    /ZW	                                Produces an output file to run on the Windows Runtime.
    
    VcBatClOptions_Linking_F                                   = 0x0600,//    /F	                                Sets stack size.
    VcBatClOptions_Linking_LD                                  = 0x0601,//    /LD	                                Creates a dynamic-link library.
    VcBatClOptions_Linking_LDd                                 = 0x0602,//    /LDd	                                Creates a debug dynamic-link library.
    VcBatClOptions_Linking_link                                = 0x0603,//    /link	                                Passes the specified option to LINK.
    VcBatClOptions_Linking_LN                                  = 0x0604,//    /LN	                                Creates an MSIL .netmodule.
    VcBatClOptions_Linking_MD                                  = 0x0605,//    /MD	                                Compiles to create a multithreaded DLL, by using MSVCRT.lib.
    VcBatClOptions_Linking_MDd                                 = 0x0606,//    /MDd	                                Compiles to create a debug multithreaded DLL, by using MSVCRTD.lib.
    VcBatClOptions_Linking_MT                                  = 0x0607,//    /MT	                                Compiles to create a multithreaded executable file, by using LIBCMT.lib.
    VcBatClOptions_Linking_MTd                                 = 0x0608,//    /MTd	                                Compiles to create a debug multithreaded executable file, by using LIBCMTD.lib.
    
    VcBatClOptions_Miscellaneous_listOptions                   = 0x0700,//    /?	                                Lists the compiler options.
    VcBatClOptions_Miscellaneous_responseFile                  = 0x0701,//    @	                                    Specifies a response file.
    VcBatClOptions_Miscellaneous_analyze                       = 0x0702,//    /analyze	                            Enables code analysis.
    VcBatClOptions_Miscellaneous_bigobj                        = 0x0703,//    /bigobj	                            Increases the number of addressable sections in an .obj file.
    VcBatClOptions_Miscellaneous_c                             = 0x0704,//    /c	                                Compiles without linking.
    VcBatClOptions_Miscellaneous_cgthreads                     = 0x0705,//    /cgthreads	                        Specifies number of cl.exe threads to use for optimization and code generation.
    VcBatClOptions_Miscellaneous_errorReport                   = 0x0706,//    /errorReport	                        Deprecated. Windows Error Reporting (WER) settings control error reporting.
    VcBatClOptions_Miscellaneous_execution                     = 0x0707,//    /execution-charset	                Set execution character set.
    VcBatClOptions_Miscellaneous_fastfail                      = 0x0708,//    /fastfail	                            Enable fast-fail mode.
    VcBatClOptions_Miscellaneous_FC                            = 0x0709,//    /FC	                                Displays the full path of source code files passed to cl.exe in diagnostic text.
    VcBatClOptions_Miscellaneous_FS                            = 0x0700,//    /FS	                                Forces writes to the PDB file to be serialized through MSPDBSRV.EXE.
    VcBatClOptions_Miscellaneous_H                             = 0x070A,//    /H	                                Deprecated. Restricts the length of external (public) names.
    VcBatClOptions_Miscellaneous_HELP                          = 0x070B,//    /HELP	                                Lists the compiler options.
    VcBatClOptions_Miscellaneous_J                             = 0x070C,//    /J	                                Changes the default char type.
    VcBatClOptions_Miscellaneous_JMC                           = 0x070D,//    /JMC	                                Supports native C++ Just My Code debugging.
    VcBatClOptions_Miscellaneous_kernel                        = 0x070E,//    /kernel	                            The compiler and linker create a binary that can be executed in the Windows kernel.
    VcBatClOptions_Miscellaneous_MP                            = 0x070F,//    /MP	                                Builds multiple source files concurrently.
    VcBatClOptions_Miscellaneous_nologo                        = 0x0710,//    /nologo	                            Suppresses display of sign-on banner.
    VcBatClOptions_Miscellaneous_presetPadding                 = 0x0711,//    /presetPadding	                    Zero initialize padding for stack based class types.
    VcBatClOptions_Miscellaneous_showIncludes                  = 0x0712,//    /showIncludes	                        Displays a list of all include files during compilation.
    VcBatClOptions_Miscellaneous_source_charset                = 0x0713,//    /source-charset	                    Set source character set.
    VcBatClOptions_Miscellaneous_Tc                            = 0x0714,//    /Tc	                                Specifies a C source file.
    VcBatClOptions_Miscellaneous_TC                            = 0x0715,//    /TC	                                Specifies all source files are C.
    VcBatClOptions_Miscellaneous_Tp                            = 0x0716,//    /Tp	                                Specifies a C++ source file.
    VcBatClOptions_Miscellaneous_TP                            = 0x0717,//    /TP	                                Specifies all source files are C++.
    VcBatClOptions_Miscellaneous_utf_8                         = 0x0718,//    /utf-8	                            Set source and execution character sets to UTF-8.
    VcBatClOptions_Miscellaneous_V                             = 0x0719,//    /V	                                Deprecated. Sets the version string.
    VcBatClOptions_Miscellaneous_validate_charset              = 0x0710,//    /validate-charset	                    Validate UTF-8 files for only compatible characters.
    VcBatClOptions_Miscellaneous_volatileMetadata              = 0x071A,//    /volatileMetadata	                    Generate metadata on volatile memory accesses.
    VcBatClOptions_Miscellaneous_Yc                            = 0x071B,//    /Yc	                                Create .PCH file.
    VcBatClOptions_Miscellaneous_Yd                            = 0x071C,//    /Yd	                                Deprecated. Places complete debugging information in all object files. Use /Zi instead.
    VcBatClOptions_Miscellaneous_Yl                            = 0x071D,//    /Yl	                                Injects a PCH reference when creating a debug library.
    VcBatClOptions_Miscellaneous_Yu                            = 0x071E,//    /Yu	                                Uses a precompiled header file during build.
    VcBatClOptions_Miscellaneous_Y                             = 0x071F,//    /Y-	                                Ignores all other precompiled-header compiler options in the current build.
    VcBatClOptions_Miscellaneous_Zm                            = 0x072A,//    /Zm	                                Specifies the precompiled header memory allocation limit.
    
    VcBatClOptions_Diagnostics_diagnostics_caret               = 0x0800,//    /diagnostics:caret[-]	                Diagnostics format: prints column and the indicated line of source.
    VcBatClOptions_Diagnostics_diagnostics_classic             = 0x0801,//    /diagnostics:classic	                Use legacy diagnostics format.
    VcBatClOptions_Diagnostics_diagnostics                     = 0x0802,//    /diagnostics	                        Diagnostics format: prints column information.
    VcBatClOptions_Diagnostics_external_anglebrackets          = 0x0803,//    /external:anglebrackets	            Treat all headers included via <> as external.
    VcBatClOptions_Diagnostics_external_env                    = 0x0804,//    /external:env:<var>	                Specify an environment variable with locations of external headers.
    VcBatClOptions_Diagnostics_external_I                      = 0x0805,//    /external:I <path>	                Specify location of external headers.
    VcBatClOptions_Diagnostics_external_templates              = 0x0806,//    /external:templates[-]	            Evaluate warning level across template instantiation chain.
    VcBatClOptions_Diagnostics_external_W                      = 0x0807,//    /external:W<n>	                    Set warning level for external headers.
    VcBatClOptions_Diagnostics_options_strict                  = 0x0808,//    /options:strict	                    Unrecognized compiler options are errors.
    VcBatClOptions_Diagnostics_sdl                             = 0x0809,//    /sdl	                                Enable more security features and warnings.
    VcBatClOptions_Diagnostics_w                               = 0x080A,//    /w	                                Disable all warnings.
    VcBatClOptions_Diagnostics_W0                              = 0x080B,//    /W0, /W1, /W2, /W3, /W4	            Set output warning level.
    VcBatClOptions_Diagnostics_w1                              = 0x080C,//    /w1<n>, /w2<n>, /w3<n>, /w4<n>	    Set warning level for the specified warning.
    VcBatClOptions_Diagnostics_Wall                            = 0x080D,//    /Wall	                                Enable all warnings, including warnings that are disabled by default.
    VcBatClOptions_Diagnostics_wd                              = 0x080E,//    /wd<n>	                            Disable the specified warning.
    VcBatClOptions_Diagnostics_we                              = 0x080F,//    /we<n>	                            Treat the specified warning as an error.
    VcBatClOptions_Diagnostics_WL                              = 0x0810,//    /WL	                                Enable one-line diagnostics for error and warning messages when compiling C++ source code from the command line.
    VcBatClOptions_Diagnostics_wo                              = 0x0811,//    /wo<n>	                            Display the specified warning only once.
    VcBatClOptions_Diagnostics_Wv                              = 0x0812,//    /Wv:xx[.yy[.zzzzz]]	                Disable warnings introduced after the specified version of the compiler.
    VcBatClOptions_Diagnostics_WX                              = 0x0813,//    /WX                                   Treat warnings as errors.
    
    VcBatClOptions_Experimental_experimental_log               = 0x0900,//    /experimental:log	                    Enables experimental structured SARIF output.
    VcBatClOptions_Experimental_experimental_module            = 0x0901,//    /experimental:module	                Enables experimental module support.
    
    VcBatClOptions_Deprecated_clr                              = 0x0A00,//    /clr:noAssembly	                    Deprecated. Use /LN (Create MSIL Module) instead.
    VcBatClOptions_Deprecated_errorReport                      = 0x0A01,//    /errorReport	                        Deprecated. Error reporting is controlled by Windows Error Reporting (WER) settings.
    VcBatClOptions_Deprecated_experimental_preprocessor        = 0x0A02,//    /experimental:preprocessor	        Deprecated. Enables experimental conforming preprocessor support. Use /Zc:preprocessor
    VcBatClOptions_Deprecated_Fr                               = 0x0A03,//    /Fr	                                Deprecated. Creates a browse information file without local variables.
    VcBatClOptions_Deprecated_Ge                               = 0x0A04,//    /Ge	                                Deprecated. Activates stack probes. On by default.
    VcBatClOptions_Deprecated_Gm                               = 0x0A05,//    /Gm	                                Deprecated. Enables minimal rebuild.
    VcBatClOptions_Deprecated_GX                               = 0x0A06,//    /GX	                                Deprecated. Enables synchronous exception handling. Use /EH instead.
    VcBatClOptions_Deprecated_GZ                               = 0x0A07,//    /GZ	                                Deprecated. Enables fast checks. Use /RTC1 instead.
    VcBatClOptions_Deprecated_H                                = 0x0A08,//    /H	                                Deprecated. Restricts the length of external (public) names.
    VcBatClOptions_Deprecated_Og                               = 0x0A0A,//    /Og	                                Deprecated. Uses global optimizations.
    VcBatClOptions_Deprecated_QIfist                           = 0x0A0B,//    /QIfist	                            Deprecated. Once used to specify how to convert from a floating-point type to an integral type.
    VcBatClOptions_Deprecated_V                                = 0x0A0C,//    /V	                                Deprecated. Sets the .obj file version string.
    VcBatClOptions_Deprecated_Wp64                             = 0x0A0D,//    /Wp64	                                Obsolete. Detects 64-bit portability problems.
    VcBatClOptions_Deprecated_Yd                               = 0x0A0E,//    /Yd	                                Deprecated. Places complete debugging information in all object files. Use /Zi instead.
    VcBatClOptions_Deprecated_Zc_forScope                      = 0x0A0F,//    /Zc:forScope-	                        Deprecated. Disables conformance in for loop scope.
    VcBatClOptions_Deprecated_Ze                               = 0x0A10,//    /Ze	                                Deprecated. Enables language extensions.
    VcBatClOptions_Deprecated_Zg                               = 0x0A11 //    /Zg	                                Removed in Visual Studio 2015. Generates function prototypes.
};


const char* VCBAT_CL_OPTIONS_FLAG_OPTIMIZATION[] = {
    "/favor:<blend|AMD64|INTEL64|ATOM>",
    "/O1",
    "/O2",
    "/Ob<n>",
    "/Od",
    "/Og",
    "/Oi[-]",
    "/Os",
    "/Ot",
    "/Ox",
    "/Oy"
};

const char* VCBAT_CL_OPTIONS_FLAG_CODE_GENERATION[] = {
    "/arch",
    "/clr",
    "/clr:implicitKeepAlive-",
    "/clr:initialAppDomain",
    "/clr:netcore",
    "/clr:noAssembly",
    "/clr:nostdimport",
    "/clr:nostdlib",
    "/clr:pure",
    "/clr:safe",
    "/EHa",
    "/EHc",
    "/EHr",
    "/EHs",
    "/feature",
    "/fp:contract",
    "/fp:except[-]",
    "/fp:fast",
    "/fp:precise",
    "/fp:strict",
    "/fpcvt:BC",
    "/fpcvt:IA",
    "/fsanitize",
    "/fsanitize-coverage",
    "/GA",
    "/Gd",
    "/Ge",
    "/GF",
    "/Gh",
    "/GH",
    "/GL[-]",
    "/Gm[-]",
    "/Gr",
    "/GR[-]",
    "/GS[-]",
    "/Gs[n]",
    "/GT",
    "/Gu[-]",
    "/guard:cf[-]",
    "/guard:ehcont[-]",
    "/Gv",
    "/Gw[-]",
    "/GX[-]",
    "/Gy[-]",
    "/Gz",
    "/GZ",
    "/homeparams",
    "/hotpatch",
    "/jumptablerdata",
    "/Qfast_transcendentals",
    "/QIfist",
    "/Qimprecise_fwaits",
    "/QIntel-jcc-erratum",
    "/Qpar",
    "/Qpar-report:n",
    "/Qsafe_fp_loads",
    "/Qspectre[-]",
    "/Qspectre-load",
    "/Qspectre-load-cf",
    "/Qvec-report:n",
    "/RTC1",
    "/RTCc",
    "/RTCs",
    "/RTCu",
    "/volatile:iso",
    "/volatile:ms"
};

const char* VCBAT_CL_OPTIONS_FLAG_OUTPUT_FILES[] = {
    "/doc",
    "/FA",
    "/Fa",
    "/Fd",
    "/Fe",
    "/Fi",
    "/Fm",
    "/Fo",
    "/Fp",
    "/FR, /Fr",
    "/Ft<dir>"
};

const char* VCBAT_CL_OPTIONS_FLAG_PREPROCESSOR[] = {
    "/AI<dir>",
    "/C",
    "/D<name>{=|#}<text>",
    "/E",
    "/EP",
    "/FI<file>",
    "/FU<file>",
    "/Fx",
    "/I<dir>",
    "/P",
    "/PD",
    "/PH",
    "/U<name>",
    "/u",
    "/X"
};

const char* VCBAT_CL_OPTIONS_FLAG_HEADER_MODULES[] = {
    "/exportHeader",
    "/headerUnit",
    "/headerName",
    "/ifcOutput",
    "/interface",
    "/internalPartition",
    "/reference",
    "/scanDependencies",
    "/sourceDependencies",
    "/sourceDependencies:directives",
    "/translateInclude"
};

const char* VCBAT_CL_OPTIONS_FLAG_LANGUAGE[] = {
    "/await",
    "/await:strict",
    "/constexpr:backtrace<N>",
    "/constexpr:depth<N>",
    "/constexpr:steps<N>",
    "/openmp",
    "/openmp:experimental",
    "/openmp:llvm",
    "/permissive[-]",
    "/std:c++14",
    "/std:c++17",
    "/std:c++20",
    "/std:c++latest",
    "/std:c11",
    "/std:c17",
    "/std:clatest",
    "/vd{0|1|2}",
    "/vmb",
    "/vmg",
    "/vmm",
    "/vms",
    "/vmv",
    "/Z7",
    "/Za",
    "/Zc:__cplusplus[-]",
    "/Zc:__STDC__",
    "/Zc:alignedNew[-]",
    "/Zc:auto[-]",
    "/Zc:char8_t[-]",
    "/Zc:enumTypes[-]",
    "/Zc:externC[-]",
    "/Zc:externConstexpr[-]",
    "/Zc:forScope[-]",
    "/Zc:gotoScope",
    "/Zc:hiddenFriend[-]",
    "/Zc:implicitNoexcept[-]",
    "/Zc:inline[-]",
    "/Zc:lambda[-]",
    "/Zc:noexceptTypes[-]",
    "/Zc:nrvo[-]",
    "/Zc:preprocessor[-]",
    "/Zc:referenceBinding[-]",
    "/Zc:rvalueCast[-]",
    "/Zc:sizedDealloc[-]",
    "/Zc:strictStrings[-]",
    "/Zc:templateScope[-]",
    "/Zc:ternary[-]",
    "/Zc:threadSafeInit[-]",
    "/Zc:throwingNew[-]",
    "/Zc:tlsGuards[-]",
    "/Zc:trigraphs",
    "/Zc:twoPhase[-]",
    "/Zc:wchar_t[-]",
    "/Zc:zeroSizeArrayNew[-]",
    "/Ze",
    "/Zf",
    "/ZH:[MD5|SHA1|SHA_256]",
    "/ZI",
    "/Zi",
    "/Zl",
    "/Zo[-]",
    "/Zp[n]",
    "/Zs",
    "/ZW"
};

const char* VCBAT_CL_OPTIONS_FLAG_LINKING[] = {
    "/F",
    "/LD",
    "/LDd",
    "/link",
    "/LN",
    "/MD",
    "/MDd",
    "/MT",
    "/MTd"
};


const char* VCBAT_CL_OPTIONS_FLAG_MISCELLANEOUS[] = {
    " /?",
    " @",
    "/analyze",
    "/bigobj",
    "/c",
    "/cgthreads",
    "/errorReport",
    "/execution-charset",
    "/fastfail",
    "/FC",
    "/FS",
    "/H",
    "/HELP",
    "/J",
    "/JMC",
    "/kernel",
    "/MP",
    "/nologo",
    "/presetPadding",
    "/showIncludes",
    "/source-charset",
    "/Tc",
    "/TC",
    "/Tp",
    "/TP",
    "/utf-8",
    "/V",
    "/validate-charset",
    "/volatileMetadata",
    "/Yc",
    "/Yd",
    "/Yl",
    "/Yu",
    "/Y-",
    "/Zm"
};

const char* VCBAT_CL_OPTIONS_FLAG_DIAGNOSTICS[] = {
    "/diagnostics:caret[-]",
    "/diagnostics:classic",
    "/diagnostics",
    "/external:anglebrackets",
    "/external:env:<var>",
    "/external:I <path>",
    "/external:templates[-]",
    "/external:W<n>",
    "/options:strict",
    "/sdl",
    "/w",
    "/W0, /W1, /W2, /W3, /W4",
    "/w1<n>, /w2<n>, /w3<n>, /w4<n>",
    "/Wall",
    "/wd<n>",
    "/we<n>",
    "/WL",
    "/wo<n>",
    "/Wv:xx[.yy[.zzzzz]]",
    "/WX"
};

const char* VCBAT_CL_OPTIONS_FLAG_EXPERIMENTAL[] = {
    "/experimental:log",
    "/experimental:module"
};

const char* VCBAT_CL_OPTIONS_FLAG_DEPRECATED[] = {
    "/clr:noAssembly",
    "/errorReport",
    "/experimental:preprocessor",
    "/Fr",
    "/Ge",
    "/Gm",
    "/GX",
    "/GZ",
    "/H",
    "/Og",
    "/QIfist",
    "/V",
    "/Wp64",
    "/Yd",
    "/Zc:forScope-",
    "/Ze",
    "/Zg"
};

const char *const * VCBAT_CL_OPTIONS_FLAG_TABLE[] {
    VCBAT_CL_OPTIONS_FLAG_OPTIMIZATION,
    VCBAT_CL_OPTIONS_FLAG_CODE_GENERATION,
    VCBAT_CL_OPTIONS_FLAG_OUTPUT_FILES,
    VCBAT_CL_OPTIONS_FLAG_PREPROCESSOR,
    VCBAT_CL_OPTIONS_FLAG_HEADER_MODULES,
    VCBAT_CL_OPTIONS_FLAG_LANGUAGE,
    VCBAT_CL_OPTIONS_FLAG_LINKING,
    VCBAT_CL_OPTIONS_FLAG_MISCELLANEOUS,
    VCBAT_CL_OPTIONS_FLAG_DIAGNOSTICS,
    VCBAT_CL_OPTIONS_FLAG_EXPERIMENTAL,
    VCBAT_CL_OPTIONS_FLAG_DEPRECATED
};

const char* VCBAT_CL_OPTIONS_DESCRIPTION_OPTIMIZATION[] = {
    "Produces code that is optimized for a specified architecture, or for a range of architectures.",
    "Creates small code.",
    "Creates fast code.",
    "Controls inline expansion.",
    "Disables optimization.",
    "Deprecated. Uses global optimizations.",
    "Generates intrinsic functions.",
    "Favors small code.",
    "Favors fast code.",
    "A subset of /O2 that doesn't include /GF or /Gy.",
    "Omits frame pointer. (x86 only)"
};

const char* VCBAT_CL_OPTIONS_DESCRIPTION_CODE_GENERATION[] = {
    "Minimum CPU architecture requirements.",
    "Produces an output file to run on the common language runtime.",
    "Turn off implicit emission of System::GC::KeepAlive(this).",
    "Enable initial AppDomain behavior of Visual C++ 2002.",
    "Produce assemblies targeting .NET Core runtime.",
    "Don't produce an assembly.",
    "Don't import any required assemblies implicitly.",
    "Ignore the system .NET framework directory when searching for assemblies.",
    "Produce an IL-only output file (no native executable code).",
    "Produce an IL-only verifiable output file.",
    "Enable C++ exception handling (with SEH exceptions).",
    "extern \"C\" defaults to nothrow.",
    "Always generate noexcept runtime termination checks.",
    "Enable C++ exception handling (no SEH exceptions).",
    "Enable architecture features.17.10",
    "Consider floating-point contractions when generating code.",
    "Consider floating-point exceptions when generating code.",
    "\"fast\" floating-point model; results are less predictable.",
    "\"precise\" floating-point model; results are predictable.",
    "\"strict\" floating-point model (implies /fp:except).",
    "Backward-compatible floating-point to unsigned integer conversions.",
    "Intel native floating-point to unsigned integer conversion behavior.",
    "Enables compilation of sanitizer instrumentation such as AddressSanitizer.",
    "Enables compilation of code coverage instrumentation for libraries such as LibFuzzer.",
    "Optimizes for Windows applications.",
    "Uses the __cdecl calling convention. (x86 only)",
    "Deprecated. Activates stack probes.",
    "Enables string pooling.",
    "Calls hook function _penter.",
    "Calls hook function _pexit.",
    "Enables whole program optimization.",
    "Deprecated. Enables minimal rebuild.",
    "Uses the __fastcall calling convention. (x86 only)",
    "Enables run-time type information (RTTI).",
    "Checks buffer security.",
    "Controls stack probes.",
    "Supports fiber safety for data allocated by using static thread-local storage.",
    "Ensure distinct functions have distinct addresses.",
    "Adds control flow guard security checks.",
    "Enables EH continuation metadata.",
    "Uses the __vectorcall calling convention. (x86 and x64 only)",
    "Enables whole-program global data optimization.",
    "Deprecated. Enables synchronous exception handling. Use /EH instead.",
    "Enables function-level linking.",
    "Uses the __stdcall calling convention. (x86 only)",
    "Deprecated. Enables fast checks. (Same as /RTC1)",
    "Forces parameters passed in registers to be written to their locations on the stack upon function entry. This compiler option is only for the x64 compilers (native and cross compile).",
    "Creates a hotpatchable image.",
    "Put switch case statement jump tables in the .rdata section.",
    "Generates fast transcendentals.",
    "Deprecated. Suppresses the call of the helper function _ftol when a conversion from a floating-point type to an integral type is required. (x86 only)",
    "Removes fwait commands inside try blocks.",
    "Mitigates the performance impact of the Intel JCC erratum microcode update.",
    "Enables automatic parallelization of loops.",
    "Enables reporting levels for automatic parallelization.",
    "Uses integer move instructions for floating-point values and disables certain floating point load optimizations.",
    "Enable mitigations for CVE 2017-5753, for a class of Spectre attacks.",
    "Generate serializing instructions for every load instruction.",
    "Generate serializing instructions for every control flow instruction that loads memory.",
    "Enables reporting levels for automatic vectorization.",
    "Enable fast runtime checks (equivalent to /RTCsu).",
    "Convert to smaller type checks at run-time.",
    "Enable stack frame runtime checks.",
    "Enables uninitialized local usage checks.",
    "Acquire/release semantics not guaranteed on volatile accesses.",
    "Acquire/release semantics guaranteed on volatile accesses."
};

const char* VCBAT_CL_OPTIONS_DESCRIPTION_OUTPUT_FILES[] = {
    "Processes documentation comments to an XML file.",
    "Configures an assembly listing file.",
    "Creates an assembly listing file.",
    "Renames program database file.",
    "Renames the executable file.",
    "Specifies the preprocessed output file name.",
    "Creates a mapfile.",
    "Creates an object file.",
    "Specifies a precompiled header file name.",
    "Name generated .sbr browser files. /Fr is deprecated.",
    "Location of the header files generated for #import."
};

const char* VCBAT_CL_OPTIONS_DESCRIPTION_PREPROCESSOR[] = {
    "Specifies a directory to search to resolve file references passed to the #using directive.",
    "Preserves comments during preprocessing.",
    "Defines constants and macros.",
    "Copies preprocessor output to standard output.",
    "Copies preprocessor output to standard output.",
    "Preprocesses the specified include file.",
    "Forces the use of a file name, as if it had been passed to the #using directive.",
    "Merges injected code with the source file.",
    "Searches a directory for include files.",
    "Writes preprocessor output to a file.",
    "Print all macro definitions.",
    "Generate #pragma file_hash when preprocessing.",
    "Removes a predefined macro.",
    "Removes all predefined macros.",
    "Ignores the standard include directory."
};

const char* VCBAT_CL_OPTIONS_DESCRIPTION_HEADER_MODULES[] = {
    "Create the header units files (.ifc) specified by the input arguments.",
    "Specify where to find the header unit file (.ifc) for the specified header.",
    "Build a header unit from the specified header.",
    "Specify the output file name or directory for built .ifc files.",
    "Treat the input file as a module interface unit.",
    "Treat the input file as an internal partition unit.",
    "Use named module IFC.",
    "List module and header unit dependencies in C++ Standard JSON form.",
    "List all source-level dependencies.",
    "List module and header unit dependencies.",
    "Treat #include as import."
};

const char* VCBAT_CL_OPTIONS_DESCRIPTION_LANGUAGE[] = {
    "Enable coroutines (resumable functions) extensions.",
    "Enable standard C++20 coroutine support with earlier language versions.",
    "Show N constexpr evaluations in diagnostics (default: 10).",
    "Recursion depth limit for constexpr evaluation (default: 512).",
    "Terminate constexpr evaluation after N steps (default: 100000)",
    "Enables #pragma omp in source code.",
    "Enable OpenMP 2.0 language extensions plus select OpenMP 3.0+ language extensions.",
    "OpenMP language extensions using LLVM runtime.",
    "Set standard-conformance mode.",
    "C++14 standard ISO/IEC 14882:2014 (default).",
    "C++17 standard ISO/IEC 14882:2017.",
    "C++20 standard ISO/IEC 14882:2020.",
    "The latest draft C++ standard preview features.",
    "C11 standard ISO/IEC 9899:2011.",
    "C17 standard ISO/IEC 9899:2018.",
    "The latest draft C standard preview features.",
    "Suppresses or enables hidden vtordisp class members.",
    "Uses best base for pointers to members.",
    "Uses full generality for pointers to members.",
    "Declares multiple inheritance.",
    "Declares single inheritance.",
    "Declares virtual inheritance.",
    "Generates C 7.0-compatible debugging information.",
    "Disables some C89 language extensions in C code.",
    "Enable the __cplusplus macro to report the supported standard (off by default).",
    "Enable the __STDC__ macro to report the C standard is supported (off by default).",
    "Enable C++17 over-aligned dynamic allocation (on by default in C++17).",
    "Enforce the new Standard C++ meaning for auto (on by default).",
    "Enable or disable C++20 native u8 literal support as const char8_t (off by default, except under /std:c++20).",
    "Enable Standard C++ rules for inferred enum base types (Off b y default, not implied by /permissive-).",
    "Enforce Standard C++ rules for extern \"C\" functions (implied by /permissive-).",
    "Enable external linkage for constexpr variables (off by default).",
    "Enforce Standard C++ for scoping rules (on by default).",
    "Enforce Standard C++ goto rules around local variable initialization (implied by /permissive-).",
    "Enforce Standard C++ hidden friend rules (implied by /permissive-)",
    "Enable implicit noexcept on required functions (on by default).",
    "Remove unreferenced functions or data if they're COMDAT or have internal linkage only (off by default).",
    "Enable new lambda processor for conformance-mode syntactic checks in generic lambdas.",
    "Enforce C++17 noexcept rules (on by default in C++17 or later).",
    "Enable optional copy and move elisions (on by default under /O2, /permissive-, or /std:c++20 or later).",
    "Use the new conforming preprocessor (off by default, except in C11/C17).",
    "A UDT temporary won't bind to a non-const lvalue reference (off by default).",
    "Enforce Standard C++ explicit type conversion rules (off by default).",
    "Enable C++14 global sized deallocation functions (on by default).",
    "Disable string-literal to char* or wchar_t* conversion (off by default).",
    "Enforce Standard C++ template parameter shadowing rules (off by default).",
    "Enforce conditional operator rules on operand types (off by default).",
    "Enable thread-safe local static initialization (on by default).",
    "Assume operator new throws on failure (off by default).",
    "Generate runtime checks for TLS variable initialization (on by default).",
    "Enable trigraphs (obsolete, off by default).",
    "Use nonconforming template parsing behavior (conforming by default).",
    "wchar_t is a native type, not a typedef (on by default).",
    "Call member new/delete for 0-size arrays of objects (on by default).",
    "Deprecated. Enables C89 language extensions.",
    "Improves PDB generation time in parallel builds.",
    "Specifies MD5, SHA-1, or SHA-256 for checksums in debug info.",
    "Includes debug information in a program database compatible with Edit and Continue. (x86 only)",
    "Generates complete debugging information.",
    "Removes the default library name from the .obj file.",
    "Generate richer debugging information for optimized code.",
    "Packs structure members.",
    "Checks syntax only.",
    "Produces an output file to run on the Windows Runtime."
};


const char* VCBAT_CL_OPTIONS_DESCRIPTION_LINKING[] = {
    "Sets stack size.",
    "Creates a dynamic-link library.",
    "Creates a debug dynamic-link library.",
    "Passes the specified option to LINK.",
    "Creates an MSIL .netmodule.",
    "Compiles to create a multithreaded DLL, by using MSVCRT.lib.",
    "Compiles to create a debug multithreaded DLL, by using MSVCRTD.lib.",
    "Compiles to create a multithreaded executable file, by using LIBCMT.lib.",
    "Compiles to create a debug multithreaded executable file, by using LIBCMTD.lib."
};

const char* VCBAT_CL_OPTIONS_DESCRIPTION_MISCELLANEOUS[] = {
    "Lists the compiler options.",
    "Specifies a response file.",
    "Enables code analysis.",
    "Increases the number of addressable sections in an .obj file.",
    "Compiles without linking.",
    "Specifies number of cl.exe threads to use for optimization and code generation.",
    "Deprecated. Windows Error Reporting (WER) settings control error reporting.",
    "Set execution character set.",
    "Enable fast-fail mode.",
    "Displays the full path of source code files passed to cl.exe in diagnostic text.",
    "Forces writes to the PDB file to be serialized through MSPDBSRV.EXE.",
    "Deprecated. Restricts the length of external (public) names.",
    "Lists the compiler options.",
    "Changes the default char type.",
    "Supports native C++ Just My Code debugging.",
    "The compiler and linker create a binary that can be executed in the Windows kernel.",
    "Builds multiple source files concurrently.",
    "Suppresses display of sign-on banner.",
    "Zero initialize padding for stack based class types.",
    "Displays a list of all include files during compilation.",
    "Set source character set.",
    "Specifies a C source file.",
    "Specifies all source files are C.",
    "Specifies a C++ source file.",
    "Specifies all source files are C++.",
    "Set source and execution character sets to UTF-8.",
    "Deprecated. Sets the version string.",
    "Validate UTF-8 files for only compatible characters.",
    "Generate metadata on volatile memory accesses.",
    "Create .PCH file.",
    "Deprecated. Places complete debugging information in all object files. Use /Zi instead.",
    "Injects a PCH reference when creating a debug library.",
    "Uses a precompiled header file during build.",
    "Ignores all other precompiled-header compiler options in the current build.",
    "Specifies the precompiled header memory allocation limit."
};

const char* VCBAT_CL_OPTIONS_DESCRIPTION_DIAGNOSTICS[] = {
    "Diagnostics format: prints column and the indicated line of source.",
    "Use legacy diagnostics format.",
    "Diagnostics format: prints column information.",
    "Treat all headers included via <> as external.",
    "Specify an environment variable with locations of external headers.",
    "Specify location of external headers.",
    "Evaluate warning level across template instantiation chain.",
    "Set warning level for external headers.",
    "Unrecognized compiler options are errors.",
    "Enable more security features and warnings.",
    "Disable all warnings.",
    "Set output warning level.",
    "Set warning level for the specified warning.",
    "Enable all warnings, including warnings that are disabled by default.",
    "Disable the specified warning.",
    "Treat the specified warning as an error.",
    "Enable one-line diagnostics for error and warning messages when compiling C++ source code from the command line.",
    "Display the specified warning only once.",
    "Disable warnings introduced after the specified version of the compiler.",
    "Treat warnings as errors."
};

const char* VCBAT_CL_OPTIONS_DESCRIPTION_EXPERIMENTAL[] = {
    "Enables experimental structured SARIF output.",
    "Enables experimental module support."
};

const char* VCBAT_CL_OPTIONS_DESCRIPTION_DEPRECATED[] = {
    "Deprecated. Use /LN (Create MSIL Module) instead.",
    "Deprecated. Error reporting is controlled by Windows Error Reporting (WER) settings.",
    "Deprecated. Enables experimental conforming preprocessor support. Use /Zc:preprocessor",
    "Deprecated. Creates a browse information file without local variables.",
    "Deprecated. Activates stack probes. On by default.",
    "Deprecated. Enables minimal rebuild.",
    "Deprecated. Enables synchronous exception handling. Use /EH instead.",
    "Deprecated. Enables fast checks. Use /RTC1 instead.",
    "Deprecated. Restricts the length of external (public) names.",
    "Deprecated. Uses global optimizations.",
    "Deprecated. Once used to specify how to convert from a floating-point type to an integral type.",
    "Deprecated. Sets the .obj file version string.",
    "Obsolete. Detects 64-bit portability problems.",
    "Deprecated. Places complete debugging information in all object files. Use /Zi instead.",
    "Deprecated. Disables conformance in for loop scope.",
    "Deprecated. Enables language extensions.",
    "Removed in Visual Studio 2015. Generates function prototypes."
};


const char *const * VCBAT_CL_OPTIONS_DESCRIPTION_TABLE[] {
    VCBAT_CL_OPTIONS_DESCRIPTION_OPTIMIZATION,
    VCBAT_CL_OPTIONS_DESCRIPTION_CODE_GENERATION,
    VCBAT_CL_OPTIONS_DESCRIPTION_OUTPUT_FILES,
    VCBAT_CL_OPTIONS_DESCRIPTION_PREPROCESSOR,
    VCBAT_CL_OPTIONS_DESCRIPTION_HEADER_MODULES,
    VCBAT_CL_OPTIONS_DESCRIPTION_LANGUAGE,
    VCBAT_CL_OPTIONS_DESCRIPTION_LINKING,
    VCBAT_CL_OPTIONS_DESCRIPTION_MISCELLANEOUS,
    VCBAT_CL_OPTIONS_DESCRIPTION_DIAGNOSTICS,
    VCBAT_CL_OPTIONS_DESCRIPTION_EXPERIMENTAL,
    VCBAT_CL_OPTIONS_DESCRIPTION_DEPRECATED
};

struct VcBatClOption {
    union {

        struct {
            u8 flag;
            u8 category;
        };
    
        VcBatClOptions key;
    };
};

inline VcBatClOption
vcbat_cl_option(
    const VcBatClOptions option_flag) {

    VcBatClOption option = {0};

    option.key = option_flag;

    return(option);
}

inline const char*
vcbat_cl_option_flag(
    const VcBatClOption option) {

    auto flag_category = VCBAT_CL_OPTIONS_FLAG_TABLE[option.category];
    auto option_flag   = flag_category[option.flag]; 

    return(option_flag);

}

inline const char*
vcbat_cl_option_description(
    const VcBatClOption option) {

    auto description_category = VCBAT_CL_OPTIONS_DESCRIPTION_TABLE[option.category];
    auto option_description   = description_category[option.flag]; 

    return(option_description);
}

struct VCBatClOptionStrings {
    const char* flag;
    const char* description;
};

inline VCBatClOptionStrings
vcbat_cl_option_strings(
    const VcBatClOption option) {

    VCBatClOptionStrings strings;
    strings.flag        = vcbat_cl_option_description(option);
    strings.description = vcbat_cl_option_flag(option);

    return(strings);

}

#endif //VCBAT_CL_OPTIONS_HPP