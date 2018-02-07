=======================================
Clang 6.0.0 (In-Progress) Release Notes
=======================================

.. contents::
   :local:
   :depth: 2

Written by the `LLVM Team <http://llvm.org/>`_

.. warning::

   These are in-progress notes for the upcoming Clang 6 release.
   Release notes for previous releases can be found on
   `the Download Page <http://releases.llvm.org/download.html>`_.

Introduction
============

This document contains the release notes for the Clang C/C++/Objective-C
frontend, part of the LLVM Compiler Infrastructure, release 6.0.0. Here we
describe the status of Clang in some detail, including major
improvements from the previous release and new feature work. For the
general LLVM release notes, see `the LLVM
documentation <http://llvm.org/docs/ReleaseNotes.html>`_. All LLVM
releases may be downloaded from the `LLVM releases web
site <http://llvm.org/releases/>`_.

For more information about Clang or LLVM, including information about the
latest release, please see the `Clang Web Site <http://clang.llvm.org>`_ or the
`LLVM Web Site <http://llvm.org>`_.

Note that if you are reading this file from a Subversion checkout or the
main Clang web page, this document applies to the *next* release, not
the current one. To see the release notes for a specific release, please
see the `releases page <http://llvm.org/releases/>`_.

What's New in Clang 6.0.0?
==========================

Some of the major new features and improvements to Clang are listed
here. Generic improvements to Clang as a whole or to its underlying
infrastructure are described first, followed by language-specific
sections with improvements to Clang's support for those languages.

Major New Features
------------------

-  ...

Improvements to Clang's diagnostics
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- ``-Wpragma-pack`` is a new warning that warns in the following cases:

  - When a translation unit is missing terminating ``#pragma pack (pop)``
    directives.

  - When leaving an included file that changes the current alignment value,
    i.e. when the alignment before ``#include`` is different to the alignment
    after ``#include``.

  - ``-Wpragma-pack-suspicious-include`` (disabled by default) warns on an
    ``#include`` when the included file contains structures or unions affected by
    a non-default alignment that has been specified using a ``#pragma pack``
    directive prior to the ``#include``.

- ``-Wobjc-messaging-id`` is a new, non-default warning that warns about
  message sends to unqualified ``id`` in Objective-C. This warning is useful
  for projects that would like to avoid any potential future compiler
  errors/warnings, as the system frameworks might add a method with the same
  selector which could make the message send to ``id`` ambiguous.

- ``-Wtautological-compare`` now warns when comparing an unsigned integer and 0
  regardless of whether the constant is signed or unsigned."

- ``-Wtautological-compare`` now warns about comparing a signed integer and 0
  when the signed integer is coerced to an unsigned type for the comparison.
  ``-Wsign-compare`` was adjusted not to warn in this case.

- ``-Wtautological-constant-compare`` is a new warning that warns on
  tautological comparisons between integer variable of the type ``T`` and the
  largest/smallest possible integer constant of that same type.

- For C code, ``-Wsign-compare``, ``-Wsign-conversion``,
  ``-Wtautological-constant-compare`` and
  ``-Wtautological-constant-out-of-range-compare`` were adjusted to use the
  underlying datatype of ``enum``.

- ``-Wnull-pointer-arithmetic`` now warns about performing pointer arithmetic
  on a null pointer. Such pointer arithmetic has an undefined behavior if the
  offset is nonzero. It also now warns about arithmetic on a null pointer
  treated as a cast from integer to pointer (GNU extension).

- ``-Wzero-as-null-pointer-constant`` was adjusted not to warn on null pointer
  constants that originate from system macros, except ``NULL`` macro.

Non-comprehensive list of changes in this release
-------------------------------------------------

- Bitrig OS was merged back into OpenBSD, so Bitrig support has been
  removed from Clang/LLVM.

- The default value of _MSC_VER was raised from 1800 to 1911, making it
  compatible with the Visual Studio 2015 and 2017 C++ standard library headers.
  Users should generally expect this to be regularly raised to match the most
  recently released version of the Visual C++ compiler.

- clang now defaults to ``.init_array`` if no gcc installation can be found.
  If a gcc installation is found, it still prefers ``.ctors`` if the found
  gcc is older than 4.7.0.

- The new builtin preprocessor macros ``__is_target_arch``,
  ``__is_target_vendor``, ``__is_target_os``, and ``__is_target_environment``
  can be used to to examine the individual components of the target triple.

New Compiler Flags
------------------

- --autocomplete was implemented to obtain a list of flags and its arguments. This is used for shell autocompletion.

- The ``-fdouble-square-bracket-attributes`` and corresponding
  ``-fno-double-square-bracket-attributes`` flags were added to enable or
  disable [[]] attributes in any language mode. Currently, only a limited
  number of attributes are supported outside of C++ mode. See the Clang
  attribute documentation for more information about which attributes are
  supported for each syntax.
  
- Added the ``-std=c17``, ``-std=gnu17``, and ``-std=iso9899:2017`` language
  mode flags for compatibility with GCC. This enables support for the next
  version of the C standard, expected to be published by ISO in 2018. The only
  difference between the ``-std=c17`` and ``-std=c11`` language modes is the
  value of the ``__STDC_VERSION__`` macro, as C17 is a bug fix release.

- Added the ``-fexperimental-isel`` and ``-fno-experimental-isel`` flags to
  enable/disable the new GlobalISel instruction selection framework. This
  feature is enabled by default for AArch64 at the ``-O0`` optimization level.
  Support for other targets or optimization levels is currently incomplete.

Deprecated Compiler Flags
-------------------------

The following options are deprecated and ignored. They will be removed in
future versions of Clang.

- ...

New Pragmas in Clang
-----------------------

Clang now supports the ...


Attribute Changes in Clang
--------------------------

- Clang now supports the majority of its attributes under both the GNU-style
  spelling (``__attribute((name))``) and the double square-bracket spelling
  in the ``clang`` vendor namespace (``[[clang::name]]``). Attributes whose
  syntax is specified by some other standard (such as CUDA and OpenCL
  attributes) continue to follow their respective specification.
  
- Added the ``__has_c_attribute()`` builtin preprocessor macro which allows
  users to dynamically detect whether a double square-bracket attribute is
  supported in C mode. This attribute syntax can be enabled with the
  ``-fdouble-square-bracket-attributes`` flag.
  
- The presence of __attribute__((availability(...))) on a declaration no longer
  implies default visibility for that declaration on macOS.

- Clang now supports configuration files. These are collections of driver
  options, which can be applied by specifying the configuration file, either
  using command line option `--config foo.cfg` or encoding it into executable
  name `foo-clang`. Clang behaves as if the options from this file were inserted
  before the options specified in command line. This feature is primary intended
  to facilitate cross compilation. Details can be found in
  `Clang Compiler User's Manual
  <http://clang.llvm.org/docs/UsersManual.html#configuration-files>`.

- ...

Windows Support
---------------

- Clang now has initial, preliminary support for targeting Windows on
  ARM64.

C Language Changes in Clang
---------------------------

- ...

...

C11 Feature Support
^^^^^^^^^^^^^^^^^^^

...

C++ Language Changes in Clang
-----------------------------

- Clang's default C++ dialect is now ``gnu++14`` instead of ``gnu++98``. This
  means Clang will by default accept code using features from C++14 and
  conforming GNU extensions. Projects incompatible with C++14 can add
  ``-std=gnu++98`` to their build settings to restore the previous behaviour.

C++1z Feature Support
^^^^^^^^^^^^^^^^^^^^^

...

Objective-C Language Changes in Clang
-------------------------------------

...

OpenCL C Language Changes in Clang
----------------------------------


- Added subgroup builtins to enqueue kernel support.

- Added CL2.0 atomics as Clang builtins that now accept
  an additional memory scope parameter propagated to atomic IR instructions
  (this is to align with the corresponding change in LLVM IR) (see `spec s6.13.11.4
  <https://www.khronos.org/registry/OpenCL/specs/opencl-2.0-openclc.pdf#107>`_).

- Miscellaneous fixes in the CL header.

- Allow per target selection of address space during CodeGen of certain OpenCL types.
  Default target implementation is provided mimicking old behavior.

- Macro ``__IMAGE_SUPPORT__`` is now automatically added (as per `spec s6.10
  <https://www.khronos.org/registry/OpenCL/specs/opencl-2.0-openclc.pdf#55>`_).

- Added ``cl_intel_subgroups`` and ``cl_intel_subgroups_short`` extensions.

- All function calls are marked by `the convergent attribute
  <https://clang.llvm.org/docs/AttributeReference.html#convergent-clang-convergent>`_
  to prevent optimizations that break SPMD program semantics. This will be removed
  by LLVM passes if it can be proved that the function does not use convergent
  operations.

- Create a kernel wrapper for enqueued blocks, which simplifies enqueue support by
  providing common functionality.

- Added private address space explicitly in AST and refactored address space support
  with several simplifications and bug fixes (`PR33419 <https://llvm.org/pr33419>`_
  and `PR33420 <https://llvm.org/pr33420>`_).

- OpenCL now allows functions with empty parameters to be treated as if they had a
  void parameter list (inspired from C++ support). OpenCL C spec update to follow.

- General miscellaneous refactoring and cleanup of blocks support for OpenCL to
  remove unused parts inherited from Objective C implementation.

- Miscellaneous improvements in vector diagnostics.

- Added half float load and store builtins without enabling half as a legal type
  (``__builtin_store_half for double``, ``__builtin_store_halff`` for double,
  ``__builtin_load_half for double``, ``__builtin_load_halff`` for float).


OpenMP Support in Clang
----------------------------------

- Added options `-f[no]-openmp-simd` that support code emission only for OpenMP
  SIMD-based directives, like `#pragma omp simd`, `#pragma omp parallel for simd`
  etc. The code is emitted only for simd-based part of the combined directives
  and clauses.

- Added support for almost all target-based directives except for
  `#pragma omp target teams distribute parallel for [simd]`. Although, please
  note that `depend` clauses on target-based directives are not supported yet.
  Clang supports offloading to X86_64, AArch64 and PPC64[LE] devices.

- Added support for `reduction`-based clauses on `task`-based directives from
  upcoming OpenMP 5.0.

- The LLVM OpenMP runtime `libomp` now supports the OpenMP Tools Interface (OMPT)
  on x86, x86_64, AArch64, and PPC64 on Linux, Windows, and macOS. If you observe
  a measurable performance impact on one of your applications without a tool
  attached, please rebuild the runtime library with `-DLIBOMP_OMPT_SUPPORT=OFF` and
  file a bug at `LLVM's Bugzilla <https://bugs.llvm.org/>`_ or send a message to the
  `OpenMP development list <http://lists.llvm.org/cgi-bin/mailman/listinfo/openmp-dev>`_.

Internal API Changes
--------------------

These are major API changes that have happened since the 4.0.0 release of
Clang. If upgrading an external codebase that uses Clang as a library,
this section should help get you past the largest hurdles of upgrading.

-  ...

AST Matchers
------------

The hasDeclaration matcher now works the same for Type and QualType and only
ever looks through one level of sugaring in a limited number of cases.

There are two main patterns affected by this:

-  qualType(hasDeclaration(recordDecl(...))): previously, we would look through
   sugar like TypedefType to get at the underlying recordDecl; now, we need
   to explicitly remove the sugaring:
   qualType(hasUnqualifiedDesugaredType(hasDeclaration(recordDecl(...))))

-  hasType(recordDecl(...)): hasType internally uses hasDeclaration; previously,
   this matcher used to match for example TypedefTypes of the RecordType, but
   after the change they don't; to fix, use:

::
   hasType(hasUnqualifiedDesugaredType(
       recordType(hasDeclaration(recordDecl(...)))))

-  templateSpecializationType(hasDeclaration(classTemplateDecl(...))):
   previously, we would directly match the underlying ClassTemplateDecl;
   now, we can explicitly match the ClassTemplateSpecializationDecl, but that
   requires to explicitly get the ClassTemplateDecl:

::
   templateSpecializationType(hasDeclaration(
       classTemplateSpecializationDecl(
           hasSpecializedTemplate(classTemplateDecl(...)))))

clang-format
------------

* Option *IndentPPDirectives* added to indent preprocessor directives on
  conditionals.

  +----------------------+----------------------+
  | Before               | After                |
  +======================+======================+
  |  .. code-block:: c++ | .. code-block:: c++  |
  |                      |                      |
  |    #if FOO           |   #if FOO            |
  |    #if BAR           |   #  if BAR          |
  |    #include <foo>    |   #    include <foo> |
  |    #endif            |   #  endif           |
  |    #endif            |   #endif             |
  +----------------------+----------------------+

* Option -verbose added to the command line.
  Shows the list of processed files.

* Option *IncludeBlocks* added to merge and regroup multiple ``#include`` blocks during sorting.

  +-------------------------+-------------------------+-------------------------+
  | Before (Preserve)       | Merge                   | Regroup                 |
  +=========================+=========================+=========================+
  |  .. code-block:: c++    | .. code-block:: c++     | .. code-block:: c++     |
  |                         |                         |                         |
  |   #include "b.h"        |   #include "a.h"        |   #include "a.h"        |
  |                         |   #include "b.h"        |   #include "b.h"        |
  |   #include "a.b"        |   #include <lib/main.h> |                         |
  |   #include <lib/main.h> |                         |   #include <lib/main.h> |
  +-------------------------+-------------------------+-------------------------+

libclang
--------

...


Static Analyzer
---------------

- Static Analyzer can now properly detect and diagnose unary pre-/post-
  increment/decrement on an uninitialized value.

...

Undefined Behavior Sanitizer (UBSan)
------------------------------------

* A minimal runtime is now available. It is suitable for use in production
  environments, and has a small attack surface. It only provides very basic
  issue logging and deduplication, and does not support ``-fsanitize=vptr``
  checking.

Core Analysis Improvements
==========================

- ...

New Issues Found
================

- ...

Python Binding Changes
----------------------

The following methods have been added:

-  ...

Significant Known Problems
==========================

Additional Information
======================

A wide variety of additional information is available on the `Clang web
page <http://clang.llvm.org/>`_. The web page contains versions of the
API documentation which are up-to-date with the Subversion version of
the source code. You can access versions of these documents specific to
this release by going into the "``clang/docs/``" directory in the Clang
tree.

If you have any questions or comments about Clang, please feel free to
contact us via the `mailing
list <http://lists.llvm.org/mailman/listinfo/cfe-dev>`_.
